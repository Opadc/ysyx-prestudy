module top(
  input [3:0] x,
  input [3:0] y,
  input sub,

  output [3:0] z,
  output carry,
  output zero,
  output overflow
);

  wire [3:0] cin;
  wire [3:0] real_y;

  assign cin =  {3'b0, sub};

  assign real_y = y ^ {4{sub}};

  assign {carry, z} = x + real_y + cin; 
  assign overflow = x[3] == real_y[3] && x[3] != z[3];
  assign zero = ~(| z);
endmodule
