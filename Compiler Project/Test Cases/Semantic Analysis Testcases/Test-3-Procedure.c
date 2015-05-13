procs:
	proc proc1(int a)->(int c):
		int b;
		assign b = 50;
		call proc1(a)->(c);
	endproc
	proc proc2(int a, bool b, real c)->(int d):
		assign d = 50;
	endproc
	proc proc3(int a,int b)->(int c,int d):
		assign d = 10;
	endproc
endprocs
execute:
	int a,b;
	real c,d;
	bool e,f;

	call proc4(a)->(b);
	call proc2(a,e,c)->(a);
	call proc2(a,c,e)->(a);
	call proc3(a,b,c)->(a,b);
	call proc3(a)->(a,b);
	call proc3(a,b)->(a,b,d);
	call proc3(a,b)->(a);

	if(a>b):
		bool b;
		real e,v;
		if(c>v):
			int k,l;
			call proc2(a,b,e)->(a);
		endif
	elif(a<b):
		bool c,d;
	else:
		bool g,h;
	endif
end