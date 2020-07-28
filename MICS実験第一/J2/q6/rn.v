module rn(q, l, d, ck);
	parameter n = 4;
	input  [n-1: 0] d;
	input  l, ck;
	output [n-1: 0] q;
	wire   [n-1: 0] d1;
	generate
		genvar g;
		for (g = 0; g < n; g = g + 1) begin : gen
		dffn f(q[g], d1[g], ck);
		end
	endgenerate
	
	assign d1[n-1: 0] = l? d[n-1: 0]: q[n-1: 0];
endmodule
