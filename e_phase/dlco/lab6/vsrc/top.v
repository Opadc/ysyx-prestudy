module top(
    input [7:0] din,
    input [2:0] shamt,
    input left,
    input arch,

    output [7:0] dout    
);
    barrel_shifter barrel_shifter0(din, shamt, left, arch, dout);

endmodule   

module lfsr_test(
    input clk,
    input [7:0] x,
    input reset,
    output [7:0] y,
    output [6:0] seg0,
    output [6:0] seg1
);

    wire [3:0] bcd0;
    wire [3:0] bcd1;

    lsfr lsfr0(clk, x, reset, y);

    byte2bcd byte2bcd0(y, bcd0, bcd1);
    
    bcd7seg bcd7seg0(bcd0, seg0);
    bcd7seg bcd7seg1(bcd1, seg1);

endmodule   
