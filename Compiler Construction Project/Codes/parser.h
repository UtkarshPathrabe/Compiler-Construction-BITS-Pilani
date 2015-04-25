/********************************
       |TEAM-1 | GROUP-20|
UTKARSH PATHRABE  - 2012A7PS034P
SHIKHAR VASHISHTH - 2012C6PS436P
********************************/
#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include "parserDef.h"
#include "SymbolLinkedList.h"
#include "SymbolStack.h"
#include "Tree.h"

Tree parser(TokenList tokens, int numTokens, bool* result);
void fillStackFromList(Node** stack, Node** list);
Rule* getGrammarRules();
Node** getFollowSet();

#endif