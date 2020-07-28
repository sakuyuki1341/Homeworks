module addn(cu, s, x, y, ci);
	parameter	n = 4;
	input		[n-1: 0] x, y;
	input		ci;
	output		cu;
	output		[n-1: 0] s;
	wire		[n: 0] result;

	assign		result = x + y + ci;
	assign		s = result[n-1: 0];
	assign		cu = result[n];
endmodule