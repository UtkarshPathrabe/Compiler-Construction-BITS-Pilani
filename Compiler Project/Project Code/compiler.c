/********************************
       |TEAM-1 | GROUP-20|
UTKARSH PATHRABE  - 2012A7PS034P
SHIKHAR VASHISHTH - 2012C6PS436P
********************************/

#include "commonHeader.h"
#include "lexer.h"
#include "parser.h"
#include "Tree.h"
#include "AST.h"
#include "SymbolTableDef.h"

bool compiler_error;

int main(int argc, char* argv[]){
	int numTokens;
	Tree ParseTree;
	bool lexerSuccess, parserSuccess;
	compiler_error = false;

	if(argc < 3){printf("Enter <source filename> <assembly output filename>\n"); exit(0);}

	printf("*******************************************LEXICAL ANALYSIS RESULT***************************************\n");
	TokenList tokens = lexer(argv[1], &numTokens, &lexerSuccess);
	printTokenTable(tokens);
	if(!lexerSuccess) {printf("ERROR DURING LEXICAL ANALYSIS!\n"); exit(0); }
	

	printf("**************************************************PARSE TREE***********************************************\n");
	ParseTree = parser(tokens, numTokens, &parserSuccess);
	if(!parserSuccess) {printf("ERROR DURING PARSING!\n\n"); exit(0); }
	printTree(ParseTree, 1);printf("\n");

	printf("**********************************************ABSTRACT SYNTAX TREE*****************************************\n");
	Tree ast = ParseTree;
	constructAST(ast, tokens, numTokens);
	printTree(ast, 1);printf("\n");

	printf("*********************************************SYMBOL TABLE GENERATION******************************************\n");
	SymbolTable st;
	initSymbolTable(&st, ast);
	// printf("\nGLOBAL SCOPE: %d\n",st.id );
	// ST_print(&st);
	// printf("\n\n");
	if(compiler_error) {printf("ERROR IN SYMBOL TABLE GENERATION!\n"); exit(0); }
	else printf("SYMBOL TABLE SUCCESSFULLY GENERATED\n");
	printf("**********************************************AST WITH SCOPE SET*****************************************\n");
	printTreeScope(ast, 1);

	printf("**********************************************TYPE CHECKING*****************************************\n");
	TC_scan(&st, ast);
	if(compiler_error) {printf("ERROR IN TYPE CHECKING PHASE!\n"); exit(0); }
	else printf("TYPE CHECKER SUCCESSFULY COMPLETED\n");

	printf("**********************************************SYMBOL TABLE*****************************************\n");
	printf("SCOPE GRAPH:\n");
	ST_traverse(&st,1);
	printf("\nSCOPE CONTENTS:\n");
	ST_printAll(&st);

	printf("********************************************CODE-GENERATION*****************************************\n");
	generateCodeMaster(ast, argv[2]);
	printf("Code Generated successfully, output in: %s\n", argv[2]);
	return 0;
}