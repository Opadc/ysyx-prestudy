module mux41(
    input a, b, c, d,
    input s0, s1,
    output y
);
    MuxKey #(4, 2, 1) m0(y, {s1, s0}, {
        2'b00, a,
        2'b01, b,
        2'b10, c,
        2'b11, d
    });

endmodule

module barrel_shifter(
    input [7:0] din,
    input [2:0] shamt,
    input left,
    input arch,

    output [7:0] dout       
);
    wire zero;
    wire sign_bit;
    wire mux_00_o;
    wire mux_01_o;
    wire mux_02_o;
    wire mux_03_o;
    wire mux_04_o;
    wire mux_05_o;
    wire mux_06_o;
    wire mux_07_o;

    wire mux_10_o;
    wire mux_11_o;
    wire mux_12_o;
    wire mux_13_o;
    wire mux_14_o;
    wire mux_15_o;
    wire mux_16_o;
    wire mux_17_o;

    wire mux_20_o;
    wire mux_21_o;
    wire mux_22_o;
    wire mux_23_o;
    wire mux_24_o;
    wire mux_25_o;
    wire mux_26_o;
    wire mux_27_o;

    assign zero = 1'b0;
    assign sign_bit = arch ? din[7] : 0;

    // first layer
    //           no shift   right shift  no shift   left shift
    mux41 mux_00(din[0],    din[1],     din[0],     zero,           shamt[0], left, mux_00_o);
    mux41 mux_01(din[1],    din[2],     din[1],     din[0],         shamt[0], left, mux_01_o);
    mux41 mux_02(din[2],    din[3],     din[2],     din[1],         shamt[0], left, mux_02_o);
    mux41 mux_03(din[3],    din[4],     din[3],     din[2],         shamt[0], left, mux_03_o);
    mux41 mux_04(din[4],    din[5],     din[4],     din[3],         shamt[0], left, mux_04_o);
    mux41 mux_05(din[5],    din[6],     din[5],     din[4],         shamt[0], left, mux_05_o);
    mux41 mux_06(din[6],    din[7],     din[6],     din[5],         shamt[0], left, mux_06_o);
    mux41 mux_07(din[7],    sign_bit,   din[7],     din[6],         shamt[0], left, mux_07_o);

    // second layer
    //           no shift   right shift  no shift    left shift
    mux41 mux_10(mux_00_o,  mux_02_o,     mux_00_o,     zero,             shamt[1], left, mux_10_o);
    mux41 mux_11(mux_01_o,  mux_03_o,     mux_01_o,     zero,             shamt[1], left, mux_11_o);
    mux41 mux_12(mux_02_o,  mux_04_o,     mux_02_o,     mux_00_o,         shamt[1], left, mux_12_o);
    mux41 mux_13(mux_03_o,  mux_05_o,     mux_03_o,     mux_01_o,         shamt[1], left, mux_13_o);
    mux41 mux_14(mux_04_o,  mux_06_o,     mux_04_o,     mux_02_o,         shamt[1], left, mux_14_o);
    mux41 mux_15(mux_05_o,  mux_07_o,     mux_05_o,     mux_03_o,         shamt[1], left, mux_15_o);
    mux41 mux_16(mux_06_o,  sign_bit,     mux_06_o,     mux_04_o,         shamt[1], left, mux_16_o);
    mux41 mux_17(mux_07_o,  sign_bit,     mux_07_o,     mux_05_o,         shamt[1], left, mux_17_o);

    // three layer
    //           no shift   right shift  no shift    left shift
    mux41 mux_20(mux_10_o,  mux_14_o,     mux_10_o,     zero,             shamt[2], left, mux_20_o);
    mux41 mux_21(mux_11_o,  mux_15_o,     mux_11_o,     zero,             shamt[2], left, mux_21_o);
    mux41 mux_22(mux_12_o,  mux_16_o,     mux_12_o,     zero,             shamt[2], left, mux_22_o);
    mux41 mux_23(mux_13_o,  mux_17_o,     mux_13_o,     zero,             shamt[2], left, mux_23_o);
    mux41 mux_24(mux_14_o,  sign_bit,     mux_14_o,     mux_10_o,         shamt[2], left, mux_24_o);
    mux41 mux_25(mux_15_o,  sign_bit,     mux_15_o,     mux_11_o,         shamt[2], left, mux_25_o);
    mux41 mux_26(mux_16_o,  sign_bit,     mux_16_o,     mux_12_o,         shamt[2], left, mux_26_o);
    mux41 mux_27(mux_17_o,  sign_bit,     mux_17_o,     mux_13_o,         shamt[2], left, mux_27_o);
    assign dout = { 
                    mux_27_o,
                    mux_26_o,
                    mux_25_o,
                    mux_24_o,
                    mux_23_o,
                    mux_22_o,
                    mux_21_o,
                    mux_20_o};


endmodule