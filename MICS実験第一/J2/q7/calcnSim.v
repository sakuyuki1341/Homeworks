module		calcnSim;
	reg		[3: 0] x1, y1;
	reg		k, a, b, c, d;
	wire	[3: 0] s;
	wire	cu;
	calcn	g1(cu, s, x1, y1, k);
	initial
		begin
			$monitor("  %b   %b   %b   %b   %b", a, b, c, d, cu, $stime);
			$display(" [3] [2] [1] [0] cu      time");
				x1 = 4'b1111; y1 = 4'b0111; k = 0;
			#50	a = s[3]; b = s[2]; c = s[1]; d = s[0];
			#50	k = 1;
			#50	a = s[3]; b = s[2]; c = s[1]; d = s[0];
			$finish;
		end
endmodule