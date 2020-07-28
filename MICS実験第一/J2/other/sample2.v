module		sample2(2, a, b);
	input	a, b;
	output	s;
	wire	w1, w2;
	assign	w1 = a & b;
	assign	w2 = a | b;
	assign	s = w1 & w2;
endmodule