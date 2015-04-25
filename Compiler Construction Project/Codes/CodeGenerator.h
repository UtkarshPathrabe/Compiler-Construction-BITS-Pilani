/********************************
       |TEAM-1 | GROUP-20|
UTKARSH PATHRABE  - 2012A7PS034P
SHIKHAR VASHISHTH - 2012C6PS436P
********************************/

#ifndef CODEGEN_H_INCLUDED
#define CODEGEN_H_INCLUDED

#include "AST.h"
#include "SymbolTable.h"

char Reg[4][5];
bool isRegEmpty[4];
int LabelNumber;
bool PowerProcUsed, IntToOutstringUsed, RealToOutstringUsed, ReverseTStr4ToOutStringUsed, CopyStringUsed, ConcatStringUsed, CopyMatrix01Used, CopyMatrix02Used, AddMatrixUsed, EmptyInStringUsed, StringLengthUsed, StringToRealUsed, StringToIntegerUsed, StringToBoolUsed;

void generateCodeMaster(TreeNode *ast, char *filename);
void generateCodeSlave(TreeNode *ast, FILE *code);
void generateCodeUtility(TreeNode *ast, FILE *code);
void initializeRegisters();
int getEmptyRegisterIndex();
void PowerProc (FILE *code);
void CodeOptimizerStack01 (FILE *input, FILE *output);
void CodeOptimizerPlus01 (FILE *input, FILE *output);
void CodeOptimizerPlus02 (FILE *input, FILE *output);
void CodeOptimizerMinus01 (FILE *input, FILE *output);
void CodeOptimizerMinus02 (FILE *input, FILE *output);
void CodeOptimizerMul01 (FILE *input, FILE *output);
void CodeOptimizerMul02 (FILE *input, FILE *output);
void CodeOptimizerDiv01 (FILE *input, FILE *output);
void CodeOptimizerMod01 (FILE *input, FILE *output);

#endif