module		eqSim;
	wire	s;
	reg		x, y;
	eq		g1(s, x, y);
	initial
		begin
			$monitor(" %b %b %b", x, y, s, $stime);
			$display(" x y s      time");
				x=0; y=0;
			#50 y=1;
			#50 x=1; y=0;
			#50 y=1;
			#50 $finish;
		end
endmodule