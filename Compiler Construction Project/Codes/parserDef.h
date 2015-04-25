/********************************
       |TEAM-1 | GROUP-20|
UTKARSH PATHRABE  - 2012A7PS034P
SHIKHAR VASHISHTH - 2012C6PS436P
********************************/
#ifndef PARSERDEF_H_INCLUDED
#define PARSERDEF_H_INCLUDED

#define INDEX(a) ((a) - (program) + 1)
#define NUM_RULES 142
#define NUM_NONTERM 69
#define NUM_TERM 69

typedef enum {
	EPSILON, EXECUTE, COLON, END, RECORDS, ENDRECORDS, REC, ID, ENDREC, PROCS, ENDPROCS,
	PROC, LPAREN, RPAREN, ARROW, ENDPROC, COMMA, SEMICOLON, STRING, MAT, LT, GT, LSQ,
	RSQ, INT, REAL, BOOL, CHAR, IF, ELIF, ELSE, ENDIF, GET, PUT, ENDL, TAB,
	STR_LIT, DOT, CALL, LOOP, ENDLOOP, BREAK, CONTINUE, NOT, BOOL_LIT, AND,
	OR, LE, GE, EQ, NEQ, INT_LIT, REAL_LIT, CHAR_LIT, ASSIGN, ASSIGN_OP, MINUS, PLUS,
	MUL, DIV, MOD, POW, MATASSIGN, LCURL, RCURL, MAT_ROWS, MAT_COLS, STRASSIGN, STR_LENGTH,
	program, execute, _records, records, recs, _recs, rec, _procedures, procedures, procs,
	_procs, proc, param_list, _param_list, stmts, _stmts, stmt, decl_stmts, _decl_stmts,
	decl_stmt, type, basic_type, id_list, _id_list, dims, _dim_list, cond_stmt, else_if,
	_cond_stmt, io_stmt, put_param, var, _var, proc_call_stmt, proc_arg_list, arg_list,
	arg_list1, arg_list2, loop_stmt, iloop_stmts, iloop_stmt, assign_list, conds, logical_op,
	rel_op, elem, assign_stmt, expr, _expr, term, _term, expo_term, _expo_term, factor,
	op_PlusMinus, op_mulDivMod, op_pow, mat_assign_stmt, mat_stmt, _mat_stmt, row_list,
	_row_list, row, _row, const_, str_assign_stmt, str_stmt, _str_stmt, ind, DOLLAR,
	ID_MAT, ID_REC, ID_PROC, ID_PRI, ID_MAT_RHS, ID_REC_RHS
} Symbol;

typedef struct node Node;
struct node {
	Symbol value;
	Node* next;
};

typedef Node* SymbolList;
typedef Node* SymbolStack;

typedef struct {
	Symbol lhs;
	SymbolList rhs;
} Rule;

typedef Rule* Rules;

typedef struct _LL_Node LL_Node;

struct _LL_Node{
	void *value;
	LL_Node *next;
};


#endif