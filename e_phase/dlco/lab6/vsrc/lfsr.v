module lsfr(
  input clk,
  input [7:0] x,
  input reset,
  
  output reg [7:0] y
);
  reg [7:0] reg0;
  
  wire next_bit;


  assign next_bit = reg0[4] ^ reg0[3] ^ reg0[2] ^ reg0[0];

  always @(posedge clk) begin
      if(reset) begin
        reg0 <= x;
      end
      else begin
        reg0 <= {next_bit, reg0[7:1]};
      end
  end


  assign y = reg0;
 
endmodule
