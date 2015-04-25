/********************************
       |TEAM-1 | GROUP-20|
UTKARSH PATHRABE  - 2012A7PS034P
SHIKHAR VASHISHTH - 2012C6PS436P
********************************/
#ifndef SYMBOLTABLE_H_INCLUDED
#define SYMBOLTABLE_H_INCLUDED
#include "parserDef.h"
#include "lexerDef.h"
#include "Tree.h"

void initSymbolTable(ST *st, Tree ast);
void ST_create(ST *st);
ST* ST_addChild(ST *st);
int ST_hash(char *str);
int ST_genKey(ST *st, char *var);
int ST_getRecAttr(ST *st, char *recname, char *compname, Type *type);
ST* ST_getinfo(ST *st, char *name, int *key_ret);
int ST_search(ST *st, char *name);
Type getType(char *str);
void ST_makeEntry(ST *st, Tree ast);
void ST_varScan(ST *st, Tree ast);
void ST_makeProcEntry(ST *st, Tree ast);
void ST_getRecComp(Tree ast, LL_Node **list);
void ST_makeRecDecEntry(ST *st, Tree ast);
void ST_procRecScan(ST *st, Tree ast);
void ST_printAll(ST *st);
void ST_print(ST *st);
#endif