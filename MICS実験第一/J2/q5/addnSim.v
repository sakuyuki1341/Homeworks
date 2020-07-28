module		addnSim;
	reg		[3: 0] x1, y1;
	reg		ci = 1, a, b, c, d;
	wire	[3: 0] s;
	wire	cu;
	addn	g1(cu, s, x1, y1, ci);
	initial
		begin
			$monitor("  %b   %b   %b   %b   %b", a, b, c, d, cu, $stime);
			$display(" [3] [2] [1] [0] cu      time");
				x1 <= 4'b1111; y1 <= 4'b0111;
			#50	a <= s[3]; b <= s[2]; c <= s[1]; d <= s[0];
			$finish;
		end
endmodule