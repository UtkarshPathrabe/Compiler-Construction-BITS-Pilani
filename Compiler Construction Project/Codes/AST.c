/********************************
       |TEAM-1 | GROUP-20|
UTKARSH PATHRABE  - 2012A7PS034P
SHIKHAR VASHISHTH - 2012C6PS436P
********************************/

#include "AST.h"
#include "LinkedList.h"

int tokenIndex = 0;
ListIndexGlobal = 0;

void constructAST(TreeNode *ast, TokenList tokens, int numTokens){
	TreeNode *root = ast;
	if (root->sym == program) {
		reduce_program(&root, tokens, numTokens);
	} else {
		printf ("\n******************ERROR******************\nAST can't be generated!\n");
	}
}

reduce_program(TreeNode **currNode, TokenList tokens, int numTokens){
	TreeNode *root = *currNode;
	if(root->child->child->sym == EPSILON){
		root->child = root->child->next;
		root->child->prev = NULL;
		if(root->child->child->sym == EPSILON){
			root->child = root->child->next;
			root->child->prev = NULL;
			reduce_execute(&(root->child), tokens, numTokens);
		} else {
			reduce_procedures(&(root->child), tokens, numTokens);
			reduce_execute(&(root->child->next), tokens, numTokens);
		}
	} else {
		if (root->child->next->child->sym == EPSILON) {
			root->child->next = root->child->next->next;
			root->child->next->prev = root->child;
			reduce_records(&(root->child), tokens, numTokens);
			reduce_execute(&(root->child->next), tokens, numTokens);
		} else {
			reduce_records(&(root->child), tokens, numTokens);
			reduce_procedures(&(root->child->next), tokens, numTokens);
			reduce_execute(&(root->child->next->next), tokens, numTokens);
		}
	}
}

reduce_execute(TreeNode **currNode, TokenList tokens, int numTokens){
	TreeNode *root = *currNode;
	TreeNode *node_stmts = root->child->next->next;
	root->sym = root->child->sym;
	root->value = root->child->value;
	root->child = node_stmts;
	node_stmts->next = NULL;
	reduce_stmts(&(root->child), tokens, numTokens);
}

reduce_records(TreeNode **currNode, TokenList tokens, int numTokens){
	TreeNode *root = *currNode;
	root->sym = root->child->child->sym;
	root->value = root->child->child->value;
	root->child = root->child->child->next->next;
	root->child->prev = NULL;
	root->child->next = NULL;
	reduce_recs(&(root->child), tokens, numTokens);
}

reduce_procedures(TreeNode **currNode, TokenList tokens, int numTokens){
	TreeNode *root = *currNode;
	root->sym = root->child->child->sym;
	root->value = root->child->child->value;
	root->child = root->child->child->next->next;
	root->child->prev = NULL;
	root->child->next = NULL;
	reduce_procs(&(root->child), tokens, numTokens);
}

void reduce_recs(TreeNode **currNode, TokenList tokens, int numTokens){
	TreeNode *root = *currNode;
	if (root->child->next->child->sym == EPSILON) {
		root->sym = root->child->child->sym;
		root->value = root->child->child->next->value;
		root->child = root->child->child->next->next->next;
		root->child->parent = root;
		root->child->prev = NULL;
		root->child->next = NULL;
		reduce_decl_stmts(&(root->child), tokens, numTokens);
	} else {
		root->child->sym = root->child->child->sym;
		root->child->value = root->child->child->next->value;
		root->child->child = root->child->child->next->next->next;
		root->child->child->prev = NULL;
		root->child->child->next = NULL;
		reduce_decl_stmts(&(root->child->child), tokens, numTokens);
		root->child->next = root->child->next->child;
		root->child->next->prev = root->child;
		reduce_recs(&(root->child->next), tokens, numTokens);
	}
}

void reduce_procs(TreeNode **currNode, TokenList tokens, int numTokens){
	TreeNode *root = *currNode;
	TreeNode *node_param_list1 = root->child->child->next->next->next;
	TreeNode *node_param_list2 = node_param_list1->next->next->next->next;
	TreeNode *node_stmts = node_param_list2->next->next->next;
	if (root->child->next->child->sym == EPSILON){
		root->sym = root->child->child->sym;
		root->value = root->child->child->next->value;
		root->child = node_param_list1;
		node_param_list1->prev = NULL;
		node_param_list1->next = node_param_list2;
		node_param_list2->prev = node_param_list1;
		node_param_list2->next = node_stmts;
		node_stmts->prev = node_param_list2;
		node_stmts->next = NULL;
		node_param_list1->parent = root;
		node_param_list2->parent = root;
		node_stmts->parent = root;
		reduce_param_list(&(node_param_list1), tokens, numTokens);
		reduce_param_list(&(node_param_list2), tokens, numTokens);
		reduce_stmts(&(node_stmts), tokens, numTokens);
	} else {
		root->child->sym = root->child->child->sym;
		root->child->value = root->child->child->next->value;
		root->child->child = node_param_list1;
		node_param_list1->prev = NULL;
		node_param_list1->next = node_param_list2;
		node_param_list2->prev = node_param_list1;
		node_param_list2->next = node_stmts;
		node_stmts->prev = node_param_list2;
		node_stmts->next = NULL;
		reduce_param_list(&(node_param_list1), tokens, numTokens);
		reduce_param_list(&(node_param_list2), tokens, numTokens);
		reduce_stmts(&(node_stmts), tokens, numTokens);
		root->child->next = root->child->next->child;
		root->child->next->prev = root->child;
		reduce_procs(&(root->child->next), tokens, numTokens);
	}
}

void reduce_param_list(TreeNode **currNode, TokenList tokens, int numTokens){
	TreeNode *root = *currNode;
	if (root->child->next->next->child->sym == EPSILON) {
		root->sym = root->child->child->sym;
		root->value = root->child->next->value;
		root->child = NULL;
	} else {
		root->sym = root->child->child->sym;
		root->value = root->child->next->value;
		root->child = root->child->next->next->child->next;
		root->child->parent = root;
		root->child->prev = NULL;
		root->child->next = NULL;
		reduce_param_list(&(root->child), tokens, numTokens);
	}
}

void reduce_stmts(TreeNode **currNode, TokenList tokens, int numTokens){
	TreeNode *root = *currNode;
	if (root->child->next->child->sym == EPSILON) {
		root->child->child->prev = root->prev;
		root->child->child->next = root->next;
		root->child->child->parent = root->parent;
		if (root->prev == NULL) root->parent->child = root->child->child;
		else root->prev->next = root->child->child;
		switch(root->child->child->sym){
			case decl_stmt:
				reduce_decl_stmt(&(root->child->child), tokens, numTokens);
				break;
			case cond_stmt:
				reduce_cond_stmt(&(root->child->child), tokens, numTokens);
				break;
			case loop_stmt:
				reduce_loop_stmt(&(root->child->child), tokens, numTokens);
				break;
			case proc_call_stmt:
				reduce_proc_call_stmt(&(root->child->child), tokens, numTokens);
				break;
			case io_stmt:
				reduce_io_stmt(&(root->child->child), tokens, numTokens);
				break;
			case assign_stmt:
				reduce_assign_stmt(&(root->child->child), tokens, numTokens);
				break;
			case mat_assign_stmt:
				reduce_mat_assign_stmt(&(root->child->child), tokens, numTokens);
				break;
			case str_assign_stmt:
				reduce_str_assign_stmt(&(root->child->child), tokens, numTokens);
				break;
		}
	} else {
		TreeNode *node_stmts = root->child->next->child;
		root->child = root->child->child;
		root->child->prev = NULL;
		root->child->next = node_stmts;
		node_stmts->parent = root;
		node_stmts->prev = root->child;
		node_stmts->next = NULL;
		switch(root->child->sym){
			case decl_stmt:
				reduce_decl_stmt(&(root->child), tokens, numTokens);
				break;
			case cond_stmt:
				reduce_cond_stmt(&(root->child), tokens, numTokens);
				break;
			case loop_stmt:
				reduce_loop_stmt(&(root->child), tokens, numTokens);
				break;
			case proc_call_stmt:
				reduce_proc_call_stmt(&(root->child), tokens, numTokens);
				break;
			case io_stmt:
				reduce_io_stmt(&(root->child), tokens, numTokens);
				break;
			case assign_stmt:
				reduce_assign_stmt(&(root->child), tokens, numTokens);
				break;
			case mat_assign_stmt:
				reduce_mat_assign_stmt(&(root->child), tokens, numTokens);
				break;
			case str_assign_stmt:
				reduce_str_assign_stmt(&(root->child), tokens, numTokens);
				break;
		}
		reduce_stmts(&(node_stmts), tokens, numTokens);
	}
}

void reduce_decl_stmts(TreeNode **currNode, TokenList tokens, int numTokens){
	TreeNode *root = *currNode;
	if (root->child->next->child->sym == EPSILON) {
		root->child->prev = root->prev;
		root->child->next = root->next;
		root->child->parent = root->parent;
		if (root->prev == NULL) root->parent->child = root->child;
		else root->prev->next = root->child;
		reduce_decl_stmt(&(root->child), tokens, numTokens);
	} else {
		root->child->next = root->child->next->child;
		root->child->next->prev = root->child;
		root->child->next->parent = root;
		root->child->next->next = NULL;
		reduce_decl_stmt(&(root->child), tokens, numTokens);
		reduce_decl_stmts(&(root->child->next), tokens, numTokens);
	}
}

void reduce_decl_stmt(TreeNode **currNode, TokenList tokens, int numTokens){
	TreeNode *root = *currNode;
	root->child->next->next = NULL;
	reduce_type(&(root->child), tokens, numTokens);
	reduce_id_list(&(root->child->next), tokens, numTokens);
}

void reduce_type(TreeNode **currNode, TokenList tokens, int numTokens){
	TreeNode *root = *currNode;
	if(root->child->sym == basic_type) {
		root->sym = root->child->child->sym;
		root->value = root->child->child->value;
		root->child = root->prev = NULL;
	} else if (root->child->sym == STRING) {
		root->sym = root->child->sym;
		root->value = root->child->value;
		root->child = root->prev = NULL;
	} else if (root->child->sym == REC) {
		recTypeIDInfo *rec_temp = malloc(sizeof(recTypeIDInfo));
		rec_temp->info = root->child->next->value;
		rec_temp->comp = NULL;
		root->sym = root->child->sym;
		root->value = rec_temp;
		root->child = root->prev = NULL;
	} else {
		matTypeIDInfo *mat_temp = malloc(sizeof(matTypeIDInfo));
		int rows, cols;
		root->sym = root->child->sym;
		mat_temp->type = (*((TokenInfo**)root->child->next->next->child->value))->lexeme;
		// printf("TYPE: %s\n", mat_temp->type);
		reduce_dims(&(root->child->next->next->next->next->next), &rows, &cols, tokens, numTokens);
		mat_temp->rows = rows;
		mat_temp->cols = cols;
		root->value = mat_temp;
		root->child = root->prev = NULL;
	}
}

void reduce_id_list(TreeNode **currNode, TokenList tokens, int numTokens) {
	TreeNode *root = *currNode;
	LL_Node *list = NULL;
	TreeNode *node_id_list = root->child->next;
	LL_insert(&list, root->child->value);
	while(node_id_list->child->sym == COMMA) {
		LL_insert(&list, node_id_list->child->next->child->value);
		node_id_list = node_id_list->child->next->child->next;
	}
	root->value = list;
	root->child = NULL;
}

void reduce_dims(TreeNode **currNode, int *rows, int *cols, TokenList tokens, int numTokens){
	TreeNode *root = *currNode;
	TokenInfo **p = (TokenInfo **)(root->child->child->value);
	*rows = atoi((*p)->lexeme);
	TreeNode *node_dim_list = root->child->next;
	switch(node_dim_list->child->sym){
		case EPSILON:
			*cols = 0;
			break;
		case COMMA:
			p = (TokenInfo **)(node_dim_list->child->next->child->value);
			*cols = atoi((*p)->lexeme);
			break;
	}
}

void reduce_conds(TreeNode **currNode, TokenList tokens, int numTokens){
	TreeNode *root = *currNode;
	TreeNode *cond1 = NULL;
	TreeNode *log_op = NULL;
	TreeNode *cond2 = NULL;
	TreeNode *elem1 = NULL;
	TreeNode *elem2 = NULL;
	TreeNode *rel_op = NULL;
	TreeNode *node_cond = NULL;
	switch(root->child->sym){
		case LPAREN:
			cond1 = root->child->next;
			log_op = cond1->next->next;
			cond2 = log_op->next->next;
			root->sym = log_op->child->sym;
			root->value = log_op->child->value;
			root->child = cond1;
			cond1->next = cond2;
			cond2->prev = cond1;
			cond1->prev = cond2->next = NULL;
			reduce_conds(&cond1, tokens, numTokens);
			reduce_conds(&cond2, tokens, numTokens);
			break;
		case elem:
			elem1 = root->child;
			rel_op = elem1->next;
			elem2 = rel_op->next;
			root->sym = rel_op->child->sym;
			root->value = rel_op->child->value;
			root->child = elem1;
			elem1->next = elem2;
			elem2->prev = elem1;
			reduce_elem(&elem1, tokens, numTokens);
			reduce_elem(&elem2, tokens, numTokens);
			break;
		case NOT:
			node_cond = root->child->next->next;
			root->sym = root->child->sym;
			root->value = root->child->value;
			root->child = node_cond;
			node_cond->next = node_cond->prev = NULL;
			reduce_conds(&node_cond, tokens, numTokens);
			break;
		case BOOL_LIT:
			root->sym = root->child->sym;
			root->value = root->child->value;
			root->child = NULL;
			break;
	}
}

void reduce_elem(TreeNode **currNode, TokenList tokens, int numTokens){
	TreeNode *root = *currNode;
	if(root->child->sym == var) {
		root->child->prev = root->prev;
		root->child->next = root->next;
		root->child->parent = root->parent;
		if (root->prev == NULL) root->parent->child = root->child;
		else root->prev->next = root->child;
		reduce_var(&(root->child), tokens, numTokens);
	} else {
		root->sym = root->child->sym;
		root->value = root->child->value;
		root->child = NULL;
	}
}

void reduce_cond_stmt(TreeNode **currNode, TokenList tokens, int numTokens){
	TreeNode *root = *currNode;
	TreeNode *node_cond = root->child->next->next;
	TreeNode *node_stmts = node_cond->next->next->next;
	TreeNode *node_elseif = node_stmts->next;
	TreeNode *node_else = node_elseif->next;
	root->sym = root->child->sym;
	root->value = root->child->value;
	root->child = node_cond;
	node_cond->prev = NULL;
	node_cond->next = node_stmts;
	node_stmts->prev = node_cond;
	if (node_elseif->child->sym == EPSILON) {
		if (node_else->child->sym == ENDIF) {
			node_stmts->next = NULL;
			reduce_conds(&node_cond, tokens, numTokens);
			reduce_stmts(&node_stmts, tokens, numTokens);
		} else {
			node_stmts->next = node_else;
			node_else->prev = node_stmts;
			node_else->next = NULL;
			reduce_conds(&node_cond, tokens, numTokens);
			reduce_stmts(&node_stmts, tokens, numTokens);
			reduce__cond_stmt(&(node_else), tokens, numTokens);
		}
	} else {
		node_stmts->next = node_elseif;
		node_elseif->prev = node_stmts;
		if (node_stmts->next->next->child->sym == ENDIF) {
			node_elseif->next = NULL;
			reduce_conds(&node_cond, tokens, numTokens);
			reduce_stmts(&node_stmts, tokens, numTokens);
			reduce_elseif(&(node_elseif), tokens, numTokens);
		} else {
			node_elseif->next = node_else;
			node_else->prev = node_elseif;
			node_else->next = NULL;
			reduce_conds(&node_cond, tokens, numTokens);
			reduce_stmts(&node_stmts, tokens, numTokens);
			reduce_elseif(&(node_elseif), tokens, numTokens);
			reduce__cond_stmt(&(node_else), tokens, numTokens);
		}
	}
}

void reduce_elseif(TreeNode **currNode, TokenList tokens, int numTokens) {
	TreeNode *root = *currNode;
	TreeNode *node_cond = root->child->next->next;
	TreeNode *node_stmts = node_cond->next->next->next;
	TreeNode *node_elseif = node_stmts->next;
	root->sym = root->child->sym;
	root->value = root->child->value;
	root->child = node_cond;
	node_cond->prev = NULL;
	node_cond->next = node_stmts;
	node_stmts->prev = node_cond;
	if (node_stmts->next->child->sym == EPSILON) {
		node_stmts->next = NULL;
		reduce_conds(&node_cond, tokens, numTokens);
		reduce_stmts(&node_stmts, tokens, numTokens);
	} else {
		node_stmts->next = node_elseif;
		node_elseif->prev = node_stmts;
		node_elseif->next = NULL;
		reduce_conds(&node_cond, tokens, numTokens);
		reduce_stmts(&node_stmts, tokens, numTokens);
		reduce_elseif(&(node_elseif), tokens, numTokens);
	}
}

void reduce__cond_stmt(TreeNode **currNode, TokenList tokens, int numTokens) {
	TreeNode *root = *currNode;
	root->sym = root->child->sym;
	root->value = root->child->value;
	root->child = root->child->next->next;
	root->child->prev = root->child->next = NULL;
	reduce_stmts(&(root->child), tokens, numTokens);
}

void reduce_io_stmt(TreeNode **currNode, TokenList tokens, int numTokens){
	TreeNode *root = *currNode, *param = NULL;
	root->sym = root->child->sym;
	root->value = root->child->value;
	param = root->child->next->next;
	root->child = param;
	param->next = NULL;
	param->prev = NULL;
	if(root->sym == GET){
		reduce_var(&param, tokens, numTokens);
	} else {
		if (param->child->sym == var) {
			root->child = param->child;
			root->child->next = root->child->prev = NULL;
			reduce_var(&(root->child), tokens, numTokens);
		} else {
			param->sym = param->child->sym;
			param->value = param->child->value;
			param->child = NULL;
		}
	}
}

void reduce_var(TreeNode **currNode, TokenList tokens, int numTokens){
	TreeNode *root = *currNode;
	TreeNode *node_var = root->child->next;
	if (node_var->child->sym == EPSILON) {
		root->sym = ID_PRI;
		root->value = root->child->value;
	} else if (node_var->child->sym == LSQ) {
		root->sym = ID_MAT_RHS;
		matAssignRHSInfo *mat_temp = malloc(sizeof(matAssignRHSInfo));
		TreeNode * node_dims = node_var->child->next;
		mat_temp->info = root->child->value;
		mat_temp->rowSym = node_dims->child->child->sym;
		mat_temp->rows = node_dims->child->child->value;
		TreeNode *node_dim_list = node_dims->child->next;
		switch(node_dim_list->child->sym){
			case EPSILON:
				mat_temp->cols = NULL;
				break;
			case COMMA:
				mat_temp->colSym = node_dim_list->child->next->child->sym;
				mat_temp->cols = node_dim_list->child->next->child->value;
				break;
		}
		root->value = mat_temp;
	} else {
		root->sym = ID_REC_RHS;
		recTypeIDInfo *rec_temp = malloc(sizeof(recTypeIDInfo));
		rec_temp->info = root->child->value;
		rec_temp->comp = root->child->next->child->next->value;
		root->value = rec_temp;
	}
	root->child = NULL;
}

void reduce_proc_call_stmt(TreeNode **currNode, TokenList tokens, int numTokens){
	TreeNode *root = *currNode;
	TreeNode *argParam = root->child->next->next->next;
	TreeNode *retParam = argParam->next->next->next->next;
	root->sym = root->child->sym;
	root->value = root->child->next->value;
	root->child = argParam;
	argParam->prev = NULL;
	argParam->next = retParam;
	retParam->prev = argParam;
	retParam->next = NULL;
	if(argParam->child->sym == EPSILON) {
		argParam->value = NULL;
		argParam->child = NULL;
	} else {
		root->child = argParam->child;
		root->child->prev = NULL;
		root->child->next = retParam;
		retParam->prev = root->child;
		root->child->parent = root;
		reduce_arg_list(&(root->child), tokens, numTokens);
	}
	if(retParam->child->sym == EPSILON) {
		retParam->value = NULL;
		retParam->child = NULL;
	} else {
		root->child->next = retParam->child;
		root->child->next->prev = root->child;
		root->child->next->next = NULL;
		root->child->next->parent = root;
		reduce_arg_list(&(root->child->next), tokens, numTokens);
	}
}

void reduce_arg_list(TreeNode **currNode, TokenList tokens, int numTokens){
	TreeNode *root = *currNode;
	if (root->child->next->child->sym == EPSILON) {
		root->sym = ID_PRI;
		root->value = root->child->value;
		root->child = NULL;
	} else if (root->child->next->child->sym == LSQ) {
		root->sym = ID_MAT;
		matTypeIDInfo *mat_temp = malloc(sizeof(matTypeIDInfo));
		int rows, cols;
		TreeNode *node_dims = root->child->next->child->next;
		TreeNode *node_arg_list_2 = node_dims->next->next;
		reduce_dims(&node_dims, &rows, &cols, tokens, numTokens);
		mat_temp->info = root->child->value;
		mat_temp->rows = rows;
		mat_temp->cols = cols;
		root->value = mat_temp;
		if (node_arg_list_2->child->sym == EPSILON) {
			root->child = NULL;
		} else {
			root->child = node_arg_list_2->child->next;
			root->child->parent = root;
			root->child->prev = NULL;
			root->child->next = NULL;
			reduce_arg_list(&(root->child), tokens, numTokens);
		}
	} else if (root->child->next->child->sym == DOT) {
		root->sym = ID_REC;
		recTypeIDInfo *rec_temp = malloc(sizeof(recTypeIDInfo));
		rec_temp->info = root->child->value;
		rec_temp->comp = root->child->next->child->next->value;
		root->value = rec_temp;
		TreeNode *node_arg_list_2 = root->child->next->child->next->next;
		if (node_arg_list_2->child->sym == EPSILON) {
			root->child = NULL;
		} else {
			root->child = node_arg_list_2->child->next;
			root->child->parent = root;
			root->child->prev = NULL;
			root->child->next = NULL;
			reduce_arg_list(&(root->child), tokens, numTokens);
		}
	} else if (root->child->next->child->sym == COMMA) {
		root->sym = ID_PRI;
		root->value = root->child->value;
		root->child = root->child->next->child->next;
		root->child->parent = root;
		root->child->prev = NULL;
		root->child->next = NULL;
		reduce_arg_list(&(root->child), tokens, numTokens);
	}
}

void reduce_loop_stmt(TreeNode **currNode, TokenList tokens, int numTokens){
	TreeNode *root = *currNode;
	TreeNode *assignList1 = root->child->next->next;
	TreeNode *node_conds = assignList1->next->next->next;
	TreeNode *assignList2 = node_conds->next->next->next;
	TreeNode *iloopStmts = assignList2->next->next->next;
	root->sym = root->child->sym;
	root->value = root->child->value;
	root->child = assignList1;
	assignList1->prev = NULL;
	assignList1->next = node_conds;
	node_conds->prev = assignList1;
	node_conds->next = assignList2;
	assignList2->prev = node_conds;
	if (iloopStmts->child->sym == EPSILON) {
		assignList2->next = NULL;
		reduce_assign_list(&(assignList1), tokens, numTokens);
		reduce_conds(&(node_conds), tokens, numTokens);
		reduce_assign_list(&(assignList2), tokens, numTokens);
	} else {
		assignList2->next = iloopStmts;
		iloopStmts->prev = assignList2;
		iloopStmts->next = NULL;
		reduce_assign_list(&(assignList1), tokens, numTokens);
		reduce_conds(&(node_conds), tokens, numTokens);
		reduce_assign_list(&(assignList2), tokens, numTokens);
		reduce_iloop_stmts(&(iloopStmts), tokens, numTokens);
	}
}

void reduce_assign_list(TreeNode **currNode, TokenList tokens, int numTokens) {
	TreeNode *root = *currNode;
	if (root->child->next->child->sym == EPSILON) {
		root->child->prev = root->prev;
		root->child->next = root->next;
		root->child->parent = root->parent;
		if (root->prev == NULL) root->parent->child = root->child;
		else root->prev->next = root->child;
		reduce_assign_stmt(&(root->child), tokens, numTokens);
	} else {
		reduce_assign_stmt(&(root->child), tokens, numTokens);
		reduce_assign_list(&(root->child->next), tokens, numTokens);
	}
}

void reduce_iloop_stmts(TreeNode **currNode, TokenList tokens, int numTokens) {
	TreeNode *root = *currNode;
	if (root->child->next->child->sym == EPSILON) {
		if (root->child->child->sym == stmt) {
			root->child->child->prev = NULL;
			root->child->child->next = NULL;
			root->child->child->parent = root;
			root->child = root->child->child;
			switch(root->child->child->sym){
				case decl_stmt:
					reduce_decl_stmt(&(root->child->child), tokens, numTokens);
					break;
				case cond_stmt:
					reduce_cond_stmt(&(root->child->child), tokens, numTokens);
					break;
				case loop_stmt:
					reduce_loop_stmt(&(root->child->child), tokens, numTokens);
					break;
				case proc_call_stmt:
					reduce_proc_call_stmt(&(root->child->child), tokens, numTokens);
					break;
				case io_stmt:
					reduce_io_stmt(&(root->child->child), tokens, numTokens);
					break;
				case assign_stmt:
					reduce_assign_stmt(&(root->child->child), tokens, numTokens);
					break;
				case mat_assign_stmt:
					reduce_mat_assign_stmt(&(root->child->child), tokens, numTokens);
					break;
				case str_assign_stmt:
					reduce_str_assign_stmt(&(root->child->child), tokens, numTokens);
					break;
			}
		} else {
			root->sym = root->child->child->sym;
			root->value = root->child->child->value;
			root->child = root->child->child->next->next;
			root->child->parent = root;
			root->child->prev = root->child->next = NULL;
			reduce_conds(&(root->child), tokens, numTokens);
		}
	} else {
		if (root->child->child->sym == stmt) {
			TreeNode *node_stmt = root->child->child;
			node_stmt->prev = NULL;
			node_stmt->next = root->child->next;
			node_stmt->parent = root;
			root->child = node_stmt;
			switch(root->child->child->sym){
				case decl_stmt:
					reduce_decl_stmt(&(root->child->child), tokens, numTokens);
					break;
				case cond_stmt:
					reduce_cond_stmt(&(root->child->child), tokens, numTokens);
					break;
				case loop_stmt:
					reduce_loop_stmt(&(root->child->child), tokens, numTokens);
					break;
				case proc_call_stmt:
					reduce_proc_call_stmt(&(root->child->child), tokens, numTokens);
					break;
				case io_stmt:
					reduce_io_stmt(&(root->child->child), tokens, numTokens);
					break;
				case assign_stmt:
					reduce_assign_stmt(&(root->child->child), tokens, numTokens);
					break;
				case mat_assign_stmt:
					reduce_mat_assign_stmt(&(root->child->child), tokens, numTokens);
					break;
				case str_assign_stmt:
					reduce_str_assign_stmt(&(root->child->child), tokens, numTokens);
					break;
			}
		} else {
			root->child->sym = root->child->child->sym;
			root->child->value = root->child->child->value;
			root->child->child = root->child->child->next->next;
			root->child->child->parent = root->child;
			root->child->child->prev = root->child->child->next = NULL;
			reduce_conds(&(root->child->child), tokens, numTokens);
		}
		reduce_iloop_stmts(&(root->child->next), tokens, numTokens);
	}
}

void reduce_assign_stmt(TreeNode **currNode, TokenList tokens, int numTokens){
	TreeNode *root = *currNode;
	TreeNode *node_var = root->child->next;
	TreeNode *node_expr = node_var->next->next;
	root->sym = root->child->sym;
	root->value = root->child->value;
	root->child = node_var;
	node_var->prev = NULL;
	node_var->next = node_expr;
	node_expr->next = NULL;
	node_expr->prev = node_var;
	reduce_var(&node_var, tokens, numTokens);
	reduce_expr(&node_expr, tokens, numTokens);
}

void reduce_expr(TreeNode **currNode, TokenList tokens, int numTokens) {
	TreeNode *root = *currNode;
	int start = 0, end = 0;
	while ((tokenIndex < numTokens) && ((*(tokens+tokenIndex))->token != TK_ASSIGN)) {
		tokenIndex++;
	}
	while ((tokenIndex < numTokens) && ((*(tokens+tokenIndex))->token != TK_ASSIGN_OP)) {
		tokenIndex++;
	}
	start = tokenIndex + 1;
	while ((tokenIndex < numTokens) && ((*(tokens+tokenIndex))->token != TK_SEMICOLON)) {
		tokenIndex++;
	}
	end = tokenIndex;

	if (tokenIndex < numTokens) {
		if (((end - start) == 3) && ((*(tokens+start+1))->token == TK_DOT)) {
			root->sym = ID_REC_RHS;
			recTypeIDInfo *rec_temp = malloc(sizeof(recTypeIDInfo));
			rec_temp->info = root->child->child->child->child->child->value;
			rec_temp->comp = root->child->child->child->child->child->next->child->next->value;
			root->value = rec_temp;
			root->child = NULL;
		} else if ((*(tokens+start+1))->token == TK_LSQ) {
			root->sym = ID_MAT_RHS;
			matAssignRHSInfo *mat_temp = malloc(sizeof(matAssignRHSInfo));
			TreeNode *node_dims = root->child->child->child->child->child->next->child->next;
			mat_temp->info = root->child->child->child->child->child->value;
			mat_temp->rowSym = node_dims->child->child->sym;
			mat_temp->rows = node_dims->child->child->value;
			TreeNode *node_dim_list = node_dims->child->next;
			switch(node_dim_list->child->sym){
				case EPSILON:
					mat_temp->cols = NULL;
					break;
				case COMMA:
					mat_temp->colSym = node_dim_list->child->next->child->sym;
					mat_temp->cols = node_dim_list->child->next->child->value;
					break;
			}
			root->value = mat_temp;
			root->child = NULL;
		} else {
			get_expr_AST(&root, tokens, start, end);
		}
	}
}

int getIndex (Token t) {
	switch (t) {
		case TK_MINUS:	return 0;
		case TK_PLUS:	return 1;
		case TK_MUL:	return 2;
		case TK_DIV:	return 3;
		case TK_MOD:	return 4;
		case TK_POW:	return 5;
	}
}

void get_expr_AST(TreeNode **currNode, TokenList tokens, const int start, const int end) {
	TreeNode *root = *currNode;
	int length = end - start, index = start, i, prev = 0;
	typedef struct{
		int assoc;
		int precedence;
	} SignInfo;
	SignInfo info[6];
	info[0].assoc = 0;
	info[1].assoc = 0;
	info[2].assoc = 0;
	info[3].assoc = 0;
	info[4].assoc = 0;
	info[5].assoc = 1;
	info[0].precedence = 2;
	info[1].precedence = 2;
	info[2].precedence = 3;
	info[3].precedence = 3;
	info[4].precedence = 3;
	info[5].precedence = 4;
	Toks *queue = NULL;
	Toks *stack = NULL;
	while (index < end) {
		Token t = (*(tokens+index))->token;
		if ((t == TK_INT_LIT) || (t == TK_BOOL_LIT) || (t == TK_REAL_LIT) || (t == CHAR_LIT) || (t == TK_ID)) {
			pushToken(&queue, *(tokens+index));
			index++;
		} else if ((t == TK_MINUS) || (t == TK_PLUS) || (t == TK_MUL) || (t == TK_DIV) || (t == TK_MOD) || (t == TK_POW)) {
			while ((!isEmptyStack(stack)) && (topToken(stack)->token != TK_LPAREN) && (topToken(stack)->token != TK_RPAREN) && (((info[getIndex(t)].assoc == 0) && (info[getIndex(t)].precedence <= info[getIndex(topToken(stack)->token)].precedence)) || ((info[getIndex(t)].assoc == 1) && (info[getIndex(t)].precedence < info[getIndex(topToken(stack)->token)].precedence)))) {
				pushToken(&queue, topToken(stack));
				popToken(&stack);
			}
			pushToken(&stack, *(tokens+index));
			index++;
		} else if (t == TK_LPAREN) {
			pushToken(&stack, *(tokens+index));
			index++;
		} else if (t == TK_RPAREN) {
			while (topToken(stack)->token != TK_LPAREN) {
				pushToken(&queue, topToken(stack));
				popToken(&stack);
			}
			popToken(&stack);
			index++;
		}
	}
	while (!isEmptyStack(stack)) {
		pushToken(&queue, topToken(stack));
		popToken(&stack);
	}
	prev = ListIndexGlobal;
	for (i = 0; (i < length) && (!isEmptyStack(queue)); ListIndexGlobal++, i++) {
		Tokenlist[ListIndexGlobal] = topToken(queue);
		popToken(&queue);
	}
	length = ListIndexGlobal - prev;
	ListIndexGlobal = prev;
	i = 0;
	root->sym = (Symbol)(Tokenlist[ListIndexGlobal]->token);
	root->value = &(Tokenlist[ListIndexGlobal]);
	ListIndexGlobal++;
	i++;
	root->child = NULL;
	TreeNode *cNode = root;
	while (i < length) {
		Tree node = createTree((Symbol)(Tokenlist[ListIndexGlobal]->token));
		node->value = &(Tokenlist[ListIndexGlobal]);
		ListIndexGlobal++;
		i++;
		if (cNode->child == NULL) {
			cNode->child = node;
			node->parent = cNode;
			if ((node->sym == MINUS) || (node->sym == PLUS) || (node->sym == MUL) || (node->sym == DIV) || (node->sym == MOD) || (node->sym == POW)) 
				cNode = node;
		} else if (cNode->child->next == NULL) {	
			cNode->child->prev = node;
			node->parent = cNode;
			cNode->child->prev->next = cNode->child;
			cNode->child = node;
			if ((node->sym == MINUS) || (node->sym == PLUS) || (node->sym == MUL) || (node->sym == DIV) || (node->sym == MOD) || (node->sym == POW)) 
				cNode = node;
			else {
				cNode = cNode->parent;
				while (cNode->child->next != NULL) {
					cNode = cNode->parent;
				}
			}
		}
	}
}

void printStackContent(Toks* head) {
	Toks *p = head;
	while (p != NULL) {
		printf("%s ", tokenToStr(p->token));
		p = p->next;
	}
	printf("\n");
}

void pushToken(Toks** head, TokenInfo *tok) {
	Toks *temp;
	temp = (Toks *)malloc(sizeof(Toks));
	temp->token = tok->token;
	strcpy(temp->lexeme, "");
	strcpy(temp->lexeme, tok->lexeme);
	temp->lineno = tok->lineno;
	temp->next = NULL;
	if (*head == NULL)
		*head = temp;
	else {
		temp->next = *head;
		*head = temp;
	}
}

void popToken(Toks** head) {
	Toks* p = *head;
	if(p != NULL) {
		*head = p->next;
		free(p);
	}
}

TokenInfo* topToken(Toks* head) {
	if(head == NULL) return -1;
	TokenInfo *temp = (TokenInfo *)malloc(sizeof(TokenInfo));
	temp->token = head->token;
	strcpy(temp->lexeme, "");
	strcpy(temp->lexeme, head->lexeme);
	temp->lineno = head->lineno;
	return temp;
}

bool isEmptyStack(Toks* head){
	if (head == NULL) return true;
	else return false;
}

void reduce_mat_assign_stmt(TreeNode **currNode, TokenList tokens, int numTokens){
	TreeNode *root = *currNode;
	TreeNode *node_mat_stmt = root->child->next->next->next;
	root->sym = root->child->sym;
	root->value = root->child->next->value;
	root->child = node_mat_stmt;
	node_mat_stmt->prev = node_mat_stmt->next = NULL;
	if(node_mat_stmt->child->sym == LCURL) {
		TreeNode *node_row_list = node_mat_stmt->child->next;
		node_row_list->prev = node_mat_stmt->prev;
		node_row_list->next = node_mat_stmt->next;
		node_row_list->prev = node_row_list->next = NULL;
		if (node_mat_stmt->prev == NULL) node_mat_stmt->parent->child = node_row_list;
		else node_mat_stmt->prev->next = node_row_list;
		root->child = node_row_list;
		node_row_list->parent = root;
		reduce_row_list(&node_row_list, tokens, numTokens);
		compact_row_list(&node_row_list);
	} else {
		TreeNode *node__mat_stmt = node_mat_stmt->child->next;
		switch(node__mat_stmt->child->sym){
			case PLUS:
				node_mat_stmt->sym = node__mat_stmt->child->sym;
				node_mat_stmt->value = node__mat_stmt->child->value;
				node_mat_stmt->child->next = node__mat_stmt->child->next;
				node_mat_stmt->child->next->prev = node_mat_stmt->child;
				node_mat_stmt->child->next->next = NULL;
				node_mat_stmt->child->next->parent = node_mat_stmt;
				node_mat_stmt->child->sym = ID_MAT;
				node_mat_stmt->child->next->sym = ID_MAT;
				break;
			case MAT_ROWS:
			case MAT_COLS:
				node_mat_stmt->sym = node__mat_stmt->child->sym;
				node_mat_stmt->value = node_mat_stmt->child->value;
				node_mat_stmt->child = NULL;
				break;
		}
	}
}

void reduce_row_list(TreeNode **currNode, TokenList tokens, int numTokens){
	TreeNode *root = *currNode;
	TreeNode *node_row = root->child;
	TreeNode *node_row_list = root->child->next;
	if (node_row_list->child->sym == EPSILON) {
		node_row->prev = root->prev;
		node_row->next = root->next;
		node_row->parent = root->parent;
		if (root->prev == NULL) root->parent->child = node_row;
		else root->prev->next = node_row;
		reduce_row(&node_row, tokens, numTokens);
	} else {
		reduce_row(&node_row, tokens, numTokens);
		reduce__row_list(&node_row_list, tokens, numTokens);
	}
}

void compact_row_list(TreeNode **root){
	TreeNode *q = *root;
	TreeNode *p = (*root)->child;
	int count = 0;
	/* Case when there is only one row*/
	if(p->next == NULL) {
		q->value = 1;
		return;
	}
	(*root)->child = NULL;
	while ( !(p->sym == row && p->next->sym == row) ){
		insertChild(*root, p->sym, p->value);
		p = p->next->child;
		count++;
	}
	insertChild(*root, p->sym, p->value);
	count++;
	insertChild(*root, p->next->sym, p->next->value);
	count++;
	q->value = count;
}

void reduce__row_list(TreeNode **currNode, TokenList tokens, int numTokens){
	TreeNode *root = *currNode;
	TreeNode *node_row = root->child->next;
	TreeNode *node_row_list = node_row->next;
	if (node_row_list->child->sym == EPSILON) {
		node_row->prev = root->prev;
		node_row->next = root->next;
		node_row->parent = root->parent;
		if (root->prev == NULL) root->parent->child = node_row;
		else root->prev->next = node_row;
		reduce_row(&node_row, tokens, numTokens);
	} else {
		root->child = node_row;
		node_row->prev = NULL;
		reduce_row(&node_row, tokens, numTokens);
		reduce__row_list(&node_row_list, tokens, numTokens);
	}
}

void reduce_row(TreeNode **currNode, TokenList tokens, int numTokens){
	TreeNode *root = *currNode;
	LL_Node *list = NULL;
	LL_insert(&list, root->child->child->value);
	TreeNode *node_row = root->child->next;
	while(node_row->child->sym != EPSILON){
		LL_insert(&list, node_row->child->next->child->value);
		node_row = node_row->child->next->next;
	}
	root->value = list;
	root->child = NULL;
}


void reduce_terminal(TreeNode **currNode, TokenList tokens, int numTokens){
	TreeNode *root = *currNode;
	if(root->prev == NULL){
		root->parent->child = root->next;
		if(root->next != NULL)root->next->prev = NULL;
	} else {
		root->prev->next = root->next;
		if(root->next != NULL) root->next->prev = root->prev;
	}
}

void reduce_str_assign_stmt(TreeNode **currNode, TokenList tokens, int numTokens){
	TreeNode *root = *currNode;
	TreeNode *node_str_stmt = root->child->next->next->next;
	TreeNode *node__str_stmt = NULL;
	TreeNode *node_ind = NULL;
	root->sym = root->child->sym;
	root->value = root->child->next->value;
	root->child = node_str_stmt;
	node_str_stmt->next = NULL;
	node_str_stmt->prev = NULL;
	if (node_str_stmt->child->sym == STR_LIT) {
		node_str_stmt->sym = node_str_stmt->child->sym;
		node_str_stmt->value = node_str_stmt->child->value;
		node_str_stmt->child = NULL;
	} else {
		node__str_stmt = node_str_stmt->child->next;
		if (node__str_stmt->child->sym == SEMICOLON) {
			node_str_stmt->sym = node_str_stmt->child->sym;
			node_str_stmt->value = node_str_stmt->child->value;
			node_str_stmt->child = NULL;
		} else if (node__str_stmt->child->sym == PLUS) {
			node_str_stmt->sym = node__str_stmt->child->sym;
			node_str_stmt->value = node__str_stmt->child->value;
			node_str_stmt->child->next = node__str_stmt->child->next;
			node_str_stmt->child->next->prev = node_str_stmt->child;
			node_str_stmt->child->next->next = NULL;
			node_str_stmt->child->next->parent = node_str_stmt;
		} else if (node__str_stmt->child->sym == STR_LENGTH) {
			node_str_stmt->sym = node__str_stmt->child->sym;
			node_str_stmt->value = node__str_stmt->child->value;
			node_str_stmt->child->next = NULL;
		} else {
			node_ind = node__str_stmt->child->next;
			node_str_stmt->sym = node_ind->child->sym;
			node_str_stmt->value = node_ind->child->value;
			node_str_stmt->child->next = NULL;
		}
	}
}