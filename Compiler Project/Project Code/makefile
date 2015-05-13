FLGS = -w
DEP  = compiler.o CodeGenerator.o SymbolTable.o TypeChecker.o AST.o parser.o Tree.o SymbolStack.o SymbolLinkedList.o mapping.o LinkedList.o lexer.o DFA.o BufferInput.o hashTable.o


c:$(DEP)
	gcc $(FLGS) $(DEP) -o compiler

co:
	gcc -w -Wall compiler.c lexer.c DFA.c hashTable.c BufferInput.c parser.c SymbolLinkedList.c SymbolStack.c Tree.c mapping.c LinkedList.c TypeChecker.c SymbolTable.c AST.c -o compiler
	
d: dcompBuild
	gdb a.out

dcompBuild:
	gcc -g -w compiler.c lexer.c DFA.c hashTable.c BufferInput.c parser.c SymbolLinkedList.c SymbolStack.c Tree.c mapping.c AST.c LinkedList.c SymbolTable.c TypeChecker.c CodeGenerator.c


compiler.o: compiler.c
	gcc $(FLGS) -c $^

CodeGenerator.o: CodeGenerator.c CodeGenerator.h
	gcc $(FLGS) -c $^

SymbolTable.o: SymbolTable.c SymbolTable.h
	gcc $(FLGS) -c $^

TypeChecker.o: TypeChecker.c TypeChecker.h SymbolTable.h AST.h
	gcc $(FLGS) -c $^

AST.o: AST.c AST.h
	gcc $(FLGS) -c $^

parser.o: parser.c parser.h
	gcc $(FLGS) -c $^

Tree.o: Tree.c Tree.h
	gcc $(FLGS) -c $^

SymbolStack.o: SymbolStack.c SymbolStack.h
	gcc $(FLGS) -c $^

SymbolLinkedList.o: SymbolLinkedList.c SymbolLinkedList.h
	gcc $(FLGS) -c $^

mapping.o: mapping.c mapping.h
	gcc $(FLGS) -c $^

LinkedList.o: LinkedList.c LinkedList.h
	gcc $(FLGS) -c $^

lexer.o: lexer.c lexer.h
	gcc $(FLGS) -c $^

DFA.o: DFA.c DFA.h
	gcc $(FLGS) -c $^

BufferInput.o: BufferInput.c BufferInput.h
	gcc $(FLGS) -c $^

hashTable.o: hashTable.c hashTable.h
	gcc $(FLGS) -c $^

clean:
	-rm -f *.o *.exe *.h.gch *.out *.asm core compiler
