module		eq_dbSim;
	wire	s;
	reg		a, b, c, d;
	eq_db	g1(s, a, b, c, d);
	initial
		begin
			$monitor(" %b %b %b %b | %b  %b  %b", a, b, c, d, s, g1.s1, g1.s2, $stime);
			$display(" a b c d | s s1 s2      time");
				a=0; b=0; c=0; d=0;
			#50 a=0; b=0; c=0; d=1;
			#50 a=0; b=0; c=1; d=0;
			#50 a=0; b=0; c=1; d=1;
			#50 a=0; b=1; c=0; d=0;
			#50 a=0; b=1; c=0; d=1;
			#50 a=0; b=1; c=1; d=0;
			#50 a=0; b=1; c=1; d=1;
			#50 a=0; b=1; c=1; d=1;
			#50 a=0; b=1; c=1; d=1;
			#50 a=1; b=0; c=0; d=0;
			#50 a=1; b=0; c=0; d=1;
			#50 a=1; b=0; c=1; d=0;
			#50 a=1; b=0; c=1; d=1;
			#50 a=1; b=1; c=0; d=0;
			#50 a=1; b=1; c=0; d=1;
			#50 a=1; b=1; c=1; d=0;
			#50 a=1; b=1; c=1; d=1;
			#50 a=1; b=1; c=1; d=1;
			#50 a=1; b=1; c=1; d=1;
			#50 $finish;
		end
endmodule