/********************************
       |TEAM-1 | GROUP-20|
UTKARSH PATHRABE  - 2012A7PS034P
SHIKHAR VASHISHTH - 2012C6PS436P
********************************/
#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED

#include "lexerDef.h"
#define HASHKEY 75

int hash(char *word);					/*Takes a string and generates corresponding hash value*/
void addResWord(resTable RT, char *word, Token s);	/*recursively called to add keyword to keywordTable*/
void initRT(resTable RT); 				/*initialize keywordTable with keywords*/
Token getWordToken(char *lexeme, resTable RT);		/*Checks if word is reserve word or not*/

#endif // HASHTABLE_H_INCLUDED
