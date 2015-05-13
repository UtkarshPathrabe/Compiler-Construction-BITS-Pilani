/********************************
       |TEAM-1 | GROUP-20|
UTKARSH PATHRABE  - 2012A7PS034P
SHIKHAR VASHISHTH - 2012C6PS436P
********************************/

#include "lexer.h"
#include "DFA.h"

int lineno, numberOfTokens = 5000, tokenNumber = 0;
resWord RT[HASHKEY];
TokenInfo **TokenTable;

void remap(){
	numberOfTokens *= 2;
	TokenTable = (TokenInfo **)realloc( TokenTable, numberOfTokens * sizeof(TokenInfo*));
}

bool Tokenize(char *lexBuff, Action act) {
	TokenInfo *tk;
	bool flag = false, error = false;;
	tk = (TokenInfo *)malloc(sizeof(TokenInfo));
	strcpy(tk->lexeme, "");
	strcpy(tk->lexeme, lexBuff);
	tk->lineno = lineno;
	switch (act) {
		case ACT_ID: 	 	tk->token = getWordToken(tk->lexeme, RT); 	flag = true; break;
		case ACT_COLON:	 tk->token = TK_COLON;  			flag = true; break;
		case ACT_SEMICOLON:	 tk->token = TK_SEMICOLON;			flag = true; break;
		case ACT_COMMA:	 tk->token = TK_COMMA;  			flag = true; break;
		case ACT_LPAREN:	 tk->token = TK_LPAREN;  			flag = true; break;
		case ACT_RPAREN:	 tk->token = TK_RPAREN;  			flag = true; break;
		case ACT_LSQ:	 tk->token = TK_LSQ;  				flag = true; break;
		case ACT_RSQ:	 tk->token = TK_RSQ;  				flag = true; break;
		case ACT_LCURL:	 tk->token = TK_LCURL;  			flag = true; break;
		case ACT_RCURL:	 tk->token = TK_RCURL;  			flag = true; break;
		case ACT_MINUS:	 tk->token = TK_MINUS;  			flag = true; break;
		case ACT_ARROW:	 tk->token = TK_ARROW;  			flag = true; break;
		case ACT_LT:	 tk->token = TK_LT;  				flag = true; break;
		case ACT_LE:	 tk->token = TK_LE;  				flag = true; break;
		case ACT_GT:	 tk->token = TK_GT;  				flag = true; break;
		case ACT_GE:	 tk->token = TK_GE;  				flag = true; break;
		case ACT_ASSIGN_OP:	 tk->token = TK_ASSIGN_OP;			flag = true; break;
		case ACT_EQ:	 tk->token = TK_EQ;  				flag = true; break;
		case ACT_NEQ:	 tk->token = TK_NEQ;  				flag = true; break;
		case ACT_PLUS:	 tk->token = TK_PLUS;  				flag = true; break;
		case ACT_MUL:	 tk->token = TK_MUL;  				flag = true; break;
		case ACT_POW:	 tk->token = TK_POW;  				flag = true; break;
		case ACT_DIV:	 tk->token = TK_DIV;  				flag = true; break;
		case ACT_MOD:	 tk->token = TK_MOD;  				flag = true; break;
		case ACT_MAT_ROWS:	 tk->token = TK_MAT_ROWS; 			flag = true; break;
		case ACT_MAT_COLS:	 tk->token = TK_MAT_COLS; 			flag = true; break;
		case ACT_STR_LENGTH: tk->token = TK_STR_LENGTH;			flag = true; break;
		case ACT_STRING_LIT: tk->token = TK_STR_LIT;			flag = true; break;
		case ACT_CHAR_LIT:	 tk->token = TK_CHAR_LIT;  			flag = true; break;
		case ACT_INT_LIT:	 tk->token = TK_INT_LIT;  			flag = true; break;
		case ACT_REAL_LIT:	 tk->token = TK_REAL_LIT; 			flag = true; break;
		case ACT_DOT:	 tk->token = TK_DOT;  				flag = true; break;
		case ACT_RELOP_ER: 	 printf("Line no. %d: Relational Operator not defined correctly\n", lineno);	error=true; break;
		case ACT_MAT_ROWS_ER:printf("Line no. %d: @rows Operator not defined correctly\n", lineno); 	error=true; break;
		case ACT_MAT_COLS_ER:printf("Line no. %d: @cols Operator not defined correctly\n", lineno); 	error=true; break;
		case ACT_STR_LEN_ER: printf("Line no. %d: @length Operator not defined correctly\n", lineno); 	error=true; break;
		case ACT_STR_LIT_ER: printf("Line no. %d: String Literal not defined correctly\n", lineno); 	error=true; break;
		case ACT_CHAR_LIT_ER:printf("Line no. %d: Character Literal not defined correctly\n", lineno); 	error=true; break;
		case ACT_NUM_LIT_ER: printf("Line no. %d: Real Literal not defined correctly\n", lineno); 		error=true; break;
		case ACT_COMMENT_ER: printf("Line no. %d: Comment not terminated properly\n", lineno); 		error=true; break;
		case ACT_ERROR:	 printf("Line no. %d: Lexical Error\n", lineno); 				error=true; break;
	}
	if(numberOfTokens-1 == tokenNumber) remap();
	if(flag) (*(TokenTable + (tokenNumber++))) = tk;
	return error;
}

void printTokenTable(TokenList TokenTable){
	TokenInfo *tk;
	int i;
	for(i=0;i<tokenNumber;i++){
		tk = *(TokenTable + i);
		printf("Token :%d \t Lexeme: %s \t\t lineno: %d \tTOKEN: %s\n",i+1, tk->lexeme ,tk->lineno, tokenToStr(tk->token) );
	}
}

TokenList lexer(char *filename, int* size, bool *lexerSuccess) {
	Buffer buffer;
	loadFile(&buffer, filename);
	char c, lexBuff[MAX_LEXEME];
	int numStates, i = 0;
	*lexerSuccess = true;

	bool error = false;

	Action act;

	/* DFA Initialization */
	DFA *dfa;
	dfa = DFA_createDFA();
	DFA_construct(dfa);
	DFA_reset(dfa);

	/* Reserve Word Hash table Initialization */
	for (i = 0; i < HASHKEY; i++) RT[i].present = false;
	initRT(RT);

	/*Token Table initialization*/
	TokenTable = (TokenInfo **)calloc(numberOfTokens, sizeof(TokenInfo*));

	i = 0;
	lineno = 1;

	while (*(buffer.forward) != '$') {
		c = getChar(&buffer);

		if (error) {
			if (c == '\n' || c == ' ' || c == ';') error = false;
			else continue;
		}

		lexBuff[i++] = c;
		if ((act = DFA_makeNextTrans(dfa, c)) != ACT_CONTINUE) {
			lexBuff[i-1] = '\0';
			DFA_reset(dfa);
			error = Tokenize(lexBuff, act);
			if(error) {
				*lexerSuccess = false;
				continue;
			}
			i = 0;
			DFA_makeNextTrans(dfa, c);
			lexBuff[i++] = c;
		}
		if ( c == '\n') lineno++;
	}
	lexBuff[i] = '\0';
	Tokenize(lexBuff, dfa->states[dfa->currID]->action);
	// printTokenTable();

	*size = tokenNumber;
	return TokenTable;
}