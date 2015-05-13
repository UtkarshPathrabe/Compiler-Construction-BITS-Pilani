/********************************
       |TEAM-1 | GROUP-20|
UTKARSH PATHRABE  - 2012A7PS034P
SHIKHAR VASHISHTH - 2012C6PS436P
********************************/
#include "mapping.h"

char *symbolToStr(Symbol sym){
	switch(sym){
		case EPSILON: return "EPSILON";
		case EXECUTE: return "EXECUTE";
		case COLON: return "COLON";
		case END: return "END";
		case RECORDS: return "RECORDS";
		case ENDRECORDS: return "ENDRECORDS";
		case REC: return "REC";
		case ID: return "ID";
		case ENDREC: return "ENDREC";
		case PROCS: return "PROCS";
		case ENDPROCS: return "ENDPROCS";
		case PROC: return "PROC";
		case LPAREN: return "LPAREN";
		case RPAREN: return "RPAREN";
		case ARROW: return "ARROW";
		case ENDPROC: return "ENDPROC";
		case COMMA: return "COMMA";
		case SEMICOLON: return "SEMICOLON";
		case STRING: return "STRING";
		case MAT: return "MAT";
		case LT: return "LT";
		case GT: return "GT";
		case LSQ: return "LSQ";
		case RSQ: return "RSQ";
		case INT: return "INT";
		case REAL: return "REAL";
		case BOOL: return "BOOL";
		case CHAR: return "CHAR";
		case INT_LIT: return "INT_LIT";
		case IF: return "IF";
		case ELIF: return "ELIF";
		case ELSE: return "ELSE";
		case ENDIF: return "ENDIF";
		case GET: return "GET";
		case PUT: return "PUT";
		case ENDL: return "ENDL";
		case TAB: return "TAB";
		case STR_LIT: return "STR_LIT";
		case DOT: return "DOT";
		case CALL: return "CALL";
		case LOOP: return "LOOP";
		case ENDLOOP: return "ENDLOOP";
		case BREAK: return "BREAK";
		case CONTINUE: return "CONTINUE";
		case NOT: return "NOT";
		case BOOL_LIT: return "BOOL_LIT";
		case AND: return "AND";
		case OR: return "OR";
		case LE: return "LE";
		case GE: return "GE";
		case EQ: return "EQ";
		case NEQ: return "NEQ";
		case REAL_LIT: return "REAL_LIT";
		case CHAR_LIT: return "CHAR_LIT";
		case ASSIGN: return "ASSIGN";
		case ASSIGN_OP: return "ASSIGN_OP";
		case MINUS: return "MINUS";
		case PLUS: return "PLUS";
		case MUL: return "MUL";
		case DIV: return "DIV";
		case MOD: return "MOD";
		case POW: return "POW";
		case MATASSIGN: return "MATASSIGN";
		case LCURL: return "LCURL";
		case RCURL: return "RCURL";
		case MAT_ROWS: return "MAT_ROWS";
		case MAT_COLS: return "MAT_COLS";
		case STRASSIGN: return "STRASSIGN";
		case STR_LENGTH: return "STR_LENGTH";
		case program: return "program";
		case execute: return "execute";
		case _records: return "_records";
		case records: return "records";
		case recs: return "recs";
		case _recs: return "_recs";
		case rec: return "rec";
		case _procedures: return "_procedures";
		case procedures: return "procedures";
		case procs: return "procs";
		case _procs: return "_procs";
		case proc: return "proc";
		case param_list: return "param_list";
		case _param_list: return "_param_list";
		case stmts: return "stmts";
		case _stmts: return "_stmts";
		case stmt: return "stmt";
		case decl_stmts: return "decl_stmts";
		case _decl_stmts: return "_decl_stmts";
		case decl_stmt: return "decl_stmt";
		case type: return "type";
		case basic_type: return "basic_type";
		case id_list: return "id_list";
		case _id_list: return "_id_list";
		case dims: return "dims";
		case _dim_list: return "_dim_list";
		case cond_stmt: return "cond_stmt";
		case else_if: return "else_if";
		case _cond_stmt: return "_cond_stmt";
		case io_stmt: return "io_stmt";
		case put_param: return "put_param";
		case var: return "var";
		case _var: return "_var";
		case proc_call_stmt: return "proc_call_stmt";
		case proc_arg_list: return "proc_arg_list";
		case arg_list: return "arg_list";
		case arg_list1: return "arg_list1";
		case arg_list2: return "arg_list2";
		case loop_stmt: return "loop_stmt";
		case iloop_stmts: return "iloop_stmts";
		case iloop_stmt: return "iloop_stmt";
		case assign_list: return "assign_list";
		case conds: return "conds";
		case logical_op: return "logical_op";
		case rel_op: return "rel_op";
		case elem: return "elem";
		case assign_stmt: return "assign_stmt";
		case expr: return "expr";
		case _expr: return "_expr";
		case term: return "term";
		case _term: return "_term";
		case expo_term: return "expo_term";
		case _expo_term: return "_expo_term";
		case factor: return "factor";
		case op_PlusMinus: return "op_PlusMinus";
		case op_mulDivMod: return "op_mulDivMod";
		case op_pow: return "op_pow";
		case mat_assign_stmt: return "mat_assign_stmt";
		case mat_stmt: return "mat_stmt";
		case _mat_stmt: return "_mat_stmt";
		case row_list: return "row_list";
		case _row_list: return "_row_list";
		case row: return "row";
		case _row: return "_row";
		case const_: return "const_";
		case str_assign_stmt: return "str_assign_stmt";
		case str_stmt: return "str_stmt";
		case _str_stmt: return "_str_stmt";
		case ind: return "ind";
		case DOLLAR: return "DOLLAR";
		case ID_MAT: return "ID_MAT";
		case ID_REC: return "ID_REC";
		case ID_PROC: return "ID_PROC";
		case ID_PRI: return "ID_PRI";
		case ID_MAT_RHS: return "ID_MAT_RHS";
		case ID_REC_RHS: return "ID_REC_RHS";
	}
}

char* tokenToStr(Token tk){
	switch(tk){
		case TK_PASS: return "";
		case TK_EXECUTE: return "execute";
		case TK_COLON: return ":";
		case TK_END: return "end";
		case TK_RECBLK: return "records";
		case TK_ENDRECBLK: return "endrecords";
		case TK_REC: return "rec";
		case TK_ID: return "identifier";
		case TK_ENDREC: return "endrec";
		case TK_PROCBLK: return "procs";
		case TK_ENDPROCBLK: return "endprocs";
		case TK_PROC: return "proc";
		case TK_LPAREN: return "(";
		case TK_RPAREN: return ")";
		case TK_ARROW: return "->";
		case TK_ENDPROC: return "endproc";
		case TK_COMMA: return ",";
		case TK_SEMICOLON: return ";";
		case TK_STRING: return "string";
		case TK_MAT: return "mat";
		case TK_LT: return "<";
		case TK_GT: return ">";
		case TK_LSQ: return "[";
		case TK_RSQ: return "]";
		case TK_INT: return "int";
		case TK_REAL: return "real";
		case TK_BOOL: return "bool";
		case TK_CHAR: return "char";
		case TK_INT_LIT: return "Integer Literal";
		case TK_IF: return "if";
		case TK_ELIF: return "elif";
		case TK_ELSE: return "else";
		case TK_ENDIF: return "endif";
		case TK_GET: return "get";
		case TK_PUT: return "put";
		case TK_ENDL: return "endl";
		case TK_TAB: return "tab";
		case TK_STR_LIT: return "String Literal";
		case TK_DOT: return ".";
		case TK_CALL: return "call";
		case TK_LOOP: return "loop";
		case TK_ENDLOOP: return "endloop";
		case TK_BREAK: return "break";
		case TK_CONTINUE: return "continue";
		case TK_NOT: return "NOT";
		case TK_BOOL_LIT: return "Boolean Literal" ;
		case TK_AND: return "AND";
		case TK_OR: return "OR";
		case TK_LE: return "<=";
		case TK_GE: return ">=";
		case TK_EQ: return "==";
		case TK_NEQ: return "!=";
		case TK_REAL_LIT: return "Real Literal";
		case TK_CHAR_LIT: return "Char Literal";
		case TK_ASSIGN: return "assign";
		case TK_ASSIGN_OP: return "=";
		case TK_MINUS: return "-";
		case TK_PLUS: return "+";
		case TK_MUL: return "*";
		case TK_DIV: return "/";
		case TK_MOD: return "%";
		case TK_POW: return "**";
		case TK_MATASSIGN: return "matassign";
		case TK_LCURL: return "{";
		case TK_RCURL: return "}";
		case TK_MAT_ROWS: return "@rows" ;
		case TK_MAT_COLS: return "@cols";
		case TK_STRASSIGN: return "strassign";
		case TK_STR_LENGTH: return "@length";
	}
}

char* typeToStr(Type type){
	switch(type){
		case INT_TYPE: return "INT_TYPE";
		case CHAR_TYPE: return "CHAR_TYPE";
		case REAL_TYPE: return "REAL_TYPE";
		case BOOL_TYPE: return "BOOL_TYPE";
		case MAT_TYPE: return "MAT_TYPE";
		case STR_TYPE: return "STR_TYPE";
		case REC_TYPE: return "REC_TYPE";
		case PROC_TYPE: return "PROC_TYPE";
		case RECDEC_TYPE: return "RECDEC_TYPE";
	}
}