execute:
	mat<int>[2,3] a,c;
	mat<int>[3,3] b;
	mat<bool>[5] d;
	mat<real>[3,3] mr;
	mat<char>[2,2] mchar;
	string str;
	int row, col;
	int cols;
	int var;

	strassign str = "Hello";
	matassign a = {	1,2,3;
			2,3,4};
			
	matassign b = { 3,2,1;
			6,5,4;
			9,8,7};

	matassign d = {True, True, False, True, True};

	matassign mr = {1.5, 2.5, 3.5;
			2.5, 3.5, 4.5;
			3.5, 4.5, 5.5};

	matassign mchar = {'a', 'b'; 'c', 'd'};

end