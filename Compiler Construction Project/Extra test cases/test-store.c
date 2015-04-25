records:
	rec student:
		int rollno;
		int marks;
		char grade;
		bool pass;
	endrec
	rec police:
		int class;
		bool isNice;
		char grade;
	endrec
	rec teacher:
		int class;
		bool isNice;
		char grade;
	endrec
endrecords

procs:
	proc proc3(int a)->(int c):
		assign c = 10;
	endproc
	proc proc1(int a, bool b,real c)->(real d, bool e, int f):
		assign d = c;
		assign e = b;
		assign f = a;
	endproc
	proc proc2(int a)->(real b):
		assign b = 100.0;
	endproc
endprocs

execute:
	mat<int>[2,2] matint;
	int a,b;
	real c,d;
	string g,h;
	bool e,f;
	char i,j;
end