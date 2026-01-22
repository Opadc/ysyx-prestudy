module bcd7seg(
  input  [3:0] b,
  output reg [6:0] h
);
// detailed implementation ...
    always @(*) begin
        case(b)
            4'h0: h = 7'b0000_001;
            4'h1: h = 7'b1001_111;
            4'h2: h = 7'b0010_010; 
            4'h3: h = 7'b0000_110;
            4'h4: h = 7'b1001_100;
            4'h5: h = 7'b0100_100;
            4'h6: h = 7'b0100_000;
            4'h7: h = 7'b0001_111;
            4'h8: h = 7'b0000_000;
            4'h9: h = 7'b0000_100;
            4'hA: h = 7'b0001_000;
            4'hB: h = 7'b1100_000;
            4'hC: h = 7'b0110_001;
            4'hD: h = 7'b1000_010;
            4'hE: h = 7'b0110_000;
            4'hF: h = 7'b0111_000;
        endcase
    end

endmodule