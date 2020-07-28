module		sample3(s, a, b);
	input	a, b;
	output	s;
	wire	w1, w2;
	sample1	m1(w1, a, b);
	sample2	m2(s, w1, w2);
	assign	w2 = a | b;
endmodule