`define AT_SCANCODE_A	8'h1C
`define AT_SCANCODE_B	8'h32
`define AT_SCANCODE_C	8'h21
`define AT_SCANCODE_D	8'h23
`define AT_SCANCODE_E	8'h24
`define AT_SCANCODE_F	8'h2B
`define AT_SCANCODE_G	8'h34
`define AT_SCANCODE_H	8'h33
`define AT_SCANCODE_I	8'h43
`define AT_SCANCODE_J	8'h3B
`define AT_SCANCODE_K	8'h42
`define AT_SCANCODE_L	8'h4B
`define AT_SCANCODE_M	8'h3A
`define AT_SCANCODE_N	8'h31
`define AT_SCANCODE_O	8'h44
`define AT_SCANCODE_P	8'h4D
`define AT_SCANCODE_Q	8'h15
`define AT_SCANCODE_R	8'h2D
`define AT_SCANCODE_S	8'h1B
`define AT_SCANCODE_T	8'h2C
`define AT_SCANCODE_U	8'h3C
`define AT_SCANCODE_V	8'h2A
`define AT_SCANCODE_W	8'h1D
`define AT_SCANCODE_X	8'h22
`define AT_SCANCODE_Y	8'h35
`define AT_SCANCODE_Z	8'h1A
`define AT_SCANCODE_0	8'h45
`define AT_SCANCODE_1	8'h16
`define AT_SCANCODE_2	8'h1E
`define AT_SCANCODE_3	8'h26
`define AT_SCANCODE_4	8'h25
`define AT_SCANCODE_5	8'h2E
`define AT_SCANCODE_6	8'h36
`define AT_SCANCODE_7	8'h3D
`define AT_SCANCODE_8	8'h3E
`define AT_SCANCODE_9	8'h46

// 七段数码管低两位显示当前按键的键码，中间两位显示对应的ASCII码（转换可以考虑自行设计一个ROM并初始化）。只需完成字符和数字键的输入，不需要实现组合键和小键盘。
module scancode(
    input [7:0] data,
    output reg [7:0] scancode
);
    always @(*) begin
        case (data)
            `AT_SCANCODE_A: scancode = "A";
            `AT_SCANCODE_B: scancode = "B";
            `AT_SCANCODE_C: scancode = "C";
            `AT_SCANCODE_D: scancode = "D";
            `AT_SCANCODE_E: scancode = "E";
            `AT_SCANCODE_F: scancode = "F";
            `AT_SCANCODE_G: scancode = "G";
            `AT_SCANCODE_H: scancode = "H";
            `AT_SCANCODE_I: scancode = "I";
            `AT_SCANCODE_J: scancode = "J";
            `AT_SCANCODE_K: scancode = "K";
            `AT_SCANCODE_L: scancode = "L";
            `AT_SCANCODE_M: scancode = "M";
            `AT_SCANCODE_N: scancode = "N";
            `AT_SCANCODE_O: scancode = "O";
            `AT_SCANCODE_P: scancode = "P";
            `AT_SCANCODE_Q: scancode = "Q";
            `AT_SCANCODE_R: scancode = "R";
            `AT_SCANCODE_S: scancode = "S";
            `AT_SCANCODE_T: scancode = "T";
            `AT_SCANCODE_U: scancode = "U";
            `AT_SCANCODE_V: scancode = "V";
            `AT_SCANCODE_W: scancode = "W";
            `AT_SCANCODE_X: scancode = "X";
            `AT_SCANCODE_Y: scancode = "Y";
            `AT_SCANCODE_Z: scancode = "Z";
            `AT_SCANCODE_0: scancode = "0";
            `AT_SCANCODE_1: scancode = "1";
            `AT_SCANCODE_2: scancode = "2";
            `AT_SCANCODE_3: scancode = "3";
            `AT_SCANCODE_4: scancode = "4";
            `AT_SCANCODE_5: scancode = "5";
            `AT_SCANCODE_6: scancode = "6";
            `AT_SCANCODE_7: scancode = "7";
            `AT_SCANCODE_8: scancode = "8";
            `AT_SCANCODE_9: scancode = "9";
            default: scancode = 8'h00;
        endcase
    end

endmodule