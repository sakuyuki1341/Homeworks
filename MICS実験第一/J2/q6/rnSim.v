module rnSim;
	reg  l, d1, d2, d3, d4;
	reg  [3: 0] d;
	wire [3: 0] q;
	clk clk1(ck);
	rn  rn(q[3: 0], l, d[3: 0], ck);

	initial
		begin
			$monitor("  %b   %b   %b   %b", d1, d2, d3, d4, $stime);
			$display(" [3] [2] [1] [0]      time");
				 d = 4'b1111; d1 = q[3]; d2 = q[2]; d3 = q[1]; d4 = q[0]; l = 1;
			#100 d = 4'b1111; d1 = q[3]; d2 = q[2]; d3 = q[1]; d4 = q[0]; l = 1;
			#100 d = 4'b0000; d1 = q[3]; d2 = q[2]; d3 = q[1]; d4 = q[0]; l = 1;
			#100 d = 4'b0000; d1 = q[3]; d2 = q[2]; d3 = q[1]; d4 = q[0]; l = 0;
			#100 d = 4'b1111; d1 = q[3]; d2 = q[2]; d3 = q[1]; d4 = q[0]; l = 0;
			#100 d = 4'b1111; d1 = q[3]; d2 = q[2]; d3 = q[1]; d4 = q[0]; l = 0;
			#100 d = 4'b1111; d1 = q[3]; d2 = q[2]; d3 = q[1]; d4 = q[0]; l = 0;
			$finish;
		end
endmodule
