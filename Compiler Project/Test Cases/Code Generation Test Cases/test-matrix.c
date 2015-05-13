execute:
	mat<int>[2,3] a,b,c;
	mat<bool>[5] d;
	mat<real>[3,3] mr;
	mat<char>[2,2] mchar;
	int row, col;
	int i, j;
	char z;
	real x;
	bool y;
	matassign a = {	1,2,3;
					2,3,4};
	matassign b = { 3,2,1;
					6,5,4};
	matassign d = {True, True, False, True, True};
	matassign mr = {1.5, 2.5, 3.5;
					2.5, 3.5, 4.5;
					3.5, 4.5, 5.5};
	matassign mchar = {'a', 'b'; 'c', 'd'};
	matassign row = mr @rows;
	matassign col = mr @cols;
	matassign c = a + b;
	loop(assign i=0;)(i<2)(assign i=i+1;):
		loop(assign j=0;)(j<3)(assign j=j+1;):
			put(c[i,j]);
			put(tab);
		endloop
		put(endl);
	endloop
	assign y = d[2];
	assign z = mchar[0,1];
	assign mchar[1,1] = z;
	put(mchar[1,1]);
end