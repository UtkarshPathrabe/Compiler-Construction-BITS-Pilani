/* 
Typecheck Test-1:
	Expression and record typecheck.
*/

records:
	rec student:
		int rollno;
		int marks;
		bool pass;
	endrec
	rec teacher:
		int id;
		real salary;
	endrec
endrecords

execute:
	rec student st1;
	rec teacher t1;
	int i1, i2, i3;
	real r1, r2, r3;
	bool result;

	assign i3 = r1+i1 + 100.0;
	assign r1 = i2+r3 + 100.0;
	assign k = 1;

	assign r1 = r1.marks;
	assign i1 = st1.pass;
	assign i2 = st1.hello;
	assign st1.rollno = 5.0;
	assign t1.id = st1.rollno;
end