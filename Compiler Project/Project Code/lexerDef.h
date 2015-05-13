/********************************
       |TEAM-1 | GROUP-20|
UTKARSH PATHRABE  - 2012A7PS034P
SHIKHAR VASHISHTH - 2012C6PS436P
********************************/
#ifndef LEXERDEF_H_INCLUDED
#define LEXERDEF_H_INCLUDED

#include "commonHeader.h"
#define MAX_LEXEME 200

typedef enum {
	TK_PASS, TK_EXECUTE, TK_COLON, TK_END, TK_RECBLK, TK_ENDRECBLK, TK_REC, TK_ID, TK_ENDREC, TK_PROCBLK,
	TK_ENDPROCBLK, TK_PROC, TK_LPAREN, TK_RPAREN, TK_ARROW, TK_ENDPROC, TK_COMMA, TK_SEMICOLON,
	TK_STRING, TK_MAT, TK_LT, TK_GT, TK_LSQ, TK_RSQ, TK_INT, TK_REAL, TK_BOOL, TK_CHAR,
	TK_IF, TK_ELIF, TK_ELSE, TK_ENDIF, TK_GET, TK_PUT, TK_ENDL, TK_TAB, TK_STR_LIT,
	TK_DOT, TK_CALL, TK_LOOP, TK_ENDLOOP, TK_BREAK, TK_CONTINUE, TK_NOT, TK_BOOL_LIT, TK_AND,
	TK_OR, TK_LE, TK_GE, TK_EQ, TK_NEQ, TK_INT_LIT, TK_REAL_LIT, TK_CHAR_LIT, TK_ASSIGN, TK_ASSIGN_OP,
	TK_MINUS, TK_PLUS, TK_MUL, TK_DIV, TK_MOD, TK_POW, TK_MATASSIGN, TK_LCURL, TK_RCURL, TK_MAT_ROWS,
	TK_MAT_COLS, TK_STRASSIGN, TK_STR_LENGTH
} Token;

/* Token info */
typedef struct {
	char lexeme[MAX_LEXEME];
	Token token;
	int lineno;
} TokenInfo;

typedef TokenInfo** TokenList;

/* Reserved word table structure */
typedef struct {
	bool present;
	Token symbol;
	char lexeme[100];
} resWord;

typedef resWord* resTable;


#endif