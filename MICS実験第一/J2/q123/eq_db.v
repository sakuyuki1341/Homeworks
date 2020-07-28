module		eq_db(s, a, b, c, d); /* a=b && c=d 検出回路 */
	input	a, b, c, d;
	output	s;
	wire	s1, s2;
	eq		e1(s1, a, b);
	eq		e2(s2, c, d);
	assign	s = s1 & s2;
endmodule