/********************************
       |TEAM-1 | GROUP-20|
UTKARSH PATHRABE  - 2012A7PS034P
SHIKHAR VASHISHTH - 2012C6PS436P
********************************/

#include "TypeChecker.h"

#define GET(ast, field) (*((TokenInfo**)ast->value))->field
#define GET2(ast, field) ((TokenInfo*)ast->value)->field

bool compiler_error;

TC_scan(ST *st, Tree ast){
	if(ast == NULL) return;
	switch(ast->sym){
		case CALL: 		TC_checkProc(ast); 		break;
		case STRASSIGN:		TC_checkStrAssign(st, ast);	break;
		case MATASSIGN:		TC_checkMatAssign(st, ast);	break;
		case ASSIGN:		TC_assign(st, ast);		break;
		case PUT:
		case GET:		TC_ioStmt(st, ast);		break;
		case GE: case LE: 
		case EQ: case NEQ: 
		case LT: case GT:	TC_condExp(ast);		break;
	}

	Tree p = ast->child;
	while(p != NULL){
		TC_scan(st, p);
		p = p->next;
	}
}
TC_ioStmt(ST *st, Tree ast){
	int key;
	Type type;
	char *varname = GET(ast->child, lexeme);

	if(ast->child->sym == STR_LIT) return;

	if(ast->child->sym == ID_PRI){
		ST_getinfo(ast->child->scope, varname, &key);
		if(key == -1){printf("error: '%s' is undefined at lineno: %d\n", varname); compiler_error = true; return; }
		type = ST_getinfo(ast->child->scope, varname, &key)->type[key];
		if( type == MAT_TYPE || type == REC_TYPE) printf("error: '%s' cannot be of '%s' at lineno: %d\n", varname, typeToStr(type), GET(ast, lineno));
	}
	else if(ast->child->sym == ID_MAT_RHS){
		TC_checkMatId(ast->child, -1);
	}
	else if(ast->child->sym == ID_REC_RHS){
		TC_checkRecId(ast->child, -1);
	}
}

Type TC_checkOperand(TreeNode *op){
	if(op->sym == ID_PRI){
		int key;
		ST *scope = ST_getinfo(op->scope, GET(op, lexeme), &key);
		if(key == -1) {printf("error: '%s' is undefined in expression at lineno: %d\n", GET(op, lexeme), GET(op, lineno)); compiler_error = true; return -1; }
		switch(scope->type[key]){
			case INT_TYPE: 	return INT_TYPE;
			case REAL_TYPE:	return REAL_TYPE;
			case CHAR_TYPE:
			case BOOL_TYPE:
			case STR_TYPE:
				printf("error: '%s' can be of int or real type at lineno: %d\n", GET(op, lexeme), GET(op, lineno));
				compiler_error = true;
				return -1;
		}
	}
	else{
		switch(op->sym){
			case INT_LIT: 	return INT_TYPE;
			case REAL_LIT:	return REAL_TYPE;
			case CHAR_LIT:
			case BOOL_LIT:
			case STR_LIT:
				printf("error: Relational exp can of int or real type at lineno: %d\n", GET(op, lineno));
				compiler_error = true;
				return -1;
		}
	}
}

TC_condExp(Tree ast){
	TreeNode* op1, *op2;
	Type type1, type2;

	op1 = ast->child;
	if(op1->next->sym == elem) op2 = op1->next->child;
	else op2 = op1->next;

	type1 = TC_checkOperand(op1);
	type2 = TC_checkOperand(op2);

	if(type1 == -1 || type2 == -1) return;

	if(type1 != type2){
		printf("error: RHS('%s') and LHS('%s') type mismatch in condition at lineno: %d\n", typeToStr(type1), typeToStr(type2), GET(op1, lineno));
		compiler_error = true;
		return;
	}
}

TC_checkMatId(Tree ast, Type exptype){
	matAssignRHSInfo *mat = ast->value;
	char *var_mat, *var_row, *var_col;
	int key, lineno;

	var_mat = (*((TokenInfo**)mat->info))->lexeme;
	var_row = (*((TokenInfo**)mat->rows))->lexeme;
	lineno = (*((TokenInfo**)mat->rows))->lineno;


	if( mat->cols != NULL) var_col = (*((TokenInfo**)mat->cols))->lexeme;
	else var_col = NULL;

	if( ST_getinfo(ast->scope, var_mat, &key)->type[key] != MAT_TYPE){printf("error: '%s' if not of matrix type at lineno: %d\n", var_mat, lineno); compiler_error = true; return; }
	mat_var *matvar = ST_getinfo(ast->scope, var_mat, &key)->entry[key];

	if(exptype != -1) if( matvar->type != exptype){printf("error: Matrix '%s' of '%s' in expression of '%s' at lineno: %d\n", var_mat, typeToStr(matvar->type), typeToStr(exptype), lineno); compiler_error = true; }
	if(mat->cols == NULL){
		switch(mat->rowSym){
			case INT_LIT: if( atoi(var_row) >= matvar->cols){printf("error: Exceeded dimension of '%s' must be <'%d' at lineno: %d\n", var_mat, matvar->cols, lineno); compiler_error = true; } break;
			case ID: if( ST_getinfo(ast->scope, var_row, &key)->type[key] != INT_TYPE){printf("error: Index: '%s' of matrix must be 'INT_TYPE' at lineno: %d\n", var_row, lineno); compiler_error = true; } break;
			default: printf("error: Index: '%s' of matrix must be 'INT_TYPE' at lineno: %d\n", var_row, lineno); compiler_error = true; 
		}
	}
	else{
		switch(mat->rowSym){
			case INT_LIT: if( atoi(var_row) >= matvar->rows){printf("error: Exceeded row dimension of '%s' must be <'%d' at lineno: %d\n", var_mat, matvar->rows, lineno); compiler_error = true; } break;
			case ID: if( ST_getinfo(ast->scope, var_row, &key)->type[key] != INT_TYPE){printf("error: Index: '%s' of matrix must be 'INT_TYPE' at lineno: %d\n", var_row,  lineno); compiler_error = true; } break;
			default: printf("error: Index: '%s' of matrix must be 'INT_TYPE' at lineno: %d\n", var_row, lineno); compiler_error = true;
		}
		switch(mat->colSym){
			case INT_LIT: if( atoi(var_col) >= matvar->cols){printf("error: Exceeded column dimension of '%s' must be <'%d' at lineno: %d\n", var_mat, matvar->cols, lineno); compiler_error = true; } break;
			case ID: if( ST_getinfo(ast->scope, var_col, &key)->type[key] != INT_TYPE){printf("error: Index: '%s' of matrix must be 'INT_TYPE' at lineno: %d\n", var_col, lineno); compiler_error = true; } break;
			default: printf("error: Index: '%s' of matrix must be 'INT_TYPE' at lineno: %d\n", var_col, lineno); compiler_error = true; 
		}
	}
	return;
}

TC_checkRecId(Tree ast, Type exptype){
	int key, lineno;
	recTypeIDInfo *info = ast->value;
	char *recname = (*((TokenInfo**)info->info))->lexeme;
	char *compname = (*((TokenInfo**)info->comp))->lexeme;
	lineno = (*((TokenInfo**)info->comp))->lineno;

	if(ST_getinfo(ast->scope, recname, &key)->type[key] != REC_TYPE){printf("error: '%s' must be of RECORD TYPE at lineno: %d\n", recname, lineno); compiler_error = true; return; }

	rec_var *temp = ST_getinfo(ast->scope, recname, &key)->entry[key];
	rec_dec *rec = ST_getinfo(ast->scope, temp->type_name, &key)->entry[key];
	LL_Node *vlist = rec->varList;
	pri_var *pri, *varcomp = NULL;

	while(vlist != NULL){
		pri = vlist->value;
		if(!strcmp(pri->name, compname)){
			varcomp = pri;
			break;
		}
		vlist = vlist->next;
	}

	if(varcomp == NULL){printf("error: undefined record component '%s' at lineno: %d\n", compname, lineno); compiler_error = true; return; }
	if(exptype!=-1)if(exptype != varcomp->type){printf("error: '%s.%s' of '%s' in expression of '%s' at lineno: %d\n", recname, compname, typeToStr(varcomp->type), typeToStr(exptype), lineno ); compiler_error = true; return; }
}

TC_checkId(Tree ast, Type exptype){
	ST* st = ast->scope;
	int key;
	char *name = GET(ast, lexeme);
	ST* p = ST_getinfo(st, name, &key);

	if( key == -1){printf("error: '%s' is undefined in expression at lineno: %d\n", GET(ast, lexeme), GET(ast, lineno)); compiler_error = true; return; }
	Type type = ST_getinfo(ast->scope, GET(ast, lexeme), &key)->type[key];
	if(type == REC_TYPE){
		Tree comp = ast->next->child->next;
		rec_var *temp = p->entry[key];

		p = ST_getinfo(p, temp->type_name, &key);
		rec_dec *rec = p->entry[key];
		LL_Node *vlist = rec->varList;
		pri_var *pri, *varcomp = NULL;

		if(rec->varList == NULL) printf("trouble\n");

		while(vlist != NULL){
			pri = vlist->value;
			if(!strcmp(pri->name, GET(comp, lexeme))){
				varcomp = pri;
				break;
			}
			vlist = vlist->next;
		}

		if(varcomp == NULL){
			printf("error: undefined record component '%s' at lineno: %d\n", GET(comp, lexeme), GET(comp ,lineno));
			compiler_error = true;
			return;
		}		
		type = varcomp->type;
		if(exptype != type){
			printf("error: '%s.%s' of '%s' in expression of '%s' at lineno: %d\n", GET(ast, lexeme), GET(comp, lexeme), typeToStr(type), typeToStr(exptype), GET(ast, lineno) );
			compiler_error = true;
			return;
		}
	}
	if( exptype != type){printf("error: '%s' of '%s' in expression of '%s' at lineno: %d\n", GET(ast, lexeme), typeToStr(type), typeToStr(exptype),  GET(ast, lineno)); compiler_error = true; return; }
}

TC_idScan(Tree ast, Type type){
	if( ast == NULL) return;

	switch( ast->sym ){
		case ID:		TC_checkId(ast, type);		break;
		case ID_REC_RHS:	TC_checkRecId(ast, type);	break;
		case ID_MAT_RHS:	TC_checkMatId(ast, type);	break;
		case INT_LIT: 		if( type != INT_TYPE) {printf("error: '%s' %s literal in expression of '%s' at lineno: %d\n", GET(ast, lexeme), typeToStr(INT_TYPE), typeToStr(type), GET(ast, lineno)); compiler_error = true; } break;
		case REAL_LIT: 		if( type != REAL_TYPE) {printf("error: '%s' %s literal in expression of '%s' at lineno: %d\n", GET(ast, lexeme), typeToStr(REAL_TYPE),typeToStr(type),  GET(ast, lineno)); compiler_error = true; } break;
		case CHAR_LIT: 		if( type != CHAR_TYPE) {printf("error: '%s' %s literal in expression of '%s' at lineno: %d\n", GET(ast, lexeme), typeToStr(CHAR_LIT), typeToStr(type), GET(ast, lineno)); compiler_error = true; } break;
		case BOOL_LIT: 		if( type != BOOL_TYPE) {printf("error: '%s' %s literal in expression of '%s' at lineno: %d\n", GET(ast, lexeme), typeToStr(BOOL_TYPE),typeToStr(type),  GET(ast, lineno)); compiler_error = true; } break;
	}

	Tree p = ast->child;
	while(p != NULL){
		TC_idScan(p, type);
		p = p->next;
	}

}

TC_opScan(Tree ast, Type type){
	if(ast == NULL) return;
	switch(ast->sym){
		case MUL: case DIV: case MOD: case POW:
			if(type != INT_TYPE){
				printf("error: '*', '/', mod, '**' only restricted to INT_TYPE at lineno: %d\n", GET(ast, lineno));
				compiler_error = true;
			}
			break;
		case PLUS: case MINUS:
			if( !(type == INT_TYPE || type == REAL_TYPE) ){
				printf("error: '+' and '-' are only restricted to INT and REAL type at lineno: %d\n", GET(ast, lineno));
				compiler_error = true;
			}
			break;
	}
	Tree p = ast->child;
	while(p != NULL){
		TC_opScan(p, type);
		p = p->next;
	}
}

TC_assign(ST *st, Tree ast){
	TreeNode *varnode = ast->child;
	int key, lineno;
	char *varname = GET(varnode, lexeme);
	matAssignRHSInfo *mat;
	mat_var *matvar;
	char *var_mat, *var_row, *var_col;
	recTypeIDInfo *info;
	char *recname;
	char *compname;
	rec_var *temp;
	rec_dec *rec;
	LL_Node *vlist;
	pri_var *pri, *varcomp;
	ST *scope;
	Type exptype;
	
	switch(ast->child->sym){
		case ID_MAT_RHS:
			mat = ast->child->value;

			var_mat = (*((TokenInfo**)mat->info))->lexeme;
			var_row = (*((TokenInfo**)mat->rows))->lexeme;
			lineno = (*((TokenInfo**)mat->rows))->lineno;

			scope = ST_getinfo(ast->child->scope, var_mat, &key);
			if(key == -1){printf("error: '%s' is undefined at lineno: %d\n", var_mat, lineno ); compiler_error = true; return; }
			if(scope->type[key] != MAT_TYPE){printf("error: '%s' must be of 'MAT_TYPE' type at lineno: %d\n", var_mat, lineno); compiler_error = true; return; }

			if( mat->cols != NULL) var_col = (*((TokenInfo**)mat->cols))->lexeme;
			else var_col = NULL;

			matvar = ST_getinfo(ast->child->scope, var_mat, &key)->entry[key];

			if(mat->cols == NULL){
				switch(mat->rowSym){
					case INT_LIT: if( atoi(var_row) >= matvar->cols){printf("1error: Exceeded dimension of '%s' must be <'%d' at lineno: %d\n", var_mat, matvar->cols, lineno); compiler_error = true; } break;
					case ID: if( ST_getinfo(ast->child->scope, var_row, &key)->type[key] != INT_TYPE){printf("error: Index: '%s' of matrix must be 'INT_TYPE' at lineno: %d\n", var_row, lineno); compiler_error = true; } break;
					default: printf("error: Index: '%s' of matrix must be 'INT_TYPE' at lineno: %d\n", var_row, lineno); compiler_error = true; 
				}
			}
			else{
				switch(mat->rowSym){
					case INT_LIT: if( atoi(var_row) >= matvar->rows){printf("error: Exceeded row dimension of '%s' must be <'%d' at lineno: %d\n", var_mat, matvar->rows, lineno); compiler_error = true; } break;
					case ID: if( ST_getinfo(ast->child->scope, var_row, &key)->type[key] != INT_TYPE){printf("error: Index: '%s' of matrix must be 'INT_TYPE' at lineno: %d\n", var_row,  lineno); compiler_error = true; } break;
					default: printf("error: Index: '%s' of matrix must be 'INT_TYPE' at lineno: %d\n", var_row, lineno); compiler_error = true;
				}
				switch(mat->colSym){
					case INT_LIT: if( atoi(var_col) >= matvar->cols){printf("error: Exceeded column dimension of '%s' must be <'%d' at lineno: %d\n", var_mat, matvar->cols, lineno); compiler_error = true; } break;
					case ID: if( ST_getinfo(ast->child->scope, var_col, &key)->type[key] != INT_TYPE){printf("error: Index: '%s' of matrix must be 'INT_TYPE' at lineno: %d\n", var_col, lineno); compiler_error = true; } break;
					default: printf("error: Index: '%s' of matrix must be 'INT_TYPE' at lineno: %d\n", var_col, lineno); compiler_error = true; 
				}
			}
			exptype = matvar->type;

			break;
		case ID_REC_RHS:
			info = ast->child->value;

			recname =  (*((TokenInfo**)info->info))->lexeme;
			compname = (*((TokenInfo**)info->comp))->lexeme;
			lineno = (*((TokenInfo**)info->comp))->lineno;	

			if(ST_getinfo(ast->child->scope, recname, &key)->type[key] != REC_TYPE){printf("error: '%s' must be of RECORD TYPE at lineno: %d\n", recname, lineno); compiler_error = true; return; }

			temp = ST_getinfo(ast->child->scope, recname, &key)->entry[key];
			rec = ST_getinfo(ast->child->scope, temp->type_name, &key)->entry[key];
			vlist = rec->varList;
			varcomp = NULL;

			while(vlist != NULL){
				pri = vlist->value;
				if(!strcmp(pri->name, compname)){
					varcomp = pri;
					break;
				}
				vlist = vlist->next;
			}

			if(varcomp == NULL){printf("error: undefined record component '%s' at lineno: %d\n", compname, lineno); compiler_error = true; return; }
			exptype = varcomp->type;
			break;
		case ID:
		case ID_PRI:
			scope = ST_getinfo(ast->scope, varname, &key);
			if(key == -1){printf("error: '%s' is undefined in expression at lineno: %d\n", GET(varnode, lexeme), GET(varnode, lineno)); compiler_error = true; return;}
			exptype = scope->type[key];
			break;
	}

	if( exptype == STR_TYPE || exptype == MAT_TYPE){printf("error: 'assign' is not for string and matrix variables at lineno: %d\n", GET(varnode, lineno)); compiler_error = true; return; }
		
	TC_idScan(ast->child->next, exptype);
	TC_opScan(ast->child->next, exptype);
}

TC_checkMatAssign(ST *st, Tree ast){
	mat_var *mat, *mat1, *mat2, *mat3;
	TreeNode* rowlist, *row;
	LL_Node *list;
	int rows, cols, i, j, key;

	char *var1, *var2, *var3;
	Type type;
	int lineno = GET(ast, lineno);
	var1 = GET(ast, lexeme);

	switch(ast->child->sym){
		case row_list:
			rowlist = ast->child;
			row = rowlist->child;

			list = (LL_Node*)row->value;
			mat  = ST_getinfo(st, var1, &key);
			if(key == -1){printf("error: '%s' is undefined at lineno: %d\n", var1, lineno); compiler_error = true; return; }
			mat  = ST_getinfo(st, var1, &key)->entry[key];

			type = ST_getinfo(st, var1, &key)->type[key]; if(type != MAT_TYPE){printf("error: '%s' should be int type at lineno:%d\n", var1, lineno); compiler_error = true; return;}

			rows = numChild(rowlist);
			cols = LL_size(list);

			if(mat->rows != rows || mat->cols != cols){printf("error: Dimension mismatch in '%s' matrix assignment at lineno:%d\n", var1, lineno); compiler_error = true; return; }

			switch(mat->type){
				case INT_TYPE:
					mat->value = malloc(mat->rows * sizeof(int*));
					for(i=0; i<mat->cols; i++) mat->value[i] = malloc(mat->cols * sizeof(int));

					for( i=0; row != NULL; row=row->next, i++){
						list = (LL_Node*)row->value; 
						for(j=0; list!=NULL; j++, list = list->next) 
							((int**)mat->value)[i][j] = atoi(GET(list, lexeme));
					}
					break;
				case REAL_TYPE:
					mat->value = malloc(mat->rows * sizeof(float*));
					for(i=0; i<mat->cols; i++) mat->value[i] = malloc(mat->cols * sizeof(float));

					for( i=0; row != NULL; row=row->next, i++){
						list = (LL_Node*)row->value; 
						for(j=0; list!=NULL; j++, list = list->next) 
							((float**)mat->value)[i][j] = atof(GET(list, lexeme));
					}
					break;
				case BOOL_TYPE:
					mat->value = malloc(mat->rows * sizeof(bool*));
					for(i=0; i<mat->cols; i++) mat->value[i] = malloc(mat->cols * sizeof(bool));

					for( i=0; row != NULL; row=row->next, i++){
						list = (LL_Node*)row->value; 
						for(j=0; list!=NULL; j++, list = list->next) 
							((bool**)mat->value)[i][j] = (!strcmp(GET(list, lexeme), "True"));
					}
					break;
				case CHAR_TYPE:
					mat->value = malloc(mat->rows * sizeof(char*));
					for(i=0; i<mat->cols; i++) mat->value[i] = malloc(mat->cols * sizeof(char));

					for( i=0; row != NULL; row=row->next, i++){
						list = (LL_Node*)row->value; 
						for(j=0; list!=NULL; j++, list = list->next) 
							((char**)mat->value)[i][j] = GET(list, lexeme)[1];
						
					}
					break;
			}

			break;
		case MAT_ROWS:
			var2 = GET(ast->child, lexeme);
			type = ST_getinfo(st, var1, &key)->type[key]; if(type != INT_TYPE){printf("error: '%s' should be int type at lineno:%d\n", var1, lineno); compiler_error = true; return; }
			type = ST_getinfo(st, var2, &key)->type[key]; if(type != MAT_TYPE){printf("error: '%s' should be of mat type at lineno:%d\n",var2, lineno ); compiler_error = true; return; }
			break;
		case MAT_COLS:
			var2 = GET(ast->child, lexeme);
			type = ST_getinfo(st, var1, &key)->type[key]; if(type != INT_TYPE){printf("error: '%s' should be int type at lineno:%d\n", var1, lineno); compiler_error = true; return; }
			type = ST_getinfo(st, var2, &key)->type[key]; if(type != MAT_TYPE){printf("error: '%s' should be of mat type at lineno:%d\n",var2, lineno ); compiler_error = true; return; }
			break;
		case PLUS:
			var2 = GET(ast->child->child, lexeme);
			var3 = GET(ast->child->child->next, lexeme);
			mat1 = ST_getinfo(st, var1, &key)->entry[key];
			mat2 = ST_getinfo(st, var2, &key)->entry[key];
			mat3 = ST_getinfo(st, var3, &key)->entry[key];

			type = ST_getinfo(st, var1, &key)->type[key]; if(type != MAT_TYPE){printf("error: '%s' should be of mat type at lineno:%d\n",var1, lineno); compiler_error = true; return; }
			type = ST_getinfo(st, var2, &key)->type[key]; if(type != MAT_TYPE){printf("error: '%s' should be of mat type at lineno:%d\n",var2, lineno); compiler_error = true; return; }
			type = ST_getinfo(st, var3, &key)->type[key]; if(type != MAT_TYPE){printf("error: '%s' should be of mat type at lineno:%d\n",var3, lineno); compiler_error = true; return; }

			if( (mat1->rows != mat2->rows) || (mat1->rows != mat3->rows) || (mat1->cols != mat2->cols) || (mat1->cols != mat3->cols) ){printf("error: Dimension mismatch of matrices at lineno: %d\n", lineno); compiler_error = true; }
			if( (mat1->type != mat2->type) || (mat1->type != mat3->type) || (mat1->type != INT_TYPE) ){printf("error: Type of matrices must be of 'INT_TYPE' for addition operation at lineno:%d \n", lineno); compiler_error = true; return; }
	}
}

TC_checkStrAssign(ST *st, Tree ast){
	str_var *mainvar, *var1, *var2;
	char *varname, *var1name, *var2name;

	TreeNode *func = ast->child;
	int lineno = GET(ast, lineno), key;
	varname = GET(ast, lexeme);

	mainvar = ST_getinfo(ast->scope, varname, &key);
	if(key == -1){printf("error: '%s' is undefined at lineno: %d\n", varname, GET(ast, lineno)); compiler_error = true; return; }
	mainvar = ST_getinfo(ast->scope, varname, &key)->entry[key];
	Type vartype = ST_getinfo(ast->scope, varname, &key)->type[key];

	switch(func->sym){
		case STR_LIT:
			if(vartype != STR_TYPE){printf("error: Data Type of '%s' must be of 'STRING' type at lineno: %d.\n", varname, lineno); compiler_error = true; }
			else{
				mainvar->value = GET(func, lexeme);
				// int i, len = strlen(mainvar->value);
				// for(i=0; i<len-2; i++) mainvar->value[i] = mainvar->value[i+1];
				// mainvar->value[len-2] = '\0';
			 	mainvar->len = strlen(mainvar->value)-2;
			}
			break;
		case PLUS:
			var1name = GET(func->child, lexeme);
			var2name = GET(func->child->next, lexeme);
			
			if(vartype != STR_TYPE){printf("error: Data Type of '%s' must be of 'STRING' type.\n", varname, lineno); compiler_error = true; }
			if( (ST_getinfo(func->scope, var1name, &key)->type[key] != STR_TYPE) || (ST_getinfo(func->scope, var2name, &key)->type[key] != STR_TYPE)){printf("error: Data Type of both '%s' and '%s' must be of 'STRING' type at lineno: %d.\n", var1name, var2name, lineno); compiler_error = true; }
			break;
		case STR_LENGTH:
			var1name = GET(func->child, lexeme);
			if( ST_getinfo(func->scope, var1name, &key)->type[key] != STR_TYPE){printf("error: Data Type of '%s' must be of 'STRING' type at lineno: %d.\n", var1name, lineno); compiler_error = true; }
			if( vartype != INT_TYPE ){printf("error: Data Type of '%s' must of 'int' type at lineno: %d.\n", varname, lineno); compiler_error = true; }
			break;
		case INT_LIT:
			var1name = GET(func->child, lexeme);
			if( ST_getinfo(func->scope, var1name, &key)->type[key] != STR_TYPE){printf("error: Data Type of '%s' must be of 'STRING' type at lineno: %d.\n", var1name, lineno); compiler_error = true; }
			if( vartype != CHAR_TYPE ){printf("error: Data Type of '%s' must of 'CHAR_TYPE' type at lineno: %d.\n", varname, lineno); compiler_error = true; }
			break;
		case ID: 
			var1name = GET(func, lexeme);
			if(func->child == NULL){
				if( ST_getinfo(func->scope, var1name, &key)->type[key] != STR_TYPE){printf("error: Data Type of '%s' must be of 'STRING' type at lineno: %d.\n", var1name, lineno); compiler_error = true; }
			}
			else{
				var2name = GET(func->child, lexeme);
				if( vartype != CHAR_TYPE){printf("error: Data Type of '%s' must be 'CHAR_TYPE' at lineno: %d\n", varname, GET(ast, lineno)); compiler_error = true; }
				if( ST_getinfo(func->scope, var1name, &key)->type[key] != INT_TYPE){printf("error: Data Type of '%s' must be of 'INT_TYPE' type at lineno: %d .\n", var1name, lineno); compiler_error = true; }
				if( ST_getinfo(func->scope, var2name, &key)->type[key] != STR_TYPE){printf("error: Data Type of '%s' must be of 'STRING' type at lineno: %d .\n", var2name, lineno); compiler_error = true; }
			}
			break;
	}
}

TC_checkProc(Tree ast){
	int i, argno, lineno, key;
	proc_dec *proc, *proc_temp;
	proc_arg *arg;
	LL_Node *p, *q;
	LL_Node *inplist = NULL, *outlist = NULL;
	ST *scope;
	bool isRecursive = false;


	lineno = GET(ast, lineno);
	char *procname = GET(ast, lexeme);

	scope = ST_getinfo(ast->scope, procname, &key);
	if(key == -1){printf("error: '%s' procedure is not defined at lineno: %d\n", procname, lineno); compiler_error=true; return;}

	proc = scope->entry[key];
	/*Check recursive call*/
	for(i=0; i<SIZE; i++){
		if(scope->entry[i] != NULL && scope->type[i] == PROC_TYPE){
			proc_temp = (proc_dec*)scope->entry[i];
			if(proc_temp->scope->id == ast->scope->id)
				isRecursive = true;
		}
	}
	if(isRecursive){printf("error: recursive procedure calls are not allowed at lineno: %d\n", GET(ast, lineno)); compiler_error = true; return; }

	TC_extProcArg(ast, &inplist, &outlist);
	/*Check input args:*/
	p = inplist;
	q = proc->inputList;
	argno = 1;

	while(p != NULL && q != NULL){
		arg = q->value;
		scope = ST_getinfo(ast->scope, p->value, &key);
		if( arg->type != scope->type[key] ){
			printf("error: '%s' input argument %d's type doesn't match at lineno: %d\n", procname, argno, lineno); compiler_error = true;
		}
		q = q->next;
		p = p->next;
		argno++;
	}
	if(q == NULL && p != NULL) 	{printf("error: '%s' has too many input arguments at lineno: %d\n", procname, lineno); compiler_error = true; }
	else if(p == NULL && q != NULL) {printf("error: '%s' has too few input arguments at lineno: %d\n" , procname, lineno); compiler_error = true; }

	/*Check output args*/
	p = outlist;
	q = proc->outputList;
	argno = 1; 

	while(p != NULL && q != NULL){
		arg = q->value;
		scope = ST_getinfo(ast->scope, p->value, &key);
		if( arg->type != scope->type[key] ){
			printf("error: '%s' output argument %d's type doesn't match at lineno: %d\n", procname, argno, lineno);
			compiler_error = true;
		}
		q = q->next;
		p = p->next;
		argno++;
	}

	if(q == NULL && p != NULL) 	{printf("error: '%s' has too many output arguments at lineno: %d\n", procname, lineno); compiler_error = true; }
	else if(p == NULL && q != NULL) {printf("error: '%s' has too few output arguments at lineno: %d\n" , procname, lineno); compiler_error = true; }
}

TC_extProcArg(Tree ast, LL_Node **inplist, LL_Node **outlist){
	Tree inp = ast->child;
	Tree out = ast->child->next;
	TokenInfo *temp;

	while(inp != NULL){
		temp = *((TokenInfo**)inp->value);
		LL_insert( inplist, temp->lexeme);
		inp = inp->child;
	}

	while(out != NULL){
		temp = *((TokenInfo**)out->value);
		LL_insert( outlist, temp->lexeme);
		out = out->child;
	}
}