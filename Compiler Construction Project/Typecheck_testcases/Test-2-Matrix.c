execute:
	mat<int>[2,3] a,b,c;
	mat<bool>[5] d;
	mat<real>[3,3] mr;
	mat<char>[2,2] mchar;
	int row, col, var;
	bool isCol;
	real r1;
	
	matassign row = a @rows;
	matassign isCol = a @cols;

	matassign c = a + b;
	matassign c = a + mr;

	assign var = a[row,1000];
	assign r1 = mchar[1,1];
	assign var = a[isCol, 1];
	assign var = row[1,1];
	assign a[1,1] = r1;
end