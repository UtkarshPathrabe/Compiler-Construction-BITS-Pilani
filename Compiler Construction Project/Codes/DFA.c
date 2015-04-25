/********************************
       |TEAM-1 | GROUP-20|
UTKARSH PATHRABE  - 2012A7PS034P
SHIKHAR VASHISHTH - 2012C6PS436P
********************************/

#include "DFA.h"
#include "hashTable.h"

int lineno;

bool is_colon(char c) { return c == ':'; }
bool is_semicolon(char c) { return c == ';'; }
bool is_comma(char c) { return c == ','; }
bool is_openParen(char c) { return c == '('; }
bool is_closeParen(char c) { return c == ')'; }
bool is_openSquare(char c) { return c == '['; }
bool is_closeSquare(char c) { return c == ']'; }
bool is_openCurl(char c) { return c == '{'; }
bool is_closeCurl(char c) { return c == '}'; }
bool is_hypen(char c) { return c == '-'; }
bool is_gt(char c) { return c == '>'; }
bool is_lt(char c) { return c == '<'; }
bool is_equal(char c) { return c == '='; }
bool is_exclaim(char c) { return c == '!'; }
bool is_plus(char c) { return c == '+'; }
bool is_asterik(char c) { return c == '*'; }
bool is_not_asterik(char c) { return !is_asterik(c); }
bool is_forwardSlash(char c) { return c == '/'; }
bool is_percent(char c) { return c == '%'; }
bool is_atTheRate(char c) { return c == '@'; }
bool is_r(char c) { return c == 'r'; }
bool is_o(char c) { return c == 'o'; }
bool is_w(char c) { return c == 'w'; }
bool is_s(char c) { return c == 's'; }
bool is_c(char c) { return c == 'c'; }
bool is_l(char c) { return c == 'l'; }
bool is_e(char c) { return c == 'e'; }
bool is_n(char c) { return c == 'n'; }
bool is_g(char c) { return c == 'g'; }
bool is_t(char c) { return c == 't'; }
bool is_h(char c) { return c == 'h'; }
bool is_doubleQuote(char c) { return c == '\"'; }
bool is_singleQuote(char c) { return c == '\''; }
bool is_backSlash(char c) { return c == '\\'; }
bool is_dot(char c) { return c == '.'; }
bool is_EOF(char c) { return c == EOF; }
bool is_num(char c) { return (('0' <= c) && (c <= '9')); }
bool is_notNum(char c) { return !is_num(c); }
bool is_alpha(char c) { return (((c >= 'a') && (c <= 'z')) || ((c >= 'A' && c <= 'Z'))); }
bool is_alphaSmall(char c) { return (c >= 'a') && (c <= 'z'); }
bool is_alphaSmallOrSpace(char c) { return c == ' ' || is_alphaSmall(c); }
bool is_char_lit(char c) { return is_alphanumeric(c) || is_blank(c) || c == ':' || c == '!' || c == '@' || c == '#' || c == '$' || c == '%' || c == '^' || c == '&' || c == '*';}
bool is_alphanumeric(char c) { return is_alpha(c) || is_num(c); }
bool is_anythingExceptNewLine(char c) { return c != '\n' && c != '\r' && c != EOF; }
bool is_blank(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r'; }

Action DFA_makeNextTrans(DFA *dfa, char c) {
	int i;
	dfaState *currState = dfa->states[dfa->currID];

	for (i = 0; i < currState->numTrans; i++) {
		if (currState->trans[i].is(c)) {
			dfa->currID = currState->trans[i].toID;
			return ACT_CONTINUE;
		}
	}
	/* Take the default action*/
	dfa->currID = currState->action;
	return currState->action;
}


void DFA_addTrans(DFA *dfa, int fromID, bool(*is)(char), int toID) {
	dfaState *state = dfa->states[fromID];
	state->trans[state->numTrans].is = is;
	state->trans[state->numTrans].toID = toID;
	state->numTrans++;
}

void DFA_AddStateInfo(DFA *dfa, int stateID, bool isFinal, Action action){
	dfa->states[stateID]->isFinal = isFinal;
	dfa->states[stateID]->action = action;
}

void DFA_defState(DFA *dfa, dfaState *newState) {
	newState->ID = dfa->numStates;
	dfa->states[dfa->numStates] = newState;
	dfa->numStates++;
}

dfaState *DFA_newState(bool isFinal, Action action) {
	dfaState *newState = (dfaState *)malloc(sizeof(dfaState));
	newState->isFinal = isFinal;
	newState->action = action;
	newState->ID = -1;
	newState->numTrans = 0;
	return newState;
}

DFA *DFA_createDFA() {
	DFA *dfa = (DFA *)malloc(sizeof(DFA));
	dfa->numStates = 0;
	dfa->startID = -1;
	dfa->currID = -1;
	return dfa;
}

void DFA_reset(DFA *dfa) {
	dfa->currID = dfa->startID;
}

void DFA_construct(DFA *dfa) {

	int i;
	dfaState **states = (dfaState **)malloc(TOTAL_STATES * sizeof(dfaState *));

	for (i = 0; i < TOTAL_STATES; i++) {
		states[i] = DFA_newState(false, ACT_ERROR);
		DFA_defState(dfa, states[i]);
	}
	
	// Define transition
	DFA_addTrans(dfa, 0, is_colon, 1);
	DFA_addTrans(dfa, 0, is_semicolon, 2);
	DFA_addTrans(dfa, 0, is_comma, 3);
	DFA_addTrans(dfa, 0, is_openParen, 4);
	DFA_addTrans(dfa, 0, is_closeParen, 5);
	DFA_addTrans(dfa, 0, is_openSquare, 6);
	DFA_addTrans(dfa, 0, is_closeSquare, 7);
	DFA_addTrans(dfa, 0, is_openCurl, 8);
	DFA_addTrans(dfa, 0, is_closeCurl, 9);
	DFA_addTrans(dfa, 0, is_hypen, 10);
	DFA_addTrans(dfa, 10, is_gt, 11);
	DFA_addTrans(dfa, 0, is_lt, 12);
	DFA_addTrans(dfa, 12, is_equal, 13);
	DFA_addTrans(dfa, 0, is_gt, 14);
	DFA_addTrans(dfa, 14, is_equal, 15);
	DFA_addTrans(dfa, 0, is_equal, 16);
	DFA_addTrans(dfa, 16, is_equal, 17);
	DFA_addTrans(dfa, 0, is_exclaim, 18);
	DFA_addTrans(dfa, 18, is_equal, 19);
	DFA_addTrans(dfa, 0, is_plus, 20);
	DFA_addTrans(dfa, 0, is_asterik, 21);
	DFA_addTrans(dfa, 21, is_asterik, 22);
	DFA_addTrans(dfa, 0, is_forwardSlash, 23);
	DFA_addTrans(dfa, 23, is_asterik, 53);
	DFA_addTrans(dfa, 53, is_not_asterik, 53);
	DFA_addTrans(dfa, 53, is_asterik, 54);
	DFA_addTrans(dfa, 54, is_forwardSlash, 55);
	DFA_addTrans(dfa, 0, is_percent, 24);
	DFA_addTrans(dfa, 0, is_atTheRate, 25);
	DFA_addTrans(dfa, 25, is_r, 26);
	DFA_addTrans(dfa, 26, is_o, 27);
	DFA_addTrans(dfa, 27, is_w, 28);
	DFA_addTrans(dfa, 28, is_s, 29);
	DFA_addTrans(dfa, 25, is_c, 30);
	DFA_addTrans(dfa, 30, is_o, 31);
	DFA_addTrans(dfa, 31, is_l, 32);
	DFA_addTrans(dfa, 32, is_s, 33);
	DFA_addTrans(dfa, 25, is_l, 34);
	DFA_addTrans(dfa, 34, is_e, 35);
	DFA_addTrans(dfa, 35, is_n, 36);
	DFA_addTrans(dfa, 36, is_g, 37);
	DFA_addTrans(dfa, 37, is_t, 38);
	DFA_addTrans(dfa, 38, is_h, 39);
	DFA_addTrans(dfa, 0, is_doubleQuote, 40);
	DFA_addTrans(dfa, 40, is_char_lit, 40);
	DFA_addTrans(dfa, 40, is_doubleQuote, 41);
	DFA_addTrans(dfa, 40, is_backSlash, 42);
	DFA_addTrans(dfa, 42, is_doubleQuote, 40);
	DFA_addTrans(dfa, 0, is_singleQuote, 43);
	DFA_addTrans(dfa, 43, is_char_lit, 44);
	DFA_addTrans(dfa, 44, is_singleQuote, 45);
	DFA_addTrans(dfa, 0, is_num, 46);
	DFA_addTrans(dfa, 46, is_num, 46);
	DFA_addTrans(dfa, 46, is_dot, 47);
	DFA_addTrans(dfa, 47, is_num, 48);
	DFA_addTrans(dfa, 48, is_num, 48);
	DFA_addTrans(dfa, 0, is_dot, 49);
	DFA_addTrans(dfa, 0, is_alpha, 50);
	DFA_addTrans(dfa, 50, is_alphanumeric, 50);
	DFA_addTrans(dfa, 0, is_blank, 51);
	DFA_addTrans(dfa, 51, is_blank, 51);
	DFA_addTrans(dfa, 0, is_EOF, 52);

	DFA_AddStateInfo(dfa, 0, false, ACT_ERROR);
	DFA_AddStateInfo(dfa, 1, true, ACT_COLON);
	DFA_AddStateInfo(dfa, 2, true, ACT_SEMICOLON);
	DFA_AddStateInfo(dfa, 3, true, ACT_COMMA);
	DFA_AddStateInfo(dfa, 4, true, ACT_LPAREN);
	DFA_AddStateInfo(dfa, 5, true, ACT_RPAREN);
	DFA_AddStateInfo(dfa, 6, true, ACT_LSQ);
	DFA_AddStateInfo(dfa, 7, true, ACT_RSQ);
	DFA_AddStateInfo(dfa, 8, true, ACT_LCURL);
	DFA_AddStateInfo(dfa, 9, true, ACT_RCURL);
	DFA_AddStateInfo(dfa, 10, true, ACT_MINUS);
	DFA_AddStateInfo(dfa, 11, true, ACT_ARROW);
	DFA_AddStateInfo(dfa, 12, true, ACT_LT);
	DFA_AddStateInfo(dfa, 13, true, ACT_LE);
	DFA_AddStateInfo(dfa, 14, true, ACT_GT);
	DFA_AddStateInfo(dfa, 15, true, ACT_GE);
	DFA_AddStateInfo(dfa, 16, true, ACT_ASSIGN_OP);
	DFA_AddStateInfo(dfa, 17, true, ACT_EQ);
	DFA_AddStateInfo(dfa, 18, false, ACT_RELOP_ER);
	DFA_AddStateInfo(dfa, 19, true, ACT_NEQ);
	DFA_AddStateInfo(dfa, 20, true, ACT_PLUS);
	DFA_AddStateInfo(dfa, 21, true, ACT_MUL);
	DFA_AddStateInfo(dfa, 22, true, ACT_POW);
	DFA_AddStateInfo(dfa, 23, true, ACT_DIV);
	DFA_AddStateInfo(dfa, 24, true, ACT_MOD);
	DFA_AddStateInfo(dfa, 25, false, ACT_ERROR);
	DFA_AddStateInfo(dfa, 26, false, ACT_MAT_ROWS_ER);
	DFA_AddStateInfo(dfa, 27, false, ACT_MAT_ROWS_ER);
	DFA_AddStateInfo(dfa, 28, false, ACT_MAT_ROWS_ER);
	DFA_AddStateInfo(dfa, 29, true, ACT_MAT_ROWS);
	DFA_AddStateInfo(dfa, 30, false, ACT_MAT_COLS_ER);
	DFA_AddStateInfo(dfa, 31, false, ACT_MAT_COLS_ER);
	DFA_AddStateInfo(dfa, 32, false, ACT_MAT_COLS_ER);
	DFA_AddStateInfo(dfa, 33, true, ACT_MAT_COLS);
	DFA_AddStateInfo(dfa, 34, false, ACT_STR_LEN_ER);
	DFA_AddStateInfo(dfa, 35, false, ACT_STR_LEN_ER);
	DFA_AddStateInfo(dfa, 36, false, ACT_STR_LEN_ER);
	DFA_AddStateInfo(dfa, 37, false, ACT_STR_LEN_ER);
	DFA_AddStateInfo(dfa, 38, false, ACT_STR_LEN_ER);
	DFA_AddStateInfo(dfa, 39, true, ACT_STR_LENGTH);
	DFA_AddStateInfo(dfa, 40, false, ACT_STR_LIT_ER);
	DFA_AddStateInfo(dfa, 41, true, ACT_STRING_LIT);
	DFA_AddStateInfo(dfa, 42, false, ACT_STR_LIT_ER);
	DFA_AddStateInfo(dfa, 43, false, ACT_CHAR_LIT_ER);
	DFA_AddStateInfo(dfa, 44, false, ACT_CHAR_LIT_ER);
	DFA_AddStateInfo(dfa, 45, true, ACT_CHAR_LIT);
	DFA_AddStateInfo(dfa, 46, true, ACT_INT_LIT);
	DFA_AddStateInfo(dfa, 47, false, ACT_NUM_LIT_ER);
	DFA_AddStateInfo(dfa, 48, true, ACT_REAL_LIT);
	DFA_AddStateInfo(dfa, 49, true, ACT_DOT);
	DFA_AddStateInfo(dfa, 50, true, ACT_ID);
	DFA_AddStateInfo(dfa, 51, true, ACT_BLANK);
	DFA_AddStateInfo(dfa, 52, true, ACT_ENDOFFILE);
	DFA_AddStateInfo(dfa, 53, false, ACT_COMMENT_ER);
	DFA_AddStateInfo(dfa, 54, false, ACT_COMMENT_ER);
	DFA_AddStateInfo(dfa, 55, true, ACT_COMMENT);
	
	dfa->startID = 0;	
}