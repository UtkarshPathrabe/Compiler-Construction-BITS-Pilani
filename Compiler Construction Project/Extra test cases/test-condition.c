execute:
	real marks;
	put("Enter marks out of 100:");
	get(marks);
	put(endl);
	if(marks >= 90.000):
		put("Grade: A");
	elif((marks < 90.000) AND (marks > 60.500)):
		put("Grade: B");
	else:
		put("Grade: C");
	endif
	put(endl);
end