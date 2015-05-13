/********************************
       |TEAM-1 | GROUP-20|
UTKARSH PATHRABE  - 2012A7PS034P
SHIKHAR VASHISHTH - 2012C6PS436P
********************************/
#ifndef LEXER_H_INCLUDED
#define LEXER_H_INCLUDED

#include "lexerDef.h"
#include "BufferInput.h"
#include "hashTable.h"
#include "DFA.h"

TokenList lexer(char *filename, int* size, bool *lexerSuccess);
void printTokenTable(TokenList tk);
bool Tokenize(char *lexBuff, Action act);
void remap();

#endif // LEXERDEF_H_INCLUDED
