procs:
	proc proc4(int a)->(int c):
		int b;
		assign b = 50;
	endproc
	proc proc3(int a)->(int c):
		int b;
		assign b = 50;
	endproc
	proc proc5(int a)->(int c):
		int d;
		assign d = 10;
	endproc
endprocs
execute:
	int a,b;
	int i,j;

	if(a>b):
		int d,a;
		real c,v;
		if(c>v):
			int k,l;
			call proc4(a)->(d);
		else:
			char c,d;
		endif
	elif(a<b):
		bool c,d;
	else:
		bool g,h;
	endif
end