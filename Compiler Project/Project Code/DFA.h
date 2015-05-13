/********************************
       |TEAM-1 | GROUP-20|
UTKARSH PATHRABE  - 2012A7PS034P
SHIKHAR VASHISHTH - 2012C6PS436P
********************************/
#ifndef _DFA_H_
#define _DFA_H_

#include "lexerDef.h"

#define TOTAL_TRANS 50
#define TOTAL_STATES 56
#define FINAL_STATES 44


typedef enum {	
	ACT_ERROR, ACT_COLON, ACT_SEMICOLON, ACT_COMMA, ACT_LPAREN, ACT_RPAREN, ACT_LSQ, ACT_RSQ, 
	ACT_LCURL, ACT_RCURL, ACT_MINUS, ACT_ARROW, ACT_LT, ACT_LE, ACT_GT, ACT_GE, ACT_ASSIGN_OP, 
	ACT_EQ, ACT_NEQ, ACT_PLUS, ACT_MUL, ACT_POW, ACT_DIV, ACT_MOD, ACT_MAT_ROWS, ACT_MAT_COLS, 
	ACT_STR_LENGTH, ACT_STRING_LIT, ACT_CHAR_LIT, ACT_INT_LIT, ACT_REAL_LIT, ACT_DOT, ACT_ID, 
	ACT_BLANK, ACT_ENDOFFILE, ACT_RELOP_ER, ACT_MAT_ROWS_ER, ACT_MAT_COLS_ER, ACT_STR_LEN_ER, 
	ACT_STR_LIT_ER, ACT_CHAR_LIT_ER, ACT_NUM_LIT_ER, ACT_COMMENT, ACT_COMMENT_ER, ACT_CONTINUE
} Action;

typedef struct {
	bool (*is)(char); //a bool-returning and char-taking function pointer which is used to test whether this transition is to be taken.
	int toID;
} dfaTrans;

typedef struct {
	int ID; //unique ID associated with every state

	bool isFinal; //indicates whether any action should be taken when DFA is in this state
	Action action; //the string based on which action is taken

	int numTrans; //number of outgoing transitions excluding the default (other) transition
	dfaTrans trans[TOTAL_TRANS]; //list of outgoing transitions

	// int defaultID;
} dfaState;

typedef struct {
	int startID;
	int currID;
	int numStates;
	dfaState *states[TOTAL_STATES];
} DFA;

void DFA_construct(DFA *dfa);
DFA *DFA_createDFA();
void DFA_reset(DFA *dfa); //makes the dfa ready for consumption. i.e. sets the current state to start state.
Action DFA_makeNextTrans(DFA *dfa, char c);
void DFA_defState(DFA *dfa, dfaState *newState);
dfaState *DFA_newState(bool isFinal, Action finalAction);
void DFA_addTrans(DFA *dfa, int fromID, bool(*is)(char), int toID);

bool is_colon(char c);
bool is_semicolon(char c);
bool is_comma(char c);
bool is_openParen(char c);
bool is_closeParen(char c);
bool is_openSquare(char c);
bool is_closeSquare(char c);
bool is_openCurl(char c);
bool is_closeCurl(char c);
bool is_hypen(char c);
bool is_gt(char c);
bool is_lt(char c);
bool is_equal(char c);
bool is_exclaim(char c);
bool is_plus(char c);
bool is_asterik(char c);
bool is_not_asterik(char c);
bool is_forwardSlash(char c);
bool is_percent(char c);
bool is_atTheRate(char c);
bool is_r(char c);
bool is_o(char c);
bool is_w(char c);
bool is_s(char c);
bool is_c(char c);
bool is_l(char c);
bool is_e(char c);
bool is_n(char c);
bool is_g(char c);
bool is_t(char c);
bool is_h(char c);
bool is_doubleQuote(char c);
bool is_singleQuote(char c);
bool is_backSlash(char c);
bool is_dot(char c);
bool is_EOF(char c);
bool is_num(char c);
bool is_notNum(char c);
bool is_alpha(char c);
bool is_alphaSmall(char c);
bool is_alphaSmallOrSpace(char c);
bool is_char_lit(char c);
bool is_alphanumeric(char c);
bool is_anythingExceptNewLine(char c);
bool is_blank(char c);

#endif