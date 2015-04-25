execute:
	int len, index;
	char c;
	string s1, s2, s3;
	assign index = 3;
	strassign s1 = "Hello ";
	put("Enter your name:");
	get(s2);
	put(endl);
	strassign s3 = s1 + s2;
	put(s3);
	put(endl);
	strassign len = s1 @length;
	put(len);
	put(endl);
	strassign len = s3 @length;
	put(len);
	put(endl);
	strassign c = s1[index];
	put(c);
	put(endl);
	strassign c = s1[4];
	put(c);
	put(endl);
end
