/********************************
       |TEAM-1 | GROUP-20|
UTKARSH PATHRABE  - 2012A7PS034P
SHIKHAR VASHISHTH - 2012C6PS436P
********************************/

#include "Tree.h"
#include "SymbolTableDef.h"
#include "SymbolTable.h"
#include "parserDef.h"
#include "commonHeader.h"
#include "mapping.h"
#include "AST.h"

TC_scan(ST *st, Tree ast);
TC_condExp(Tree ast);
TC_checkRecId(Tree ast, Type exptype);
TC_checkMatId(Tree ast, Type exptype);
TC_checkId(Tree ast, Type exptype);
TC_idScan(Tree ast, Type type);
TC_opScan(Tree ast, Type type);
TC_assign(ST *st, Tree ast);
TC_checkMatAssign(ST *st, Tree ast);
TC_checkStrAssign(ST *st, Tree ast);
TC_checkProc(Tree ast);
TC_extProcArg(Tree ast, LL_Node **inplist, LL_Node **outlist);