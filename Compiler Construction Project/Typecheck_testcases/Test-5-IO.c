records:
	rec student:
		int rollno;
		int marks;
		bool pass;
	endrec
endrecords

execute:
	rec student st1;
	mat<int>[2,3] a,b,c;
	mat<bool>[5] d;

	put(aaf);
	put(a);
	put(st1);
	put(a[1,1000]);
	put(st1.hello);
	put("Hello World");
end