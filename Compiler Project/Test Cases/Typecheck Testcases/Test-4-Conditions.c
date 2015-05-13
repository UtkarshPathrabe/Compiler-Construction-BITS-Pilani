execute:
	bool marks;
	real marks2;
	char mrk;
	get(marks);

	if(marks <= 9):
		put("Grade: A");
	elif( (marks2 < 90) AND (marks2 >= 70.2) ):
		put("Grade: B");
	else:
		put("Grade: C");
	endif
	put(endl);
end