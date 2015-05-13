records:
	rec student:
		int rollno;
		int marks;
		bool pass;
	endrec
endrecords

execute:
	rec student st1;
	
	assign i3 = r1 + i1;
	assign r1 = i2 + r3;

	assign result = st1.pass;
	assign r1 = st1.marks;
end