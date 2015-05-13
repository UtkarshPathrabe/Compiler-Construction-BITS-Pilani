/********************************
       |TEAM-1 | GROUP-20|
UTKARSH PATHRABE  - 2012A7PS034P
SHIKHAR VASHISHTH - 2012C6PS436P
********************************/

#include "SymbolTableDef.h"
#include "SymbolTable.h"
#include "Tree.h"
#include "AST.h"

#define GET(ast, field) (*((TokenInfo**)ast->value))->field
bool compiler_error;

/*********************************************SYMBOL TABLE FUNCTIONS*************************************************/

void initSymbolTable(ST *st, Tree ast){
	ST_create(st);
	ST_procRecScan(st, ast);

	Tree exec = ast->child;
	while(exec->sym != EXECUTE) exec = exec->next;

	ST_varScan(st, exec);
	ST_setScope(st, ast);
}

void ST_setScope(ST *st, Tree ast){
	if (ast == NULL) return;
	ast->scope = st;

	Tree p = ast->child;
	while(p != NULL){
		if(p->sym == LOOP || p->sym ==  PROC)
			ST_setScope(p->scope, p);
		else if (p->sym == IF);
		else ST_setScope(st, p);
		p = p->next;
	}
}

void ST_create(ST *st){
	int i;
	for(i=0; i<SIZE; i++) st->entry[i] = NULL;
	st->next = st->parent = st->child = st->prev = NULL;
	st->parent = NULL;
	st->id = 1;
}

int ST_hash(char *str){
	int sum=0, i;
	for(i=0; i<strlen(str); i++)
		sum += str[i]*(i+1);
	return sum % SIZE;
}

int ST_genKey(ST *st, char *var){
	int key = ST_hash(var);
	while(st->entry[key] != NULL) 
		key = (key+1)%SIZE;
	return key;
}

int ST_getDeclId(ST *st, char *name){
	int key;
	ST *scope = ST_getinfo(st, name, &key);
	if(key == -1) return -1;
	return scope->id;
}

int ST_getRecAttr(ST *st, char *recname, char *compname, Type *type){
	int key, index = 0;
	pri_var *pri;
	rec_var *rec = ST_getinfo(st, recname, &key)->entry[key];
	rec_dec *recd = ST_getinfo(st, rec->type_name, &key)->entry[key];
	LL_Node *p = recd->varList;
	while(p != NULL){
		pri = p->value;
		if(!strcmp(compname, pri->name)){
			*type = pri->type;
			return index;
		}
		p = p->next;
		index++;
	}
	return -1;
}

ST* ST_addChild(ST *st){
	int i;
	if(st->child == NULL){
		st->child = malloc(sizeof(ST));
		for(i=0; i<SIZE; i++) st->child->entry[i] = NULL;
		st->child->parent = st;
		st->child->child = st->child->next = st->child->prev = NULL;
		st->child->id = st->id*100 + 1;
		return st->child;
	}
	ST *p = st->child;

	while(p->next != NULL)
		p = p->next;

	p->next = malloc(sizeof(ST));
	for(i=0; i<SIZE; i++) p->next->entry[i] = NULL;
	p->next->parent = st;
	p->next->prev = p;
	p->next->child = p->next->next = NULL;
	p->next->id = p->id + 1;
	return p->next;
}


Type getType(char *str){
	if(!strcmp(str, "int")) return INT_TYPE;
	if(!strcmp(str, "bool")) return BOOL_TYPE;
	if(!strcmp(str, "real")) return REAL_TYPE;
	if(!strcmp(str, "char")) return CHAR_TYPE;
}

ST* ST_getinfo(ST *st, char *name, int *key_ret){
	int key;
	ST* p = st;
	while( p != NULL){
		key = ST_search(p, name);
		if(key == -1) p = p->parent;
		else break;
	}

	if(key == -1){
		*key_ret = -1;
		return NULL;
	}
	*key_ret = key;
	if( p == NULL) return st;
	else return p;
}

int ST_search(ST *st, char *name){
	int i, key = ST_hash(name);
	pri_var *pri_temp;
	str_var *str_temp;
	mat_var *mat_temp;
	rec_dec *recdec_temp;
	rec_var *rec_temp;
	proc_dec *proc_temp;

	while(st->entry[key] != NULL){
		switch(st->type[key]){
			case INT_TYPE: case CHAR_TYPE: case BOOL_TYPE: case REAL_TYPE:
				pri_temp = (pri_var*)st->entry[key];
				if(!strcmp(pri_temp->name, name)) return key;
				break;
			case MAT_TYPE:
				mat_temp = (mat_var*)st->entry[key];
				if(!strcmp(mat_temp->name, name)) return key;
				break;
			case STR_TYPE:
				str_temp = (str_var*)st->entry[key];
				if(!strcmp(str_temp->name, name)) return key;
				break;
			case PROC_TYPE: 
				proc_temp = (proc_dec*)st->entry[key];
				if(!strcmp(proc_temp->name, name)) return key;
				break;
			case RECDEC_TYPE:
				recdec_temp = (rec_dec*)st->entry[key];
				if(!strcmp(recdec_temp->name, name)) return key;
				break;
			case REC_TYPE:
				rec_temp = (rec_var*)st->entry[key];
				if(!strcmp(rec_temp->name, name)) return key;
				break;
		}
		key = (key+1)%SIZE;
	}
	return -1;
}
/***********************************************GLOBAL VARIABLE ENTRY************************************************/
void ST_makeEntry(ST *st, Tree ast){

	TreeNode *node_type   = ast->child;
	TreeNode *node_idlist = ast->child->next;

	LL_Node *list = (LL_Node*)(node_idlist->value);
	LL_Node *p = list;
	int key;

	pri_var* pri_temp;
	mat_var* mat_temp;
	str_var* str_temp;
	rec_var* rec_temp;

	switch(node_type->sym){
		case INT:
			while(p!=NULL){
				pri_temp = malloc(sizeof(pri_var));
				pri_temp->name = (*(TokenInfo**)p->value)->lexeme;

				if(ST_search(st, pri_temp->name) != -1){
					printf("error: '%s' is redefined on lineno: %d\n", pri_temp->name, (*(TokenInfo**)p->value)->lineno);
					compiler_error = true;
					p = p->next;
					continue;
				}

				key = ST_genKey(st, pri_temp->name);
				pri_temp->offset = key;
				pri_temp->decl_line = (*(TokenInfo**)p->value)->lineno;
				pri_temp->value = NULL;

				st->entry[key] = pri_temp;
				st->type[key] = INT_TYPE;
				p = p->next;
			}
			break;
		case REAL:
			while(p!=NULL){
				pri_temp = malloc(sizeof(pri_var));
				pri_temp->name = (*(TokenInfo**)p->value)->lexeme;

				if(ST_search(st, pri_temp->name) != -1){
					printf("error: '%s' is redefined on lineno: %d \n", pri_temp->name, (*(TokenInfo**)p->value)->lineno);
					compiler_error = true;
					p = p->next;
					continue;
				}

				key = ST_genKey(st, pri_temp->name);
				pri_temp->offset = key;
				pri_temp->decl_line = (*(TokenInfo**)p->value)->lineno;
				pri_temp->value = NULL;

				st->entry[key] = pri_temp;
				st->type[key] = REAL_TYPE;

				p = p->next;
			}
			break;
		case BOOL:
			while(p!=NULL){
				pri_temp = malloc(sizeof(pri_var));
				pri_temp->name = (*(TokenInfo**)p->value)->lexeme;

				if(ST_search(st, pri_temp->name) != -1){
					printf("error: '%s' is redefined on lineno: %d \n", pri_temp->name, (*(TokenInfo**)p->value)->lineno);
					compiler_error = true;
					p = p->next;
					continue;
				}

				key = ST_genKey(st, pri_temp->name);
				pri_temp->offset = key;
				pri_temp->decl_line = (*(TokenInfo**)p->value)->lineno;
				pri_temp->value = NULL;

				st->entry[key] = pri_temp;
				st->type[key] = BOOL_TYPE;

				p = p->next;
			}
			break;
		case CHAR:
			while(p!=NULL){
				pri_temp = malloc(sizeof(pri_var));
				pri_temp->name = (*(TokenInfo**)p->value)->lexeme;

				if(ST_search(st, pri_temp->name) != -1){
					printf("error: '%s' is redefined on lineno: %d \n", pri_temp->name, (*(TokenInfo**)p->value)->lineno);
					compiler_error = true;
					p = p->next;
					continue;
				}

				key = ST_genKey(st, pri_temp->name);
				pri_temp->offset = key;
				pri_temp->decl_line = (*(TokenInfo**)p->value)->lineno;
				pri_temp->value = NULL;

				st->entry[key] = pri_temp;
				st->type[key] = CHAR_TYPE;

				p = p->next;
			}
			break;
		case MAT:
			while(p!=NULL){
				mat_temp = malloc(sizeof(mat_var));
				mat_temp->name = (*(TokenInfo**)p->value)->lexeme;

				if(ST_search(st, mat_temp->name) != -1){
					printf("error: '%s' is redefined on lineno: %d \n", mat_temp->name, (*(TokenInfo**)p->value)->lineno);
					compiler_error = true;
					p = p->next;
					continue;
				}

				key = ST_genKey(st, mat_temp->name);
				mat_temp->rows =  ((matTypeIDInfo*)(node_type->value))->rows;
				mat_temp->cols =  ((matTypeIDInfo*)(node_type->value))->cols;

				if(mat_temp->cols == 0) {
					mat_temp->cols = mat_temp->rows;
					mat_temp->rows = 1;
				}

				mat_temp->type = getType(((matTypeIDInfo*)(node_type->value))->type);
				mat_temp->offset = key;
				mat_temp->decl_line = (*(TokenInfo**)p->value)->lineno;
				mat_temp->value = NULL;

				st->entry[key] = mat_temp;
				st->type[key] = MAT_TYPE;
				p = p->next;
			}
			break;
		case STRING:
			while(p!=NULL){
				str_temp = malloc(sizeof(str_var));
				str_temp->name = (*(TokenInfo**)p->value)->lexeme;

				if(ST_search(st, str_temp->name) != -1){
					printf("error: '%s' is redefined on lineno: %d \n", str_temp->name, (*(TokenInfo**)p->value)->lineno);
					compiler_error = true;
					p = p->next;
					continue;
				}

				key = ST_genKey(st, str_temp->name);
				str_temp->offset = key;
				str_temp->decl_line = (*(TokenInfo**)p->value)->lineno;
				str_temp->value = NULL;
				str_temp->len = 0;

				st->entry[key] = str_temp;
				st->type[key] = STR_TYPE;
				p = p->next;
			}

			break;
		case REC:
			while(p!=NULL){
				rec_temp = malloc(sizeof(rec_var));
				rec_temp->name = (*(TokenInfo**)p->value)->lexeme;

				if(ST_search(st, rec_temp->name) != -1){
					printf("error: '%s' is redefined on lineno: %d \n", rec_temp->name, (*(TokenInfo**)p->value)->lineno);
					compiler_error = true;
					p = p->next;
					continue;
				}

				key = ST_genKey(st, rec_temp->name);
				rec_temp->offset = key;
				rec_temp->decl_line = (*(TokenInfo**)p->value)->lineno;

				ST *global = st; 
				while(global->parent != NULL) global=global->parent;

				recTypeIDInfo *rec = node_type->value;
				rec_temp->type_name = (*((TokenInfo**)rec->info))->lexeme;
				rec_temp->type_st = global;
				rec_temp->type_offset = ST_search(global, rec_temp->type_name);

				st->entry[key] = rec_temp;
				st->type[key] = REC_TYPE;

				p = p->next;
			}
			break;
	}

	/*Make entry in ast as well*/
	ast->scope = st;
	ast->offset = key;
}


void ST_varScan(ST *st, Tree ast){
	if(ast == NULL) return;

	if(ast->sym == decl_stmt){
		ST_makeEntry(st, ast);
	}

	Tree p = ast->child;
	while(p != NULL){
		if(p->sym != IF && p->sym != LOOP && p->sym != PROCS)
			ST_varScan(st, p);
		else if(p->sym == IF)
			ST_ifScan(st, p);
		else if(p->sym == LOOP)
			ST_loopScan(st, p);

		p = p->next;
	}
}

void ST_ifScan(ST *st, Tree ast){
	TreeNode *node_if = ast->child->next;
	TreeNode *node_elif;
	TreeNode *node_else;

	ast->scope = st;
	ST_setScope(st, ast->child);

	node_if->scope = ST_addChild(st);
	ST_varScan(node_if->scope, node_if);
	ST_setScope(node_if->scope, node_if);

	// printf("IF Scope: %d\n", node_if->scope->id);
	// ST_print(node_if->scope);

	/*Only if case*/
	if(node_if->next == NULL) return;
	/*Only else case*/
	if(node_if->next->next == NULL){
		node_else = ast->child->next->next;

		node_else->scope = ST_addChild(st);
		ST_varScan(node_else->scope, node_else);
		ST_setScope(node_else->scope, node_else);

		// printf("ELSE Scope: %d\n", node_else->scope->id);
		// ST_print(node_else->scope);
	}

	/*both else and elif case*/
	else{
		node_elif = ast->child->next->next;
		node_else = ast->child->next->next->next;
		node_elif->scope = ST_addChild(st);

		ST_varScan(node_elif->scope, node_elif);
		ST_setScope(node_elif->scope, node_elif);

		node_else->scope = ST_addChild(st);
		ST_varScan(node_else->scope, node_else);
		ST_setScope(node_else->scope, node_else);

		// printf("ELIF Scope: %d\n", node_elif->scope->id);
		// ST_print(node_elif->scope);

		// printf("ELSE Scope: %d\n", node_else->scope->id);
		// ST_print(node_else->scope);
	}
}

void ST_loopScan(ST *st, Tree ast){
	ast->scope = ST_addChild(st);
	ST_varScan(ast->scope, ast);

	// printf("LOOP Scope: %d\n", ast->scope->id);
	// ST_print(ast->scope);
}

/***********************************************PROCEDURE ENTRY************************************************/

void ST_makeProcEntry(ST *st, Tree ast){
	proc_dec *temp = malloc(sizeof(proc_dec));

	temp->name = GET(ast, lexeme);
	temp->decl_line = GET(ast, lineno);
	temp->inputList = NULL;
	temp->outputList = NULL;

	if(ST_search(st, temp->name) != -1){
		printf("error: procedure '%s' is redefined on lineno: %d \n", temp->name, (*(TokenInfo**)ast->value)->lineno);
		compiler_error = true;
	}


	int key = ST_genKey(st, temp->name);
	temp->offset = key;

	TreeNode* inp = ast->child;
	TreeNode* out = ast->child->next;
	LL_Node *ilist = NULL;
	LL_Node *olist = NULL;
	Token* tk;
	proc_arg* ptemp;

	while(inp != NULL){
		ptemp = malloc(sizeof(proc_arg));
		ptemp->name = (*((TokenInfo**)inp->value))->lexeme;
		switch(inp->sym){
			case INT: ptemp->type = INT_TYPE; break;
			case REAL: ptemp->type = REAL_TYPE; break;
			case BOOL: ptemp->type = BOOL_TYPE; break;
			case CHAR: ptemp->type = CHAR_TYPE; break;
		}
		ptemp->value = NULL;
		LL_insert( &ilist, ptemp);
		inp = inp->child;
	}

	while(out != NULL){
		ptemp = malloc(sizeof(proc_arg));
		ptemp->name = (*((TokenInfo**)out->value))->lexeme;
		switch(out->sym){
			case INT: ptemp->type = INT_TYPE; break;
			case REAL: ptemp->type = REAL_TYPE; break;
			case BOOL: ptemp->type = BOOL_TYPE; break;
			case CHAR: ptemp->type = CHAR_TYPE; break;
		}
		ptemp->value = NULL;
		LL_insert( &olist, ptemp);
		out = out->child;
	}

	temp->inputList = ilist;
	temp->outputList = olist;
	temp->scope = ST_addChild(st);

	LL_Node *p = ilist;
	pri_var *pri_temp;
	int proc_key;

	while(p != NULL){
		ptemp = (proc_arg*)p->value;

		if(ST_search(temp->scope, ptemp->name) != -1){
			printf("error: '%s' is redefined on lineno: %d\n", ptemp->name, temp->decl_line);
			compiler_error = true;
			p = p->next;
			continue;
		}

		proc_key = ST_genKey(temp->scope, ptemp->name);

		pri_temp = malloc(sizeof(pri_var));
		pri_temp->name = ptemp->name;
		pri_temp->type = ptemp->type;
		pri_temp->decl_line = temp->decl_line;
		pri_temp->offset = proc_key;
		pri_temp->value = NULL;

		temp->scope->entry[proc_key] = pri_temp;
		temp->scope->type[proc_key] = pri_temp->type;

		p = p->next;
	}

	p = olist;

	while(p != NULL){
		ptemp = (proc_arg*)p->value;

		if(ST_search(temp->scope, ptemp->name) != -1){
			printf("error: '%s' is redefined on lineno: %d\n", ptemp->name, temp->decl_line);
			compiler_error = true;
			p = p->next;
			continue;
		}

		proc_key = ST_genKey(temp->scope, ptemp->name);

		pri_temp = malloc(sizeof(pri_var));
		pri_temp->name = ptemp->name;
		pri_temp->type = ptemp->type;
		pri_temp->decl_line = temp->decl_line;
		pri_temp->offset = proc_key;
		pri_temp->value = NULL;

		temp->scope->entry[proc_key] = pri_temp;
		temp->scope->type[proc_key] = pri_temp->type;

		p = p->next;
	}

	ST_varScan(temp->scope, ast);
	st->entry[key] = temp;
	st->type[key] = PROC_TYPE;

	ast->scope = temp->scope;
	ast->offset = key;
	// printf("PROC SCOPE: %d\n", temp->scope->id);
	// ST_print(temp->scope);
}

/*********************************************RECORD ENTRY***************************************************/
void ST_getRecComp(Tree ast, LL_Node **list){
	if(ast == NULL) return;
	if(ast->sym == decl_stmt){

		TreeNode *node_type   = ast->child;
		TreeNode *node_idlist = ast->child->next;

		TokenInfo *varinfo = *((TokenInfo**)(((LL_Node*)node_idlist->value)->value));
		pri_var* pri_temp;

		switch(node_type->sym){
			case INT:
				pri_temp = malloc(sizeof(pri_var));
				pri_temp->name = varinfo->lexeme;
				pri_temp->decl_line = varinfo->lineno;
				pri_temp->type = INT_TYPE;
				pri_temp->value = NULL;
				break;
			case REAL:
				pri_temp = malloc(sizeof(pri_var));
				pri_temp->name = varinfo->lexeme;
				pri_temp->decl_line = varinfo->lineno;
				pri_temp->type = REAL_TYPE;
				pri_temp->value = NULL;
				break;
			case BOOL:
				pri_temp = malloc(sizeof(pri_var));
				pri_temp->name = varinfo->lexeme;
				pri_temp->decl_line = varinfo->lineno;
				pri_temp->type = BOOL_TYPE;
				pri_temp->value = NULL;
				break;
			case CHAR:
				pri_temp = malloc(sizeof(pri_var));
				pri_temp->name = varinfo->lexeme;
				pri_temp->decl_line = varinfo->lineno;
				pri_temp->type = CHAR_TYPE;
				pri_temp->value = NULL;
				break;
		}
		LL_insert(list, pri_temp);
	}

	Tree p = ast->child;
	while(p != NULL){
		ST_getRecComp(p, list);
		p = p->next;
	}
}

void ST_makeRecDecEntry(ST *st, Tree ast){
	int key;
	rec_dec *temp = malloc(sizeof(rec_dec));
	temp->name =  (*((TokenInfo**)(ast->value)))->lexeme;
	temp->decl_line = (*((TokenInfo**)(ast->value)))->lineno;

	key = ST_search(st, temp->name);
	if(key != -1){printf("error: record '%s' is redefined at lineno: %d\n", temp->name, GET(ast, lineno)); compiler_error = true; return; }

	ST_getRecComp(ast, &(temp->varList));
	key = ST_genKey(st, temp->name);
	LL_Node *p = temp->varList;
	temp->numEntries = 0;
	while(p != NULL){
		temp->numEntries++;
		p = p->next;
	}

	temp->offset = key;
	st->entry[key] = temp;
	st->type[key] = RECDEC_TYPE;

	ast->scope = st;
	ast->offset = key;

}

void ST_procRecScan(ST *st, Tree ast){
	if(ast == NULL) return;

	if(ast->sym == PROC) 		ST_makeProcEntry(st, ast);
	else if(ast->sym == REC) 	ST_makeRecDecEntry(st, ast);

	Tree p = ast->child;
	while(p != NULL){
		if(p->sym != EXECUTE) 	ST_procRecScan(st, p);
		p = p->next;
	}
}

/************************************************************SYMBOL TABLE DISPLAY FUNCTION*******************************************************************/
void ST_printAll(ST *st){
	ST_print(st);
	ST *p = st->child;
	while(p != NULL){
		ST_print(p);
		p = p->next;
	}

}

void ST_print(ST *st){
	printf("----------------------->SCOPE: %d\n", st->id);
	if(st == NULL) return;
	int i, j, k; LL_Node *p;
	pri_var* pri_temp;
	rec_var* rec_temp;
	rec_dec* recdec;
	mat_var* mat;
	str_var* str_temp;
	proc_dec* proc_temp;
	proc_arg* procarg;

	for(i=0; i<SIZE; i++){
		if(st->entry[i] == NULL) continue;
		printf("[%3d] ", i);
		switch(st->type[i]){
			case INT_TYPE: 
				pri_temp = (pri_var*)st->entry[i];
				printf("TYPE:int  |\t name:%s,\t offset:%d,\t decl_line:%d,\t ", pri_temp->name, pri_temp->offset, pri_temp->decl_line);
				if(pri_temp->value == NULL) printf("value=NULL\n");
				else printf("value:%d\n", *((int*)pri_temp->value));
				break;
			case CHAR_TYPE: 
				pri_temp = (pri_var*)st->entry[i];
				printf("TYPE:char |\t name:%s,\t offset:%d,\t decl_line:%d,\t ", pri_temp->name, pri_temp->offset, pri_temp->decl_line);
				if(pri_temp->value == NULL) printf("value=NULL\n");
				else printf("value:%c\n", *((char*)pri_temp->value));
				break;
			case REAL_TYPE:
				pri_temp = (pri_var*)st->entry[i];
				printf("TYPE:real |\t name:%s,\t offset:%d,\t decl_line:%d,\t ", pri_temp->name, pri_temp->offset, pri_temp->decl_line);
				if(pri_temp->value == NULL) printf("value=NULL\n");
				else printf("value:%f\n", *((float*)pri_temp->value));
				break; 
			case BOOL_TYPE: 
				pri_temp = (pri_var*)st->entry[i];
				printf("TYPE:bool |\t name:%s,\t offset:%d,\t decl_line:%d,\t ", pri_temp->name, pri_temp->offset, pri_temp->decl_line);
				if(((pri_var*)(st->entry[i]))->value == NULL) printf("value=NULL\n");
				else printf("value:%f\n", *((int*)((pri_var*)(st->entry[i]))->value));
				break; 
			case MAT_TYPE: 
				mat = (mat_var*)st->entry[i];
				printf("TYPE:mat<%s> |\t name:%s,\t offset:%d,\t decl_line:%d,\t rows:%d,\t cols:%d,\t ", typeToStr(mat->type), mat->name, mat->offset, mat->decl_line, mat->rows, mat->cols);
				if(mat->value == NULL) printf("value=NULL\n");
				else{
					printf("\n");
					switch(mat->type){
						case INT_TYPE:
							for(k=0; k<mat->rows; k++){
								for(j=0; j<mat->cols; j++) printf("%3d ", ((int**)mat->value)[k][j]);
								printf("\n");
							}
							break;
						case REAL_TYPE:
							for(k=0; k<mat->rows; k++){
								for(j=0; j<mat->cols; j++) printf("%3.2f ", ((float**)mat->value)[k][j]);
								
								printf("\n");
							}
							break;
						case BOOL_TYPE:
							for(k=0; k<mat->rows; k++){
								for(j=0; j<mat->cols; j++) printf("%3d ", ((bool**)mat->value)[k][j]);
								printf("\n");
							}
							break;
						case CHAR_TYPE:
							for(k=0; k<mat->rows; k++){
								for(j=0; j<mat->cols; j++) printf("%3c ", ((char**)mat->value)[k][j]);
								printf("\n");
							}
							break;
						default:
						 	printf("No value\n");
					}

				}
				break; 
			case STR_TYPE:
				str_temp = (str_var*)st->entry[i];
				printf("TYPE:string |\t name:%s,\t offset:%d,\t decl_line:%d,\t len:%d,\t ", str_temp->name, str_temp->offset, str_temp->decl_line, str_temp->len);

				if(str_temp->value == NULL) printf("value=NULL\n");
				else printf("value:%s\n", str_temp->value);
				break; 
			case RECDEC_TYPE:
				recdec = (rec_dec*)st->entry[i];
				printf("TYPE:recdec |\t name:%s offset:%d,\t decl_line:%d,\t\n", recdec->name, recdec->offset, recdec->decl_line);
				p = recdec->varList;
				while(p != NULL){
					printf("\t\t\t =>name:%s \t type:%s  \t",((pri_var*)p->value)->name, typeToStr(((pri_var*)p->value)->type));
					if( ((pri_var*)p->value)->value == NULL)printf("value=NULL\n");
					else printf("value=SOMETHING\n");
					p = p->next;
				}
				break;
			case REC_TYPE:
				rec_temp = (rec_var*)st->entry[i];
				recdec = (rec_dec*)rec_temp->type_st->entry[rec_temp->type_offset];
				printf("TYPE:RECORD_VAR |\t name:%s offset:%d,\t decl_line:%d,\t Record type: %s\t\n", rec_temp->name, rec_temp->offset, rec_temp->decl_line, recdec->name);
				break;
			case PROC_TYPE:
				proc_temp = (proc_dec*)st->entry[i];
				printf("TYPE:proc |\t name:%s,\t offset:%d,\t decl_line:%d,\n",proc_temp->name, proc_temp->offset, proc_temp->decl_line );
				
				p = proc_temp->inputList;
				while(p!=NULL) {
					procarg = (proc_arg*)p->value;
					printf("\t\t\t =INPUT=>name: %s (type:%s)\n", procarg->name, typeToStr(procarg->type) );
					p = p->next;
				}

				p = proc_temp->outputList;
				while(p!=NULL){
					procarg = (proc_arg*)p->value;
					printf("\t\t\t =OUTPUT=>name: %s (type:%s)\n", procarg->name, typeToStr(procarg->type) );
					p = p->next;
				}printf("\n");

				// printf("PROC SCOPE (%s):\n", proc_temp->name);
				// ST_print(proc_temp->scope);
				// printf("proc scope(%s) ends\n",proc_temp->name );
				break;
		}
	}
}

void ST_traverse(ST *st, int level){
	int i;
	if(st == NULL) return;
	for(i=0; i<level; i++) printf("--");
	printf(">%d\n",st->id );

	ST *p = st->child;
	while(p != NULL){
		ST_traverse(p, level+1);
		p = p->next;
	}
}