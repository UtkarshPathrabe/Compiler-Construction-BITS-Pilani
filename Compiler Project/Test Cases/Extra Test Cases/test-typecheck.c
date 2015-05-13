procs:
	proc proc1(int a, bool b,real c)->(real d, bool e, int f):
		assign d = c;
		assign e = b;
		assign f = a;
	endproc
	proc proc3(int a)->(int c):
		assign c = 10;
	endproc
endprocs

execute:
	int a; 
	int b;
	real c;
	bool d;

	assign a=b+c;
	assign a=b+c;
	int b;


	call proc3(a)->(a);
	call proc1(a,b,c)->(c, b, a,a);
end