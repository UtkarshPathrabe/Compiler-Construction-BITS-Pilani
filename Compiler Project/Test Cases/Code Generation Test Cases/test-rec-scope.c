/* Testcase 1 - operators*/

records:
	rec student:
		int rollno;
		int marks;
	endrec
endrecords

execute:
	int a;
	rec student st1;
	assign a = 5;
	put("Value of a in outer scope is ");
	put(a);
	put(endl);
	assign st1.rollno = a;
	assign st1.marks = 34;
	put(st1.rollno);
	put(tab);
	put(st1.marks);
	put(endl);
	if (a < 100):
		int a;
		assign a = 8;
		put("Value of a in inner scope is ");
		put(a);
		put(endl);
	endif
	assign a = 10;
	put(a);
	put(endl);
end