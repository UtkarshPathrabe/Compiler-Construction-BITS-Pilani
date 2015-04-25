procs:
	proc calculateInterest(real principal, real rate, real time)->(real interest, real amount):
		assign interest = principal * rate * time / 100 ;
		assign amount = principal + interest;
	endproc
endprocs

execute:
	real P,R,T;
	assign P = 10000.0; 
	assign R = 7.5; 
	assign T = 4.0;

	real I, A;
	call calculateInterest(P, R, T)->(I, A);

	put("Interest :"); 
	put(I); 
	put(endl);
	put("Amount :"); 
	put(A); 
end