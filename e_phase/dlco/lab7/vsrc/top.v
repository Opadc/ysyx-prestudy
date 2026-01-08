module top(
    input   clk, in, reset,
    output reg out
);
    fsm_bin fsm_bin0(clk, in, reset, out);

endmodule   
