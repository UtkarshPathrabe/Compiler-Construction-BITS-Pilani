records:
	rec student:
		int rollno;
		int marks;
	endrec
	rec student:
		bool grade;
		real marks;
	endrec
endrecords
procs:
	proc calculateInterest(int principal, int rate, int time)->(int interest, int amount):
		assign interest = principal * rate * time / 100 ;
		assign amount = principal + interest;
	endproc
	proc calculateInterest(int principal, int rate, int time)->(int interest, int amount):
		assign interest = principal * rate * time / 100 ;
		assign amount = principal + interest;
	endproc
endprocs

execute:
	rec student st1;
	int a,a;
end