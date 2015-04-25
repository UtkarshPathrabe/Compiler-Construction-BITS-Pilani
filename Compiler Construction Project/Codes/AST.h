/********************************
       |TEAM-1 | GROUP-20|
UTKARSH PATHRABE  - 2012A7PS034P
SHIKHAR VASHISHTH - 2012C6PS436P
********************************/
#ifndef AST_H_INCLUDED
#define AST_H_INCLUDED

#include "parserDef.h"
#include "lexerDef.h"
#include "Tree.h"
#include "LinkedList.h"

TokenInfo * Tokenlist[2000];
int ListIndexGlobal;

struct tok;
typedef struct tok Toks;
struct tok{
	char lexeme[MAX_LEXEME];
	Token token;
	int lineno;
	Toks *next;
};

typedef struct {
	TokenInfo *info;
	int rows;
	int cols;
	char *type;
} matTypeIDInfo;

typedef struct{
	TokenInfo *info;
	Symbol rowSym;
	Symbol colSym;
	TokenInfo *rows;
	TokenInfo *cols;
} matAssignRHSInfo;

typedef struct {
	TokenInfo *info;
	TokenInfo *comp;
} recTypeIDInfo;


void constructAST(TreeNode *ast, TokenList tokens, int numTokens);
void reduce_program(TreeNode **currNode, TokenList tokens, int numTokens);
void reduce_execute(TreeNode **currNode, TokenList tokens, int numTokens);
void reduce_records(TreeNode **currNode, TokenList tokens, int numTokens);
void reduce_procedures(TreeNode **currNode, TokenList tokens, int numTokens);
void reduce_recs(TreeNode **currNode, TokenList tokens, int numTokens);
void reduce_procs(TreeNode **currNode, TokenList tokens, int numTokens);
void reduce_param_list(TreeNode **currNode, TokenList tokens, int numTokens);
void reduce_stmts(TreeNode **currNode, TokenList tokens, int numTokens);
void reduce_decl_stmts(TreeNode **currNode, TokenList tokens, int numTokens);
void reduce_decl_stmt(TreeNode **currNode, TokenList tokens, int numTokens);
void reduce_type(TreeNode **currNode, TokenList tokens, int numTokens);
void reduce_id_list(TreeNode **currNode, TokenList tokens, int numTokens);
void reduce_dims(TreeNode **currNode, int *rows, int *cols, TokenList tokens, int numTokens);
void reduce_conds(TreeNode **currNode, TokenList tokens, int numTokens);
void reduce_elem(TreeNode **currNode, TokenList tokens, int numTokens);
void reduce_cond_stmt(TreeNode **currNode, TokenList tokens, int numTokens);
void reduce_elseif(TreeNode **currNode, TokenList tokens, int numTokens);
void reduce__cond_stmt(TreeNode **currNode, TokenList tokens, int numTokens);
void reduce_io_stmt(TreeNode **currNode, TokenList tokens, int numTokens);
void reduce_var(TreeNode **currNode, TokenList tokens, int numTokens);
void reduce_proc_call_stmt(TreeNode **currNode, TokenList tokens, int numTokens);
void reduce_arg_list(TreeNode **currNode, TokenList tokens, int numTokens);
void reduce_loop_stmt(TreeNode **currNode, TokenList tokens, int numTokens);
void reduce_assign_list(TreeNode **currNode, TokenList tokens, int numTokens);
void reduce_iloop_stmts(TreeNode **currNode, TokenList tokens, int numTokens);
void reduce_assign_stmt(TreeNode **currNode, TokenList tokens, int numTokens);
void reduce_expr(TreeNode **currNode, TokenList tokens, int numTokens);
void get_expr_AST(TreeNode **currNode, TokenList tokens, const int start, const int end);
void reduce_mat_assign_stmt(TreeNode **currNode, TokenList tokens, int numTokens);
void reduce_row_list(TreeNode **currNode, TokenList tokens, int numTokens);
void reduce__row_list(TreeNode **currNode, TokenList tokens, int numTokens);
void reduce_row(TreeNode **currNode, TokenList tokens, int numTokens);
void reduce_str_assign_stmt(TreeNode **currNode, TokenList tokens, int numTokens);
void pushToken(Toks** head, TokenInfo *tok);
void popToken(Toks** head);
TokenInfo* topToken(Toks* head);
bool isEmptyStack(Toks* head);
int getIndex (Token t);

#endif