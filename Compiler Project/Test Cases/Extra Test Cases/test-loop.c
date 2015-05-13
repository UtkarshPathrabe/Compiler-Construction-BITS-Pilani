execute:
	mat<int>[2,2] A;
	int i,j;
	loop(assign i=0;)(i<2)(assign i=i+1;):
		loop(assign j=0;)(j<2)(assign j=j+1;):
			get(A[i,j]);
		endloop
	endloop
	loop(assign i=0;)(i<2)(assign i=i+1;):
		loop(assign j=0;)(j<2)(assign j=j+1;):
			put(A[i,j]);
			put(tab);
		endloop
		put(endl);
	endloop
end