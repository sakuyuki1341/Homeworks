module m2(b, a, ck);
	input	a, ck;
	output	b;
	wire	s1, s0, na, ns1, ns0, c1, c2, c3, c4, c5, d1, d0;
	dffn	f1(s1, d1, ck), f2(s0, d0, ck);
	assign	na = ~a, ns1 = ~s1, ns0 = ~s0;
	assign	c1 = a & ns1 & s0, c2 = na & s1, c3 = s1 & ns0, c4 = a & ns0, c5 = na & s0;
	assign	b = a & s1 & s0, d1 = c1 | c2 | c3, d0 = c4 | c5;
endmodule