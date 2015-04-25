execute:
	int i, j, k, l, m, n, sum;
	assign i = 3;
	assign j = 4;
	assign k = 5;
	assign l = 6;
	assign m = 2;
	assign n = 3;
	assign i = i + 1;
	assign i = i + 0;
	assign j = j - 1;
	assign k = k * 1;
	assign k = k * 0;
	assign l = l / 1;
	assign m = m % 1;
	assign n = n ** 1;
	assign sum = i + ( l - m ) ** n / j * 2;
	put(sum);
	put(endl);
end

/* Output should be 46 */