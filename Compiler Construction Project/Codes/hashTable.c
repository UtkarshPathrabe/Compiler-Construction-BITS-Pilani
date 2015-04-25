/********************************
       |TEAM-1 | GROUP-20|
UTKARSH PATHRABE  - 2012A7PS034P
SHIKHAR VASHISHTH - 2012C6PS436P
********************************/
#include "hashTable.h"

// Takes a string and generates corresponding hash value
int hash(char *word) {
	int hash = 0, mul = 3, i = 0;
	while (word[i] != '\0')
		hash = (hash * mul + word[i++]) % HASHKEY;
	return hash;
}

void addResWord(resTable RT, char *word, Token symbol) { //recursively called to add keyword to keywordTable
	int hashValue;
	hashValue = hash(word);

	while (RT[hashValue].present == true)
		hashValue = (++hashValue) % HASHKEY;

	strcpy(RT[hashValue].lexeme, word);

	RT[hashValue].present = true;
	RT[hashValue].symbol = symbol;
}


// initialize keywordTable with keywords
void initRT(resTable RT) { 
	addResWord(RT, "execute" , TK_EXECUTE);
	addResWord(RT, "end" , TK_END);
	addResWord(RT, "records" , TK_RECBLK);
	addResWord(RT, "endrecords" , TK_ENDRECBLK);
	addResWord(RT, "procs" , TK_PROCBLK);
	addResWord(RT, "endprocs" , TK_ENDPROCBLK);
	addResWord(RT, "rec" , TK_REC);
	addResWord(RT, "endrec" , TK_ENDREC);
	addResWord(RT, "proc" , TK_PROC);
	addResWord(RT, "endproc" , TK_ENDPROC);
	addResWord(RT, "string" , TK_STRING);
	addResWord(RT, "mat" , TK_MAT);
	addResWord(RT, "int" , TK_INT);
	addResWord(RT, "real" , TK_REAL);
	addResWord(RT, "bool" , TK_BOOL);
	addResWord(RT, "char" , TK_CHAR);
	addResWord(RT, "if" , TK_IF);
	addResWord(RT, "elif" , TK_ELIF);
	addResWord(RT, "else" , TK_ELSE);
	addResWord(RT, "endif" , TK_ENDIF);
	addResWord(RT, "get" , TK_GET);
	addResWord(RT, "put" , TK_PUT);
	addResWord(RT, "endl" , TK_ENDL);
	addResWord(RT, "tab" , TK_TAB);
	addResWord(RT, "call" , TK_CALL);
	addResWord(RT, "loop" , TK_LOOP);
	addResWord(RT, "endloop" , TK_ENDLOOP);
	addResWord(RT, "break" , TK_BREAK);
	addResWord(RT, "continue" , TK_CONTINUE);
	addResWord(RT, "True" , TK_BOOL_LIT);
	addResWord(RT, "False" , TK_BOOL_LIT);
	addResWord(RT, "AND" , TK_AND);
	addResWord(RT, "NOT" , TK_NOT);
	addResWord(RT, "OR" , TK_OR);
	addResWord(RT, "assign" , TK_ASSIGN);
	addResWord(RT, "matassign" , TK_MATASSIGN);
	addResWord(RT, "strassign" , TK_STRASSIGN);
}

Token getWordToken(char *lexeme, resTable RT){
	int hashValue = hash(lexeme);

	while (RT[hashValue].present == true){
		if(strcmp(RT[hashValue].lexeme, lexeme) == 0) return RT[hashValue].symbol;
		hashValue = (++hashValue) % HASHKEY;
	}
	return TK_ID;
}

// int main(){
// 	int i;
// 	resWord RT[HASHKEY];
// 	for(i=0;i<HASHKEY;i++) RT[i].present = false;
// 	initRT(RT);

// 	/*for(i=0;i<HASHKEY;i++){
// 		if(RT[i].present){
// 			printf("pos: %d => lexeme: %s  Token :%d\n",i,RT[i].lexeme,RT[i].s);
// 		}
// 	}*/
// 	char name[7] = "ABCDEFG";
// 	for(i=0;i<1000;i++){
// 		int key = hash(name);
// 		// printf("%s\n",name );
// 		if(isResWord(name, RT)) printf("Wrong\n");
// 		else printf("Correct\n");
// 		name[i%7] = name[i%7]+1;
// 		// else printf("Passed\n");
// 	}

// 	return 0;
// }