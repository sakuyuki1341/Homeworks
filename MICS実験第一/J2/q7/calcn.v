module calcn(cu, s, x, y, k);
	parameter	n = 4;
	input		[n-1: 0] x, y;
	input		k;
	output		cu;
	output		[n-1: 0] s;
	wire		[n: 0] result;
	wire		[n-1: 0] ny;
	assign		ny = ~y;

	assign		result = k? x + ny + 1: x + y ;
	assign		cu = result[n];
	assign		s = result[n-1: 0];
endmodule