procs:
	proc square(int num, bool a, int b)->(int sqr, real c, int d):
		assign sqr = num * num;
		assign sqr = sqr * times;
		assign sqr = sqr * times;
	endproc
endprocs

execute:
	int num, times, n, res;
	assign num = 10;
	assign times = 2;
	assign n = 20;
	
	call square(n)->(res);
	int d;
	put("Result: "); 
	put(res);
end
