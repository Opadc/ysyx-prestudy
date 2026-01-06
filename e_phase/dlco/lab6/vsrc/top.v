module top(
    input clk,
    input [7:0] x,
    input reset,
    output [7:0] y

);
    lsfr lsfr0(clk, x, reset, y);

    // todo: show byte use bcd.    
endmodule   