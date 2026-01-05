module top(
    input [7:0] x,
    output [2:0] y,
    output y_valid,
    output [6:0] seg
);
    wire [3:0] bcd;
    assign bcd = {1'b0, y};
    encode83 ec0(x, y, y_valid);
    bcd7seg seg0(bcd, seg);
endmodule   