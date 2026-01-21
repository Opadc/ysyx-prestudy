module byte2bcd(
    input [7:0] bytee,

    output [3:0] bcd0,
    output [3:0] bcd1
);
    assign bcd0 = bytee[3:0];
    assign bcd1 = bytee[7:4];
endmodule