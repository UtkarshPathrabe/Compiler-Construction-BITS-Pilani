/********************************
       |TEAM-1 | GROUP-20|
UTKARSH PATHRABE  - 2012A7PS034P
SHIKHAR VASHISHTH - 2012C6PS436P
********************************/

#include "CodeGenerator.h"
#define GET(ast, field) (*((TokenInfo**)ast->value))->field

void generateCodeMaster(TreeNode *ast, char *filename){
	FILE *code, *temp;
	code = fopen(filename, "w");
	LabelNumber = 0;
	PowerProcUsed = false;
	IntToOutstringUsed = false;
	RealToOutstringUsed = false;
	ReverseTStr4ToOutStringUsed = false;
	CopyStringUsed = false;
	CopyMatrix01Used = false;
	CopyMatrix02Used = false;
	ConcatStringUsed = false;
	AddMatrixUsed = false;
	EmptyInStringUsed = false;
	StringLengthUsed = false;
	StringToRealUsed = false;
	StringToIntegerUsed = false;
	StringToBoolUsed = false;
	initializeRegisters();
	fprintf(code, ".model tiny\n");
	fprintf(code, ".stack\t10000\n");
	fprintf(code, ".data\n");
	declScan(ast->scope, code);
	fprintf(code, "\ttempString1\tdb\t100 dup(?), '$'\n");
	fprintf(code, "\ttempString2\tdb\t100 dup(?), '$'\n");
	fprintf(code, "\ttempString3\tdb\t100 dup(?), '$'\n");
	fprintf(code, "\ttempString4\tdb\t100 dup(?), '$'\n");
	fprintf(code, "\ttempString5\tdb\t100 dup(?), '$'\n");
	fprintf(code, "\tmaximumInputLength\tdb\t100\n");
	fprintf(code, "\tactualInputLength\tdb\t?\n");
	fprintf(code, "\tinString\tdb\t100 dup(?), '$'\n");
	fprintf(code, "\toutString\tdb\t100 dup(?), '$'\n");
	fprintf(code, "\tendlString\tdb\t0Ah, 0Dh, '$'\n");
	fprintf(code, "\ttabString\tdb\t09h, '$'\n");
	fprintf(code, "\ttempMatrix1\tdw\t100 dup(0)\n");
	fprintf(code, "\ttempMatrix2\tdw\t100 dup(0)\n");
	fprintf(code, "\tdestinationMatrixAddress\tdw\t?\n");
	fprintf(code, "\tsourceMatrixAddress\tdw\t?\n");
	fprintf(code, "\tmatrixSize\tdw\t?\n");
	fprintf(code, "\tsourceStringAddress\tdw\t?\n");
	fprintf(code, "\tdestinationStringAddress\tdw\t?\n");
	fprintf(code, "\n.code\n");
	fprintf(code, ".startup\n");
	generateCodeSlave(ast, code);
	fprintf(code, ".exit\n");
	if (PowerProcUsed) {
		PowerProc(code);
	}
	if (IntToOutstringUsed) {
		IntToOutstring(code);
	}
	if (RealToOutstringUsed) {
		RealToOutstring(code);
	}
	if (ReverseTStr4ToOutStringUsed) {
		ReverseTStr4ToOutString(code);
	}
	if (CopyStringUsed) {
		CopyString(code);
	}
	if (CopyMatrix01Used) {
		CopyMatrix01(code);
	}
	if (CopyMatrix02Used) {
		CopyMatrix02(code);
	}
	if (ConcatStringUsed) {
		ConcatString(code);
	}
	if (AddMatrixUsed) {
		AddMatrix(code);
	}
	if (EmptyInStringUsed) {
		EmptyInString(code);
	}
	if (StringLengthUsed) {
		StringLength(code);
	}
	if (StringToIntegerUsed) {
		StringToInteger(code);
	}
	if (StringToBoolUsed) {
		StringToBool(code);
	}
	if (StringToRealUsed) {
		StringToReal(code);
	}
	fprintf(code, "\nend\n");
	fclose(code);
	code = fopen(filename, "r");
	temp = fopen("temp.asm", "w");
	CodeOptimizerStack01(code, temp);
	fclose(code);
	fclose(temp);
	code = fopen(filename, "w");
	temp = fopen("temp.asm", "r");
	CodeOptimizerStack01(temp, code);
	fclose(code);
	fclose(temp);
	code = fopen(filename, "r");
	temp = fopen("temp.asm", "w");
	CodeOptimizerPlus01(code, temp);
	fclose(code);
	fclose(temp);
	code = fopen(filename, "w");
	temp = fopen("temp.asm", "r");
	CodeOptimizerPlus02(temp, code);
	fclose(code);
	fclose(temp);
	code = fopen(filename, "r");
	temp = fopen("temp.asm", "w");
	CodeOptimizerMinus01(code, temp);
	fclose(code);
	fclose(temp);
	code = fopen(filename, "w");
	temp = fopen("temp.asm", "r");
	CodeOptimizerMinus02(temp, code);
	fclose(code);
	fclose(temp);
	code = fopen(filename, "r");
	temp = fopen("temp.asm", "w");
	CodeOptimizerMul01(code, temp);
	fclose(code);
	fclose(temp);
	code = fopen(filename, "w");
	temp = fopen("temp.asm", "r");
	CodeOptimizerMul02(temp, code);
	fclose(code);
	fclose(temp);
	code = fopen(filename, "r");
	temp = fopen("temp.asm", "w");
	CodeOptimizerDiv01(code, temp);
	fclose(code);
	fclose(temp);
	code = fopen(filename, "w");
	temp = fopen("temp.asm", "r");
	CodeOptimizerMod01(temp, code);
	fclose(code);
	fclose(temp);
}

void StringToInteger (FILE *code) {
	int currentLabel = LabelNumber++;
	fprintf(code, "\nStringToInteger\tPROC\tNEAR\n");
	isRegEmpty[0] = false;
	isRegEmpty[1] = false;
	isRegEmpty[3] = false;
	fprintf(code, "\tMOV\tSI,\tsourceStringAddress\n");
	fprintf(code, "\tMOV\tAX,\t0\n");
	fprintf(code, "\tMOV\tBX,\t10\n");
	fprintf(code, "StringToIntegerLoop_%d:\n", currentLabel);
	fprintf(code, "\tCMP\tBYTE PTR[SI],\t0Dh\n");
	fprintf(code, "\tJE\tStringToIntegerEnd_%d\n", currentLabel);
	fprintf(code, "\tMUL\tBX\n");
	fprintf(code, "\tMOV\tDX,\t0\n");
	fprintf(code, "\tMOV\tDL,\tBYTE PTR[SI]\n");
	fprintf(code, "\tSUB\tDL,\t48\n");
	fprintf(code, "\tADD\tAX,\tDX\n");
	fprintf(code, "\tINC\tSI\n");
	fprintf(code, "\tJMP\tStringToIntegerLoop_%d\n", currentLabel);
	fprintf(code, "StringToIntegerEnd_%d:\n", currentLabel);
	isRegEmpty[0] = true;
	isRegEmpty[1] = true;
	isRegEmpty[3] = true;
	fprintf(code, "\tRET\n");
	fprintf(code, "StringToInteger\tENDP\n");
}

void StringToReal (FILE *code) {
	int currentLabel = LabelNumber++;
	fprintf(code, "\nStringToReal\tPROC\tNEAR\n");
	isRegEmpty[0] = false;
	isRegEmpty[1] = false;
	isRegEmpty[3] = false;
	fprintf(code, "\tMOV\tSI,\tsourceStringAddress\n");
	fprintf(code, "\tMOV\tAX,\t0\n");
	fprintf(code, "\tMOV\tBX,\t10\n");
	fprintf(code, "StringToRealLoop01_%d:\n", currentLabel);
	fprintf(code, "\tCMP\tBYTE PTR[SI],\t'.'\n");
	fprintf(code, "\tJE\tStringToRealEnd01_%d\n", currentLabel);
	fprintf(code, "\tMUL\tBX\n");
	fprintf(code, "\tMOV\tDX,\t0\n");
	fprintf(code, "\tMOV\tDL,\tBYTE PTR[SI]\n");
	fprintf(code, "\tSUB\tDL,\t48\n");
	fprintf(code, "\tADD\tAX,\tDX\n");
	fprintf(code, "\tINC\tSI\n");
	fprintf(code, "\tJMP\tStringToRealLoop01_%d\n", currentLabel);
	fprintf(code, "StringToRealEnd01_%d:\n", currentLabel);
	fprintf(code, "\tPUSH\tAX\n");
	fprintf(code, "\tINC\tSI\n");
	fprintf(code, "\tMOV\tAX,\t0\n");
	fprintf(code, "StringToRealLoop02_%d:\n", currentLabel);
	fprintf(code, "\tCMP\tBYTE PTR[SI],\t0Dh\n");
	fprintf(code, "\tJE\tStringToRealEnd02_%d\n", currentLabel);
	fprintf(code, "\tMUL\tBX\n");
	fprintf(code, "\tMOV\tDX,\t0\n");
	fprintf(code, "\tMOV\tDL,\tBYTE PTR[SI]\n");
	fprintf(code, "\tSUB\tDL,\t48\n");
	fprintf(code, "\tADD\tAX,\tDX\n");
	fprintf(code, "\tINC\tSI\n");
	fprintf(code, "\tJMP\tStringToRealLoop02_%d\n", currentLabel);
	fprintf(code, "StringToRealEnd02_%d:\n", currentLabel);
	fprintf(code, "\tMOV\tBX,\tAX\n");
	fprintf(code, "\tPOP\tAX\n");
	isRegEmpty[0] = true;
	isRegEmpty[1] = true;
	isRegEmpty[3] = true;
	fprintf(code, "\tRET\n");
	fprintf(code, "StringToReal\tENDP\n");
}

void StringToBool (FILE *code) {
	int currentLabel = LabelNumber++;
	fprintf(code, "\nStringToBool\tPROC\tNEAR\n");
	isRegEmpty[2] = false;
	fprintf(code, "\tMOV\tSI,\tsourceStringAddress\n");
	fprintf(code, "\tCMP\tBYTE PTR[SI],\t'T'\n");
	fprintf(code, "\tJNE\tStringToBoolCond_%d\n", currentLabel);
	fprintf(code, "\tMOV\tCX,\t1\n");
	fprintf(code, "\tJMP\tStringToBoolEnd_%d\n", currentLabel);
	fprintf(code, "StringToBoolCond_%d:\n", currentLabel);
	fprintf(code, "\tMOV\tCX,\t0\n");
	fprintf(code, "StringToBoolEnd_%d:\n", currentLabel);
	isRegEmpty[2] = true;
	fprintf(code, "\tRET\n");
	fprintf(code, "StringToBool\tENDP\n");
}

void StringLength (FILE *code) {
	int currentLabel = LabelNumber++;
	fprintf(code, "\nStringLength\tPROC\tNEAR\n");
	isRegEmpty[2] = false;
	fprintf(code, "\tMOV\tSI,\tsourceStringAddress\n");
	fprintf(code, "\tMOV\tCX,\t0\n");
	fprintf(code, "StringLengthLoop_%d:\n", currentLabel);
	fprintf(code, "\tCMP\tBYTE PTR[SI],\t'$'\n");
	fprintf(code, "\tJE\tStringLengthEnd_%d\n", currentLabel);
	fprintf(code, "\tINC\tSI\n");
	fprintf(code, "\tINC\tCX\n");
	fprintf(code, "\tJMP\tStringLengthLoop_%d\n", currentLabel);
	fprintf(code, "StringLengthEnd_%d:\n", currentLabel);
	isRegEmpty[2] = true;
	fprintf(code, "\tRET\n");
	fprintf(code, "StringLength\tENDP\n");
}

void EmptyInString (FILE *code) {
	int currentLabel = LabelNumber++;
	fprintf(code, "\nEmptyInString\tPROC\tNEAR\n");
	isRegEmpty[0] = false;
	isRegEmpty[2] = false;
	fprintf(code, "\tLEA\tSI,\tinString\n");
	fprintf(code, "\tMOV\tCX,\t100\n");
	fprintf(code, "EmptyInStringLoop_%d:\n", currentLabel);
	fprintf(code, "\tMOV\tBYTE PTR[SI],\t'$'\n");
	fprintf(code, "\tINC\tSI\n");
	fprintf(code, "\tDEC\tCX\n");
	fprintf(code, "\tJNZ\tEmptyInStringLoop_%d\n", currentLabel);
	isRegEmpty[0] = true;
	isRegEmpty[2] = true;
	fprintf(code, "\tRET\n");
	fprintf(code, "EmptyInString\tENDP\n");
}

void CopyString (FILE *code) {
	int currentLabel = LabelNumber++;
	fprintf(code, "\nCopyString\tPROC\tNEAR\n");
	isRegEmpty[0] = false;
	fprintf(code, "\tMOV\tSI,\tsourceStringAddress\n");
	fprintf(code, "\tMOV\tDI,\tdestinationStringAddress\n");
	fprintf(code, "CopyStringLoop_%d:\n", currentLabel);
	fprintf(code, "\tCMP\tBYTE PTR[SI],\t'$'\n");
	fprintf(code, "\tJE\tCopyStringEnd_%d\n", currentLabel);
	fprintf(code, "\tMOV\tAL,\tBYTE PTR[SI]\n");
	fprintf(code, "\tMOV\tBYTE PTR[DI],\tAL\n");
	fprintf(code, "\tINC\tSI\n");
	fprintf(code, "\tINC\tDI\n");
	fprintf(code, "\tJMP\tCopyStringLoop_%d\n", currentLabel);
	fprintf(code, "CopyStringEnd_%d:\n", currentLabel);
	fprintf(code, "\tMOV\tBYTE PTR[DI],\t'$'\n");
	isRegEmpty[0] = true;
	fprintf(code, "\tRET\n");
	fprintf(code, "CopyString\tENDP\n");
}

void CopyMatrix01 (FILE *code) {
	int currentLabel = LabelNumber++;
	fprintf(code, "\nCopyMatrix01\tPROC\tNEAR\n");
	isRegEmpty[0] = false;
	isRegEmpty[2] = false;
	fprintf(code, "\tMOV\tSI,\tsourceMatrixAddress\n");
	fprintf(code, "\tMOV\tDI,\tdestinationMatrixAddress\n");
	fprintf(code, "\tMOV\tCX,\tmatrixSize\n");
	fprintf(code, "CopyMatrixLoop_%d:\n", currentLabel);
	fprintf(code, "\tMOV\tAL,\tBYTE PTR[SI]\n");
	fprintf(code, "\tMOV\tBYTE PTR[DI],\tAL\n");
	fprintf(code, "\tINC\tSI\n");
	fprintf(code, "\tINC\tDI\n");
	fprintf(code, "\tDEC\tCX\n");
	fprintf(code, "\tJNZ\tCopyMatrixLoop_%d\n", currentLabel);
	isRegEmpty[0] = true;
	isRegEmpty[2] = true;
	fprintf(code, "\tRET\n");
	fprintf(code, "CopyMatrix01\tENDP\n");
}

void CopyMatrix02 (FILE *code) {
	int currentLabel = LabelNumber++;
	fprintf(code, "\nCopyMatrix02\tPROC\tNEAR\n");
	isRegEmpty[0] = false;
	isRegEmpty[2] = false;
	fprintf(code, "\tMOV\tSI,\tsourceMatrixAddress\n");
	fprintf(code, "\tMOV\tDI,\tdestinationMatrixAddress\n");
	fprintf(code, "\tMOV\tCX,\tmatrixSize\n");
	fprintf(code, "CopyMatrixLoop_%d:\n", currentLabel);
	fprintf(code, "\tMOV\tAX,\tWORD PTR[SI]\n");
	fprintf(code, "\tMOV\tWORD PTR[DI],\tAX\n");
	fprintf(code, "\tADD\tSI,\t2\n");
	fprintf(code, "\tADD\tDI,\t2\n");
	fprintf(code, "\tDEC\tCX\n");
	fprintf(code, "\tJNZ\tCopyMatrixLoop_%d\n", currentLabel);
	isRegEmpty[0] = true;
	isRegEmpty[2] = true;
	fprintf(code, "\tRET\n");
	fprintf(code, "CopyMatrix02\tENDP\n");
}

void AddMatrix (FILE *code) {
	int currentLabel = LabelNumber++;
	fprintf(code, "\nAddMatrix\tPROC\tNEAR\n");
	isRegEmpty[0] = false;
	isRegEmpty[1] = false;
	isRegEmpty[2] = false;
	fprintf(code, "\tLEA\tSI,\ttempMatrix2\n");
	fprintf(code, "\tLEA\tDI,\ttempMatrix1\n");
	fprintf(code, "\tMOV\tCX,\tmatrixSize\n");
	fprintf(code, "AddMatrixLoop_%d:\n", currentLabel);
	fprintf(code, "\tMOV\tAX,\tWORD PTR[SI]\n");
	fprintf(code, "\tMOV\tBX,\tWORD PTR[DI]\n");
	fprintf(code, "\tADD\tAX,\tBX\n");
	fprintf(code, "\tMOV\tWORD PTR[DI],\tAX\n");
	fprintf(code, "\tADD\tSI,\t2\n");
	fprintf(code, "\tADD\tDI,\t2\n");
	fprintf(code, "\tDEC\tCX\n");
	fprintf(code, "\tJNZ\tAddMatrixLoop_%d\n", currentLabel);
	isRegEmpty[0] = true;
	isRegEmpty[1] = true;
	isRegEmpty[2] = true;
	fprintf(code, "\tRET\n");
	fprintf(code, "AddMatrix\tENDP\n");
}

void ConcatString (FILE *code) {
	int currentLabel = LabelNumber++;
	fprintf(code, "\nConcatString\tPROC\tNEAR\n");
	isRegEmpty[0] = false;
	fprintf(code, "\tLEA\tSI,\ttempString2\n");
	fprintf(code, "\tLEA\tDI,\ttempString1\n");
	fprintf(code, "CopyStringLoop1_%d:\n", currentLabel);
	fprintf(code, "\tCMP\tBYTE PTR[SI],\t'$'\n");
	fprintf(code, "\tJE\tCopyStringEnd1_%d\n", currentLabel);
	fprintf(code, "\tMOV\tAL,\tBYTE PTR[SI]\n");
	fprintf(code, "\tMOV\tBYTE PTR[DI],\tAL\n");
	fprintf(code, "\tINC\tSI\n");
	fprintf(code, "\tINC\tDI\n");
	fprintf(code, "\tJMP\tCopyStringLoop1_%d\n", currentLabel);
	fprintf(code, "CopyStringEnd1_%d:\n", currentLabel);
	fprintf(code, "\tLEA\tSI,\ttempString3\n");
	fprintf(code, "CopyStringLoop2_%d:\n", currentLabel);
	fprintf(code, "\tCMP\tBYTE PTR[SI],\t'$'\n");
	fprintf(code, "\tJE\tCopyStringEnd2_%d\n", currentLabel);
	fprintf(code, "\tMOV\tAL,\tBYTE PTR[SI]\n");
	fprintf(code, "\tMOV\tBYTE PTR[DI],\tAL\n");
	fprintf(code, "\tINC\tSI\n");
	fprintf(code, "\tINC\tDI\n");
	fprintf(code, "\tJMP\tCopyStringLoop2_%d\n", currentLabel);
	fprintf(code, "CopyStringEnd2_%d:\n", currentLabel);
	fprintf(code, "\tMOV\tBYTE PTR[DI],\t'$'\n");
	isRegEmpty[0] = true;
	fprintf(code, "\tRET\n");
	fprintf(code, "ConcatString\tENDP\n");
}

void ReverseTStr4ToOutString (FILE *code) {
	int currentLabel = LabelNumber++;
	fprintf(code, "\nReverseTStr4ToOutString\tPROC\tNEAR\n");
	fprintf(code, "\tLEA\tSI,\ttempString4\n");
	fprintf(code, "\tLEA\tDI,\toutString\n");
	isRegEmpty[0] = false;
	isRegEmpty[2] = false;
	fprintf(code, "\tMOV\tCX,\t0\n");
	fprintf(code, "RTS4TOSLoop1_%d:\n", currentLabel);
	fprintf(code, "\tCMP\tBYTE PTR[SI],\t'$'\n");
	fprintf(code, "\tJE\tRTS4TOSEnd1_%d\n", currentLabel);
	fprintf(code, "\tINC\tSI\n");
	fprintf(code, "\tINC\tCX\n");
	fprintf(code, "\tJMP\tRTS4TOSLoop1_%d\n", currentLabel);
	fprintf(code, "RTS4TOSEnd1_%d:\n", currentLabel);
	fprintf(code, "\tDEC\tSI\n");
	fprintf(code, "RTS4TOSLoop2_%d:\n", currentLabel);
	fprintf(code, "\tMOV\tAL,\tBYTE PTR[SI]\n");
	fprintf(code, "\tMOV\tBYTE PTR[DI],\tAL\n");
	fprintf(code, "\tINC\tDI\n");
	fprintf(code, "\tDEC\tSI\n");
	fprintf(code, "\tDEC\tCX\n");
	fprintf(code, "\tJNZ\tRTS4TOSLoop2_%d\n", currentLabel);
	fprintf(code, "\tMOV\tBYTE PTR[DI],\t'$'\n");
	isRegEmpty[0] = true;
	isRegEmpty[2] = true;
	fprintf(code, "\tRET\n");
	fprintf(code, "ReverseTStr4ToOutString\tENDP\n");
}

void RealToOutstring (FILE *code) {
	int currentLabel = LabelNumber++;
	fprintf(code, "\nRealToOutstring\tPROC\tNEAR\n");
	isRegEmpty[0] = false;
	isRegEmpty[1] = false;
	isRegEmpty[2] = false;
	isRegEmpty[3] = false;
	fprintf(code, "\tPOP\tBX\n");
	fprintf(code, "\tPOP\tAX\n");
	fprintf(code, "\tPUSH\tBX\n");
	fprintf(code, "\tLEA\tSI,\ttempString4\n");
	fprintf(code, "\tMOV\tBX,\t0\n");
	fprintf(code, "\tMOV\tCX,\t10\n");
	fprintf(code, "RealToOutstringLoopLabel01_%d:\n", currentLabel);
	fprintf(code, "\tCWD\n");
	fprintf(code, "\tIDIV\tCX\n");
	fprintf(code, "\tCMP\tAX,\t0\n");
	fprintf(code, "\tJE\tRealToOutstringEndLabel01_%d\n", currentLabel);
	fprintf(code, "\tADD\tDL,\t48\n");
	fprintf(code, "\tMOV\tBYTE PTR[SI + BX],\tDL\n");
	fprintf(code, "\tINC\tBX\n");
	fprintf(code, "\tJMP\tRealToOutstringLoopLabel01_%d\n", currentLabel);
	fprintf(code, "RealToOutstringEndLabel01_%d:\n", currentLabel);
	fprintf(code, "\tADD\tDL,\t48\n");
	fprintf(code, "\tMOV\tBYTE PTR[SI + BX],\tDL\n");
	fprintf(code, "\tINC\tBX\n");
	fprintf(code, "\tMOV\tBYTE PTR[SI + BX],\t'$'\n");
	fprintf(code, "\tPOP\tBX\n");
	fprintf(code, "\tPOP\tAX\n");
	fprintf(code, "\tPUSH\tBX\n");
	fprintf(code, "\tLEA\tSI,\ttempString5\n");
	fprintf(code, "\tMOV\tBX,\t0\n");
	fprintf(code, "\tMOV\tCX,\t10\n");
	fprintf(code, "RealToOutstringLoopLabel02_%d:\n", currentLabel);
	fprintf(code, "\tCWD\n");
	fprintf(code, "\tIDIV\tCX\n");
	fprintf(code, "\tCMP\tAX,\t0\n");
	fprintf(code, "\tJE\tRealToOutstringEndLabel02_%d\n", currentLabel);
	fprintf(code, "\tADD\tDL,\t48\n");
	fprintf(code, "\tMOV\tBYTE PTR[SI + BX],\tDL\n");
	fprintf(code, "\tINC\tBX\n");
	fprintf(code, "\tJMP\tRealToOutstringLoopLabel02_%d\n", currentLabel);
	fprintf(code, "RealToOutstringEndLabel02_%d:\n", currentLabel);
	fprintf(code, "\tADD\tDL,\t48\n");
	fprintf(code, "\tMOV\tBYTE PTR[SI + BX],\tDL\n");
	fprintf(code, "\tINC\tBX\n");
	fprintf(code, "\tMOV\tBYTE PTR[SI + BX],\t'.'\n");
	fprintf(code, "\tINC\tBX\n");
	fprintf(code, "\tMOV\tBYTE PTR[SI + BX],\t'$'\n");
	fprintf(code, "\tLEA\tSI,\ttempString4\n");
	fprintf(code, "\tLEA\tDI,\toutString\n");
	fprintf(code, "\tMOV\tBX,\t0\n");
	fprintf(code, "RTS4TOSLoop1_%d:\n", currentLabel);
	fprintf(code, "\tCMP\tBYTE PTR[SI],\t'$'\n");
	fprintf(code, "\tJE\tRTS4TOSEnd1_%d\n", currentLabel);
	fprintf(code, "\tINC\tSI\n");
	fprintf(code, "\tINC\tBX\n");
	fprintf(code, "\tJMP\tRTS4TOSLoop1_%d\n", currentLabel);
	fprintf(code, "RTS4TOSEnd1_%d:\n", currentLabel);
	fprintf(code, "\tDEC\tSI\n");
	fprintf(code, "RTS4TOSLoop2_%d:\n", currentLabel);
	fprintf(code, "\tMOV\tAX,\tBYTE PTR[SI]\n");
	fprintf(code, "\tMOV\tBYTE PTR[DI],\tAX\n");
	fprintf(code, "\tINC\tDI\n");
	fprintf(code, "\tDEC\tSI\n");
	fprintf(code, "\tDEC\tBX\n");
	fprintf(code, "\tJNZ\tRTS4TOSLoop2_%d\n", currentLabel);
	fprintf(code, "\tLEA\tSI,\ttempString5\n");
	fprintf(code, "\tMOV\tBX,\t0\n");
	fprintf(code, "RTS5TOSLoop1_%d:\n", currentLabel);
	fprintf(code, "\tCMP\tBYTE PTR[SI],\t'$'\n");
	fprintf(code, "\tJE\tRTS5TOSEnd1_%d\n", currentLabel);
	fprintf(code, "\tINC\tSI\n");
	fprintf(code, "\tINC\tBX\n");
	fprintf(code, "\tJMP\tRTS5TOSLoop1_%d\n", currentLabel);
	fprintf(code, "RTS5TOSEnd1_%d:\n", currentLabel);
	fprintf(code, "\tDEC\tSI\n");
	fprintf(code, "RTS5TOSLoop2_%d:\n", currentLabel);
	fprintf(code, "\tMOV\tAX,\tBYTE PTR[SI]\n");
	fprintf(code, "\tMOV\tBYTE PTR[DI],\tAX\n");
	fprintf(code, "\tINC\tDI\n");
	fprintf(code, "\tDEC\tSI\n");
	fprintf(code, "\tDEC\tBX\n");
	fprintf(code, "\tJNZ\tRTS5TOSLoop2_%d\n", currentLabel);
	fprintf(code, "\tMOV\tBYTE PTR[DI],\t'$'\n");
	isRegEmpty[0] = true;
	isRegEmpty[1] = true;
	isRegEmpty[2] = true;
	isRegEmpty[3] = true;
	fprintf(code, "\tRET\n");
	fprintf(code, "RealToOutstring\tENDP\n");
}

void IntToOutstring (FILE *code) {
	int currentLabel = LabelNumber++;
	fprintf(code, "\nIntToOutstring\tPROC\tNEAR\n");
	isRegEmpty[0] = false;
	isRegEmpty[1] = false;
	isRegEmpty[2] = false;
	isRegEmpty[3] = false;
	fprintf(code, "\tLEA\tSI,\ttempString4\n");
	fprintf(code, "\tMOV\tBX,\t0\n");
	fprintf(code, "\tMOV\tCX,\t10\n");
	fprintf(code, "IntToOutstringLoopLabel_%d:\n", currentLabel);
	fprintf(code, "\tCWD\n");
	fprintf(code, "\tIDIV\tCX\n");
	fprintf(code, "\tCMP\tAX,\t0\n");
	fprintf(code, "\tJE\tIntToOutstringEndLabel_%d\n", currentLabel);
	fprintf(code, "\tADD\tDL,\t48\n");
	fprintf(code, "\tMOV\tBYTE PTR[SI + BX],\tDL\n");
	fprintf(code, "\tINC\tBX\n");
	fprintf(code, "\tJMP\tIntToOutstringLoopLabel_%d\n", currentLabel);
	fprintf(code, "IntToOutstringEndLabel_%d:\n", currentLabel);
	fprintf(code, "\tADD\tDL,\t48\n");
	fprintf(code, "\tMOV\tBYTE PTR[SI + BX],\tDL\n");
	fprintf(code, "\tINC\tBX\n");
	fprintf(code, "\tMOV\tBYTE PTR[SI + BX],\t'$'\n");
	fprintf(code, "\tCALL\tReverseTStr4ToOutString\n");
	ReverseTStr4ToOutStringUsed = true;
	isRegEmpty[0] = true;
	isRegEmpty[1] = true;
	isRegEmpty[2] = true;
	isRegEmpty[3] = true;
	fprintf(code, "\tRET\n");
	fprintf(code, "IntToOutstring\tENDP\n");
}

void PowerProc (FILE *code) {
	int currentLabel = LabelNumber++;
	fprintf(code, "\nPowerProc\tPROC\tNEAR\n");
	isRegEmpty[0] = false;
	isRegEmpty[1] = false;
	isRegEmpty[2] = false;
	fprintf(code, "\tMOV\tBX,\tAX\n");
	fprintf(code, "\tDEC\tCX\n");
	fprintf(code, "\tCMP\tCX,\t0\n");
	fprintf(code, "\tJLE\tPowerEnd_%d\n", currentLabel);
	fprintf(code, "PowerLabel_%d:\n", currentLabel);
	fprintf(code, "\tIMUL\tBX\n");
	fprintf(code, "\tDEC\tCX\n");
	fprintf(code, "\tJNZ\tPowerLabel_%d\n", currentLabel);
	fprintf(code, "PowerEnd_%d:\n", currentLabel);
	isRegEmpty[0] = true;
	isRegEmpty[1] = true;
	isRegEmpty[2] = true;
	fprintf(code, "\tRET\n");
	fprintf(code, "PowerProc\tENDP\n");
}

void generateCodeSlave(TreeNode *ast, FILE *code){
	TreeNode *root = ast;
	TreeNode *node_execute = searchTree(root->child, EXECUTE, program);
	TreeNode *node_utility = node_execute;
	while(node_utility != NULL){
		if(node_utility->child != NULL){
			generateCodeUtility(node_utility->child, code);
		}
		node_utility = node_utility->next;
	}
}

void generateCodeUtility(TreeNode *ast, FILE *code){
	int emptyRegister, reg1, reg2, reg3, reg4, key;
	char op[10];
	TreeNode *root = ast;
	if (root->sym == decl_stmt) {
		return;
	} else if(root->sym == stmts || root->sym == iloop_stmts) {
		generateCodeUtility(root->child, code);
		if (root->child->next != NULL) {
			generateCodeUtility(root->child->next, code);
		}
	} else if (root->sym == stmt) {
		generateCodeUtility(root->child, code);
	} else if (root->sym == GET) {
		isRegEmpty[0] = false;
		isRegEmpty[3] = false;
		fprintf(code, "\tCALL\tEmptyInString\n");
		EmptyInStringUsed = true;
		fprintf(code, "\tLEA\tDX,\tmaximumInputLength\n");
		fprintf(code, "\tMOV\tAH,\t0Ah\n");
		fprintf(code, "\tINT\t21h\n");
		isRegEmpty[0] = true;
		isRegEmpty[3] = true;
		if (root->child->sym == ID_PRI) {
			ST* st = root->child->scope;
			Type type = ST_getinfo(st, GET(root->child, lexeme), &key)->type[key];
			fprintf(code, "\tLEA\tSI,\tinString\n");
			if (type == INT_TYPE) {
				isRegEmpty[2] = false;
				fprintf(code, "\tMOV\tsourceStringAddress,\tSI\n");
				fprintf(code, "\tCALL\tStringToInteger\n");
				fprintf(code, "\tPUSH\tAX\n");
				StringToIntegerUsed = true;
				fprintf(code, "\tPOP\tCX\n");
				fprintf(code, "\tMOV\t%s%d,\tCX\n", GET(root->child, lexeme), ST_getDeclId(st, GET(root->child, lexeme)));
				isRegEmpty[2] = true;
			} else if (type == BOOL_TYPE) {
				int currentLabel = LabelNumber++;
				isRegEmpty[2] = false;
				fprintf(code, "\tMOV\tsourceStringAddress,\tSI\n");
				fprintf(code, "\tCALL\tStringToBool\n");
				fprintf(code, "\tPUSH\tCX\n");
				StringToBoolUsed = true;
				fprintf(code, "\tPOP\tCX\n");
				fprintf(code, "\tMOV\t%s%d,\tCX\n", GET(root->child, lexeme), ST_getDeclId(st, GET(root->child, lexeme)));
				isRegEmpty[2] = true;
			} else if (type == CHAR_TYPE) {
				isRegEmpty[2] = false;
				fprintf(code, "\tMOV\tCL,\tBYTE PTR[SI]\n");
				fprintf(code, "\tMOV\t%s%d,\tCL\n", GET(root->child, lexeme), ST_getDeclId(st, GET(root->child, lexeme)));
				isRegEmpty[2] = true;
			} else if (type == REAL_TYPE) {
				fprintf(code, "\tMOV\tsourceStringAddress,\tSI\n");
				fprintf(code, "\tCALL\tStringToReal\n");
				fprintf(code, "\tPUSH\tAX\n");
				fprintf(code, "\tPUSH\tBX\n");
				StringToRealUsed = true;
				fprintf(code, "\tLEA\tSI,\t%s%d\n", GET(root->child, lexeme), ST_getDeclId(st, GET(root->child, lexeme)));
				fprintf(code, "\tPOP\tWORD PTR[SI + 2]\n");
				fprintf(code, "\tPOP\tWORD PTR[SI]\n");
			} else if (type == STR_TYPE) {
				fprintf(code, "\tMOV\tsourceStringAddress,\tSI\n");
				fprintf(code, "\tLEA\tDI,\t%s%d\n", GET(root->child, lexeme), ST_getDeclId(st, GET(root->child, lexeme)));
				fprintf(code, "\tMOV\tdestinationStringAddress,\tDI\n");
				fprintf(code, "\tCALL\tCopyString\n");
				CopyStringUsed = true;
			}
		} else if (root->child->sym == ID_MAT_RHS) {
			ST *st = root->child->scope;
			matAssignRHSInfo *mat = root->child->value;
			char *var_mat, *var_row, *var_col;
			var_mat = (*((TokenInfo**)mat->info))->lexeme;
			var_row = (*((TokenInfo**)mat->rows))->lexeme;
			Symbol rSym = mat->rowSym, cSym;
			if(mat->cols != NULL) {
				var_col = (*((TokenInfo**)mat->cols))->lexeme;
				cSym = mat->colSym;
			} else {
				var_col = NULL;
			}
			mat_var *matv = ST_getinfo(st, var_mat, &key)->entry[key];
			int mul = matv->cols;
			Type type = matv->type;
			isRegEmpty[0] = false;
			isRegEmpty[1] = false;
			isRegEmpty[2] = false;
			isRegEmpty[3] = false;
			fprintf(code, "\tLEA\tSI,\tinString\n");
			if (var_col != NULL) {
				if (type == INT_TYPE) {
					fprintf(code, "\tMOV\tsourceStringAddress,\tSI\n");
					fprintf(code, "\tCALL\tStringToInteger\n");
					fprintf(code, "\tPUSH\tAX\n");
					StringToIntegerUsed = true;
					if (rSym == INT_LIT) {
						fprintf(code, "\tMOV\tAX,\t%s\n", var_row);
					} else {
						fprintf(code, "\tMOV\tAX,\t%s%d\n", var_row, ST_getDeclId(st, var_row));
					}
					fprintf(code, "\tMOV\tBX,\t%d\n", mul * 2);
					fprintf(code, "\tMUL\tBX\n");
					fprintf(code, "\tMOV\tCX,\tAX\n");
					if (cSym == INT_LIT) {
						fprintf(code, "\tMOV\tAX,\t%s\n", var_col);
					} else {
						fprintf(code, "\tMOV\tAX,\t%s%d\n", var_col, ST_getDeclId(st, var_col));
					}
					fprintf(code, "\tMOV\tBX,\t2\n");
					fprintf(code, "\tMUL\tBX\n");
					fprintf(code, "\tADD\tCX,\tAX\n");
					fprintf(code, "\tMOV\tBX,\tCX\n");
					fprintf(code, "\tPOP\tAX\n");
					fprintf(code, "\tLEA\tSI,\t%s%d\n", var_mat, ST_getDeclId(st, var_mat));
					fprintf(code, "\tMOV\tWORD PTR[SI + BX],\tAX\n");
				} else if (type == BOOL_TYPE) {
					fprintf(code, "\tMOV\tsourceStringAddress,\tSI\n");
					fprintf(code, "\tCALL\tStringToBool\n");
					fprintf(code, "\tPUSH\tCX\n");
					StringToBoolUsed = true;
					if (rSym == INT_LIT) {
						fprintf(code, "\tMOV\tAX,\t%s\n", var_row);
					} else {
						fprintf(code, "\tMOV\tAX,\t%s%d\n", var_row, ST_getDeclId(st, var_row));
					}
					fprintf(code, "\tMOV\tBX,\t%d\n", mul * 2);
					fprintf(code, "\tMUL\tBX\n");
					fprintf(code, "\tMOV\tCX,\tAX\n");
					if (cSym == INT_LIT) {
						fprintf(code, "\tMOV\tAX,\t%s\n", var_col);
					} else {
						fprintf(code, "\tMOV\tAX,\t%s%d\n", var_col, ST_getDeclId(st, var_col));
					}
					fprintf(code, "\tMOV\tBX,\t2\n");
					fprintf(code, "\tMUL\tBX\n");
					fprintf(code, "\tADD\tCX,\tAX\n");
					fprintf(code, "\tMOV\tBX,\tCX\n");
					fprintf(code, "\tPOP\tAX\n");
					fprintf(code, "\tLEA\tSI,\t%s%d\n", var_mat, ST_getDeclId(st, var_mat));
					fprintf(code, "\tMOV\tWORD PTR[SI + BX],\tAX\n");
				} else if (type == CHAR_TYPE) {
					if (rSym == INT_LIT) {
						fprintf(code, "\tMOV\tAX,\t%s\n", var_row);
					} else {
						fprintf(code, "\tMOV\tAX,\t%s%d\n", var_row, ST_getDeclId(st, var_row));
					}
					fprintf(code, "\tMOV\tBX,\t%d\n", mul);
					fprintf(code, "\tMUL\tBX\n");
					fprintf(code, "\tMOV\tCX,\tAX\n");
					if (cSym == INT_LIT) {
						fprintf(code, "\tMOV\tAX,\t%s\n", var_col);
					} else {
						fprintf(code, "\tMOV\tAX,\t%s%d\n", var_col, ST_getDeclId(st, var_col));
					}
					fprintf(code, "\tADD\tCX,\tAX\n");
					fprintf(code, "\tMOV\tBX,\tCX\n");
					fprintf(code, "\tMOV\tAL,\tBYTE PTR[SI]\n");
					fprintf(code, "\tLEA\tSI,\t%s%d\n", var_mat, ST_getDeclId(st, var_mat));
					fprintf(code, "\tMOV\tBYTE PTR[SI + BX],\tAL\n");
				} else {
					fprintf(code, "\tMOV\tsourceStringAddress,\tSI\n");
					fprintf(code, "\tCALL\tStringToReal\n");
					fprintf(code, "\tPUSH\tAX\n");
					fprintf(code, "\tPUSH\tBX\n");
					StringToRealUsed = true;
					if (rSym == INT_LIT) {
						fprintf(code, "\tMOV\tAX,\t%s\n", var_row);
					} else {
						fprintf(code, "\tMOV\tAX,\t%s%d\n", var_row, ST_getDeclId(st, var_row));
					}
					fprintf(code, "\tMOV\tBX,\t%d\n", mul * 4);
					fprintf(code, "\tMUL\tBX\n");
					fprintf(code, "\tMOV\tCX,\tAX\n");
					if (cSym == INT_LIT) {
						fprintf(code, "\tMOV\tAX,\t%s\n", var_col);
					} else {
						fprintf(code, "\tMOV\tAX,\t%s%d\n", var_col, ST_getDeclId(st, var_col));
					}
					fprintf(code, "\tMOV\tBX,\t4\n");
					fprintf(code, "\tMUL\tBX\n");
					fprintf(code, "\tADD\tCX,\tAX\n");
					fprintf(code, "\tMOV\tBX,\tCX\n");
					fprintf(code, "\tLEA\tSI,\t%s%d\n", var_mat, ST_getDeclId(st, var_mat));
					fprintf(code, "\tPOP\tCX\n");
					fprintf(code, "\tPOP\tAX\n");
					fprintf(code, "\tMOV\tWORD PTR[SI + BX],\tAX\n");
					fprintf(code, "\tADD\tBX,\t2\n");
					fprintf(code, "\tMOV\tWORD PTR[SI + BX],\tCX\n");
				}
			} else {
				if (type == INT_TYPE) {
					fprintf(code, "\tMOV\tsourceStringAddress,\tSI\n");
					fprintf(code, "\tCALL\tStringToInteger\n");
					fprintf(code, "\tPUSH\tAX\n");
					StringToIntegerUsed = true;
					if (rSym == INT_LIT) {
						fprintf(code, "\tMOV\tAX,\t%s\n", var_row);
					} else {
						fprintf(code, "\tMOV\tAX,\t%s%d\n", var_row, ST_getDeclId(st, var_row));
					}
					fprintf(code, "\tMOV\tBX,\t2\n");
					fprintf(code, "\tMUL\tBX\n");
					fprintf(code, "\tMOV\tBX,\tAX\n");
					fprintf(code, "\tPOP\tAX\n");
					fprintf(code, "\tLEA\tSI,\t%s%d\n", var_mat, ST_getDeclId(st, var_mat));
					fprintf(code, "\tMOV\tWORD PTR[SI + BX],\tAX\n");
				} else if (type == BOOL_TYPE) {
					fprintf(code, "\tMOV\tsourceStringAddress,\tSI\n");
					fprintf(code, "\tCALL\tStringToBool\n");
					fprintf(code, "\tPUSH\tCX\n");
					StringToBoolUsed = true;
					if (rSym == INT_LIT) {
						fprintf(code, "\tMOV\tAX,\t%s\n", var_row);
					} else {
						fprintf(code, "\tMOV\tAX,\t%s%d\n", var_row, ST_getDeclId(st, var_row));
					}
					fprintf(code, "\tMOV\tBX,\t2\n");
					fprintf(code, "\tMUL\tBX\n");
					fprintf(code, "\tMOV\tBX,\tAX\n");
					fprintf(code, "\tPOP\tAX\n");
					fprintf(code, "\tLEA\tSI,\t%s%d\n", var_mat, ST_getDeclId(st, var_mat));
					fprintf(code, "\tMOV\tWORD PTR[SI + BX],\tAX\n");
				} else if (type == CHAR_TYPE) {
					if (rSym == INT_LIT) {
						fprintf(code, "\tMOV\tBX,\t%s\n", var_row);
					} else {
						fprintf(code, "\tMOV\tBX,\t%s%d\n", var_row, ST_getDeclId(st, var_row));
					}
					fprintf(code, "\tMOV\tAL,\tBYTE PTR[SI]\n");
					fprintf(code, "\tLEA\tSI,\t%s%d\n", var_mat, ST_getDeclId(st, var_mat));
					fprintf(code, "\tMOV\tBYTE PTR[SI + BX],\tAL\n");
				} else {
					fprintf(code, "\tMOV\tsourceStringAddress,\tSI\n");
					fprintf(code, "\tCALL\tStringToReal\n");
					fprintf(code, "\tPUSH\tAX\n");
					fprintf(code, "\tPUSH\tBX\n");
					StringToRealUsed = true;
					if (rSym == INT_LIT) {
						fprintf(code, "\tMOV\tAX,\t%s\n", var_row);
					} else {
						fprintf(code, "\tMOV\tAX,\t%s%d\n", var_row, ST_getDeclId(st, var_row));
					}
					fprintf(code, "\tMOV\tBX,\t4\n");
					fprintf(code, "\tMUL\tBX\n");
					fprintf(code, "\tMOV\tBX,\tAX\n");
					fprintf(code, "\tLEA\tSI,\t%s%d\n", var_mat, ST_getDeclId(st, var_mat));
					fprintf(code, "\tPOP\tCX\n");
					fprintf(code, "\tPOP\tAX\n");
					fprintf(code, "\tMOV\tWORD PTR[SI + BX],\tAX\n");
					fprintf(code, "\tADD\tBX,\t2\n");
					fprintf(code, "\tMOV\tWORD PTR[SI + BX],\tCX\n");
				}
			}
			isRegEmpty[0] = true;
			isRegEmpty[1] = true;
			isRegEmpty[2] = true;
			isRegEmpty[3] = true;
		} else if (root->child->sym == ID_REC_RHS) {
			ST *st = root->child->scope;
			Type type;
			recTypeIDInfo *info = root->child->value;
			char *recname = (*((TokenInfo**)info->info))->lexeme;
			char *compname = (*((TokenInfo**)info->comp))->lexeme;
			rec_var *temp = ST_getinfo(st, recname, &key)->entry[key];
			int off = ST_getRecAttr(st, recname, compname, &type);
			isRegEmpty[0] = false;
			isRegEmpty[2] = false;
			fprintf(code, "\tMOV\tBX,\t%d\n", off * 4);
			fprintf(code, "\tLEA\tSI,\tinString\n");
			if (type == INT_TYPE) {
				fprintf(code, "\tMOV\tsourceStringAddress,\tSI\n");
				fprintf(code, "\tCALL\tStringToInteger\n");
				fprintf(code, "\tPUSH\tAX\n");
				StringToIntegerUsed = true;
				fprintf(code, "\tPOP\tAX\n");
				fprintf(code, "\tLEA\tSI,\t%s%d\n", recname, ST_getDeclId(st, recname));
				fprintf(code, "\tMOV\tWORD PTR[SI + BX],\tAX\n");
			} else if (type == BOOL_TYPE) {
				fprintf(code, "\tMOV\tsourceStringAddress,\tSI\n");
				fprintf(code, "\tCALL\tStringToBool\n");
				fprintf(code, "\tPUSH\tCX\n");
				StringToBoolUsed = true;
				fprintf(code, "\tPOP\tAX\n");
				fprintf(code, "\tLEA\tSI,\t%s%d\n", recname, ST_getDeclId(st, recname));
				fprintf(code, "\tMOV\tWORD PTR[SI + BX],\tAX\n");
			} else if (type == CHAR_TYPE) {
				fprintf(code, "\tMOV\tAL,\tBYTE PTR[SI]\n");
				fprintf(code, "\tLEA\tSI,\t%s%d\n", recname, ST_getDeclId(st, recname));
				fprintf(code, "\tMOV\tBYTE PTR[SI + BX],\tAL\n");
			} else if (type == REAL_TYPE) {
				isRegEmpty[1] = false;
				fprintf(code, "\tMOV\tsourceStringAddress,\tSI\n");
				fprintf(code, "\tCALL\tStringToReal\n");
				fprintf(code, "\tPUSH\tAX\n");
				fprintf(code, "\tPUSH\tBX\n");
				StringToRealUsed = true;
				fprintf(code, "\tLEA\tSI,\t%s%d\n", recname, ST_getDeclId(st, recname));
				fprintf(code, "\tPOP\tCX\n");
				fprintf(code, "\tPOP\tAX\n");
				fprintf(code, "\tMOV\tWORD PTR[SI + BX],\tAX\n");
				fprintf(code, "\tADD\tBX,\t2\n");
				fprintf(code, "\tMOV\tWORD PTR[SI + BX],\tCX\n");
				isRegEmpty[1] = true;
			}
			isRegEmpty[0] = true;
			isRegEmpty[2] = true;
		}	
	} else if (root->sym == PUT) {
		isRegEmpty[0] = false;
		isRegEmpty[3] = false;
		if (root->child->sym == ENDL) {
			fprintf(code, "\tLEA\tDX,\tendlString\n");
		} else if (root->child->sym == TAB) {
			fprintf(code, "\tLEA\tDX,\ttabString\n");
		} else if (root->child->sym == ID_PRI) {
			ST* st = root->child->scope;
			Type type = ST_getinfo(st, GET(root->child, lexeme), &key)->type[key];
			if (type == INT_TYPE) {
				fprintf(code, "\tMOV\tAX,\t%s%d\n", GET(root->child, lexeme), ST_getDeclId(st, GET(root->child, lexeme)));
				fprintf(code, "\tCALL\tIntToOutstring\n");
				IntToOutstringUsed = true;
				fprintf(code, "\tLEA\tDX,\toutString\n");
			} else if (type == CHAR_TYPE) {
				isRegEmpty[2] = false;
				fprintf(code, "\tLEA\tSI,\toutString\n");
				fprintf(code, "\tMOV\tCL,\t%s%d\n", GET(root->child, lexeme), ST_getDeclId(st, GET(root->child, lexeme)));
				fprintf(code, "\tMOV\tBYTE PTR[SI],\tCL\n");
				fprintf(code, "\tMOV\tBYTE PTR[SI + 1],\t'%c'\n", '$');
				fprintf(code, "\tLEA\tDX,\toutString\n");
				isRegEmpty[2] = true;
			} else if (type == BOOL_TYPE) {
				int currentLabel = LabelNumber++;
				isRegEmpty[2] = false;
				fprintf(code, "\tLEA\tSI,\toutString\n");
				fprintf(code, "\tMOV\tCX,\t%s%d\n", GET(root->child, lexeme), ST_getDeclId(st, GET(root->child, lexeme)));
				fprintf(code, "\tCMP\tCX,\t0\n");
				fprintf(code, "\tJE\tBoolLabel_%d\n", currentLabel);
				fprintf(code, "\tMOV\tBYTE PTR[SI],\t'T'\n");
				fprintf(code, "\tMOV\tBYTE PTR[SI + 1],\t'r'\n");
				fprintf(code, "\tMOV\tBYTE PTR[SI + 2],\t'u'\n");
				fprintf(code, "\tMOV\tBYTE PTR[SI + 3],\t'e'\n");
				fprintf(code, "\tMOV\tBYTE PTR[SI + 4],\t'$'\n");
				fprintf(code, "\tJMP\tBoolEndLabel_%d\n", currentLabel);
				fprintf(code, "BoolLabel_%d:\n", currentLabel);
				fprintf(code, "\tMOV\tBYTE PTR[SI],\t'F'\n");
				fprintf(code, "\tMOV\tBYTE PTR[SI + 1],\t'a'\n");
				fprintf(code, "\tMOV\tBYTE PTR[SI + 2],\t'l'\n");
				fprintf(code, "\tMOV\tBYTE PTR[SI + 3],\t's'\n");
				fprintf(code, "\tMOV\tBYTE PTR[SI + 4],\t'e'\n");
				fprintf(code, "\tMOV\tBYTE PTR[SI + 5],\t'$'\n");
				fprintf(code, "BoolEndLabel_%d:\n", currentLabel);
				fprintf(code, "\tLEA\tDX,\toutString\n");
				isRegEmpty[2] = true;
			} else if (type == STR_TYPE) {
				fprintf(code, "\tLEA\tSI,\t%s%d\n", GET(root->child, lexeme), ST_getDeclId(st, GET(root->child, lexeme)));
				fprintf(code, "\tMOV\tsourceStringAddress,\tSI\n");
				fprintf(code, "\tLEA\tDI,\toutString\n");
				fprintf(code, "\tMOV\tdestinationStringAddress,\tDI\n");
				fprintf(code, "\tCALL\tCopyString\n");
				CopyStringUsed = true;
				fprintf(code, "\tLEA\tDX,\toutString\n");
			} else if (type == REAL_TYPE) {
				fprintf(code, "\tLEA\tSI,\t%s%d\n", GET(root->child, lexeme), ST_getDeclId(st, GET(root->child, lexeme)));
				fprintf(code, "\tPUSH\tWORD PTR[SI]\n");
				fprintf(code, "\tPUSH\tWORD PTR[SI + 2]\n");
				fprintf(code, "\tCALL\tRealToOutstring\n");
				RealToOutstringUsed = true;
				fprintf(code, "\tLEA\tDX,\toutString\n");
			}
		} else if (root->child->sym == STR_LIT) {
			int i;
			char buff[100];
			strcpy(buff, GET(root->child, lexeme));
			fprintf(code, "\tLEA\tSI,\toutString\n");
			for (i = 1; i < strlen(buff) - 1; i++) {
				fprintf(code, "\tMOV\tBYTE PTR[SI + %d],\t'%c'\n", i-1, buff[i]);
			}
			fprintf(code, "\tMOV\tBYTE PTR[SI + %d],\t'%c'\n", i-1, '$');
			fprintf(code, "\tLEA\tDX,\toutString\n");
		} else if (root->child->sym == ID_MAT_RHS) {
			ST *st = root->child->scope;
			matAssignRHSInfo *mat = root->child->value;
			char *var_mat, *var_row, *var_col;
			var_mat = (*((TokenInfo**)mat->info))->lexeme;
			var_row = (*((TokenInfo**)mat->rows))->lexeme;
			Symbol rSym = mat->rowSym, cSym;
			if(mat->cols != NULL) {
				var_col = (*((TokenInfo**)mat->cols))->lexeme;
				cSym = mat->colSym;
			} else {
				var_col = NULL;
			}
			mat_var *matv = ST_getinfo(st, var_mat, &key)->entry[key];
			int mul = matv->cols;
			Type type = matv->type;
			isRegEmpty[0] = false;
			isRegEmpty[1] = false;
			isRegEmpty[2] = false;
			isRegEmpty[3] = false;
			fprintf(code, "\tLEA\tSI,\t%s%d\n", var_mat, ST_getDeclId(st, var_mat));
			if (var_col != NULL) {
				if (type == INT_TYPE) {
					if (rSym == INT_LIT) {
						fprintf(code, "\tMOV\tAX,\t%s\n", var_row);
					} else {
						fprintf(code, "\tMOV\tAX,\t%s%d\n", var_row, ST_getDeclId(st, var_row));
					}
					fprintf(code, "\tMOV\tBX,\t%d\n", mul * 2);
					fprintf(code, "\tMUL\tBX\n");
					fprintf(code, "\tMOV\tCX,\tAX\n");
					if (cSym == INT_LIT) {
						fprintf(code, "\tMOV\tAX,\t%s\n", var_col);
					} else {
						fprintf(code, "\tMOV\tAX,\t%s%d\n", var_col, ST_getDeclId(st, var_col));
					}
					fprintf(code, "\tMOV\tBX,\t2\n");
					fprintf(code, "\tMUL\tBX\n");
					fprintf(code, "\tADD\tCX,\tAX\n");
					fprintf(code, "\tMOV\tBX,\tCX\n");
					fprintf(code, "\tMOV\tAX,\tWORD PTR[SI + BX]\n");
					fprintf(code, "\tCALL\tIntToOutstring\n");
					IntToOutstringUsed = true;
					fprintf(code, "\tLEA\tDX,\toutString\n");
				} else if (type == BOOL_TYPE) {
					int currentLabel = LabelNumber++;
					if (rSym == INT_LIT) {
						fprintf(code, "\tMOV\tAX,\t%s\n", var_row);
					} else {
						fprintf(code, "\tMOV\tAX,\t%s%d\n", var_row, ST_getDeclId(st, var_row));
					}
					fprintf(code, "\tMOV\tBX,\t%d\n", mul * 2);
					fprintf(code, "\tMUL\tBX\n");
					fprintf(code, "\tMOV\tCX,\tAX\n");
					if (cSym == INT_LIT) {
						fprintf(code, "\tMOV\tAX,\t%s\n", var_col);
					} else {
						fprintf(code, "\tMOV\tAX,\t%s%d\n", var_col, ST_getDeclId(st, var_col));
					}
					fprintf(code, "\tMOV\tBX,\t2\n");
					fprintf(code, "\tMUL\tBX\n");
					fprintf(code, "\tADD\tCX,\tAX\n");
					fprintf(code, "\tMOV\tBX,\tCX\n");
					fprintf(code, "\tMOV\tAX,\tWORD PTR[SI + BX]\n");
					fprintf(code, "\tLEA\tSI,\toutString\n");
					fprintf(code, "\tCMP\tAX,\t0\n");
					fprintf(code, "\tJE\tBoolMatLabel_%d\n", currentLabel);
					fprintf(code, "\tMOV\tBYTE PTR[SI],\t'T'\n");
					fprintf(code, "\tMOV\tBYTE PTR[SI + 1],\t'r'\n");
					fprintf(code, "\tMOV\tBYTE PTR[SI + 2],\t'u'\n");
					fprintf(code, "\tMOV\tBYTE PTR[SI + 3],\t'e'\n");
					fprintf(code, "\tMOV\tBYTE PTR[SI + 4],\t'$'\n");
					fprintf(code, "\tJMP\tBoolMatEndLabel_%d\n", currentLabel);
					fprintf(code, "BoolMatLabel_%d:\n", currentLabel);
					fprintf(code, "\tMOV\tBYTE PTR[SI],\t'F'\n");
					fprintf(code, "\tMOV\tBYTE PTR[SI + 1],\t'a'\n");
					fprintf(code, "\tMOV\tBYTE PTR[SI + 2],\t'l'\n");
					fprintf(code, "\tMOV\tBYTE PTR[SI + 3],\t's'\n");
					fprintf(code, "\tMOV\tBYTE PTR[SI + 4],\t'e'\n");
					fprintf(code, "\tMOV\tBYTE PTR[SI + 5],\t'$'\n");
					fprintf(code, "BoolMatEndLabel_%d:\n", currentLabel);
					fprintf(code, "\tLEA\tDX,\toutString\n");
				} else if (type == CHAR_TYPE) {
					if (rSym == INT_LIT) {
						fprintf(code, "\tMOV\tAX,\t%s\n", var_row);
					} else {
						fprintf(code, "\tMOV\tAX,\t%s%d\n", var_row, ST_getDeclId(st, var_row));
					}
					fprintf(code, "\tMOV\tBX,\t%d\n", mul);
					fprintf(code, "\tMUL\tBX\n");
					fprintf(code, "\tMOV\tCX,\tAX\n");
					if (cSym == INT_LIT) {
						fprintf(code, "\tMOV\tAX,\t%s\n", var_col);
					} else {
						fprintf(code, "\tMOV\tAX,\t%s%d\n", var_col, ST_getDeclId(st, var_col));
					}
					fprintf(code, "\tADD\tCX,\tAX\n");
					fprintf(code, "\tMOV\tBX,\tCX\n");
					fprintf(code, "\tMOV\tAL,\tBYTE PTR[SI + BX]\n");
					fprintf(code, "\tLEA\tSI,\toutString\n");
					fprintf(code, "\tMOV\tBYTE PTR[SI],\tAL\n");
					fprintf(code, "\tMOV\tBYTE PTR[SI + 1],\t'$'\n");
					fprintf(code, "\tLEA\tDX,\toutString\n");
				} else {
					if (rSym == INT_LIT) {
						fprintf(code, "\tMOV\tAX,\t%s\n", var_row);
					} else {
						fprintf(code, "\tMOV\tAX,\t%s%d\n", var_row, ST_getDeclId(st, var_row));
					}
					fprintf(code, "\tMOV\tBX,\t%d\n", mul * 4);
					fprintf(code, "\tMUL\tBX\n");
					fprintf(code, "\tMOV\tCX,\tAX\n");
					if (cSym == INT_LIT) {
						fprintf(code, "\tMOV\tAX,\t%s\n", var_col);
					} else {
						fprintf(code, "\tMOV\tAX,\t%s%d\n", var_col, ST_getDeclId(st, var_col));
					}
					fprintf(code, "\tMOV\tBX,\t4\n");
					fprintf(code, "\tMUL\tBX\n");
					fprintf(code, "\tADD\tCX,\tAX\n");
					fprintf(code, "\tMOV\tBX,\tCX\n");
					fprintf(code, "\tMOV\tAX,\tWORD PTR[SI + BX]\n");
					fprintf(code, "\tADD\tBX,\t2\n");
					fprintf(code, "\tMOV\tCX,\tWORD PTR[SI + BX]\n");
					fprintf(code, "\tPUSH\tAX\n");
					fprintf(code, "\tPUSH\tCX\n");
					fprintf(code, "\tCALL\tRealToOutstring\n");
					RealToOutstringUsed = true;
					fprintf(code, "\tLEA\tDX,\toutString\n");
				}
			} else {
				if (type == INT_TYPE) {
					if (rSym == INT_LIT) {
						fprintf(code, "\tMOV\tAX,\t%s\n", var_row);
					} else {
						fprintf(code, "\tMOV\tAX,\t%s%d\n", var_row, ST_getDeclId(st, var_row));
					}
					fprintf(code, "\tMOV\tBX,\t2\n");
					fprintf(code, "\tMUL\tBX\n");
					fprintf(code, "\tMOV\tBX,\tAX\n");
					fprintf(code, "\tMOV\tAX,\tWORD PTR[SI + BX]\n");
					fprintf(code, "\tCALL\tIntToOutstring\n");
					IntToOutstringUsed = true;
					fprintf(code, "\tLEA\tDX,\toutString\n");
				} else if (type == BOOL_TYPE) {
					int currentLabel = LabelNumber++;
					if (rSym == INT_LIT) {
						fprintf(code, "\tMOV\tAX,\t%s\n", var_row);
					} else {
						fprintf(code, "\tMOV\tAX,\t%s%d\n", var_row, ST_getDeclId(st, var_row));
					}
					fprintf(code, "\tMOV\tBX,\t2\n");
					fprintf(code, "\tMUL\tBX\n");
					fprintf(code, "\tMOV\tBX,\tAX\n");
					fprintf(code, "\tMOV\tAX,\tWORD PTR[SI + BX]\n");
					fprintf(code, "\tLEA\tSI,\toutString\n");
					fprintf(code, "\tCMP\tAX,\t0\n");
					fprintf(code, "\tJE\tBoolMatLabel_%d\n", currentLabel);
					fprintf(code, "\tMOV\tBYTE PTR[SI],\t'T'\n");
					fprintf(code, "\tMOV\tBYTE PTR[SI + 1],\t'r'\n");
					fprintf(code, "\tMOV\tBYTE PTR[SI + 2],\t'u'\n");
					fprintf(code, "\tMOV\tBYTE PTR[SI + 3],\t'e'\n");
					fprintf(code, "\tMOV\tBYTE PTR[SI + 4],\t'$'\n");
					fprintf(code, "\tJMP\tBoolMatEndLabel_%d\n", currentLabel);
					fprintf(code, "BoolMatLabel_%d:\n", currentLabel);
					fprintf(code, "\tMOV\tBYTE PTR[SI],\t'F'\n");
					fprintf(code, "\tMOV\tBYTE PTR[SI + 1],\t'a'\n");
					fprintf(code, "\tMOV\tBYTE PTR[SI + 2],\t'l'\n");
					fprintf(code, "\tMOV\tBYTE PTR[SI + 3],\t's'\n");
					fprintf(code, "\tMOV\tBYTE PTR[SI + 4],\t'e'\n");
					fprintf(code, "\tMOV\tBYTE PTR[SI + 5],\t'$'\n");
					fprintf(code, "BoolMatEndLabel_%d:\n", currentLabel);
					fprintf(code, "\tLEA\tDX,\toutString\n");
				} else if (type == CHAR_TYPE) {
					if (rSym == INT_LIT) {
						fprintf(code, "\tMOV\tBX,\t%s\n", var_row);
					} else {
						fprintf(code, "\tMOV\tBX,\t%s%d\n", var_row, ST_getDeclId(st, var_row));
					}
					fprintf(code, "\tMOV\tAL,\tBYTE PTR[SI + BX]\n");
					fprintf(code, "\tLEA\tSI,\toutString\n");
					fprintf(code, "\tMOV\tBYTE PTR[SI],\tAL\n");
					fprintf(code, "\tMOV\tBYTE PTR[SI + 1],\t'$'\n");
					fprintf(code, "\tLEA\tDX,\toutString\n");
				} else {
					if (rSym == INT_LIT) {
						fprintf(code, "\tMOV\tAX,\t%s\n", var_row);
					} else {
						fprintf(code, "\tMOV\tAX,\t%s%d\n", var_row, ST_getDeclId(st, var_row));
					}
					fprintf(code, "\tMOV\tBX,\t4\n");
					fprintf(code, "\tMUL\tBX\n");
					fprintf(code, "\tMOV\tBX,\tAX\n");
					fprintf(code, "\tMOV\tAX,\tWORD PTR[SI + BX]\n");
					fprintf(code, "\tADD\tBX,\t2\n");
					fprintf(code, "\tMOV\tCX,\tWORD PTR[SI + BX]\n");
					fprintf(code, "\tPUSH\tAX\n");
					fprintf(code, "\tPUSH\tCX\n");
					fprintf(code, "\tCALL\tRealToOutstring\n");
					RealToOutstringUsed = true;
					fprintf(code, "\tLEA\tDX,\toutString\n");
				}
			}
			isRegEmpty[0] = true;
			isRegEmpty[1] = true;
			isRegEmpty[2] = true;
			isRegEmpty[3] = true;
		} else if (root->child->sym == ID_REC_RHS) {
			ST *st = root->child->scope;
			Type type;
			recTypeIDInfo *info = root->child->value;
			char *recname = (*((TokenInfo**)info->info))->lexeme;
			char *compname = (*((TokenInfo**)info->comp))->lexeme;
			rec_var *temp = ST_getinfo(st, recname, &key)->entry[key];
			int off = ST_getRecAttr(st, recname, compname, &type);
			isRegEmpty[0] = false;
			isRegEmpty[2] = false;
			fprintf(code, "\tLEA\tSI,\t%s%d\n", recname, ST_getDeclId(st, recname));
			fprintf(code, "\tMOV\tBX,\t%d\n", off * 4);
			if (type == INT_TYPE) {
				fprintf(code, "\tMOV\tAX,\tWORD PTR[SI + BX]\n");
				fprintf(code, "\tCALL\tIntToOutstring\n");
				IntToOutstringUsed = true;
				fprintf(code, "\tLEA\tDX,\toutString\n");
			} else if (type == BOOL_TYPE) {
				int currentLabel = LabelNumber++;
				fprintf(code, "\tMOV\tAX,\tWORD PTR[SI + BX]\n");
				fprintf(code, "\tLEA\tSI,\toutString\n");
				fprintf(code, "\tCMP\tAX,\t0\n");
				fprintf(code, "\tJE\tBoolMatLabel_%d\n", currentLabel);
				fprintf(code, "\tMOV\tBYTE PTR[SI],\t'T'\n");
				fprintf(code, "\tMOV\tBYTE PTR[SI + 1],\t'r'\n");
				fprintf(code, "\tMOV\tBYTE PTR[SI + 2],\t'u'\n");
				fprintf(code, "\tMOV\tBYTE PTR[SI + 3],\t'e'\n");
				fprintf(code, "\tMOV\tBYTE PTR[SI + 4],\t'$'\n");
				fprintf(code, "\tJMP\tBoolMatEndLabel_%d\n", currentLabel);
				fprintf(code, "BoolMatLabel_%d:\n", currentLabel);
				fprintf(code, "\tMOV\tBYTE PTR[SI],\t'F'\n");
				fprintf(code, "\tMOV\tBYTE PTR[SI + 1],\t'a'\n");
				fprintf(code, "\tMOV\tBYTE PTR[SI + 2],\t'l'\n");
				fprintf(code, "\tMOV\tBYTE PTR[SI + 3],\t's'\n");
				fprintf(code, "\tMOV\tBYTE PTR[SI + 4],\t'e'\n");
				fprintf(code, "\tMOV\tBYTE PTR[SI + 5],\t'$'\n");
				fprintf(code, "BoolMatEndLabel_%d:\n", currentLabel);
				fprintf(code, "\tLEA\tDX,\toutString\n");
			} else if (type == CHAR_TYPE) {
				fprintf(code, "\tMOV\tAL,\tBYTE PTR[SI + BX]\n");
				fprintf(code, "\tLEA\tSI,\toutString\n");
				fprintf(code, "\tMOV\tBYTE PTR[SI],\tAL\n");
				fprintf(code, "\tMOV\tBYTE PTR[SI + 1],\t'$'\n");
				fprintf(code, "\tLEA\tDX,\toutString\n");
			} else if (type == REAL_TYPE) {
				isRegEmpty[1] = false;
				fprintf(code, "\tMOV\tAX,\tWORD PTR[SI + BX]\n");
				fprintf(code, "\tADD\tBX,\t2\n");
				fprintf(code, "\tMOV\tCX,\tWORD PTR[SI + BX]\n");
				fprintf(code, "\tPUSH\tAX\n");
				fprintf(code, "\tPUSH\tCX\n");
				fprintf(code, "\tCALL\tRealToOutstring\n");
				RealToOutstringUsed = true;
				fprintf(code, "\tLEA\tDX,\toutString\n");
				isRegEmpty[1] = true;
			}
			isRegEmpty[0] = true;
			isRegEmpty[2] = true;
		}
		fprintf(code, "\tMOV\tAH,\t09h\n");
		fprintf(code, "\tINT\t21h\n");
		isRegEmpty[0] = true;
		isRegEmpty[3] = true;
	} else if(root->sym == IF){
		int currentLabel = LabelNumber++, i = 1;
		generateCodeUtility(root->child, code);
		emptyRegister = getEmptyRegisterIndex();
		if (emptyRegister == -1) {
			printf("****ERROR No Register Empty****");
			return;
		}
		fprintf(code, "\tPOP\t%s\n", Reg[emptyRegister]);
		fprintf(code, "\tCMP\t%s,\t0\n", Reg[emptyRegister]);
		fprintf(code, "\tJE\tElseIfPart_%d\n", currentLabel);
		isRegEmpty[emptyRegister] = true;
		generateCodeUtility(root->child->next, code);
		fprintf(code, "\tJMP\tEndIf_%d\n", currentLabel);
		fprintf(code, "ElseIfPart_%d:\n", currentLabel);
		TreeNode *node_elseif = root->child->next->next;
		while (node_elseif != NULL) {
			if (node_elseif->sym == ELIF) {
				generateCodeUtility(node_elseif->child, code);
				emptyRegister = getEmptyRegisterIndex();
				if (emptyRegister == -1) {
					printf("****ERROR No Register Empty****");
					return;
				}
				fprintf(code, "\tPOP\t%s\n", Reg[emptyRegister]);
				fprintf(code, "\tCMP\t%s,\t0\n", Reg[emptyRegister]);
				if (node_elseif->child->next->next == NULL) {
					fprintf(code, "\tJE\tElsePart_%d\n", currentLabel);
				} else {
					fprintf(code, "\tJE\tElseIfPart_%d\n", currentLabel + i);
				}
				isRegEmpty[emptyRegister] = true;
				generateCodeUtility(node_elseif->child->next, code);
				fprintf(code, "\tJMP\tEndIf_%d\n", currentLabel);
				if (node_elseif->child->next->next != NULL) {
					fprintf(code, "ElseIfPart_%d:\n", currentLabel + i);
				}
				node_elseif = node_elseif->child->next->next;
				i++;
			} else {
				break;
			}
		}
		fprintf(code, "ElsePart_%d:\n", currentLabel);
		if (root->child->next->next != NULL) {
			if (root->child->next->next->sym == ELSE) {
				generateCodeUtility(root->child->next->next->child, code);
			} else if (root->child->next->next->next != NULL) {
				if (root->child->next->next->next->sym == ELSE) {
					generateCodeUtility(root->child->next->next->next->child, code);
				}
			}
		}
		fprintf(code, "EndIf_%d:\n", currentLabel);
	} else if (root->sym == LOOP) {
		int currentLabel = LabelNumber++;
		generateCodeUtility(root->child, code);
		fprintf(code, "Loop_%d:\n", currentLabel);
		generateCodeUtility(root->child->next, code);
		emptyRegister = getEmptyRegisterIndex();
		if (emptyRegister == -1) {
			printf("****ERROR No Register Empty****");
			return;
		}
		fprintf(code, "\tPOP\t%s\n", Reg[emptyRegister]);
		fprintf(code, "\tCMP\t%s,\t0\n", Reg[emptyRegister]);
		fprintf(code, "\tJE\tEndLoop_%d\n", currentLabel);
		isRegEmpty[emptyRegister] = true;
		generateCodeUtility(root->child->next->next->next, code);
		generateCodeUtility(root->child->next->next, code);
		fprintf(code, "\tJMP\tLoop_%d\n", currentLabel);
		fprintf(code, "EndLoop_%d:\n", currentLabel);
	} else if(root->sym == ASSIGN) {
		if (root->child->sym == ID_MAT_RHS) {
			generateCodeUtility (root->child->next, code);
			ST *st = root->child->scope;
			matAssignRHSInfo *mat = root->child->value;
			char *var_mat, *var_row, *var_col;
			var_mat = (*((TokenInfo**)mat->info))->lexeme;
			var_row = (*((TokenInfo**)mat->rows))->lexeme;
			Symbol rSym = mat->rowSym, cSym;
			if(mat->cols != NULL) {
				var_col = (*((TokenInfo**)mat->cols))->lexeme;
				cSym = mat->colSym;
			} else {
				var_col = NULL;
			}
			mat_var *matv = ST_getinfo(st, var_mat, &key)->entry[key];
			int mul = matv->cols;
			Type type = matv->type;
			isRegEmpty[0] = false;
			isRegEmpty[1] = false;
			isRegEmpty[2] = false;
			isRegEmpty[3] = false;
			fprintf(code, "\tLEA\tSI,\t%s%d\n", var_mat, ST_getDeclId(st, var_mat));
			if (var_col != NULL) {
				if (type == INT_TYPE || type == BOOL_TYPE) {
					if (rSym == INT_LIT) {
						fprintf(code, "\tMOV\tAX,\t%s\n", var_row);
					} else {
						fprintf(code, "\tMOV\tAX,\t%s%d\n", var_row, ST_getDeclId(st, var_row));
					}
					fprintf(code, "\tMOV\tBX,\t%d\n", mul * 2);
					fprintf(code, "\tMUL\tBX\n");
					fprintf(code, "\tMOV\tCX,\tAX\n");
					if (cSym == INT_LIT) {
						fprintf(code, "\tMOV\tAX,\t%s\n", var_col);
					} else {
						fprintf(code, "\tMOV\tAX,\t%s%d\n", var_col, ST_getDeclId(st, var_col));
					}
					fprintf(code, "\tMOV\tBX,\t2\n");
					fprintf(code, "\tMUL\tBX\n");
					fprintf(code, "\tADD\tCX,\tAX\n");
					fprintf(code, "\tMOV\tBX,\tCX\n");
					fprintf(code, "\tPOP\tAX\n");
					fprintf(code, "\tMOV\tWORD PTR[SI + BX],\tAX\n");
				} else if (type == CHAR_TYPE) {
					if (rSym == INT_LIT) {
						fprintf(code, "\tMOV\tAX,\t%s\n", var_row);
					} else {
						fprintf(code, "\tMOV\tAX,\t%s%d\n", var_row, ST_getDeclId(st, var_row));
					}
					fprintf(code, "\tMOV\tBX,\t%d\n", mul);
					fprintf(code, "\tMUL\tBX\n");
					fprintf(code, "\tMOV\tCX,\tAX\n");
					if (cSym == INT_LIT) {
						fprintf(code, "\tMOV\tAX,\t%s\n", var_col);
					} else {
						fprintf(code, "\tMOV\tAX,\t%s%d\n", var_col, ST_getDeclId(st, var_col));
					}
					fprintf(code, "\tADD\tCX,\tAX\n");
					fprintf(code, "\tMOV\tBX,\tCX\n");
					fprintf(code, "\tPOP\tAX\n");
					fprintf(code, "\tMOV\tBYTE PTR[SI + BX],\tAL\n");
				} else {
					if (rSym == INT_LIT) {
						fprintf(code, "\tMOV\tAX,\t%s\n", var_row);
					} else {
						fprintf(code, "\tMOV\tAX,\t%s%d\n", var_row, ST_getDeclId(st, var_row));
					}
					fprintf(code, "\tMOV\tBX,\t%d\n", mul * 4);
					fprintf(code, "\tMUL\tBX\n");
					fprintf(code, "\tMOV\tCX,\tAX\n");
					if (cSym == INT_LIT) {
						fprintf(code, "\tMOV\tAX,\t%s\n", var_col);
					} else {
						fprintf(code, "\tMOV\tAX,\t%s%d\n", var_col, ST_getDeclId(st, var_col));
					}
					fprintf(code, "\tMOV\tBX,\t4\n");
					fprintf(code, "\tMUL\tBX\n");
					fprintf(code, "\tADD\tCX,\tAX\n");
					fprintf(code, "\tMOV\tBX,\tCX\n");
					fprintf(code, "\tPOP\tCX\n");
					fprintf(code, "\tPOP\tAX\n");
					fprintf(code, "\tMOV\tWORD PTR[SI + BX],\tAX\n");
					fprintf(code, "\tADD\tBX,\t2\n");
					fprintf(code, "\tMOV\tWORD PTR[SI + BX],\tCX\n");
				}
			} else {
				if (type == BOOL_TYPE || type == INT_TYPE) {
					if (rSym == INT_LIT) {
						fprintf(code, "\tMOV\tAX,\t%s\n", var_row);
					} else {
						fprintf(code, "\tMOV\tAX,\t%s%d\n", var_row, ST_getDeclId(st, var_row));
					}
					fprintf(code, "\tMOV\tBX,\t2\n");
					fprintf(code, "\tMUL\tBX\n");
					fprintf(code, "\tMOV\tBX,\tAX\n");
					fprintf(code, "\tPOP\tAX\n");
					fprintf(code, "\tMOV\tWORD PTR[SI + BX],\tAX\n");
				} else if (type == CHAR_TYPE) {
					if (rSym == INT_LIT) {
						fprintf(code, "\tMOV\tAX,\t%s\n", var_row);
					} else {
						fprintf(code, "\tMOV\tAX,\t%s%d\n", var_row, ST_getDeclId(st, var_row));
					}
					fprintf(code, "\tMOV\tBX,\tAX\n");
					fprintf(code, "\tPOP\tAX\n");
					fprintf(code, "\tMOV\tBYTE PTR[SI + BX],\tAL\n");
				} else {
					if (rSym == INT_LIT) {
						fprintf(code, "\tMOV\tAX,\t%s\n", var_row);
					} else {
						fprintf(code, "\tMOV\tAX,\t%s%d\n", var_row, ST_getDeclId(st, var_row));
					}
					fprintf(code, "\tMOV\tBX,\t4\n");
					fprintf(code, "\tMUL\tBX\n");
					fprintf(code, "\tMOV\tBX,\tAX\n");
					fprintf(code, "\tPOP\tCX\n");
					fprintf(code, "\tPOP\tAX\n");
					fprintf(code, "\tMOV\tWORD PTR[SI + BX],\tAX\n");
					fprintf(code, "\tADD\tBX,\t2\n");
					fprintf(code, "\tMOV\tWORD PTR[SI + BX],\tCX\n");
				}
			}
			isRegEmpty[0] = true;
			isRegEmpty[1] = true;
			isRegEmpty[2] = true;
			isRegEmpty[3] = true;
		} else if (root->child->sym == ID_REC_RHS) {
			generateCodeUtility (root->child->next, code);
			ST *st = root->child->scope;
			Type type;
			recTypeIDInfo *info = root->child->value;
			char *recname = (*((TokenInfo**)info->info))->lexeme;
			char *compname = (*((TokenInfo**)info->comp))->lexeme;
			rec_var *temp = ST_getinfo(st, recname, &key)->entry[key];
			int off = ST_getRecAttr(st, recname, compname, &type);
			isRegEmpty[0] = false;
			isRegEmpty[2] = false;
			fprintf(code, "\tLEA\tSI,\t%s%d\n", recname, ST_getDeclId(st, recname));
			fprintf(code, "\tMOV\tBX,\t%d\n", off * 4);
			if (type == BOOL_TYPE || type == INT_TYPE) {
				fprintf(code, "\tPOP\tAX\n");
				fprintf(code, "\tMOV\tWORD PTR[SI + BX],\tAX\n");
			} else if (type == CHAR_TYPE) {
				fprintf(code, "\tPOP\tAX\n");
				fprintf(code, "\tMOV\tBYTE PTR[SI + BX],\tAL\n");
			} else if (type == REAL_TYPE) {
				isRegEmpty[1] = false;
				fprintf(code, "\tPOP\tCX\n");
				fprintf(code, "\tPOP\tAX\n");
				fprintf(code, "\tMOV\tWORD PTR[SI + BX],\tAX\n");
				fprintf(code, "\tADD\tBX,\t2\n");
				fprintf(code, "\tMOV\tWORD PTR[SI + BX],\tCX\n");
				isRegEmpty[1] = true;
			}
			isRegEmpty[0] = true;
			isRegEmpty[2] = true;
		} else {
			ST* st = root->child->scope;
			Type type = ST_getinfo(st, GET(root->child, lexeme), &key)->type[key];
			if (type == BOOL_TYPE || type == INT_TYPE) {
				generateCodeUtility (root->child->next, code);
				emptyRegister = getEmptyRegisterIndex ();
				if (emptyRegister == -1) {
					printf("****ERROR No Register Empty****");
					return;
				}
				fprintf(code, "\tPOP\t%s\n", Reg[emptyRegister]);
				fprintf(code, "\tMOV\t%s%d,\t%s\n", GET(root->child, lexeme), ST_getDeclId(st, GET(root->child, lexeme)), Reg[emptyRegister]);
				isRegEmpty[emptyRegister] = true;
			} else if (type == REAL_TYPE) {
				generateCodeUtility (root->child->next, code);
				emptyRegister = getEmptyRegisterIndex ();
				if (emptyRegister == -1) {
					printf("****ERROR No Register Empty****");
					return;
				}
				reg1 = emptyRegister;
				emptyRegister = getEmptyRegisterIndex ();
				if (emptyRegister == -1) {
					printf("****ERROR No Register Empty****");
					return;
				}
				reg2 = emptyRegister;
				fprintf(code, "\tPOP\t%s\n", Reg[reg2]);
				fprintf(code, "\tPOP\t%s\n", Reg[reg1]);
				fprintf(code, "\tLEA\tSI,\t%s%d\n", GET(root->child, lexeme), ST_getDeclId(st, GET(root->child, lexeme)));
				fprintf(code, "\tMOV\tWORD PTR[SI],\t%s\n", Reg[reg1]);
				fprintf(code, "\tMOV\tWORD PTR[SI + 2],\t%s\n", Reg[reg2]);
				isRegEmpty[reg1] = true;
				isRegEmpty[reg2] = true;
			} else if (type == CHAR_TYPE) {
				generateCodeUtility (root->child->next, code);
				emptyRegister = getEmptyRegisterIndex ();
				if (emptyRegister == -1) {
					printf("****ERROR No Register Empty****");
					return;
				}
				fprintf(code, "\tPOP\t%s\n", Reg[emptyRegister]);
				fprintf(code, "\tMOV\t%s%d,\t%c%s\n", GET(root->child, lexeme), ST_getDeclId(st, GET(root->child, lexeme)), Reg[emptyRegister][0], "L");
				isRegEmpty[emptyRegister] = true;
			}
		}
	} else if (root->sym == STRASSIGN) {
		ST* st;
		str_var *str;
		if (root->child->sym == STR_LENGTH) {
			st = root->child->child->scope;
			str = ST_getinfo(st, GET(root->child->child, lexeme), &key)->entry[key];
			int len = str->len;
			emptyRegister = getEmptyRegisterIndex ();
			if (emptyRegister == -1) {
				printf("****ERROR No Register Empty****");
				return;
			}
			if (len == 0) {
				fprintf (code, "\tLEA\tSI,\t%s%d\n", GET(root->child->child, lexeme), ST_getDeclId(st, GET(root->child->child, lexeme)));
				fprintf (code, "\tMOV\tsourceStringAddress,\tSI\n");
				fprintf (code, "\tCALL\tStringLength\n");
				fprintf(code, "\tPUSH\tCX\n");
				StringLengthUsed = true;
				fprintf (code, "\tPOP\t%s\n", Reg[emptyRegister]);
			} else {
				fprintf (code, "\tMOV\t%s,\t%d\n", Reg[emptyRegister], len);
			}
			fprintf (code, "\tMOV\t%s%d,\t%s\n", GET(root, lexeme), ST_getDeclId(st, GET(root, lexeme)), Reg[emptyRegister]);
			isRegEmpty[emptyRegister] = true;
		} else if (root->child->sym == ID || root->child->sym == INT_LIT) {
			st = root->child->child->scope;
			str = ST_getinfo(st, GET(root->child->child, lexeme), &key)->entry[key];
			fprintf (code, "\tLEA\tSI,\t%s%d\n", GET(root->child->child, lexeme), ST_getDeclId(st, GET(root->child->child, lexeme)));
			isRegEmpty[0] = false;
			isRegEmpty[1] = false;
			emptyRegister = 1;
			if (root->child->sym == ID) {
				fprintf (code, "\tMOV\t%s,\t%s%d\n", Reg[emptyRegister], GET(root->child, lexeme), ST_getDeclId(st, GET(root->child, lexeme)));
			} else {
				fprintf (code, "\tMOV\t%s,\t%s\n", Reg[emptyRegister], GET(root->child, lexeme));
			}
			fprintf (code, "\tMOV\tAL,\tBYTE PTR[SI + %s]\n", Reg[emptyRegister]);
			fprintf (code, "\tMOV\t%s%d,\tAL\n", GET(root, lexeme), ST_getDeclId(st, GET(root, lexeme)));
			isRegEmpty[emptyRegister] = true;
			isRegEmpty[0] = true;
		} else {
			st = root->scope;
			generateCodeUtility(root->child, code);
			fprintf(code, "\tLEA\tDI,\t%s%d\n", GET(root, lexeme), ST_getDeclId(st, GET(root, lexeme)));
			fprintf(code, "\tMOV\tdestinationStringAddress,\tDI\n");
			fprintf(code, "\tLEA\tSI,\ttempString1\n");
			fprintf(code, "\tMOV\tsourceStringAddress,\tSI\n");
			fprintf(code, "\tCALL\tCopyString\n");
			CopyStringUsed = true;
		}
	} else if (root->sym == MATASSIGN) {
		ST* st;
		mat_var *mat;
		if (root->child->sym == MAT_ROWS || root->child->sym == MAT_COLS) {
			st = root->child->scope;
			mat = ST_getinfo(st, GET(root->child, lexeme), &key)->entry[key];
			int rows;
			if (root->child->sym == MAT_ROWS) {
				rows = mat->rows;
			} else {
				rows = mat->cols;
			}
			emptyRegister = getEmptyRegisterIndex ();
			if (emptyRegister == -1) {
				printf("****ERROR No Register Empty****");
				return;
			}
			fprintf (code, "\tMOV\t%s,\t%d\n", Reg[emptyRegister], rows);
			fprintf (code, "\tMOV\t%s%d,\t%s\n", GET(root, lexeme), ST_getDeclId(st, GET(root, lexeme)), Reg[emptyRegister]);
			isRegEmpty[emptyRegister] = true;
		} else {
			st = root->scope;
			mat = ST_getinfo(st, GET(root, lexeme), &key)->entry[key];
			int rows = mat->rows, cols = mat->cols;
			generateCodeUtility(root->child, code);
			fprintf(code, "\tLEA\tDI,\t%s%d\n", GET(root, lexeme), ST_getDeclId(st, GET(root, lexeme)));
			fprintf(code, "\tMOV\tdestinationMatrixAddress,\tDI\n");
			fprintf(code, "\tLEA\tSI,\ttempMatrix1\n");
			fprintf(code, "\tMOV\tsourceMatrixAddress,\tSI\n");
			if (mat->type == INT_TYPE || mat->type == BOOL_TYPE) {
				fprintf(code, "\tMOV\tmatrixSize,\t%d\n", rows * cols);
				fprintf(code, "\tCALL\tCopyMatrix02\n");
				CopyMatrix02Used = true;
			} else if (mat->type == REAL_TYPE) {
				fprintf(code, "\tMOV\tmatrixSize,\t%d\n", rows * cols * 2);
				fprintf(code, "\tCALL\tCopyMatrix02\n");
				CopyMatrix02Used = true;
			} else {
				fprintf(code, "\tMOV\tmatrixSize,\t%d\n", rows * cols);
				fprintf(code, "\tCALL\tCopyMatrix01\n");
				CopyMatrix01Used = true;
			}
		}
	} else if (root->sym == row_list) {
		ST *st = root->parent->scope;
		mat_var *mat = ST_getinfo(st, GET(root->parent, lexeme), &key)->entry[key];
		Type type = mat->type;
		int i, rows = (int)(root->value), index = 0;
		TreeNode *node_row = root->child;
		LL_Node *list = NULL;
		fprintf(code, "\tLEA\tSI,\ttempMatrix1\n");
		for (i = 0; i < rows; i++) {
			list = (LL_Node*)node_row->value;
			while (list != NULL) {
				if (type == INT_TYPE) {
					fprintf(code, "\tMOV\tWORD PTR[SI + %d],\t%s\n", index, GET(list, lexeme));
					index += 2;
				} else if (type == REAL_TYPE) {
					char integerPart[10], decimalPart[10], Lexeme[22];
					int k = 0, l = 0;
					strcpy(Lexeme, GET(list, lexeme));
					while (Lexeme[k] != '.') {
						integerPart[k] = Lexeme[k];
						k++;
					}
					integerPart[k++] = '\0';
					while ((Lexeme[k] != '\0') && (l < 3)) {
						decimalPart[l++] = Lexeme[k++];
					}
					decimalPart[l] = '\0';
					fprintf(code, "\tMOV\tWORD PTR[SI + %d],\t%s\n", index, integerPart);
					index += 2;
					fprintf(code, "\tMOV\tWORD PTR[SI + %d],\t%s\n", index, decimalPart);
					index += 2;
				} else if (type == BOOL_TYPE){
					if (strcmp(GET(list, lexeme), "False") == 0) {
						fprintf (code, "\tMOV\tBYTE PTR[SI + %d],\t%s\n", index, "0");
					} else {
						fprintf (code, "\tMOV\tBYTE PTR[SI + %d],\t%s\n", index, "1");
					}
					index += 2;
				} else {
					fprintf (code, "\tMOV\tBYTE PTR[SI + %d],\t%s\n", index, GET(list, lexeme));
					index++;
				}
				list = list->next;
			}
			node_row = node_row->next;
		}
	} else if (root->sym == row) {
		ST *st = root->parent->scope;
		mat_var *mat = ST_getinfo(st, GET(root->parent, lexeme), &key)->entry[key];
		Type type = mat->type;
		LL_Node *list = (LL_Node*)root->value;
		fprintf(code, "\tLEA\tSI,\ttempMatrix1\n");
		int index = 0;
		while (list != NULL) {
			if (type == INT_TYPE) {
				fprintf(code, "\tMOV\tWORD PTR[SI + %d],\t%s\n", index, GET(list, lexeme));
				index += 2;
			} else if (type == REAL_TYPE) {
				char integerPart[10], decimalPart[10], Lexeme[22];
				int k = 0, l = 0;
				strcpy(Lexeme, GET(list, lexeme));
				while (Lexeme[k] != '.') {
					integerPart[k] = Lexeme[k];
					k++;
				}
				integerPart[k++] = '\0';
				while ((Lexeme[k] != '\0') && (l < 3)) {
					decimalPart[l++] = Lexeme[k++];
				}
				decimalPart[l] = '\0';
				fprintf(code, "\tMOV\tWORD PTR[SI + %d],\t%s\n", index, integerPart);
				index += 2;
				fprintf(code, "\tMOV\tWORD PTR[SI + %d],\t%s\n", index, decimalPart);
				index += 2;
			} else if (type == BOOL_TYPE){
				if (strcmp(GET(list, lexeme), "False") == 0) {
					fprintf (code, "\tMOV\tBYTE PTR[SI + %d],\t%s\n", index, "0");
				} else {
					fprintf (code, "\tMOV\tBYTE PTR[SI + %d],\t%s\n", index, "1");
				}
				index += 2;
			} else {
				fprintf (code, "\tMOV\tBYTE PTR[SI + %d],\t%s\n", index, GET(list, lexeme));
				index++;
			}
			list = list->next;
		}
	} else if (root->sym == GE || root->sym == GT || root->sym == LE || root->sym == LT || root->sym == EQ || root->sym == NEQ) {
		int currentLabel = LabelNumber++;
		ST* st;
		Type type;
		if (root->child->sym == ID_PRI) {
			st = root->child->scope;
			type = ST_getinfo(st, GET(root->child, lexeme), &key)->type[key];
		}
		if (root->child->sym == REAL_LIT || (root->child->sym == ID_PRI && type == REAL_TYPE)) {
			generateCodeUtility (root->child, code);
			generateCodeUtility (root->child->next, code);
			emptyRegister = getEmptyRegisterIndex ();
			if (emptyRegister == -1) {
				printf("****ERROR No Register Empty****");
				return;
			}
			reg1 = emptyRegister;
			emptyRegister = getEmptyRegisterIndex ();
			if (emptyRegister == -1) {
				printf("****ERROR No Register Empty****");
				return;
			}
			reg2 = emptyRegister;
			emptyRegister = getEmptyRegisterIndex ();
			if (emptyRegister == -1) {
				printf("****ERROR No Register Empty****");
				return;
			}
			reg3 = emptyRegister;
			emptyRegister = getEmptyRegisterIndex ();
			if (emptyRegister == -1) {
				printf("****ERROR No Register Empty****");
				return;
			}
			reg4 = emptyRegister;
			fprintf(code, "\tPOP\t%s\n", Reg[reg4]);
			fprintf(code, "\tPOP\t%s\n", Reg[reg3]);
			fprintf(code, "\tPOP\t%s\n", Reg[reg2]);
			fprintf(code, "\tPOP\t%s\n", Reg[reg1]);
			fprintf(code, "\tCMP\t%s,\t%s\n", Reg[reg1], Reg[reg3]);
			if (root->sym == GE || root->sym == GT) {
				fprintf (code, "\tJE\tRealCompareFractionalPart_%d\n", currentLabel);
				fprintf (code, "\tJG\tRealGreater_%d\n", currentLabel);
				fprintf (code, "\tJMP\tRealLess_%d\n", currentLabel);
				fprintf (code, "RealCompareFractionalPart_%d:\n", currentLabel);
				fprintf (code, "\tCMP\t%s,\t%s\n", Reg[reg2], Reg[reg4]);
				fprintf (code, "\tJE\tRealEqual_%d\n", currentLabel);
				fprintf (code, "\tJG\tRealGreater_%d\n", currentLabel);
				fprintf (code, "RealLess_%d:\n", currentLabel);
				fprintf (code, "\tMOV\t%s,\t0\n", Reg[reg1]);
				fprintf (code, "\tPUSH\t%s\n", Reg[reg1]);
				fprintf (code, "\tJMP\tRealGTEEnd_%d\n", currentLabel);
				fprintf (code, "RealGreater_%d:\n", currentLabel);
				fprintf (code, "\tMOV\t%s,\t1\n", Reg[reg1]);
				fprintf (code, "\tPUSH\t%s\n", Reg[reg1]);
				fprintf (code, "\tJMP\tRealGTEEnd_%d\n", currentLabel);
				fprintf (code, "RealEqual_%d:\n", currentLabel);
				if (root->sym == GT) {
					fprintf (code, "\tMOV\t%s,\t0\n", Reg[reg1]);
				} else {
					fprintf (code, "\tMOV\t%s,\t1\n", Reg[reg1]);
				}
				fprintf (code, "\tPUSH\t%s\n", Reg[reg1]);
				fprintf (code, "RealGTEEnd_%d:\n", currentLabel);
			} else if (root->sym == LE || root->sym == LT) {
				fprintf (code, "\tJE\tRealCompareFractionalPart_%d\n", currentLabel);
				fprintf (code, "\tJG\tRealGreater_%d\n", currentLabel);
				fprintf (code, "\tJMP\tRealLess_%d\n", currentLabel);
				fprintf (code, "RealCompareFractionalPart_%d:\n", currentLabel);
				fprintf (code, "\tCMP\t%s,\t%s\n", Reg[reg2], Reg[reg4]);
				fprintf (code, "\tJE\tRealEqual_%d\n", currentLabel);
				fprintf (code, "\tJG\tRealGreater_%d\n", currentLabel);
				fprintf (code, "RealLess_%d:\n", currentLabel);
				fprintf (code, "\tMOV\t%s,\t1\n", Reg[reg1]);
				fprintf (code, "\tPUSH\t%s\n", Reg[reg1]);
				fprintf (code, "\tJMP\tRealLTEEnd_%d\n", currentLabel);
				fprintf (code, "RealGreater_%d:\n", currentLabel);
				fprintf (code, "\tMOV\t%s,\t0\n", Reg[reg1]);
				fprintf (code, "\tPUSH\t%s\n", Reg[reg1]);
				fprintf (code, "\tJMP\tRealLTEEnd_%d\n", currentLabel);
				fprintf (code, "RealEqual_%d:\n", currentLabel);
				if (root->sym == LT) {
					fprintf (code, "\tMOV\t%s,\t0\n", Reg[reg1]);
				} else {
					fprintf (code, "\tMOV\t%s,\t1\n", Reg[reg1]);
				}
				fprintf (code, "\tPUSH\t%s\n", Reg[reg1]);
				fprintf (code, "RealLTEEnd_%d:\n", currentLabel);
			} else {
				fprintf (code, "\tJE\tRealCheckFractional_%d\n", currentLabel);
				fprintf (code, "\tJMP\tRealNotEqual_%d\n", currentLabel);
				fprintf (code, "RealCheckFractional_%d:\n", currentLabel);
				fprintf (code, "\tCMP\t%s,\t%s\n", Reg[reg2], Reg[reg4]);
				fprintf (code, "\tJE\tRealEqual_%d\n", currentLabel);
				fprintf (code, "RealNotEqual_%d:\n", currentLabel);
				if (root->sym == EQ) {
					fprintf (code, "\tMOV\t%s,\t0\n", Reg[reg1]);
				} else {
					fprintf (code, "\tMOV\t%s,\t1\n", Reg[reg1]);
				}
				fprintf (code, "\tPUSH\t%s\n", Reg[reg1]);
				fprintf (code, "\tJMP\tRealENEEnd_%d\n", currentLabel);
				fprintf (code, "RealEqual_%d:\n", currentLabel);
				if (root->sym == EQ) {
					fprintf (code, "\tMOV\t%s,\t1\n", Reg[reg1]);
				} else {
					fprintf (code, "\tMOV\t%s,\t0\n", Reg[reg1]);
				}
				fprintf (code, "\tPUSH\t%s\n", Reg[reg1]);
				fprintf (code, "RealENEEnd_%d:\n", currentLabel);
			}
			isRegEmpty[reg1] = true;
			isRegEmpty[reg2] = true;
			isRegEmpty[reg3] = true;
			isRegEmpty[reg4] = true;
		} else if (root->child->sym == INT_LIT || (root->child->sym == ID_PRI && type == INT_TYPE)) {
			generateCodeUtility (root->child, code);
			generateCodeUtility (root->child->next, code);
			emptyRegister = getEmptyRegisterIndex ();
			if (emptyRegister == -1) {
				printf("****ERROR No Register Empty****");
				return;
			}
			reg1 = emptyRegister;
			emptyRegister = getEmptyRegisterIndex ();
			if (emptyRegister == -1) {
				printf("****ERROR No Register Empty****");
				return;
			}
			reg2 = emptyRegister;
			fprintf(code, "\tPOP\t%s\n", Reg[reg2]);
			fprintf(code, "\tPOP\t%s\n", Reg[reg1]);
			fprintf(code, "\tCMP\t%s,\t%s\n", Reg[reg1], Reg[reg2]);
			if (root->sym == GE || root->sym == GT) {
				if (root->sym == GE) {
					fprintf(code, "\tJGE\tIntegerGreaterThanLabel_%d\n", currentLabel);
				} else {
					fprintf(code, "\tJG\tIntegerGreaterThanLabel_%d\n ", currentLabel);
				}
				fprintf(code, "\tMOV\t%s,\t0\n", Reg[reg1]);
				fprintf(code, "\tPUSH\t%s\n", Reg[reg1]);
				fprintf(code, "\tJMP\tIntegerGreaterThanEndPart_%d\n", currentLabel);
				fprintf(code, "IntegerGreaterThanLabel_%d:\n", currentLabel);
				fprintf(code, "\tMOV\t%s,\t1\n", Reg[reg1]);
				fprintf(code, "\tPUSH\t%s\n", Reg[reg1]);
				fprintf(code, "IntegerGreaterThanEndPart_%d:\n", currentLabel);
			} else if (root->sym == LE || root->sym == LT) {
				if (root->sym == LE) {
					fprintf(code, "\tJLE\tIntegerLessThanLabel_%d\n", currentLabel);
				} else {
					fprintf(code, "\tJL\tIntegerLessThanLabel_%d\n ", currentLabel);
				}
				fprintf(code, "\tMOV\t%s,\t0\n", Reg[reg1]);
				fprintf(code, "\tPUSH\t%s\n", Reg[reg1]);
				fprintf(code, "\tJMP\tIntegerLessThanEndPart_%d\n", currentLabel);
				fprintf(code, "IntegerLessThanLabel_%d:\n", currentLabel);
				fprintf(code, "\tMOV\t%s,\t1\n", Reg[reg1]);
				fprintf(code, "\tPUSH\t%s\n", Reg[reg1]);
				fprintf(code, "IntegerLessThanEndPart_%d:\n", currentLabel);
			} else {
				if (root->sym == EQ) {
					fprintf(code, "\tJE\tIntegerEqualLabel_%d\n", currentLabel);
					fprintf(code, "\tMOV\t%s,\t0\n", Reg[reg1]);
					fprintf(code, "\tPUSH\t%s\n", Reg[reg1]);
					fprintf(code, "\tJMP\tIntegerEqualEndLabel_%d\n", currentLabel);
					fprintf(code, "IntegerEqualLabel_%d:\n", currentLabel);
					fprintf(code, "\tMOV\t%s,\t1\n", Reg[reg1]);
					fprintf(code, "\tPUSH\t%s\n", Reg[reg1]);
					fprintf(code, "IntegerEqualEndLabel_%d:\n", currentLabel);
				} else {
					fprintf(code, "\tJNE\tIntegerNotEqualLabel_%d\n", currentLabel);
					fprintf(code, "\tMOV\t%s,\t0\n", Reg[reg1]);
					fprintf(code, "\tPUSH\t%s\n", Reg[reg1]);
					fprintf(code, "\tJMP\tIntegerNotEqualEndLabel_%d\n", currentLabel);
					fprintf(code, "IntegerNotEqualLabel_%d:\n", currentLabel);
					fprintf(code, "\tMOV\t%s,\t1\n", Reg[reg1]);
					fprintf(code, "\tPUSH\t%s\n", Reg[reg1]);
					fprintf(code, "IntegerNotEqualEndLabel_%d:\n", currentLabel);
				}
			}
			isRegEmpty[reg1] = true;
			isRegEmpty[reg2] = true;
		}
	} else if (root->sym == AND || root->sym == OR) {
		int currentLabel = LabelNumber++;
		generateCodeUtility (root->child, code);
		generateCodeUtility (root->child->next, code);
		emptyRegister = getEmptyRegisterIndex ();
		if (emptyRegister == -1) {
			printf("****ERROR No Register Empty****");
			return;
		}
		reg1 = emptyRegister;
		emptyRegister = getEmptyRegisterIndex ();
		if (emptyRegister == -1) {
			printf("****ERROR No Register Empty****");
			return;
		}
		reg2 = emptyRegister;
		fprintf(code, "\tPOP\t%s\n", Reg[reg2]);
		fprintf(code, "\tPOP\t%s\n", Reg[reg1]);
		if (root->sym == AND) {
			fprintf(code, "\tAND\t%s,\t%s\n", Reg[reg1], Reg[reg2]);
		} else {
			fprintf(code, "\tOR\t%s,\t%s\n", Reg[reg1], Reg[reg2]);
		}
		fprintf(code, "\tCMP\t%s,\t0\n", Reg[reg1]);
		fprintf(code, "\tJE\tLogicalLabel_%d\n", currentLabel);
		fprintf(code, "\tMOV\t%s,\t1\n", Reg[reg1]);
		fprintf(code, "\tPUSH\t%s\n", Reg[reg1]);
		fprintf(code, "\tJMP\tLogicalLabelEnd_%d\n", currentLabel);
		fprintf(code, "LogicalLabel_%d:\n", currentLabel);
		fprintf(code, "\tPUSH\t%s\n", Reg[reg1]);
		fprintf(code, "LogicalLabelEnd_%d:\n", currentLabel);
		isRegEmpty[reg1] = true;
		isRegEmpty[reg2] = true;
	} else if (root->sym == NOT) {
		int currentLabel = LabelNumber++;
		generateCodeUtility (root->child, code);
		emptyRegister = getEmptyRegisterIndex ();
		if (emptyRegister == -1) {
			printf("****ERROR No Register Empty****");
			return;
		}
		fprintf(code, "\tPOP\t%s\n", Reg[emptyRegister]);
		fprintf(code, "\tCMP\t%s,\t0\n", Reg[emptyRegister]);
		fprintf(code, "\tJE\tNotLabel_%d\n", currentLabel);
		fprintf(code, "\tMOV\t%s,\t0\n", Reg[emptyRegister]);
		fprintf(code, "\tPUSH\t%s\n", Reg[emptyRegister]);
		fprintf(code, "\tJMP\tNotLabelEnd_%d\n", currentLabel);
		fprintf(code, "NotLabel_%d:\n", currentLabel);
		fprintf(code, "\tMOV\t%s,\t1\n", Reg[emptyRegister]);
		fprintf(code, "\tPUSH\t%s\n", Reg[emptyRegister]);
		fprintf(code, "NotLabelEnd_%d:\n", currentLabel);
		isRegEmpty[emptyRegister] = true;
	} else if (root->sym == PLUS) {
		ST* st = ST_getinfo(root->child->scope, GET(root->child, lexeme), &key);
		Type type;
		if (key == -1) {
			if (root->child->sym == INT_LIT) {
				type = INT_TYPE;
			} else if (root->child->sym == STR_LIT) {
				type = STR_TYPE;
			} else if (root->child->sym == REAL_LIT) {
				type = REAL_TYPE;
			}
		} else {
			type = st->type[key];
		}
		if (type == INT_TYPE) {
			generateCodeUtility(root->child, code);
			generateCodeUtility(root->child->next, code);
			emptyRegister = getEmptyRegisterIndex ();
			if (emptyRegister == -1) {
				printf("****ERROR No Register Empty****");
				return;
			}
			reg1 = emptyRegister;
			emptyRegister = getEmptyRegisterIndex ();
			if (emptyRegister == -1) {
				printf("****ERROR No Register Empty****");
				return;
			}
			reg2 = emptyRegister;
			fprintf(code, "\tPOP\t%s\n", Reg[reg2]);
			fprintf(code, "\tPOP\t%s\n", Reg[reg1]);
			fprintf(code, "\tADD\t%s,\t%s\n", Reg[reg1], Reg[reg2]);
			fprintf(code, "\tPUSH\t%s\n", Reg[reg1]);
			isRegEmpty[reg1] = true;
			isRegEmpty[reg2] = true;
		} else if (type == REAL_TYPE) {
			int currentLabel = LabelNumber++;
			generateCodeUtility(root->child, code);
			generateCodeUtility(root->child->next, code);
			emptyRegister = getEmptyRegisterIndex ();
			if (emptyRegister == -1) {
				printf("****ERROR No Register Empty****");
				return;
			}
			reg1 = emptyRegister;
			emptyRegister = getEmptyRegisterIndex ();
			if (emptyRegister == -1) {
				printf("****ERROR No Register Empty****");
				return;
			}
			reg2 = emptyRegister;
			emptyRegister = getEmptyRegisterIndex ();
			if (emptyRegister == -1) {
				printf("****ERROR No Register Empty****");
				return;
			}
			reg3 = emptyRegister;
			emptyRegister = getEmptyRegisterIndex ();
			if (emptyRegister == -1) {
				printf("****ERROR No Register Empty****");
				return;
			}
			reg4 = emptyRegister;
			fprintf(code, "\tPOP\t%s\n", Reg[reg4]);
			fprintf(code, "\tPOP\t%s\n", Reg[reg3]);
			fprintf(code, "\tPOP\t%s\n", Reg[reg2]);
			fprintf(code, "\tPOP\t%s\n", Reg[reg1]);
			fprintf(code, "\tADD\t%s,\t%s\n", Reg[reg2], Reg[reg4]);
			fprintf(code, "\tCMP\t%s,\t1000\n", Reg[reg2]);
			fprintf(code, "\tJL\tNoAddCarry_%d\n", currentLabel);
			fprintf(code, "\tSUB\t%s,\t1000\n", Reg[reg2]);
			fprintf(code, "\tADD\t%s,\t%s\n", Reg[reg1], Reg[reg3]);
			fprintf(code, "\tINC\t%s\n", Reg[reg1]);
			fprintf(code, "\tJMP\tAddEndPart_%d\n", currentLabel);
			fprintf(code, "NoAddCarry_%d:\n", currentLabel);
			fprintf(code, "\tADD\t%s,\t%s\n", Reg[reg1], Reg[reg3]);
			fprintf(code, "AddEndPart_%d:\n", currentLabel);
			fprintf(code, "\tPUSH\t%s\n", Reg[reg1]);
			fprintf(code, "\tPUSH\t%s\n", Reg[reg2]);
			isRegEmpty[0] = true;
			isRegEmpty[1] = true;
			isRegEmpty[2] = true;
			isRegEmpty[3] = true;
		} else if (type == STR_TYPE) {
			generateCodeUtility(root->child->next, code);
			fprintf(code, "\tLEA\tSI,\ttempString1\n");
			fprintf(code, "\tMOV\tsourceStringAddress,\tSI\n");
			fprintf(code, "\tLEA\tDI,\ttempString3\n");
			fprintf(code, "\tMOV\tdestinationStringAddress,\tDI\n");
			fprintf(code, "\tCALL\tCopyString\n");
			CopyStringUsed = true;
			generateCodeUtility(root->child, code);
			fprintf(code, "\tLEA\tSI,\ttempString1\n");
			fprintf(code, "\tMOV\tsourceStringAddress,\tSI\n");
			fprintf(code, "\tLEA\tDI,\ttempString2\n");
			fprintf(code, "\tMOV\tdestinationStringAddress,\tDI\n");
			fprintf(code, "\tCALL\tCopyString\n");
			CopyStringUsed = true;
			fprintf(code, "\tCALL\tConcatString\n");
			ConcatStringUsed = true;
		}
		if (root->child->sym == ID_MAT) {
			ST *st = root->child->scope;
			mat_var *mat = ST_getinfo(st, GET(root->child, lexeme), &key)->entry[key];
			int rows = mat->rows, cols = mat->cols;
			generateCodeUtility(root->child->next, code);
			fprintf(code, "\tLEA\tSI,\ttempMatrix1\n");
			fprintf(code, "\tMOV\tsourceMatrixAddress,\tSI\n");
			fprintf(code, "\tLEA\tDI,\ttempMatrix2\n");
			fprintf(code, "\tMOV\tdestinationMatrixAddress,\tDI\n");
			fprintf(code, "\tMOV\tmatrixSize,\t%d\n", rows * cols);
			fprintf(code, "\tCALL\tCopyMatrix02\n");
			CopyMatrix02Used = true;
			generateCodeUtility(root->child, code);
			fprintf(code, "\tCALL\tAddMatrix\n");
			AddMatrixUsed = true;
		}
	} else if (root->sym == MINUS) {
		ST* st = ST_getinfo(root->child->scope, GET(root->child, lexeme), &key);
		Type type;
		if (key == -1) {
			if (root->child->sym == INT_LIT) {
				type = INT_TYPE;
			} else if (root->child->sym == REAL_LIT) {
				type = REAL_TYPE;
			}
		} else {
			type = st->type[key];
		}
		if (type == INT_TYPE) {
			generateCodeUtility(root->child, code);
			generateCodeUtility(root->child->next, code);
			emptyRegister = getEmptyRegisterIndex ();
			if (emptyRegister == -1) {
				printf("****ERROR No Register Empty****");
				return;
			}
			reg1 = emptyRegister;
			emptyRegister = getEmptyRegisterIndex ();
			if (emptyRegister == -1) {
				printf("****ERROR No Register Empty****");
				return;
			}
			reg2 = emptyRegister;
			fprintf(code, "\tPOP\t%s\n", Reg[reg2]);
			fprintf(code, "\tPOP\t%s\n", Reg[reg1]);
			fprintf(code, "\tSUB\t%s,\t%s\n", Reg[reg1], Reg[reg2]);
			fprintf(code, "\tPUSH\t%s\n", Reg[reg1]);
			isRegEmpty[reg1] = true;
			isRegEmpty[reg2] = true;
		} else if (type == REAL_TYPE) {
			int currentLabel = LabelNumber++;
			generateCodeUtility(root->child, code);
			generateCodeUtility(root->child->next, code);
			emptyRegister = getEmptyRegisterIndex ();
			if (emptyRegister == -1) {
				printf("****ERROR No Register Empty****");
				return;
			}
			reg1 = emptyRegister;
			emptyRegister = getEmptyRegisterIndex ();
			if (emptyRegister == -1) {
				printf("****ERROR No Register Empty****");
				return;
			}
			reg2 = emptyRegister;
			emptyRegister = getEmptyRegisterIndex ();
			if (emptyRegister == -1) {
				printf("****ERROR No Register Empty****");
				return;
			}
			reg3 = emptyRegister;
			emptyRegister = getEmptyRegisterIndex ();
			if (emptyRegister == -1) {
				printf("****ERROR No Register Empty****");
				return;
			}
			reg4 = emptyRegister;
			fprintf(code, "\tPOP\t%s\n", Reg[reg4]);
			fprintf(code, "\tPOP\t%s\n", Reg[reg3]);
			fprintf(code, "\tPOP\t%s\n", Reg[reg2]);
			fprintf(code, "\tPOP\t%s\n", Reg[reg1]);
			fprintf(code, "\tCMP\t%s,\t%s\n", Reg[reg2], Reg[reg4]);
			fprintf(code, "\tJL\tBorrowCase_%d\n", currentLabel);
			fprintf(code, "\tSUB\t%s,\t%s\n", Reg[reg2], Reg[reg4]);
			fprintf(code, "\tSUB\t%s,\t%s\n", Reg[reg1], Reg[reg3]);
			fprintf(code, "\tJMP\tSubEndPart_%d\n", currentLabel);
			fprintf(code, "\tBorrowCase_%d:\n", currentLabel);
			fprintf(code, "\tADD\t%s,\t1000\n", Reg[reg2]);
			fprintf(code, "\tSUB\t%s,\t%s\n", Reg[reg2], Reg[reg4]);
			fprintf(code, "\tDEC\t%s\n", Reg[reg1]);
			fprintf(code, "\tSUB\t%s,\t%s\n", Reg[reg1], Reg[reg3]);
			fprintf(code, "\tSubEndPart_%d:\n", currentLabel);
			fprintf(code, "\tPUSH\t%s\n", Reg[reg1]);
			fprintf(code, "\tPUSH\t%s\n", Reg[reg2]);
			isRegEmpty[0] = true;
			isRegEmpty[1] = true;
			isRegEmpty[2] = true;
			isRegEmpty[3] = true;
		}
	} else if (root->sym == MUL) {
		ST* st = ST_getinfo(root->child->scope, GET(root->child, lexeme), &key);
		Type type;
		if (key == -1) {
			if (root->child->sym == INT_LIT) {
				type = INT_TYPE;
			}
		} else {
			type = st->type[key];
		}
		if (type == INT_TYPE) {
			generateCodeUtility(root->child, code);
			generateCodeUtility(root->child->next, code);
			isRegEmpty[0] = false;
			isRegEmpty[3] = false;
			emptyRegister = getEmptyRegisterIndex ();
			if (emptyRegister == -1) {
				printf("****ERROR No Register Empty****");
				return;
			}
			fprintf(code, "\tPOP\t%s\n", Reg[emptyRegister]);
			fprintf(code, "\tPOP\t%s\n", "AX");
			fprintf(code, "\tIMUL\t%s\n", Reg[emptyRegister]);
			fprintf(code, "\tPUSH\t%s\n", "AX");
			isRegEmpty[0] = true;
			isRegEmpty[3] = true;
			isRegEmpty[emptyRegister] = true;
		}
	} else if (root->sym == DIV) {
		ST* st = ST_getinfo(root->child->scope, GET(root->child, lexeme), &key);
		Type type;
		if (key == -1) {
			if (root->child->sym == INT_LIT) {
				type = INT_TYPE;
			}
		} else {
			type = st->type[key];
		}
		if (type == INT_TYPE) {
			generateCodeUtility(root->child, code);
			generateCodeUtility(root->child->next, code);
			isRegEmpty[0] = false;
			isRegEmpty[3] = false;
			emptyRegister = getEmptyRegisterIndex ();
			if (emptyRegister == -1) {
				printf("****ERROR No Register Empty****");
				return;
			}
			fprintf(code, "\tPOP\t%s\n", Reg[emptyRegister]);
			fprintf(code, "\tPOP\t%s\n", "AX");
			fprintf(code, "\tCWD\n");
			fprintf(code, "\tIDIV\t%s\n", Reg[emptyRegister]);
			fprintf(code, "\tPUSH\t%s\n", "AX");
			isRegEmpty[0] = true;
			isRegEmpty[3] = true;
			isRegEmpty[emptyRegister] = true;
		}
	} else if (root->sym == MOD) {
		ST* st = ST_getinfo(root->child->scope, GET(root->child, lexeme), &key);
		Type type;
		if (key == -1) {
			if (root->child->sym == INT_LIT) {
				type = INT_TYPE;
			}
		} else {
			type = st->type[key];
		}
		if (type == INT_TYPE) {
			generateCodeUtility(root->child, code);
			generateCodeUtility(root->child->next, code);
			isRegEmpty[0] = false;
			isRegEmpty[3] = false;
			emptyRegister = getEmptyRegisterIndex ();
			if (emptyRegister == -1) {
				printf("****ERROR No Register Empty****");
				return;
			}
			fprintf(code, "\tPOP\t%s\n", Reg[emptyRegister]);
			fprintf(code, "\tPOP\t%s\n", "AX");
			fprintf(code, "\tCWD\n");
			fprintf(code, "\tIDIV\t%s\n", Reg[emptyRegister]);
			fprintf(code, "\tPUSH\t%s\n", "DX");
			isRegEmpty[0] = true;
			isRegEmpty[3] = true;
			isRegEmpty[emptyRegister] = true;
		}
	} else if (root->sym == POW) {
		ST* st = ST_getinfo(root->child->scope, GET(root->child, lexeme), &key);
		Type type;
		if (key == -1) {
			if (root->child->sym == INT_LIT) {
				type = INT_TYPE;
			}
		} else {
			type = st->type[key];
		}
		if (type == INT_TYPE) {
			generateCodeUtility(root->child, code);
			generateCodeUtility(root->child->next, code);
			fprintf(code, "\tPOP\tCX\n");
			fprintf(code, "\tPOP\tAX\n");
			fprintf(code, "\tCALL\tPowerProc\n");
			fprintf(code, "\tPUSH\tAX\n");
			PowerProcUsed = true;
		}
	} else if (root->sym == ID_PRI) {
		ST* st = root->scope;
		Type type = ST_getinfo(st, GET(root, lexeme), &key)->type[key];
		if (type == BOOL_TYPE || type == INT_TYPE) {
			emptyRegister = getEmptyRegisterIndex ();
			if (emptyRegister == -1) {
				printf("****ERROR No Register Empty****");
				return;
			}
			fprintf (code, "\tMOV\t%s,\t%s%d\n", Reg[emptyRegister], GET(root, lexeme), ST_getDeclId(st, GET(root, lexeme)));
			fprintf (code, "\tPUSH\t%s\n", Reg[emptyRegister]);
			isRegEmpty[emptyRegister] = true;
		} else if(type == REAL_TYPE) {
			fprintf(code, "\tLEA\tSI,\t%s%d\n", GET(root, lexeme), ST_getDeclId(st, GET(root, lexeme)));
			fprintf(code, "\tPUSH\tWORD PTR[SI]\n");
			fprintf(code, "\tPUSH\tWORD PTR[SI + 2]\n");
		} else if(type == CHAR_TYPE) {
			emptyRegister = getEmptyRegisterIndex ();
			if (emptyRegister == -1) {
				printf("****ERROR No Register Empty****");
				return;
			}
			fprintf(code, "\tXOR\tAX,\tAX\n");
			fprintf (code, "\tMOV\t%c%s,\t%s%d\n", Reg[emptyRegister][0], "L", GET(root, lexeme), ST_getDeclId(st, GET(root, lexeme)));
			fprintf (code, "\tPUSH\t%s\n", Reg[emptyRegister]);
			isRegEmpty[emptyRegister] = true;
		}
	} else if (root->sym == ID) {
		ST* st = root->scope;
		Type type = ST_getinfo(st, GET(root, lexeme), &key)->type[key];
		if (type == BOOL_TYPE || type == INT_TYPE) {
			emptyRegister = getEmptyRegisterIndex ();
			if (emptyRegister == -1) {
				printf("****ERROR No Register Empty****");
				return;
			}
			fprintf (code, "\tMOV\t%s,\t%s%d\n", Reg[emptyRegister], GET(root, lexeme), ST_getDeclId(st, GET(root, lexeme)));
			fprintf (code, "\tPUSH\t%s\n", Reg[emptyRegister]);
			isRegEmpty[emptyRegister] = true;
		} else if(type == REAL_TYPE) {
			fprintf(code, "\tLEA\tSI,\t%s%d\n", GET(root, lexeme), ST_getDeclId(st, GET(root, lexeme)));
			fprintf(code, "\tPUSH\tWORD PTR[SI]\n");
			fprintf(code, "\tPUSH\tWORD PTR[SI + 2]\n");
		} else if(type == CHAR_TYPE) {
			emptyRegister = getEmptyRegisterIndex ();
			if (emptyRegister == -1) {
				printf("****ERROR No Register Empty****");
				return;
			}
			fprintf(code, "\tXOR\tAX,\tAX\n");
			fprintf (code, "\tMOV\t%c%s,\t%s%d\n", Reg[emptyRegister][0], "L", GET(root, lexeme), ST_getDeclId(st, GET(root, lexeme)));
			fprintf (code, "\tPUSH\t%s\n", Reg[emptyRegister]);
			isRegEmpty[emptyRegister] = true;
		} else if (type == STR_TYPE) {
			fprintf(code, "\tLEA\tSI,\t%s%d\n", GET(root, lexeme), ST_getDeclId(st, GET(root, lexeme)));
			fprintf(code, "\tMOV\tsourceStringAddress,\tSI\n");
			fprintf(code, "\tLEA\tDI,\ttempString1\n");
			fprintf(code, "\tMOV\tdestinationStringAddress,\tDI\n");
			fprintf(code, "\tCALL\tCopyString\n");
			CopyStringUsed = true;
		}
	} else if(root->sym == INT_LIT) {
		emptyRegister = getEmptyRegisterIndex ();
		if (emptyRegister == -1) {
			printf("****ERROR No Register Empty****");
			return;
		}
		fprintf (code, "\tMOV\t%s,\t%s\n", Reg[emptyRegister], GET(root, lexeme));
		fprintf (code, "\tPUSH\t%s\n", Reg[emptyRegister]);
		isRegEmpty[emptyRegister] = true;
	} else if(root->sym == REAL_LIT) {
		char integerPart[10], decimalPart[10], Lexeme[22];
		int i, j;
		strcpy(Lexeme, GET(root, lexeme));
		emptyRegister = getEmptyRegisterIndex ();
		if (emptyRegister == -1) {
			printf("****ERROR No Register Empty****");
			return;
		}
		reg1 = emptyRegister;
		emptyRegister = getEmptyRegisterIndex ();
		if (emptyRegister == -1) {
			printf("****ERROR No Register Empty****");
			return;
		}
		reg2 = emptyRegister;
		j = 0;
		i = 0;
		while (Lexeme[i] != '.') {
			integerPart[i] = Lexeme[i];
			i++;
		}
		integerPart[i++] = '\0';
		while ((Lexeme[i] != '\0') && (j < 3)) {
			decimalPart[j++] = Lexeme[i++];
		}
		decimalPart[j] = '\0';
		fprintf(code, "\tMOV\t%s,\t%s\n", Reg[reg1], integerPart);
		fprintf(code, "\tMOV\t%s,\t%s\n", Reg[reg2], decimalPart);
		fprintf(code, "\tPUSH\t%s\n", Reg[reg1]);
		fprintf(code, "\tPUSH\t%s\n", Reg[reg2]);
		isRegEmpty[reg1] = true;
		isRegEmpty[reg2] = true;
	} else if(root->sym == BOOL_LIT) {
		emptyRegister = getEmptyRegisterIndex ();
		if (emptyRegister == -1) {
			printf("****ERROR No Register Empty****");
			return;
		}
		if (strcmp(GET(root, lexeme), "False") == 0) {
			fprintf (code, "\tMOV\t%c%s,\t%s\n", Reg[emptyRegister], "0");
		} else {
			fprintf (code, "\tMOV\t%c%s,\t%s\n", Reg[emptyRegister], "1");
		}
		fprintf (code, "\tPUSH\t%c%s\n", Reg[emptyRegister]);
		isRegEmpty[emptyRegister] = true;
	} else if(root->sym == CHAR_LIT) {
		emptyRegister = getEmptyRegisterIndex ();
		if (emptyRegister == -1) {
			printf("****ERROR No Register Empty****");
			return;
		}
		fprintf(code, "\tXOR\tAX,\tAX\n");
		fprintf (code, "\tMOV\t%c%s,\t%s\n", Reg[emptyRegister][0], "L", GET(root, lexeme));
		fprintf (code, "\tPUSH\t%s\n", Reg[emptyRegister]);
		isRegEmpty[emptyRegister] = true;
	} else if (root->sym == STR_LIT) {
		int i;
		char Lexeme[100];
		strcpy (Lexeme, GET(root, lexeme));
		for (i = 0; i < strlen(Lexeme) - 1; i++) {
			Lexeme[i] = Lexeme[i + 1];
		}
		Lexeme[i - 1] = '\0';
		i = 0;
		fprintf(code, "\tLEA\tSI,\ttempString1\n");
		while(Lexeme[i] != '\0'){
			fprintf(code, "\tMOV\t[SI + %d],\t'%c'\n", i, Lexeme[i]);
			i++;
		}
		fprintf(code, "\tMOV\t[SI + %d],\t'$'\n", i);
	} else if (root->sym == ID_MAT) {
		ST *st = root->scope;
		mat_var *mat = ST_getinfo(st, GET(root, lexeme), &key)->entry[key];
		int rows = mat->rows, cols = mat->cols;
		fprintf(code, "\tLEA\tSI,\t%s%d\n", GET(root, lexeme), ST_getDeclId(st, GET(root, lexeme)));
		fprintf(code, "\tMOV\tsourceMatrixAddress,\tSI\n");
		fprintf(code, "\tLEA\tDI,\ttempMatrix1\n");
		fprintf(code, "\tMOV\tdestinationMatrixAddress,\tDI\n");
		if (mat->type == INT_TYPE || mat->type == BOOL_TYPE) {
			fprintf(code, "\tMOV\tmatrixSize,\t%d\n", rows * cols);
			fprintf(code, "\tCALL\tCopyMatrix02\n");
			CopyMatrix02Used = true;
		} else if (mat->type == REAL_TYPE) {
			fprintf(code, "\tMOV\tmatrixSize,\t%d\n", rows * cols * 2);
			fprintf(code, "\tCALL\tCopyMatrix02\n");
			CopyMatrix02Used = true;
		} else {
			fprintf(code, "\tMOV\tmatrixSize,\t%d\n", rows * cols);
			fprintf(code, "\tCALL\tCopyMatrix01\n");
			CopyMatrix01Used = true;
		}
	} else if (root->sym == ID_MAT_RHS) {
		ST *st = root->scope;
		matAssignRHSInfo *mat = root->value;
		char *var_mat, *var_row, *var_col;
		var_mat = (*((TokenInfo**)mat->info))->lexeme;
		var_row = (*((TokenInfo**)mat->rows))->lexeme;
		Symbol rSym = mat->rowSym, cSym;
		if(mat->cols != NULL) {
			var_col = (*((TokenInfo**)mat->cols))->lexeme;
			cSym = mat->colSym;
		} else {
			var_col = NULL;
		}
		mat_var *matv = ST_getinfo(st, var_mat, &key)->entry[key];
		int mul = matv->cols;
		Type type = matv->type;
		isRegEmpty[0] = false;
		isRegEmpty[1] = false;
		isRegEmpty[2] = false;
		isRegEmpty[3] = false;
		fprintf(code, "\tLEA\tSI,\t%s%d\n", var_mat, ST_getDeclId(st, var_mat));
		if (var_col != NULL) {
			if (type == BOOL_TYPE || type == INT_TYPE) {
				if (rSym == INT_LIT) {
					fprintf(code, "\tMOV\tAX,\t%s\n", var_row);
				} else {
					fprintf(code, "\tMOV\tAX,\t%s%d\n", var_row, ST_getDeclId(st, var_row));
				}
				fprintf(code, "\tMOV\tBX,\t%d\n", mul * 2);
				fprintf(code, "\tMUL\tBX\n");
				fprintf(code, "\tMOV\tCX,\tAX\n");
				if (cSym == INT_LIT) {
					fprintf(code, "\tMOV\tAX,\t%s\n", var_col);
				} else {
					fprintf(code, "\tMOV\tAX,\t%s%d\n", var_col, ST_getDeclId(st, var_col));
				}
				fprintf(code, "\tMOV\tBX,\t2\n");
				fprintf(code, "\tMUL\tBX\n");
				fprintf(code, "\tADD\tCX,\tAX\n");
				fprintf(code, "\tMOV\tBX,\tCX\n");
				fprintf(code, "\tMOV\tAX,\tWORD PTR[SI + BX]\n");
				fprintf(code, "\tPUSH\tAX\n");
			} else if (type == CHAR_TYPE) {
				if (rSym == INT_LIT) {
					fprintf(code, "\tMOV\tAX,\t%s\n", var_row);
				} else {
					fprintf(code, "\tMOV\tAX,\t%s%d\n", var_row, ST_getDeclId(st, var_row));
				}
				fprintf(code, "\tMOV\tBX,\t%d\n", mul);
				fprintf(code, "\tMUL\tBX\n");
				fprintf(code, "\tMOV\tBX,\tAX\n");
				if (cSym == INT_LIT) {
					fprintf(code, "\tMOV\tAX,\t%s\n", var_col);
				} else {
					fprintf(code, "\tMOV\tAX,\t%s%d\n", var_col, ST_getDeclId(st, var_col));
				}
				fprintf(code, "\tADD\tBX,\tAX\n");
				fprintf(code, "\tXOR\tAX,\tAX\n");
				fprintf(code, "\tMOV\tAL,\tBYTE PTR[SI + BX]\n");
				fprintf(code, "\tPUSH\tAX\n");
			} else {
				if (rSym == INT_LIT) {
					fprintf(code, "\tMOV\tAX,\t%s\n", var_row);
				} else {
					fprintf(code, "\tMOV\tAX,\t%s%d\n", var_row, ST_getDeclId(st, var_row));
				}
				fprintf(code, "\tMOV\tBX,\t%d\n", mul * 4);
				fprintf(code, "\tMUL\tBX\n");
				fprintf(code, "\tMOV\tCX,\tAX\n");
				if (cSym == INT_LIT) {
					fprintf(code, "\tMOV\tAX,\t%s\n", var_col);
				} else {
					fprintf(code, "\tMOV\tAX,\t%s%d\n", var_col, ST_getDeclId(st, var_col));
				}
				fprintf(code, "\tMOV\tBX,\t4\n");
				fprintf(code, "\tMUL\tBX\n");
				fprintf(code, "\tADD\tCX,\tAX\n");
				fprintf(code, "\tMOV\tBX,\tCX\n");
				fprintf(code, "\tMOV\tAX,\tWORD PTR[SI + BX]\n");
				fprintf(code, "\tADD\tBX,\t2\n");
				fprintf(code, "\tMOV\tCX,\tWORD PTR[SI + BX]\n");
				fprintf(code, "\tPUSH\tAX\n");
				fprintf(code, "\tPUSH\tCX\n");
			}
		} else {
			if (type == BOOL_TYPE || type == INT_TYPE) {
				if (rSym == INT_LIT) {
					fprintf(code, "\tMOV\tAX,\t%s\n", var_row);
				} else {
					fprintf(code, "\tMOV\tAX,\t%s%d\n", var_row, ST_getDeclId(st, var_row));
				}
				fprintf(code, "\tMOV\tBX,\t2\n");
				fprintf(code, "\tMUL\tBX\n");
				fprintf(code, "\tMOV\tBX,\tAX\n");
				fprintf(code, "\tMOV\tAX,\tWORD PTR[SI + BX]\n");
				fprintf(code, "\tPUSH\tAX\n");
			} else if (type == CHAR_TYPE) {
				if (rSym == INT_LIT) {
					fprintf(code, "\tMOV\tBX,\t%s\n", var_row);
				} else {
					fprintf(code, "\tMOV\tBX,\t%s%d\n", var_row, ST_getDeclId(st, var_row));
				}
				fprintf(code, "\tXOR\tAX,\tAX\n");
				fprintf(code, "\tMOV\tAL,\tBYTE PTR[SI + BX]\n");
				fprintf(code, "\tPUSH\tAX\n");
			} else {
				if (rSym == INT_LIT) {
					fprintf(code, "\tMOV\tAX,\t%s\n", var_row);
				} else {
					fprintf(code, "\tMOV\tAX,\t%s%d\n", var_row, ST_getDeclId(st, var_row));
				}
				fprintf(code, "\tMOV\tBX,\t4\n");
				fprintf(code, "\tMUL\tBX\n");
				fprintf(code, "\tMOV\tBX,\tAX\n");
				fprintf(code, "\tMOV\tAX,\tWORD PTR[SI + BX]\n");
				fprintf(code, "\tADD\tBX,\t2\n");
				fprintf(code, "\tMOV\tCX,\tWORD PTR[SI + BX]\n");
				fprintf(code, "\tPUSH\tAX\n");
				fprintf(code, "\tPUSH\tCX\n");
			}
		}
		isRegEmpty[0] = true;
		isRegEmpty[1] = true;
		isRegEmpty[2] = true;
		isRegEmpty[3] = true;
	} else if (root->sym == ID_REC_RHS) {
		ST *st = root->scope;
		Type type;
		recTypeIDInfo *info = root->value;
		char *recname = (*((TokenInfo**)info->info))->lexeme;
		char *compname = (*((TokenInfo**)info->comp))->lexeme;
		rec_var *temp = ST_getinfo(st, recname, &key)->entry[key];
		int off = ST_getRecAttr(st, recname, compname, &type);
		isRegEmpty[0] = false;
		isRegEmpty[2] = false;
		fprintf(code, "\tLEA\tSI,\t%s%d\n", recname, ST_getDeclId(st, recname));
		fprintf(code, "\tMOV\tBX,\t%d\n", off * 4);
		if (type == BOOL_TYPE || type == INT_TYPE) {
			fprintf(code, "\tMOV\tAX,\tWORD PTR[SI + BX]\n");
			fprintf(code, "\tPUSH\tAX\n");
		} else if (type == CHAR_TYPE) {
			fprintf(code, "\tXOR\tAX,\tAX\n");
			fprintf(code, "\tMOV\tAL,\tBYTE PTR[SI + BX]\n");
			fprintf(code, "\tPUSH\tAX\n");
		} else if (type == REAL_TYPE) {
			isRegEmpty[1] = false;
			fprintf(code, "\tMOV\tAX,\tWORD PTR[SI + BX]\n");
			fprintf(code, "\tADD\tBX,\t2\n");
			fprintf(code, "\tMOV\tCX,\tWORD PTR[SI + BX]\n");
			fprintf(code, "\tPUSH\tAX\n");
			fprintf(code, "\tPUSH\tCX\n");
			isRegEmpty[1] = true;
		}
		isRegEmpty[0] = true;
		isRegEmpty[2] = true;
	}
}

void declCode(ST *st, FILE *code){
	int i, size;
	pri_var *pri;
	str_var *str;
	mat_var *mat;
	rec_var *rec;
	rec_dec *recdec;
	for (i = 0; i < SIZE; i++) {
		if (st->entry[i] == NULL) continue;
		switch (st->type[i]) {
			case INT_TYPE:
				pri = st->entry[i];
				fprintf(code, "\t%s%d\tdw\t0\n", pri->name, st->id);
				break;
			case REAL_TYPE:
				pri = st->entry[i];
				fprintf(code, "\t%s%d\tdw\t2 dup(0)\n", pri->name, st->id);
				break;
			case CHAR_TYPE:
				pri = st->entry[i];
				fprintf(code, "\t%s%d\tdb\t0\n", pri->name, st->id);
				break;
			case BOOL_TYPE:
				pri = st->entry[i];
				fprintf(code, "\t%s%d\tdw\t0\n", pri->name, st->id);
				break;
			case STR_TYPE:
				str = st->entry[i];
				fprintf(code, "\t%s%d\tdb\t100 dup(?), '$'\n", str->name, st->id);
				break;
			case MAT_TYPE:
				mat = st->entry[i];
				size = mat->rows * mat->cols;
				switch(mat->type){
					case INT_TYPE: 		fprintf(code, "\t%s%d\tdw\t%d dup(0)\n", mat->name, st->id, size);		break;
					case REAL_TYPE:		fprintf(code, "\t%s%d\tdw\t%d dup(0)\n", mat->name, st->id, size * 2);	break;
					case CHAR_TYPE:		fprintf(code, "\t%s%d\tdb\t%d dup(0)\n", mat->name, st->id, size);		break;
					case BOOL_TYPE:		fprintf(code, "\t%s%d\tdw\t%d dup(0)\n", mat->name, st->id, size);		break;
				}
				break;
			case REC_TYPE:
				rec = st->entry[i];
				recdec = rec->type_st->entry[rec->type_offset];
				size = 4 * recdec->numEntries;
				fprintf(code, "\t%s%d\tdw\t%d dup(0)\n", rec->name, st->id, size);
				break;
		}
	}
}

void declScan(ST *st, FILE *code){
	int i;
	if(st == NULL) return;
	declCode(st, code);
	ST *p = st->child;
	while(p != NULL){
		declScan(p, code);
		p = p->next;
	}
}

void initializeRegisters(){
	int i;
	strcpy(Reg[0], "AX");
	strcpy(Reg[1], "BX");
	strcpy(Reg[2], "CX");
	strcpy(Reg[3], "DX");
	for (i = 0; i < 4; i++){
		isRegEmpty[i] = true;
	}
	return;
}

int getEmptyRegisterIndex(){
	int i;
	for (i = 0; i < 4; i++){
		if (isRegEmpty[i]){
			isRegEmpty[i] = false;
			return i;
		}
	}
	return -1;
}

void CodeOptimizerStack01 (FILE *input, FILE *output) {
	char string1[40] = "", string2[40] = "", substr1[20] = "", substr2[20] = "", substr3[20] = "", substr4[20] = "";
	char *buff;
	int i, j, size1 = 40, size2 = 40;
	bool flag = true;
	fgets(string1, size1, input);
	while (strcmp(string1, ".startup\n") != 0) {
		fprintf(output, string1);
		fgets(string1, size1, input);
	}
	fprintf(output, string1);
	buff = fgets(string1, size1, input);
	buff = fgets(string2, size2, input);
	while (buff != NULL) {
		if (string1[1] == 'P' && string2[1] == 'P') {
			i = 1;
			while (string1[i] != '\t') {
				substr1[i-1] = string1[i];
				i++;
			}
			substr1[i-1] = '\0';
			j = 0;
			i++;
			while (string1[i] != '\n') {
				substr2[j++] = string1[i++];
			}
			substr2[j] = '\0';
			i = 1;
			while (string2[i] != '\t') {
				substr3[i-1] = string2[i];
				i++;
			}
			substr3[i-1] = '\0';
			j = 0;
			i++;
			while (string2[i] != '\n') {
				substr4[j++] = string2[i++];
			}
			substr4[j] = '\0';
			if (flag) {
				if ((strcmp(substr1, "PUSH") == 0) && (strcmp(substr3, "POP") == 0) && (strcmp(substr2, substr4) == 0)) {
					buff = fgets(string1, size1, input);
					buff = fgets(string2, size2, input);
					if (buff == NULL) {
						fprintf(output, string1);
					}
				} else {
					fprintf(output, string1);
					buff = fgets(string1, size1, input);
					if (buff == NULL) {
						fprintf(output, string2);
					}
					flag = false;
				}
			} else {
				if ((strcmp(substr3, "PUSH") == 0) && (strcmp(substr1, "POP") == 0) && (strcmp(substr2, substr4) == 0)) {
					buff = fgets(string2, size2, input);
					buff = fgets(string1, size1, input);
					if (buff == NULL) {
						fprintf(output, string2);
					}
				} else {
					fprintf(output, string2);
					buff = fgets(string2, size2, input);
					if (buff == NULL) {
						fprintf(output, string1);
					}
					flag = true;
				}
			}
		} else {
			if (flag) {
				fprintf(output, string1);
				buff = fgets(string1, size1, input);
				if (buff == NULL) {
					fprintf(output, string2);
				}
				flag = false;
			} else {
				fprintf(output, string2);
				buff = fgets(string2, size2, input);
				if (buff == NULL) {
					fprintf(output, string1);
				}
				flag = true;
			}
		}
	}
}

void CodeOptimizerPlus01 (FILE *input, FILE *output) {
	char set1[6][40], set2[8][40], string1[40] = "", substr1[20] = "", substr2[40] = "", substr3[40] = "", substr4[20] = "", substr5[40] = "", substr6[40] = "";
	strcpy(set1[0], "\tPUSH\tAX\n");
	strcpy(set1[1], "\tMOV\tAX,\t1\n");
	strcpy(set1[2], "\tPUSH\tAX\n");
	strcpy(set1[3], "\tPOP\tBX\n");
	strcpy(set1[4], "\tPOP\tAX\n");
	strcpy(set1[5], "\tADD\tAX,\tBX\n");
	char *buff;
	int i, j, size = 40;
	bool flag = true;
	fgets(string1, size, input);
	while (strcmp(string1, ".startup\n") != 0) {
		fprintf(output, string1);
		fgets(string1, size, input);
	}
	fprintf(output, string1);
	buff = fgets(string1, size, input);
	while (buff != NULL) {
		if (string1[1] == 'M') {																		/* MOV AX, ? */
			strcpy(set2[0], string1);
			buff = fgets(string1, size, input);
			if (buff != NULL) {
				if (strcmp(set1[0], string1) == 0) {													/* PUSH AX */
					strcpy(set2[1], string1);
					buff = fgets(string1, size, input);
					if (buff != NULL) {
						if (strcmp(set1[1], string1) == 0) {											/* MOV AX, 1 */
							strcpy(set2[2], string1);
							buff = fgets(string1, size, input);
							if (buff != NULL) {
								if (strcmp(set1[2], string1) == 0) {									/* PUSH AX */
									strcpy(set2[3], string1);
									buff = fgets(string1, size, input);
									if (buff != NULL) {
										if (strcmp(set1[3], string1) == 0) {							/* POP BX */
											strcpy(set2[4], string1);
											buff = fgets(string1, size, input);
											if (buff != NULL) {
												if (strcmp(set1[4], string1) == 0) {					/* POP AX */
													strcpy(set2[5], string1);
													buff = fgets(string1, size, input);
													if (buff != NULL) {
														if (strcmp(set1[5], string1) == 0) {			/* ADD AX, BX */
															strcpy(set2[6], string1);
															buff = fgets(string1, size, input);
															if (buff != NULL) {
																if (string1[1] == 'M') {				/* MOV ?, AX */
																	strcpy(set2[7], string1);
																	i = 1;
																	while (set2[0][i] != '\t') {
																		substr1[i-1] = set2[0][i];
																		i++;
																	}
																	substr1[i-1] = '\0';
																	j = 0;
																	i++;
																	while (set2[0][i] != ',') {
																		substr2[j++] = set2[0][i++];
																	}
																	substr2[j] = '\0';
																	j = 0;
																	i++;
																	i++;
																	while (set2[0][i] != '\n') {
																		substr3[j++] = set2[0][i++];
																	}
																	substr3[j] = '\0';
																	i = 1;
																	while (set2[7][i] != '\t') {
																		substr4[i-1] = set2[7][i];
																		i++;
																	}
																	substr4[i-1] = '\0';
																	j = 0;
																	i++;
																	while (set2[7][i] != ',') {
																		substr5[j++] = set2[7][i++];
																	}
																	substr5[j] = '\0';
																	j = 0;
																	i++;
																	i++;
																	while (set2[7][i] != '\n') {
																		substr6[j++] = set2[7][i++];
																	}
																	substr6[j] = '\0';
																	if ((strcmp(substr1, "MOV") == 0) && (strcmp(substr4, "MOV") == 0) && (strcmp(substr2, "AX") == 0) && (strcmp(substr6, "AX") == 0) && (strcmp(substr3, substr5) == 0)) {
																		fprintf(output, "\tINC\t%s\n", substr3);
																		buff = fgets(string1, size, input);
																	} else {
																		if (string1[1] == 'M') {
																			fprintf(output, set2[0]);
																			fprintf(output, set2[1]);
																			fprintf(output, set2[2]);
																			fprintf(output, set2[3]);
																			fprintf(output, set2[4]);
																			fprintf(output, set2[5]);
																			fprintf(output, set2[6]);
																			continue;
																		}
																		fprintf(output, set2[0]);
																		fprintf(output, set2[1]);
																		fprintf(output, set2[2]);
																		fprintf(output, set2[3]);
																		fprintf(output, set2[4]);
																		fprintf(output, set2[5]);
																		fprintf(output, set2[6]);
																		fprintf(output, string1);
																		buff = fgets(string1, size, input);
																	}
																} else {
																	if (string1[1] == 'M') {
																		fprintf(output, set2[0]);
																		fprintf(output, set2[1]);
																		fprintf(output, set2[2]);
																		fprintf(output, set2[3]);
																		fprintf(output, set2[4]);
																		fprintf(output, set2[5]);
																		fprintf(output, set2[6]);
																		continue;
																	}
																	fprintf(output, set2[0]);
																	fprintf(output, set2[1]);
																	fprintf(output, set2[2]);
																	fprintf(output, set2[3]);
																	fprintf(output, set2[4]);
																	fprintf(output, set2[5]);
																	fprintf(output, set2[6]);
																	fprintf(output, string1);
																	buff = fgets(string1, size, input);
																}
															} else {
																fprintf(output, set2[0]);
																fprintf(output, set2[1]);
																fprintf(output, set2[2]);
																fprintf(output, set2[3]);
																fprintf(output, set2[4]);
																fprintf(output, set2[5]);
																fprintf(output, set2[6]);
															}
														} else {
															if (string1[1] == 'M') {
																fprintf(output, set2[0]);
																fprintf(output, set2[1]);
																fprintf(output, set2[2]);
																fprintf(output, set2[3]);
																fprintf(output, set2[4]);
																fprintf(output, set2[5]);
																continue;
															}
															fprintf(output, set2[0]);
															fprintf(output, set2[1]);
															fprintf(output, set2[2]);
															fprintf(output, set2[3]);
															fprintf(output, set2[4]);
															fprintf(output, set2[5]);
															fprintf(output, string1);
															buff = fgets(string1, size, input);
														}
													} else {
														fprintf(output, set2[0]);
														fprintf(output, set2[1]);
														fprintf(output, set2[2]);
														fprintf(output, set2[3]);
														fprintf(output, set2[4]);
														fprintf(output, set2[5]);
													}
												} else {
													if (string1[1] == 'M') {
														fprintf(output, set2[0]);
														fprintf(output, set2[1]);
														fprintf(output, set2[2]);
														fprintf(output, set2[3]);
														fprintf(output, set2[4]);
														continue;
													}
													fprintf(output, set2[0]);
													fprintf(output, set2[1]);
													fprintf(output, set2[2]);
													fprintf(output, set2[3]);
													fprintf(output, set2[4]);
													fprintf(output, string1);
													buff = fgets(string1, size, input);
												}
											} else {
												fprintf(output, set2[0]);
												fprintf(output, set2[1]);
												fprintf(output, set2[2]);
												fprintf(output, set2[3]);
												fprintf(output, set2[4]);
											}
										} else {
											if (string1[1] == 'M') {
												fprintf(output, set2[0]);
												fprintf(output, set2[1]);
												fprintf(output, set2[2]);
												fprintf(output, set2[3]);
												continue;
											}
											fprintf(output, set2[0]);
											fprintf(output, set2[1]);
											fprintf(output, set2[2]);
											fprintf(output, set2[3]);
											fprintf(output, string1);
											buff = fgets(string1, size, input);
										}
									} else {
										fprintf(output, set2[0]);
										fprintf(output, set2[1]);
										fprintf(output, set2[2]);
										fprintf(output, set2[3]);
									}
								} else {
									if (string1[1] == 'M') {
										fprintf(output, set2[0]);
										fprintf(output, set2[1]);
										fprintf(output, set2[2]);
										continue;
									}
									fprintf(output, set2[0]);
									fprintf(output, set2[1]);
									fprintf(output, set2[2]);
									fprintf(output, string1);
									buff = fgets(string1, size, input);
								}
							} else {
								fprintf(output, set2[0]);
								fprintf(output, set2[1]);
								fprintf(output, set2[2]);
							}
						} else {
							if (string1[1] == 'M') {
								fprintf(output, set2[0]);
								fprintf(output, set2[1]);
								continue;
							}
							fprintf(output, set2[0]);
							fprintf(output, set2[1]);
							fprintf(output, string1);
							buff = fgets(string1, size, input);
						}
					} else {
						fprintf(output, set2[0]);
						fprintf(output, set2[1]);
					}
				} else {
					if (string1[1] == 'M') {
						fprintf(output, set2[0]);
						continue;
					}
					fprintf(output, set2[0]);
					fprintf(output, string1);
					buff = fgets(string1, size, input);
				}
			} else {
				fprintf(output, set2[0]);
			}
		} else {
			fprintf(output, string1);
			buff = fgets(string1, size, input);
		}
	}
}

void CodeOptimizerPlus02 (FILE *input, FILE *output) {
	char set1[6][40], set2[8][40], string1[40] = "", substr1[20] = "", substr2[40] = "", substr3[40] = "", substr4[20] = "", substr5[40] = "", substr6[40] = "";
	strcpy(set1[0], "\tPUSH\tAX\n");
	strcpy(set1[1], "\tMOV\tAX,\t0\n");
	strcpy(set1[2], "\tPUSH\tAX\n");
	strcpy(set1[3], "\tPOP\tBX\n");
	strcpy(set1[4], "\tPOP\tAX\n");
	strcpy(set1[5], "\tADD\tAX,\tBX\n");
	char *buff;
	int i, j, size = 40;
	bool flag = true;
	fgets(string1, size, input);
	while (strcmp(string1, ".startup\n") != 0) {
		fprintf(output, string1);
		fgets(string1, size, input);
	}
	fprintf(output, string1);
	buff = fgets(string1, size, input);
	while (buff != NULL) {
		if (string1[1] == 'M') {																		/* MOV AX, ? */
			strcpy(set2[0], string1);
			buff = fgets(string1, size, input);
			if (buff != NULL) {
				if (strcmp(set1[0], string1) == 0) {													/* PUSH AX */
					strcpy(set2[1], string1);
					buff = fgets(string1, size, input);
					if (buff != NULL) {
						if (strcmp(set1[1], string1) == 0) {											/* MOV AX, 0 */
							strcpy(set2[2], string1);
							buff = fgets(string1, size, input);
							if (buff != NULL) {
								if (strcmp(set1[2], string1) == 0) {									/* PUSH AX */
									strcpy(set2[3], string1);
									buff = fgets(string1, size, input);
									if (buff != NULL) {
										if (strcmp(set1[3], string1) == 0) {							/* POP BX */
											strcpy(set2[4], string1);
											buff = fgets(string1, size, input);
											if (buff != NULL) {
												if (strcmp(set1[4], string1) == 0) {					/* POP AX */
													strcpy(set2[5], string1);
													buff = fgets(string1, size, input);
													if (buff != NULL) {
														if (strcmp(set1[5], string1) == 0) {			/* ADD AX, BX */
															strcpy(set2[6], string1);
															buff = fgets(string1, size, input);
															if (buff != NULL) {
																if (string1[1] == 'M') {				/* MOV ?, AX */
																	strcpy(set2[7], string1);
																	i = 1;
																	while (set2[0][i] != '\t') {
																		substr1[i-1] = set2[0][i];
																		i++;
																	}
																	substr1[i-1] = '\0';
																	j = 0;
																	i++;
																	while (set2[0][i] != ',') {
																		substr2[j++] = set2[0][i++];
																	}
																	substr2[j] = '\0';
																	j = 0;
																	i++;
																	i++;
																	while (set2[0][i] != '\n') {
																		substr3[j++] = set2[0][i++];
																	}
																	substr3[j] = '\0';
																	i = 1;
																	while (set2[7][i] != '\t') {
																		substr4[i-1] = set2[7][i];
																		i++;
																	}
																	substr4[i-1] = '\0';
																	j = 0;
																	i++;
																	while (set2[7][i] != ',') {
																		substr5[j++] = set2[7][i++];
																	}
																	substr5[j] = '\0';
																	j = 0;
																	i++;
																	i++;
																	while (set2[7][i] != '\n') {
																		substr6[j++] = set2[7][i++];
																	}
																	substr6[j] = '\0';
																	if ((strcmp(substr1, "MOV") == 0) && (strcmp(substr4, "MOV") == 0) && (strcmp(substr2, "AX") == 0) && (strcmp(substr6, "AX") == 0) && (strcmp(substr3, substr5) == 0)) {
																		buff = fgets(string1, size, input);
																	} else {
																		if (string1[1] == 'M') {
																			fprintf(output, set2[0]);
																			fprintf(output, set2[1]);
																			fprintf(output, set2[2]);
																			fprintf(output, set2[3]);
																			fprintf(output, set2[4]);
																			fprintf(output, set2[5]);
																			fprintf(output, set2[6]);
																			continue;
																		}
																		fprintf(output, set2[0]);
																		fprintf(output, set2[1]);
																		fprintf(output, set2[2]);
																		fprintf(output, set2[3]);
																		fprintf(output, set2[4]);
																		fprintf(output, set2[5]);
																		fprintf(output, set2[6]);
																		fprintf(output, string1);
																		buff = fgets(string1, size, input);
																	}
																} else {
																	if (string1[1] == 'M') {
																		fprintf(output, set2[0]);
																		fprintf(output, set2[1]);
																		fprintf(output, set2[2]);
																		fprintf(output, set2[3]);
																		fprintf(output, set2[4]);
																		fprintf(output, set2[5]);
																		fprintf(output, set2[6]);
																		continue;
																	}
																	fprintf(output, set2[0]);
																	fprintf(output, set2[1]);
																	fprintf(output, set2[2]);
																	fprintf(output, set2[3]);
																	fprintf(output, set2[4]);
																	fprintf(output, set2[5]);
																	fprintf(output, set2[6]);
																	fprintf(output, string1);
																	buff = fgets(string1, size, input);
																}
															} else {
																fprintf(output, set2[0]);
																fprintf(output, set2[1]);
																fprintf(output, set2[2]);
																fprintf(output, set2[3]);
																fprintf(output, set2[4]);
																fprintf(output, set2[5]);
																fprintf(output, set2[6]);
															}
														} else {
															if (string1[1] == 'M') {
																fprintf(output, set2[0]);
																fprintf(output, set2[1]);
																fprintf(output, set2[2]);
																fprintf(output, set2[3]);
																fprintf(output, set2[4]);
																fprintf(output, set2[5]);
																continue;
															}
															fprintf(output, set2[0]);
															fprintf(output, set2[1]);
															fprintf(output, set2[2]);
															fprintf(output, set2[3]);
															fprintf(output, set2[4]);
															fprintf(output, set2[5]);
															fprintf(output, string1);
															buff = fgets(string1, size, input);
														}
													} else {
														fprintf(output, set2[0]);
														fprintf(output, set2[1]);
														fprintf(output, set2[2]);
														fprintf(output, set2[3]);
														fprintf(output, set2[4]);
														fprintf(output, set2[5]);
													}
												} else {
													if (string1[1] == 'M') {
														fprintf(output, set2[0]);
														fprintf(output, set2[1]);
														fprintf(output, set2[2]);
														fprintf(output, set2[3]);
														fprintf(output, set2[4]);
														continue;
													}
													fprintf(output, set2[0]);
													fprintf(output, set2[1]);
													fprintf(output, set2[2]);
													fprintf(output, set2[3]);
													fprintf(output, set2[4]);
													fprintf(output, string1);
													buff = fgets(string1, size, input);
												}
											} else {
												fprintf(output, set2[0]);
												fprintf(output, set2[1]);
												fprintf(output, set2[2]);
												fprintf(output, set2[3]);
												fprintf(output, set2[4]);
											}
										} else {
											if (string1[1] == 'M') {
												fprintf(output, set2[0]);
												fprintf(output, set2[1]);
												fprintf(output, set2[2]);
												fprintf(output, set2[3]);
												continue;
											}
											fprintf(output, set2[0]);
											fprintf(output, set2[1]);
											fprintf(output, set2[2]);
											fprintf(output, set2[3]);
											fprintf(output, string1);
											buff = fgets(string1, size, input);
										}
									} else {
										fprintf(output, set2[0]);
										fprintf(output, set2[1]);
										fprintf(output, set2[2]);
										fprintf(output, set2[3]);
									}
								} else {
									if (string1[1] == 'M') {
										fprintf(output, set2[0]);
										fprintf(output, set2[1]);
										fprintf(output, set2[2]);
										continue;
									}
									fprintf(output, set2[0]);
									fprintf(output, set2[1]);
									fprintf(output, set2[2]);
									fprintf(output, string1);
									buff = fgets(string1, size, input);
								}
							} else {
								fprintf(output, set2[0]);
								fprintf(output, set2[1]);
								fprintf(output, set2[2]);
							}
						} else {
							if (string1[1] == 'M') {
								fprintf(output, set2[0]);
								fprintf(output, set2[1]);
								continue;
							}
							fprintf(output, set2[0]);
							fprintf(output, set2[1]);
							fprintf(output, string1);
							buff = fgets(string1, size, input);
						}
					} else {
						fprintf(output, set2[0]);
						fprintf(output, set2[1]);
					}
				} else {
					if (string1[1] == 'M') {
						fprintf(output, set2[0]);
						continue;
					}
					fprintf(output, set2[0]);
					fprintf(output, string1);
					buff = fgets(string1, size, input);
				}
			} else {
				fprintf(output, set2[0]);
			}
		} else {
			fprintf(output, string1);
			buff = fgets(string1, size, input);
		}
	}
}

void CodeOptimizerMinus01 (FILE *input, FILE *output) {
	char set1[6][40], set2[8][40], string1[40] = "", substr1[20] = "", substr2[40] = "", substr3[40] = "", substr4[20] = "", substr5[40] = "", substr6[40] = "";
	strcpy(set1[0], "\tPUSH\tAX\n");
	strcpy(set1[1], "\tMOV\tAX,\t1\n");
	strcpy(set1[2], "\tPUSH\tAX\n");
	strcpy(set1[3], "\tPOP\tBX\n");
	strcpy(set1[4], "\tPOP\tAX\n");
	strcpy(set1[5], "\tSUB\tAX,\tBX\n");
	char *buff;
	int i, j, size = 40;
	bool flag = true;
	fgets(string1, size, input);
	while (strcmp(string1, ".startup\n") != 0) {
		fprintf(output, string1);
		fgets(string1, size, input);
	}
	fprintf(output, string1);
	buff = fgets(string1, size, input);
	while (buff != NULL) {
		if (string1[1] == 'M') {																		/* MOV AX, ? */
			strcpy(set2[0], string1);
			buff = fgets(string1, size, input);
			if (buff != NULL) {
				if (strcmp(set1[0], string1) == 0) {													/* PUSH AX */
					strcpy(set2[1], string1);
					buff = fgets(string1, size, input);
					if (buff != NULL) {
						if (strcmp(set1[1], string1) == 0) {											/* MOV AX, 1 */
							strcpy(set2[2], string1);
							buff = fgets(string1, size, input);
							if (buff != NULL) {
								if (strcmp(set1[2], string1) == 0) {									/* PUSH AX */
									strcpy(set2[3], string1);
									buff = fgets(string1, size, input);
									if (buff != NULL) {
										if (strcmp(set1[3], string1) == 0) {							/* POP BX */
											strcpy(set2[4], string1);
											buff = fgets(string1, size, input);
											if (buff != NULL) {
												if (strcmp(set1[4], string1) == 0) {					/* POP AX */
													strcpy(set2[5], string1);
													buff = fgets(string1, size, input);
													if (buff != NULL) {
														if (strcmp(set1[5], string1) == 0) {			/* SUB AX, BX */
															strcpy(set2[6], string1);
															buff = fgets(string1, size, input);
															if (buff != NULL) {
																if (string1[1] == 'M') {				/* MOV ?, AX */
																	strcpy(set2[7], string1);
																	i = 1;
																	while (set2[0][i] != '\t') {
																		substr1[i-1] = set2[0][i];
																		i++;
																	}
																	substr1[i-1] = '\0';
																	j = 0;
																	i++;
																	while (set2[0][i] != ',') {
																		substr2[j++] = set2[0][i++];
																	}
																	substr2[j] = '\0';
																	j = 0;
																	i++;
																	i++;
																	while (set2[0][i] != '\n') {
																		substr3[j++] = set2[0][i++];
																	}
																	substr3[j] = '\0';
																	i = 1;
																	while (set2[7][i] != '\t') {
																		substr4[i-1] = set2[7][i];
																		i++;
																	}
																	substr4[i-1] = '\0';
																	j = 0;
																	i++;
																	while (set2[7][i] != ',') {
																		substr5[j++] = set2[7][i++];
																	}
																	substr5[j] = '\0';
																	j = 0;
																	i++;
																	i++;
																	while (set2[7][i] != '\n') {
																		substr6[j++] = set2[7][i++];
																	}
																	substr6[j] = '\0';
																	if ((strcmp(substr1, "MOV") == 0) && (strcmp(substr4, "MOV") == 0) && (strcmp(substr2, "AX") == 0) && (strcmp(substr6, "AX") == 0) && (strcmp(substr3, substr5) == 0)) {
																		fprintf(output, "\tDEC\t%s\n", substr3);
																		buff = fgets(string1, size, input);
																	} else {
																		if (string1[1] == 'M') {
																			fprintf(output, set2[0]);
																			fprintf(output, set2[1]);
																			fprintf(output, set2[2]);
																			fprintf(output, set2[3]);
																			fprintf(output, set2[4]);
																			fprintf(output, set2[5]);
																			fprintf(output, set2[6]);
																			continue;
																		}
																		fprintf(output, set2[0]);
																		fprintf(output, set2[1]);
																		fprintf(output, set2[2]);
																		fprintf(output, set2[3]);
																		fprintf(output, set2[4]);
																		fprintf(output, set2[5]);
																		fprintf(output, set2[6]);
																		fprintf(output, string1);
																		buff = fgets(string1, size, input);
																	}
																} else {
																	if (string1[1] == 'M') {
																		fprintf(output, set2[0]);
																		fprintf(output, set2[1]);
																		fprintf(output, set2[2]);
																		fprintf(output, set2[3]);
																		fprintf(output, set2[4]);
																		fprintf(output, set2[5]);
																		fprintf(output, set2[6]);
																		continue;
																	}
																	fprintf(output, set2[0]);
																	fprintf(output, set2[1]);
																	fprintf(output, set2[2]);
																	fprintf(output, set2[3]);
																	fprintf(output, set2[4]);
																	fprintf(output, set2[5]);
																	fprintf(output, set2[6]);
																	fprintf(output, string1);
																	buff = fgets(string1, size, input);
																}
															} else {
																fprintf(output, set2[0]);
																fprintf(output, set2[1]);
																fprintf(output, set2[2]);
																fprintf(output, set2[3]);
																fprintf(output, set2[4]);
																fprintf(output, set2[5]);
																fprintf(output, set2[6]);
															}
														} else {
															if (string1[1] == 'M') {
																fprintf(output, set2[0]);
																fprintf(output, set2[1]);
																fprintf(output, set2[2]);
																fprintf(output, set2[3]);
																fprintf(output, set2[4]);
																fprintf(output, set2[5]);
																continue;
															}
															fprintf(output, set2[0]);
															fprintf(output, set2[1]);
															fprintf(output, set2[2]);
															fprintf(output, set2[3]);
															fprintf(output, set2[4]);
															fprintf(output, set2[5]);
															fprintf(output, string1);
															buff = fgets(string1, size, input);
														}
													} else {
														fprintf(output, set2[0]);
														fprintf(output, set2[1]);
														fprintf(output, set2[2]);
														fprintf(output, set2[3]);
														fprintf(output, set2[4]);
														fprintf(output, set2[5]);
													}
												} else {
													if (string1[1] == 'M') {
														fprintf(output, set2[0]);
														fprintf(output, set2[1]);
														fprintf(output, set2[2]);
														fprintf(output, set2[3]);
														fprintf(output, set2[4]);
														continue;
													}
													fprintf(output, set2[0]);
													fprintf(output, set2[1]);
													fprintf(output, set2[2]);
													fprintf(output, set2[3]);
													fprintf(output, set2[4]);
													fprintf(output, string1);
													buff = fgets(string1, size, input);
												}
											} else {
												fprintf(output, set2[0]);
												fprintf(output, set2[1]);
												fprintf(output, set2[2]);
												fprintf(output, set2[3]);
												fprintf(output, set2[4]);
											}
										} else {
											if (string1[1] == 'M') {
												fprintf(output, set2[0]);
												fprintf(output, set2[1]);
												fprintf(output, set2[2]);
												fprintf(output, set2[3]);
												continue;
											}
											fprintf(output, set2[0]);
											fprintf(output, set2[1]);
											fprintf(output, set2[2]);
											fprintf(output, set2[3]);
											fprintf(output, string1);
											buff = fgets(string1, size, input);
										}
									} else {
										fprintf(output, set2[0]);
										fprintf(output, set2[1]);
										fprintf(output, set2[2]);
										fprintf(output, set2[3]);
									}
								} else {
									if (string1[1] == 'M') {
										fprintf(output, set2[0]);
										fprintf(output, set2[1]);
										fprintf(output, set2[2]);
										continue;
									}
									fprintf(output, set2[0]);
									fprintf(output, set2[1]);
									fprintf(output, set2[2]);
									fprintf(output, string1);
									buff = fgets(string1, size, input);
								}
							} else {
								fprintf(output, set2[0]);
								fprintf(output, set2[1]);
								fprintf(output, set2[2]);
							}
						} else {
							if (string1[1] == 'M') {
								fprintf(output, set2[0]);
								fprintf(output, set2[1]);
								continue;
							}
							fprintf(output, set2[0]);
							fprintf(output, set2[1]);
							fprintf(output, string1);
							buff = fgets(string1, size, input);
						}
					} else {
						fprintf(output, set2[0]);
						fprintf(output, set2[1]);
					}
				} else {
					if (string1[1] == 'M') {
						fprintf(output, set2[0]);
						continue;
					}
					fprintf(output, set2[0]);
					fprintf(output, string1);
					buff = fgets(string1, size, input);
				}
			} else {
				fprintf(output, set2[0]);
			}
		} else {
			fprintf(output, string1);
			buff = fgets(string1, size, input);
		}
	}
}

void CodeOptimizerMinus02 (FILE *input, FILE *output) {
	char set1[6][40], set2[8][40], string1[40] = "", substr1[20] = "", substr2[40] = "", substr3[40] = "", substr4[20] = "", substr5[40] = "", substr6[40] = "";
	strcpy(set1[0], "\tPUSH\tAX\n");
	strcpy(set1[1], "\tMOV\tAX,\t0\n");
	strcpy(set1[2], "\tPUSH\tAX\n");
	strcpy(set1[3], "\tPOP\tBX\n");
	strcpy(set1[4], "\tPOP\tAX\n");
	strcpy(set1[5], "\tSUB\tAX,\tBX\n");
	char *buff;
	int i, j, size = 40;
	bool flag = true;
	fgets(string1, size, input);
	while (strcmp(string1, ".startup\n") != 0) {
		fprintf(output, string1);
		fgets(string1, size, input);
	}
	fprintf(output, string1);
	buff = fgets(string1, size, input);
	while (buff != NULL) {
		if (string1[1] == 'M') {																		/* MOV AX, ? */
			strcpy(set2[0], string1);
			buff = fgets(string1, size, input);
			if (buff != NULL) {
				if (strcmp(set1[0], string1) == 0) {													/* PUSH AX */
					strcpy(set2[1], string1);
					buff = fgets(string1, size, input);
					if (buff != NULL) {
						if (strcmp(set1[1], string1) == 0) {											/* MOV AX, 0 */
							strcpy(set2[2], string1);
							buff = fgets(string1, size, input);
							if (buff != NULL) {
								if (strcmp(set1[2], string1) == 0) {									/* PUSH AX */
									strcpy(set2[3], string1);
									buff = fgets(string1, size, input);
									if (buff != NULL) {
										if (strcmp(set1[3], string1) == 0) {							/* POP BX */
											strcpy(set2[4], string1);
											buff = fgets(string1, size, input);
											if (buff != NULL) {
												if (strcmp(set1[4], string1) == 0) {					/* POP AX */
													strcpy(set2[5], string1);
													buff = fgets(string1, size, input);
													if (buff != NULL) {
														if (strcmp(set1[5], string1) == 0) {			/* SUB AX, BX */
															strcpy(set2[6], string1);
															buff = fgets(string1, size, input);
															if (buff != NULL) {
																if (string1[1] == 'M') {				/* MOV ?, AX */
																	strcpy(set2[7], string1);
																	i = 1;
																	while (set2[0][i] != '\t') {
																		substr1[i-1] = set2[0][i];
																		i++;
																	}
																	substr1[i-1] = '\0';
																	j = 0;
																	i++;
																	while (set2[0][i] != ',') {
																		substr2[j++] = set2[0][i++];
																	}
																	substr2[j] = '\0';
																	j = 0;
																	i++;
																	i++;
																	while (set2[0][i] != '\n') {
																		substr3[j++] = set2[0][i++];
																	}
																	substr3[j] = '\0';
																	i = 1;
																	while (set2[7][i] != '\t') {
																		substr4[i-1] = set2[7][i];
																		i++;
																	}
																	substr4[i-1] = '\0';
																	j = 0;
																	i++;
																	while (set2[7][i] != ',') {
																		substr5[j++] = set2[7][i++];
																	}
																	substr5[j] = '\0';
																	j = 0;
																	i++;
																	i++;
																	while (set2[7][i] != '\n') {
																		substr6[j++] = set2[7][i++];
																	}
																	substr6[j] = '\0';
																	if ((strcmp(substr1, "MOV") == 0) && (strcmp(substr4, "MOV") == 0) && (strcmp(substr2, "AX") == 0) && (strcmp(substr6, "AX") == 0) && (strcmp(substr3, substr5) == 0)) {
																		buff = fgets(string1, size, input);
																	} else {
																		if (string1[1] == 'M') {
																			fprintf(output, set2[0]);
																			fprintf(output, set2[1]);
																			fprintf(output, set2[2]);
																			fprintf(output, set2[3]);
																			fprintf(output, set2[4]);
																			fprintf(output, set2[5]);
																			fprintf(output, set2[6]);
																			continue;
																		}
																		fprintf(output, set2[0]);
																		fprintf(output, set2[1]);
																		fprintf(output, set2[2]);
																		fprintf(output, set2[3]);
																		fprintf(output, set2[4]);
																		fprintf(output, set2[5]);
																		fprintf(output, set2[6]);
																		fprintf(output, string1);
																		buff = fgets(string1, size, input);
																	}
																} else {
																	if (string1[1] == 'M') {
																		fprintf(output, set2[0]);
																		fprintf(output, set2[1]);
																		fprintf(output, set2[2]);
																		fprintf(output, set2[3]);
																		fprintf(output, set2[4]);
																		fprintf(output, set2[5]);
																		fprintf(output, set2[6]);
																		continue;
																	}
																	fprintf(output, set2[0]);
																	fprintf(output, set2[1]);
																	fprintf(output, set2[2]);
																	fprintf(output, set2[3]);
																	fprintf(output, set2[4]);
																	fprintf(output, set2[5]);
																	fprintf(output, set2[6]);
																	fprintf(output, string1);
																	buff = fgets(string1, size, input);
																}
															} else {
																fprintf(output, set2[0]);
																fprintf(output, set2[1]);
																fprintf(output, set2[2]);
																fprintf(output, set2[3]);
																fprintf(output, set2[4]);
																fprintf(output, set2[5]);
																fprintf(output, set2[6]);
															}
														} else {
															if (string1[1] == 'M') {
																fprintf(output, set2[0]);
																fprintf(output, set2[1]);
																fprintf(output, set2[2]);
																fprintf(output, set2[3]);
																fprintf(output, set2[4]);
																fprintf(output, set2[5]);
																continue;
															}
															fprintf(output, set2[0]);
															fprintf(output, set2[1]);
															fprintf(output, set2[2]);
															fprintf(output, set2[3]);
															fprintf(output, set2[4]);
															fprintf(output, set2[5]);
															fprintf(output, string1);
															buff = fgets(string1, size, input);
														}
													} else {
														fprintf(output, set2[0]);
														fprintf(output, set2[1]);
														fprintf(output, set2[2]);
														fprintf(output, set2[3]);
														fprintf(output, set2[4]);
														fprintf(output, set2[5]);
													}
												} else {
													if (string1[1] == 'M') {
														fprintf(output, set2[0]);
														fprintf(output, set2[1]);
														fprintf(output, set2[2]);
														fprintf(output, set2[3]);
														fprintf(output, set2[4]);
														continue;
													}
													fprintf(output, set2[0]);
													fprintf(output, set2[1]);
													fprintf(output, set2[2]);
													fprintf(output, set2[3]);
													fprintf(output, set2[4]);
													fprintf(output, string1);
													buff = fgets(string1, size, input);
												}
											} else {
												fprintf(output, set2[0]);
												fprintf(output, set2[1]);
												fprintf(output, set2[2]);
												fprintf(output, set2[3]);
												fprintf(output, set2[4]);
											}
										} else {
											if (string1[1] == 'M') {
												fprintf(output, set2[0]);
												fprintf(output, set2[1]);
												fprintf(output, set2[2]);
												fprintf(output, set2[3]);
												continue;
											}
											fprintf(output, set2[0]);
											fprintf(output, set2[1]);
											fprintf(output, set2[2]);
											fprintf(output, set2[3]);
											fprintf(output, string1);
											buff = fgets(string1, size, input);
										}
									} else {
										fprintf(output, set2[0]);
										fprintf(output, set2[1]);
										fprintf(output, set2[2]);
										fprintf(output, set2[3]);
									}
								} else {
									if (string1[1] == 'M') {
										fprintf(output, set2[0]);
										fprintf(output, set2[1]);
										fprintf(output, set2[2]);
										continue;
									}
									fprintf(output, set2[0]);
									fprintf(output, set2[1]);
									fprintf(output, set2[2]);
									fprintf(output, string1);
									buff = fgets(string1, size, input);
								}
							} else {
								fprintf(output, set2[0]);
								fprintf(output, set2[1]);
								fprintf(output, set2[2]);
							}
						} else {
							if (string1[1] == 'M') {
								fprintf(output, set2[0]);
								fprintf(output, set2[1]);
								continue;
							}
							fprintf(output, set2[0]);
							fprintf(output, set2[1]);
							fprintf(output, string1);
							buff = fgets(string1, size, input);
						}
					} else {
						fprintf(output, set2[0]);
						fprintf(output, set2[1]);
					}
				} else {
					if (string1[1] == 'M') {
						fprintf(output, set2[0]);
						continue;
					}
					fprintf(output, set2[0]);
					fprintf(output, string1);
					buff = fgets(string1, size, input);
				}
			} else {
				fprintf(output, set2[0]);
			}
		} else {
			fprintf(output, string1);
			buff = fgets(string1, size, input);
		}
	}
}

void CodeOptimizerMul01 (FILE *input, FILE *output) {
	char set1[6][40], set2[8][40], string1[40] = "", substr1[20] = "", substr2[40] = "", substr3[40] = "", substr4[20] = "", substr5[40] = "", substr6[40] = "";
	strcpy(set1[0], "\tPUSH\tAX\n");
	strcpy(set1[1], "\tMOV\tAX,\t1\n");
	strcpy(set1[2], "\tPUSH\tAX\n");
	strcpy(set1[3], "\tPOP\tBX\n");
	strcpy(set1[4], "\tPOP\tAX\n");
	strcpy(set1[5], "\tIMUL\tBX\n");
	char *buff;
	int i, j, size = 40;
	bool flag = true;
	fgets(string1, size, input);
	while (strcmp(string1, ".startup\n") != 0) {
		fprintf(output, string1);
		fgets(string1, size, input);
	}
	fprintf(output, string1);
	buff = fgets(string1, size, input);
	while (buff != NULL) {
		if (string1[1] == 'M') {																		/* MOV AX, ? */
			strcpy(set2[0], string1);
			buff = fgets(string1, size, input);
			if (buff != NULL) {
				if (strcmp(set1[0], string1) == 0) {													/* PUSH AX */
					strcpy(set2[1], string1);
					buff = fgets(string1, size, input);
					if (buff != NULL) {
						if (strcmp(set1[1], string1) == 0) {											/* MOV AX, 1 */
							strcpy(set2[2], string1);
							buff = fgets(string1, size, input);
							if (buff != NULL) {
								if (strcmp(set1[2], string1) == 0) {									/* PUSH AX */
									strcpy(set2[3], string1);
									buff = fgets(string1, size, input);
									if (buff != NULL) {
										if (strcmp(set1[3], string1) == 0) {							/* POP BX */
											strcpy(set2[4], string1);
											buff = fgets(string1, size, input);
											if (buff != NULL) {
												if (strcmp(set1[4], string1) == 0) {					/* POP AX */
													strcpy(set2[5], string1);
													buff = fgets(string1, size, input);
													if (buff != NULL) {
														if (strcmp(set1[5], string1) == 0) {			/* IMUL BX */
															strcpy(set2[6], string1);
															buff = fgets(string1, size, input);
															if (buff != NULL) {
																if (string1[1] == 'M') {				/* MOV ?, AX */
																	strcpy(set2[7], string1);
																	i = 1;
																	while (set2[0][i] != '\t') {
																		substr1[i-1] = set2[0][i];
																		i++;
																	}
																	substr1[i-1] = '\0';
																	j = 0;
																	i++;
																	while (set2[0][i] != ',') {
																		substr2[j++] = set2[0][i++];
																	}
																	substr2[j] = '\0';
																	j = 0;
																	i++;
																	i++;
																	while (set2[0][i] != '\n') {
																		substr3[j++] = set2[0][i++];
																	}
																	substr3[j] = '\0';
																	i = 1;
																	while (set2[7][i] != '\t') {
																		substr4[i-1] = set2[7][i];
																		i++;
																	}
																	substr4[i-1] = '\0';
																	j = 0;
																	i++;
																	while (set2[7][i] != ',') {
																		substr5[j++] = set2[7][i++];
																	}
																	substr5[j] = '\0';
																	j = 0;
																	i++;
																	i++;
																	while (set2[7][i] != '\n') {
																		substr6[j++] = set2[7][i++];
																	}
																	substr6[j] = '\0';
																	if ((strcmp(substr1, "MOV") == 0) && (strcmp(substr4, "MOV") == 0) && (strcmp(substr2, "AX") == 0) && (strcmp(substr6, "AX") == 0) && (strcmp(substr3, substr5) == 0)) {
																		buff = fgets(string1, size, input);
																	} else {
																		if (string1[1] == 'M') {
																			fprintf(output, set2[0]);
																			fprintf(output, set2[1]);
																			fprintf(output, set2[2]);
																			fprintf(output, set2[3]);
																			fprintf(output, set2[4]);
																			fprintf(output, set2[5]);
																			fprintf(output, set2[6]);
																			continue;
																		}
																		fprintf(output, set2[0]);
																		fprintf(output, set2[1]);
																		fprintf(output, set2[2]);
																		fprintf(output, set2[3]);
																		fprintf(output, set2[4]);
																		fprintf(output, set2[5]);
																		fprintf(output, set2[6]);
																		fprintf(output, string1);
																		buff = fgets(string1, size, input);
																	}
																} else {
																	if (string1[1] == 'M') {
																		fprintf(output, set2[0]);
																		fprintf(output, set2[1]);
																		fprintf(output, set2[2]);
																		fprintf(output, set2[3]);
																		fprintf(output, set2[4]);
																		fprintf(output, set2[5]);
																		fprintf(output, set2[6]);
																		continue;
																	}
																	fprintf(output, set2[0]);
																	fprintf(output, set2[1]);
																	fprintf(output, set2[2]);
																	fprintf(output, set2[3]);
																	fprintf(output, set2[4]);
																	fprintf(output, set2[5]);
																	fprintf(output, set2[6]);
																	fprintf(output, string1);
																	buff = fgets(string1, size, input);
																}
															} else {
																fprintf(output, set2[0]);
																fprintf(output, set2[1]);
																fprintf(output, set2[2]);
																fprintf(output, set2[3]);
																fprintf(output, set2[4]);
																fprintf(output, set2[5]);
																fprintf(output, set2[6]);
															}
														} else {
															if (string1[1] == 'M') {
																fprintf(output, set2[0]);
																fprintf(output, set2[1]);
																fprintf(output, set2[2]);
																fprintf(output, set2[3]);
																fprintf(output, set2[4]);
																fprintf(output, set2[5]);
																continue;
															}
															fprintf(output, set2[0]);
															fprintf(output, set2[1]);
															fprintf(output, set2[2]);
															fprintf(output, set2[3]);
															fprintf(output, set2[4]);
															fprintf(output, set2[5]);
															fprintf(output, string1);
															buff = fgets(string1, size, input);
														}
													} else {
														fprintf(output, set2[0]);
														fprintf(output, set2[1]);
														fprintf(output, set2[2]);
														fprintf(output, set2[3]);
														fprintf(output, set2[4]);
														fprintf(output, set2[5]);
													}
												} else {
													if (string1[1] == 'M') {
														fprintf(output, set2[0]);
														fprintf(output, set2[1]);
														fprintf(output, set2[2]);
														fprintf(output, set2[3]);
														fprintf(output, set2[4]);
														continue;
													}
													fprintf(output, set2[0]);
													fprintf(output, set2[1]);
													fprintf(output, set2[2]);
													fprintf(output, set2[3]);
													fprintf(output, set2[4]);
													fprintf(output, string1);
													buff = fgets(string1, size, input);
												}
											} else {
												fprintf(output, set2[0]);
												fprintf(output, set2[1]);
												fprintf(output, set2[2]);
												fprintf(output, set2[3]);
												fprintf(output, set2[4]);
											}
										} else {
											if (string1[1] == 'M') {
												fprintf(output, set2[0]);
												fprintf(output, set2[1]);
												fprintf(output, set2[2]);
												fprintf(output, set2[3]);
												continue;
											}
											fprintf(output, set2[0]);
											fprintf(output, set2[1]);
											fprintf(output, set2[2]);
											fprintf(output, set2[3]);
											fprintf(output, string1);
											buff = fgets(string1, size, input);
										}
									} else {
										fprintf(output, set2[0]);
										fprintf(output, set2[1]);
										fprintf(output, set2[2]);
										fprintf(output, set2[3]);
									}
								} else {
									if (string1[1] == 'M') {
										fprintf(output, set2[0]);
										fprintf(output, set2[1]);
										fprintf(output, set2[2]);
										continue;
									}
									fprintf(output, set2[0]);
									fprintf(output, set2[1]);
									fprintf(output, set2[2]);
									fprintf(output, string1);
									buff = fgets(string1, size, input);
								}
							} else {
								fprintf(output, set2[0]);
								fprintf(output, set2[1]);
								fprintf(output, set2[2]);
							}
						} else {
							if (string1[1] == 'M') {
								fprintf(output, set2[0]);
								fprintf(output, set2[1]);
								continue;
							}
							fprintf(output, set2[0]);
							fprintf(output, set2[1]);
							fprintf(output, string1);
							buff = fgets(string1, size, input);
						}
					} else {
						fprintf(output, set2[0]);
						fprintf(output, set2[1]);
					}
				} else {
					if (string1[1] == 'M') {
						fprintf(output, set2[0]);
						continue;
					}
					fprintf(output, set2[0]);
					fprintf(output, string1);
					buff = fgets(string1, size, input);
				}
			} else {
				fprintf(output, set2[0]);
			}
		} else {
			fprintf(output, string1);
			buff = fgets(string1, size, input);
		}
	}
}

void CodeOptimizerMul02 (FILE *input, FILE *output) {
	char set1[6][40], set2[8][40], string1[40] = "", substr1[20] = "", substr2[40] = "", substr3[40] = "", substr4[20] = "", substr5[40] = "", substr6[40] = "";
	strcpy(set1[0], "\tPUSH\tAX\n");
	strcpy(set1[1], "\tMOV\tAX,\t0\n");
	strcpy(set1[2], "\tPUSH\tAX\n");
	strcpy(set1[3], "\tPOP\tBX\n");
	strcpy(set1[4], "\tPOP\tAX\n");
	strcpy(set1[5], "\tIMUL\tBX\n");
	char *buff;
	int i, j, size = 40;
	bool flag = true;
	fgets(string1, size, input);
	while (strcmp(string1, ".startup\n") != 0) {
		fprintf(output, string1);
		fgets(string1, size, input);
	}
	fprintf(output, string1);
	buff = fgets(string1, size, input);
	while (buff != NULL) {
		if (string1[1] == 'M') {																		/* MOV AX, ? */
			strcpy(set2[0], string1);
			buff = fgets(string1, size, input);
			if (buff != NULL) {
				if (strcmp(set1[0], string1) == 0) {													/* PUSH AX */
					strcpy(set2[1], string1);
					buff = fgets(string1, size, input);
					if (buff != NULL) {
						if (strcmp(set1[1], string1) == 0) {											/* MOV AX, 0 */
							strcpy(set2[2], string1);
							buff = fgets(string1, size, input);
							if (buff != NULL) {
								if (strcmp(set1[2], string1) == 0) {									/* PUSH AX */
									strcpy(set2[3], string1);
									buff = fgets(string1, size, input);
									if (buff != NULL) {
										if (strcmp(set1[3], string1) == 0) {							/* POP BX */
											strcpy(set2[4], string1);
											buff = fgets(string1, size, input);
											if (buff != NULL) {
												if (strcmp(set1[4], string1) == 0) {					/* POP AX */
													strcpy(set2[5], string1);
													buff = fgets(string1, size, input);
													if (buff != NULL) {
														if (strcmp(set1[5], string1) == 0) {			/* IMUL BX */
															strcpy(set2[6], string1);
															buff = fgets(string1, size, input);
															if (buff != NULL) {
																if (string1[1] == 'M') {				/* MOV ?, AX */
																	strcpy(set2[7], string1);
																	i = 1;
																	while (set2[0][i] != '\t') {
																		substr1[i-1] = set2[0][i];
																		i++;
																	}
																	substr1[i-1] = '\0';
																	j = 0;
																	i++;
																	while (set2[0][i] != ',') {
																		substr2[j++] = set2[0][i++];
																	}
																	substr2[j] = '\0';
																	j = 0;
																	i++;
																	i++;
																	while (set2[0][i] != '\n') {
																		substr3[j++] = set2[0][i++];
																	}
																	substr3[j] = '\0';
																	i = 1;
																	while (set2[7][i] != '\t') {
																		substr4[i-1] = set2[7][i];
																		i++;
																	}
																	substr4[i-1] = '\0';
																	j = 0;
																	i++;
																	while (set2[7][i] != ',') {
																		substr5[j++] = set2[7][i++];
																	}
																	substr5[j] = '\0';
																	j = 0;
																	i++;
																	i++;
																	while (set2[7][i] != '\n') {
																		substr6[j++] = set2[7][i++];
																	}
																	substr6[j] = '\0';
																	if ((strcmp(substr1, "MOV") == 0) && (strcmp(substr4, "MOV") == 0) && (strcmp(substr2, "AX") == 0) && (strcmp(substr6, "AX") == 0) && (strcmp(substr3, substr5) == 0)) {
																		fprintf(output, "\tMOV\t%s,\t0\n", substr3);
																		buff = fgets(string1, size, input);
																	} else {
																		if (string1[1] == 'M') {
																			fprintf(output, set2[0]);
																			fprintf(output, set2[1]);
																			fprintf(output, set2[2]);
																			fprintf(output, set2[3]);
																			fprintf(output, set2[4]);
																			fprintf(output, set2[5]);
																			fprintf(output, set2[6]);
																			continue;
																		}
																		fprintf(output, set2[0]);
																		fprintf(output, set2[1]);
																		fprintf(output, set2[2]);
																		fprintf(output, set2[3]);
																		fprintf(output, set2[4]);
																		fprintf(output, set2[5]);
																		fprintf(output, set2[6]);
																		fprintf(output, string1);
																		buff = fgets(string1, size, input);
																	}
																} else {
																	if (string1[1] == 'M') {
																		fprintf(output, set2[0]);
																		fprintf(output, set2[1]);
																		fprintf(output, set2[2]);
																		fprintf(output, set2[3]);
																		fprintf(output, set2[4]);
																		fprintf(output, set2[5]);
																		fprintf(output, set2[6]);
																		continue;
																	}
																	fprintf(output, set2[0]);
																	fprintf(output, set2[1]);
																	fprintf(output, set2[2]);
																	fprintf(output, set2[3]);
																	fprintf(output, set2[4]);
																	fprintf(output, set2[5]);
																	fprintf(output, set2[6]);
																	fprintf(output, string1);
																	buff = fgets(string1, size, input);
																}
															} else {
																fprintf(output, set2[0]);
																fprintf(output, set2[1]);
																fprintf(output, set2[2]);
																fprintf(output, set2[3]);
																fprintf(output, set2[4]);
																fprintf(output, set2[5]);
																fprintf(output, set2[6]);
															}
														} else {
															if (string1[1] == 'M') {
																fprintf(output, set2[0]);
																fprintf(output, set2[1]);
																fprintf(output, set2[2]);
																fprintf(output, set2[3]);
																fprintf(output, set2[4]);
																fprintf(output, set2[5]);
																continue;
															}
															fprintf(output, set2[0]);
															fprintf(output, set2[1]);
															fprintf(output, set2[2]);
															fprintf(output, set2[3]);
															fprintf(output, set2[4]);
															fprintf(output, set2[5]);
															fprintf(output, string1);
															buff = fgets(string1, size, input);
														}
													} else {
														fprintf(output, set2[0]);
														fprintf(output, set2[1]);
														fprintf(output, set2[2]);
														fprintf(output, set2[3]);
														fprintf(output, set2[4]);
														fprintf(output, set2[5]);
													}
												} else {
													if (string1[1] == 'M') {
														fprintf(output, set2[0]);
														fprintf(output, set2[1]);
														fprintf(output, set2[2]);
														fprintf(output, set2[3]);
														fprintf(output, set2[4]);
														continue;
													}
													fprintf(output, set2[0]);
													fprintf(output, set2[1]);
													fprintf(output, set2[2]);
													fprintf(output, set2[3]);
													fprintf(output, set2[4]);
													fprintf(output, string1);
													buff = fgets(string1, size, input);
												}
											} else {
												fprintf(output, set2[0]);
												fprintf(output, set2[1]);
												fprintf(output, set2[2]);
												fprintf(output, set2[3]);
												fprintf(output, set2[4]);
											}
										} else {
											if (string1[1] == 'M') {
												fprintf(output, set2[0]);
												fprintf(output, set2[1]);
												fprintf(output, set2[2]);
												fprintf(output, set2[3]);
												continue;
											}
											fprintf(output, set2[0]);
											fprintf(output, set2[1]);
											fprintf(output, set2[2]);
											fprintf(output, set2[3]);
											fprintf(output, string1);
											buff = fgets(string1, size, input);
										}
									} else {
										fprintf(output, set2[0]);
										fprintf(output, set2[1]);
										fprintf(output, set2[2]);
										fprintf(output, set2[3]);
									}
								} else {
									if (string1[1] == 'M') {
										fprintf(output, set2[0]);
										fprintf(output, set2[1]);
										fprintf(output, set2[2]);
										continue;
									}
									fprintf(output, set2[0]);
									fprintf(output, set2[1]);
									fprintf(output, set2[2]);
									fprintf(output, string1);
									buff = fgets(string1, size, input);
								}
							} else {
								fprintf(output, set2[0]);
								fprintf(output, set2[1]);
								fprintf(output, set2[2]);
							}
						} else {
							if (string1[1] == 'M') {
								fprintf(output, set2[0]);
								fprintf(output, set2[1]);
								continue;
							}
							fprintf(output, set2[0]);
							fprintf(output, set2[1]);
							fprintf(output, string1);
							buff = fgets(string1, size, input);
						}
					} else {
						fprintf(output, set2[0]);
						fprintf(output, set2[1]);
					}
				} else {
					if (string1[1] == 'M') {
						fprintf(output, set2[0]);
						continue;
					}
					fprintf(output, set2[0]);
					fprintf(output, string1);
					buff = fgets(string1, size, input);
				}
			} else {
				fprintf(output, set2[0]);
			}
		} else {
			fprintf(output, string1);
			buff = fgets(string1, size, input);
		}
	}
}

void CodeOptimizerDiv01 (FILE *input, FILE *output) {
	char set1[7][40], set2[9][40], string1[40] = "", substr1[20] = "", substr2[40] = "", substr3[40] = "", substr4[20] = "", substr5[40] = "", substr6[40] = "";
	strcpy(set1[0], "\tPUSH\tAX\n");
	strcpy(set1[1], "\tMOV\tAX,\t1\n");
	strcpy(set1[2], "\tPUSH\tAX\n");
	strcpy(set1[3], "\tPOP\tBX\n");
	strcpy(set1[4], "\tPOP\tAX\n");
	strcpy(set1[5], "\tCWD\n");
	strcpy(set1[6], "\tIDIV\tBX\n");
	char *buff;
	int i, j, size = 40;
	bool flag = true;
	fgets(string1, size, input);
	while (strcmp(string1, ".startup\n") != 0) {
		fprintf(output, string1);
		fgets(string1, size, input);
	}
	fprintf(output, string1);
	buff = fgets(string1, size, input);
	while (buff != NULL) {
		if (string1[1] == 'M') {																				/* MOV AX, ? */
			strcpy(set2[0], string1);
			buff = fgets(string1, size, input);
			if (buff != NULL) {
				if (strcmp(set1[0], string1) == 0) {															/* PUSH AX */
					strcpy(set2[1], string1);
					buff = fgets(string1, size, input);
					if (buff != NULL) {
						if (strcmp(set1[1], string1) == 0) {													/* MOV AX, 1 */
							strcpy(set2[2], string1);
							buff = fgets(string1, size, input);
							if (buff != NULL) {
								if (strcmp(set1[2], string1) == 0) {											/* PUSH AX */
									strcpy(set2[3], string1);
									buff = fgets(string1, size, input);
									if (buff != NULL) {
										if (strcmp(set1[3], string1) == 0) {									/* POP BX */
											strcpy(set2[4], string1);
											buff = fgets(string1, size, input);
											if (buff != NULL) {
												if (strcmp(set1[4], string1) == 0) {							/* POP AX */
													strcpy(set2[5], string1);
													buff = fgets(string1, size, input);
													if (buff != NULL) {
														if (strcmp(set1[5], string1) == 0) {					/* CWD */
															strcpy(set2[6], string1);
															buff = fgets(string1, size, input);
															if (buff != NULL) {
																if (strcmp(set1[6], string1) == 0) {			/* IDIV BX */
																	strcpy(set2[7], string1);
																	buff = fgets(string1, size, input);
																	if (buff != NULL) {
																		if (string1[1] == 'M') {				/* MOV ?, AX */
																			strcpy(set2[8], string1);
																			i = 1;
																			while (set2[0][i] != '\t') {
																				substr1[i-1] = set2[0][i];
																				i++;
																			}
																			substr1[i-1] = '\0';
																			j = 0;
																			i++;
																			while (set2[0][i] != ',') {
																				substr2[j++] = set2[0][i++];
																			}
																			substr2[j] = '\0';
																			j = 0;
																			i++;
																			i++;
																			while (set2[0][i] != '\n') {
																				substr3[j++] = set2[0][i++];
																			}
																			substr3[j] = '\0';
																			i = 1;
																			while (set2[8][i] != '\t') {
																				substr4[i-1] = set2[8][i];
																				i++;
																			}
																			substr4[i-1] = '\0';
																			j = 0;
																			i++;
																			while (set2[8][i] != ',') {
																				substr5[j++] = set2[8][i++];
																			}
																			substr5[j] = '\0';
																			j = 0;
																			i++;
																			i++;
																			while (set2[8][i] != '\n') {
																				substr6[j++] = set2[8][i++];
																			}
																			substr6[j] = '\0';
																			if ((strcmp(substr1, "MOV") == 0) && (strcmp(substr4, "MOV") == 0) && (strcmp(substr2, "AX") == 0) && (strcmp(substr6, "AX") == 0) && (strcmp(substr3, substr5) == 0)) {
																				buff = fgets(string1, size, input);
																			} else {
																				if (string1[1] == 'M') {
																					fprintf(output, set2[0]);
																					fprintf(output, set2[1]);
																					fprintf(output, set2[2]);
																					fprintf(output, set2[3]);
																					fprintf(output, set2[4]);
																					fprintf(output, set2[5]);
																					fprintf(output, set2[6]);
																					fprintf(output, set2[7]);
																					continue;
																				}
																				fprintf(output, set2[0]);
																				fprintf(output, set2[1]);
																				fprintf(output, set2[2]);
																				fprintf(output, set2[3]);
																				fprintf(output, set2[4]);
																				fprintf(output, set2[5]);
																				fprintf(output, set2[6]);
																				fprintf(output, set2[7]);
																				fprintf(output, string1);
																				buff = fgets(string1, size, input);
																			}
																		} else {
																			if (string1[1] == 'M') {
																				fprintf(output, set2[0]);
																				fprintf(output, set2[1]);
																				fprintf(output, set2[2]);
																				fprintf(output, set2[3]);
																				fprintf(output, set2[4]);
																				fprintf(output, set2[5]);
																				fprintf(output, set2[6]);
																				fprintf(output, set2[7]);
																				continue;
																			}
																			fprintf(output, set2[0]);
																			fprintf(output, set2[1]);
																			fprintf(output, set2[2]);
																			fprintf(output, set2[3]);
																			fprintf(output, set2[4]);
																			fprintf(output, set2[5]);
																			fprintf(output, set2[6]);
																			fprintf(output, set2[7]);
																			fprintf(output, string1);
																			buff = fgets(string1, size, input);
																		}
																	} else {
																		fprintf(output, set2[0]);
																		fprintf(output, set2[1]);
																		fprintf(output, set2[2]);
																		fprintf(output, set2[3]);
																		fprintf(output, set2[4]);
																		fprintf(output, set2[5]);
																		fprintf(output, set2[6]);
																		fprintf(output, set2[7]);
																	}
																} else {
																	if (string1[1] == 'M') {
																		fprintf(output, set2[0]);
																		fprintf(output, set2[1]);
																		fprintf(output, set2[2]);
																		fprintf(output, set2[3]);
																		fprintf(output, set2[4]);
																		fprintf(output, set2[5]);
																		fprintf(output, set2[6]);
																		continue;
																	}
																	fprintf(output, set2[0]);
																	fprintf(output, set2[1]);
																	fprintf(output, set2[2]);
																	fprintf(output, set2[3]);
																	fprintf(output, set2[4]);
																	fprintf(output, set2[5]);
																	fprintf(output, set2[6]);
																	fprintf(output, string1);
																	buff = fgets(string1, size, input);
																}
															} else {
																fprintf(output, set2[0]);
																fprintf(output, set2[1]);
																fprintf(output, set2[2]);
																fprintf(output, set2[3]);
																fprintf(output, set2[4]);
																fprintf(output, set2[5]);
																fprintf(output, set2[6]);
															}
														} else {
															if (string1[1] == 'M') {
																fprintf(output, set2[0]);
																fprintf(output, set2[1]);
																fprintf(output, set2[2]);
																fprintf(output, set2[3]);
																fprintf(output, set2[4]);
																fprintf(output, set2[5]);
																continue;
															}
															fprintf(output, set2[0]);
															fprintf(output, set2[1]);
															fprintf(output, set2[2]);
															fprintf(output, set2[3]);
															fprintf(output, set2[4]);
															fprintf(output, set2[5]);
															fprintf(output, string1);
															buff = fgets(string1, size, input);
														}
													} else {
														fprintf(output, set2[0]);
														fprintf(output, set2[1]);
														fprintf(output, set2[2]);
														fprintf(output, set2[3]);
														fprintf(output, set2[4]);
														fprintf(output, set2[5]);
													}
												} else {
													if (string1[1] == 'M') {
														fprintf(output, set2[0]);
														fprintf(output, set2[1]);
														fprintf(output, set2[2]);
														fprintf(output, set2[3]);
														fprintf(output, set2[4]);
														continue;
													}
													fprintf(output, set2[0]);
													fprintf(output, set2[1]);
													fprintf(output, set2[2]);
													fprintf(output, set2[3]);
													fprintf(output, set2[4]);
													fprintf(output, string1);
													buff = fgets(string1, size, input);
												}
											} else {
												fprintf(output, set2[0]);
												fprintf(output, set2[1]);
												fprintf(output, set2[2]);
												fprintf(output, set2[3]);
												fprintf(output, set2[4]);
											}
										} else {
											if (string1[1] == 'M') {
												fprintf(output, set2[0]);
												fprintf(output, set2[1]);
												fprintf(output, set2[2]);
												fprintf(output, set2[3]);
												continue;
											}
											fprintf(output, set2[0]);
											fprintf(output, set2[1]);
											fprintf(output, set2[2]);
											fprintf(output, set2[3]);
											fprintf(output, string1);
											buff = fgets(string1, size, input);
										}
									} else {
										fprintf(output, set2[0]);
										fprintf(output, set2[1]);
										fprintf(output, set2[2]);
										fprintf(output, set2[3]);
									}
								} else {
									if (string1[1] == 'M') {
										fprintf(output, set2[0]);
										fprintf(output, set2[1]);
										fprintf(output, set2[2]);
										continue;
									}
									fprintf(output, set2[0]);
									fprintf(output, set2[1]);
									fprintf(output, set2[2]);
									fprintf(output, string1);
									buff = fgets(string1, size, input);
								}
							} else {
								fprintf(output, set2[0]);
								fprintf(output, set2[1]);
								fprintf(output, set2[2]);
							}
						} else {
							if (string1[1] == 'M') {
								fprintf(output, set2[0]);
								fprintf(output, set2[1]);
								continue;
							}
							fprintf(output, set2[0]);
							fprintf(output, set2[1]);
							fprintf(output, string1);
							buff = fgets(string1, size, input);
						}
					} else {
						fprintf(output, set2[0]);
						fprintf(output, set2[1]);
					}
				} else {
					if (string1[1] == 'M') {
						fprintf(output, set2[0]);
						continue;
					}
					fprintf(output, set2[0]);
					fprintf(output, string1);
					buff = fgets(string1, size, input);
				}
			} else {
				fprintf(output, set2[0]);
			}
		} else {
			fprintf(output, string1);
			buff = fgets(string1, size, input);
		}
	}
}

void CodeOptimizerMod01 (FILE *input, FILE *output) {
	char set1[9][40], set2[11][40], string1[40] = "", substr1[20] = "", substr2[40] = "", substr3[40] = "", substr4[20] = "", substr5[40] = "", substr6[40] = "";
	strcpy(set1[0], "\tPUSH\tAX\n");
	strcpy(set1[1], "\tMOV\tAX,\t1\n");
	strcpy(set1[2], "\tPUSH\tAX\n");
	strcpy(set1[3], "\tPOP\tBX\n");
	strcpy(set1[4], "\tPOP\tAX\n");
	strcpy(set1[5], "\tCWD\n");
	strcpy(set1[6], "\tIDIV\tBX\n");
	strcpy(set1[7], "\tPUSH\tDX\n");
	strcpy(set1[8], "\tPOP\tAX\n");
	char *buff;
	int i, j, size = 40;
	bool flag = true;
	fgets(string1, size, input);
	while (strcmp(string1, ".startup\n") != 0) {
		fprintf(output, string1);
		fgets(string1, size, input);
	}
	fprintf(output, string1);
	buff = fgets(string1, size, input);
	while (buff != NULL) {
		if (string1[1] == 'M') {																								/* MOV AX, ? */
			strcpy(set2[0], string1);
			buff = fgets(string1, size, input);
			if (buff != NULL) {
				if (strcmp(set1[0], string1) == 0) {																			/* PUSH AX */
					strcpy(set2[1], string1);
					buff = fgets(string1, size, input);
					if (buff != NULL) {
						if (strcmp(set1[1], string1) == 0) {																	/* MOV AX, 1 */
							strcpy(set2[2], string1);
							buff = fgets(string1, size, input);
							if (buff != NULL) {
								if (strcmp(set1[2], string1) == 0) {															/* PUSH AX */
									strcpy(set2[3], string1);
									buff = fgets(string1, size, input);
									if (buff != NULL) {
										if (strcmp(set1[3], string1) == 0) {													/* POP BX */
											strcpy(set2[4], string1);
											buff = fgets(string1, size, input);
											if (buff != NULL) {
												if (strcmp(set1[4], string1) == 0) {											/* POP AX */
													strcpy(set2[5], string1);
													buff = fgets(string1, size, input);
													if (buff != NULL) {
														if (strcmp(set1[5], string1) == 0) {									/* CWD */
															strcpy(set2[6], string1);
															buff = fgets(string1, size, input);
															if (buff != NULL) {
																if (strcmp(set1[6], string1) == 0) {							/* IDIV BX */
																	strcpy(set2[7], string1);
																	buff = fgets(string1, size, input);
																	if (buff != NULL) {
																		if (strcmp(set1[7], string1) == 0) {					/* PUSH DX */
																			strcpy(set2[8], string1);
																			buff = fgets(string1, size, input);
																			if (buff != NULL) {
																				if (strcmp(set1[8], string1) == 0) {			/* POP AX */
																					strcpy(set2[9], string1);
																					buff = fgets(string1, size, input);
																					if (buff != NULL) {
																						if (string1[1] == 'M') {				/* MOV ?, AX */
																							strcpy(set2[10], string1);
																							i = 1;
																							while (set2[0][i] != '\t') {
																								substr1[i-1] = set2[0][i];
																								i++;
																							}
																							substr1[i-1] = '\0';
																							j = 0;
																							i++;
																							while (set2[0][i] != ',') {
																								substr2[j++] = set2[0][i++];
																							}
																							substr2[j] = '\0';
																							j = 0;
																							i++;
																							i++;
																							while (set2[0][i] != '\n') {
																								substr3[j++] = set2[0][i++];
																							}
																							substr3[j] = '\0';
																							i = 1;
																							while (set2[10][i] != '\t') {
																								substr4[i-1] = set2[10][i];
																								i++;
																							}
																							substr4[i-1] = '\0';
																							j = 0;
																							i++;
																							while (set2[10][i] != ',') {
																								substr5[j++] = set2[10][i++];
																							}
																							substr5[j] = '\0';
																							j = 0;
																							i++;
																							i++;
																							while (set2[10][i] != '\n') {
																								substr6[j++] = set2[10][i++];
																							}
																							substr6[j] = '\0';
																							if ((strcmp(substr1, "MOV") == 0) && (strcmp(substr4, "MOV") == 0) && (strcmp(substr2, "AX") == 0) && (strcmp(substr6, "AX") == 0) && (strcmp(substr3, substr5) == 0)) {
																								buff = fgets(string1, size, input);
																							} else {
																								if (string1[1] == 'M') {
																									fprintf(output, set2[0]);
																									fprintf(output, set2[1]);
																									fprintf(output, set2[2]);
																									fprintf(output, set2[3]);
																									fprintf(output, set2[4]);
																									fprintf(output, set2[5]);
																									fprintf(output, set2[6]);
																									fprintf(output, set2[7]);
																									fprintf(output, set2[8]);
																									fprintf(output, set2[9]);
																									continue;
																								}
																								fprintf(output, set2[0]);
																								fprintf(output, set2[1]);
																								fprintf(output, set2[2]);
																								fprintf(output, set2[3]);
																								fprintf(output, set2[4]);
																								fprintf(output, set2[5]);
																								fprintf(output, set2[6]);
																								fprintf(output, set2[7]);
																								fprintf(output, set2[8]);
																								fprintf(output, set2[9]);
																								fprintf(output, string1);
																								buff = fgets(string1, size, input);
																							}
																						} else {
																							if (string1[1] == 'M') {
																								fprintf(output, set2[0]);
																								fprintf(output, set2[1]);
																								fprintf(output, set2[2]);
																								fprintf(output, set2[3]);
																								fprintf(output, set2[4]);
																								fprintf(output, set2[5]);
																								fprintf(output, set2[6]);
																								fprintf(output, set2[7]);
																								fprintf(output, set2[8]);
																								fprintf(output, set2[9]);
																								continue;
																							}
																							fprintf(output, set2[0]);
																							fprintf(output, set2[1]);
																							fprintf(output, set2[2]);
																							fprintf(output, set2[3]);
																							fprintf(output, set2[4]);
																							fprintf(output, set2[5]);
																							fprintf(output, set2[6]);
																							fprintf(output, set2[7]);
																							fprintf(output, set2[8]);
																							fprintf(output, set2[9]);
																							fprintf(output, string1);
																							buff = fgets(string1, size, input);
																						}
																					} else {
																						fprintf(output, set2[0]);
																						fprintf(output, set2[1]);
																						fprintf(output, set2[2]);
																						fprintf(output, set2[3]);
																						fprintf(output, set2[4]);
																						fprintf(output, set2[5]);
																						fprintf(output, set2[6]);
																						fprintf(output, set2[7]);
																						fprintf(output, set2[8]);
																						fprintf(output, set2[9]);
																					}
																				} else {
																					if (string1[1] == 'M') {
																						fprintf(output, set2[0]);
																						fprintf(output, set2[1]);
																						fprintf(output, set2[2]);
																						fprintf(output, set2[3]);
																						fprintf(output, set2[4]);
																						fprintf(output, set2[5]);
																						fprintf(output, set2[6]);
																						fprintf(output, set2[7]);
																						fprintf(output, set2[8]);
																						continue;
																					}
																					fprintf(output, set2[0]);
																					fprintf(output, set2[1]);
																					fprintf(output, set2[2]);
																					fprintf(output, set2[3]);
																					fprintf(output, set2[4]);
																					fprintf(output, set2[5]);
																					fprintf(output, set2[6]);
																					fprintf(output, set2[7]);
																					fprintf(output, set2[8]);
																					fprintf(output, string1);
																					buff = fgets(string1, size, input);
																				}
																			} else {
																				fprintf(output, set2[0]);
																				fprintf(output, set2[1]);
																				fprintf(output, set2[2]);
																				fprintf(output, set2[3]);
																				fprintf(output, set2[4]);
																				fprintf(output, set2[5]);
																				fprintf(output, set2[6]);
																				fprintf(output, set2[7]);
																				fprintf(output, set2[8]);
																			}
																		} else {
																			if (string1[1] == 'M') {
																				fprintf(output, set2[0]);
																				fprintf(output, set2[1]);
																				fprintf(output, set2[2]);
																				fprintf(output, set2[3]);
																				fprintf(output, set2[4]);
																				fprintf(output, set2[5]);
																				fprintf(output, set2[6]);
																				fprintf(output, set2[7]);
																				continue;
																			}
																			fprintf(output, set2[0]);
																			fprintf(output, set2[1]);
																			fprintf(output, set2[2]);
																			fprintf(output, set2[3]);
																			fprintf(output, set2[4]);
																			fprintf(output, set2[5]);
																			fprintf(output, set2[6]);
																			fprintf(output, set2[7]);
																			fprintf(output, string1);
																			buff = fgets(string1, size, input);
																		}
																	} else {
																		fprintf(output, set2[0]);
																		fprintf(output, set2[1]);
																		fprintf(output, set2[2]);
																		fprintf(output, set2[3]);
																		fprintf(output, set2[4]);
																		fprintf(output, set2[5]);
																		fprintf(output, set2[6]);
																		fprintf(output, set2[7]);
																	}
																} else {
																	if (string1[1] == 'M') {
																		fprintf(output, set2[0]);
																		fprintf(output, set2[1]);
																		fprintf(output, set2[2]);
																		fprintf(output, set2[3]);
																		fprintf(output, set2[4]);
																		fprintf(output, set2[5]);
																		fprintf(output, set2[6]);
																		continue;
																	}
																	fprintf(output, set2[0]);
																	fprintf(output, set2[1]);
																	fprintf(output, set2[2]);
																	fprintf(output, set2[3]);
																	fprintf(output, set2[4]);
																	fprintf(output, set2[5]);
																	fprintf(output, set2[6]);
																	fprintf(output, string1);
																	buff = fgets(string1, size, input);
																}
															} else {
																fprintf(output, set2[0]);
																fprintf(output, set2[1]);
																fprintf(output, set2[2]);
																fprintf(output, set2[3]);
																fprintf(output, set2[4]);
																fprintf(output, set2[5]);
																fprintf(output, set2[6]);
															}
														} else {
															if (string1[1] == 'M') {
																fprintf(output, set2[0]);
																fprintf(output, set2[1]);
																fprintf(output, set2[2]);
																fprintf(output, set2[3]);
																fprintf(output, set2[4]);
																fprintf(output, set2[5]);
																continue;
															}
															fprintf(output, set2[0]);
															fprintf(output, set2[1]);
															fprintf(output, set2[2]);
															fprintf(output, set2[3]);
															fprintf(output, set2[4]);
															fprintf(output, set2[5]);
															fprintf(output, string1);
															buff = fgets(string1, size, input);
														}
													} else {
														fprintf(output, set2[0]);
														fprintf(output, set2[1]);
														fprintf(output, set2[2]);
														fprintf(output, set2[3]);
														fprintf(output, set2[4]);
														fprintf(output, set2[5]);
													}
												} else {
													if (string1[1] == 'M') {
														fprintf(output, set2[0]);
														fprintf(output, set2[1]);
														fprintf(output, set2[2]);
														fprintf(output, set2[3]);
														fprintf(output, set2[4]);
														continue;
													}
													fprintf(output, set2[0]);
													fprintf(output, set2[1]);
													fprintf(output, set2[2]);
													fprintf(output, set2[3]);
													fprintf(output, set2[4]);
													fprintf(output, string1);
													buff = fgets(string1, size, input);
												}
											} else {
												fprintf(output, set2[0]);
												fprintf(output, set2[1]);
												fprintf(output, set2[2]);
												fprintf(output, set2[3]);
												fprintf(output, set2[4]);
											}
										} else {
											if (string1[1] == 'M') {
												fprintf(output, set2[0]);
												fprintf(output, set2[1]);
												fprintf(output, set2[2]);
												fprintf(output, set2[3]);
												continue;
											}
											fprintf(output, set2[0]);
											fprintf(output, set2[1]);
											fprintf(output, set2[2]);
											fprintf(output, set2[3]);
											fprintf(output, string1);
											buff = fgets(string1, size, input);
										}
									} else {
										fprintf(output, set2[0]);
										fprintf(output, set2[1]);
										fprintf(output, set2[2]);
										fprintf(output, set2[3]);
									}
								} else {
									if (string1[1] == 'M') {
										fprintf(output, set2[0]);
										fprintf(output, set2[1]);
										fprintf(output, set2[2]);
										continue;
									}
									fprintf(output, set2[0]);
									fprintf(output, set2[1]);
									fprintf(output, set2[2]);
									fprintf(output, string1);
									buff = fgets(string1, size, input);
								}
							} else {
								fprintf(output, set2[0]);
								fprintf(output, set2[1]);
								fprintf(output, set2[2]);
							}
						} else {
							if (string1[1] == 'M') {
								fprintf(output, set2[0]);
								fprintf(output, set2[1]);
								continue;
							}
							fprintf(output, set2[0]);
							fprintf(output, set2[1]);
							fprintf(output, string1);
							buff = fgets(string1, size, input);
						}
					} else {
						fprintf(output, set2[0]);
						fprintf(output, set2[1]);
					}
				} else {
					if (string1[1] == 'M') {
						fprintf(output, set2[0]);
						continue;
					}
					fprintf(output, set2[0]);
					fprintf(output, string1);
					buff = fgets(string1, size, input);
				}
			} else {
				fprintf(output, set2[0]);
			}
		} else {
			fprintf(output, string1);
			buff = fgets(string1, size, input);
		}
	}
}