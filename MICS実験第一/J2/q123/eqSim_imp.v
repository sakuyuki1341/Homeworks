module		eqSim_imp;
	wire	s;
	reg		x, y;
	eq		g1(s, x, y);
	initial
		begin
			$monitor(" %b %b %b  %b  %b", x, y, s, g1.s1, g1.s2, $stime);
			$display(" x y s s1 s2      time");
				x=0; y=0;
			#50 y=1;
			#50 x=1; y=0;
			#50 y=1;
			#50 $finish;
		end
endmodule