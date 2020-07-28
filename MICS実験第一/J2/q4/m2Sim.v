module		m2Sim;
	reg		i;
	wire	o;
	clk		clk1(ck);
	m2		g1(o, i, ck);
	initial
		begin
			$monitor(" %b  %b  %b  %b  %b  %b", i, g1.s1, g1.s0, o, g1.d1, g1.d0, $stime);
			$display(" a s1 s0  b s1's0'     time");
				 i = 0;
			#100 i = 1;
			#100 i = 0;
			#100 i = 1;
			#100 i = 0;
			#100 i = 1;
			#100 i = 0;
			#100 i = 1;
			$finish;
		end
endmodule