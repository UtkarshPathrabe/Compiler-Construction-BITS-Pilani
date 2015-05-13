/********************************
       |TEAM-1 | GROUP-20|
UTKARSH PATHRABE  - 2012A7PS034P
SHIKHAR VASHISHTH - 2012C6PS436P
********************************/

-> All features of compiler are successfully implemented.

Type checking rules:
 1. The type of an identifier is the type appearing while declaring the variable.
 2. The type of an identifier of a record type expanded with a dot followed by the field name is same as that of the field.
 3. The type of a record type is a tuple.
 4. If undefined component of record is accessed then error is generated.
 5. The type of a simple expression of the form EXP <operator> EXP
	a. is integer, if both expressions are of type integer and the operator is arithmetic operator.
	b. is real, if both the expressions are of type real and the operator is arithmetic operator.
	c. is boolean, if both expressions are of type integer and the operator is relational operator.
	d. is boolean, if both expressions are of type real and the operator is relational.
	e. is record type T if both E1 and E2 are of the same record type T.
 6. In matassign:
 	a. @rows, @cols operations LHS must be of integer type and RHS of matrix type.
 	b. matrix addition operation dimension and type of matrices on both sides of equation must be same.
 	c. While accessing a matrix element indices must be of integer type and should be less than dimension of matrix
 7. In strassign:
 	a. @length operation LHS must be of integer type and RHS of string type.
 	b. string concatenation operation checks all variables are of string type.
 	c. While accessing a string element indices must be of integer type.
 8. In failure of any of above cases error is generated on stdout.
 9. The type of an identifier or an expression is computed by traversing the abstract syntax tree.
 10. INT_LIT token is of integer type, REAL_LIT token is of real type, BOOL_LIT token is of bool type, CHAR_LIT token is of char type and STR_LIT token is of string type.


Semantic Analysis Rules:
 1. Identifier cannot be declared multiple times in the same scope.
 2. Identifier declared globally can be redeclared anywhere else in procedure definitions and new scope.
 3. Identifier needs to be declared in the same scope or in its parent's scope for its use.
 4. Redefinition of same record is not allowed.
 5. Procedure overloading is not allowed.
 6. Procedure cannot be invoked recursively.
 7. Types and the number of input and output parameters passed while invoking procedure should be the same as in its definition.
 8. Matrix and string can be intialized with appropriate values.
 9. The right hand side expression of an assignment statement must be of the same type as that of the left hand side identifier.
 10. A record type definition is visible anywhere in the program.