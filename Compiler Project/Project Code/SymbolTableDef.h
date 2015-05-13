/********************************
       |TEAM-1 | GROUP-20|
UTKARSH PATHRABE  - 2012A7PS034P
SHIKHAR VASHISHTH - 2012C6PS436P
********************************/
#ifndef SYMBOLDEF_H_INCLUDED
#define SYMBOLDEF_H_INCLUDED
#include "parserDef.h"
#include "lexerDef.h"

#define SIZE 500
#define STR_MAXLEN 1000

/* TYPE */
typedef enum{
	INT_TYPE, CHAR_TYPE, REAL_TYPE, BOOL_TYPE, 
	MAT_TYPE, STR_TYPE, REC_TYPE, RECDEC_TYPE, 
	PROC_TYPE
} Type;

typedef struct _SymbolTable SymbolTable;
typedef struct _SymbolTable ST;

/* SYMBOL TABLE */
struct _SymbolTable{
	int id;
	void *entry[SIZE];
	Type type[SIZE];
	ST *next;
	ST *parent;
	ST *child;
	ST *prev;
};

/* INT, REAL, CHAR, BOOL*/
typedef struct{
	char *name;
	int decl_line;
	int ref_line;
	int offset;
	void *value;
	Type type;
} pri_var;

/* STRING*/
typedef struct{
	char *name;
	int decl_line;
	int ref_line;
	int offset;
	int len;
	char *value;
} str_var;

/* MATRIX */
typedef struct{
	char *name;
	int decl_line;
	int ref_line;
	int offset;
	int rows;
	int cols;
	Type type;
	void **value;
} mat_var;

/* RECORD declaration */
typedef struct{
	char *name;
	int decl_line;
	int offset;
	LL_Node *varList;
	int numEntries;
} rec_dec;

/* RECORD INSTANTIATION */
typedef struct{
	char *name;
	int decl_line;
	int ref_line;
	int offset;
	char *type_name;
	ST* type_st;
	int type_offset;
	LL_Node *varList;
} rec_var;

/* PROCEDURE DECLARATION */
typedef struct{
	char *name;
	int decl_line;
	int ref_line;
	int offset;
	ST *scope;
	LL_Node *inputList;
	LL_Node *outputList;
} proc_dec;

/* PROCEDURE ARGUMENT*/
typedef struct{
	char *name;
	Type type;
	void *value;
} proc_arg;

#endif