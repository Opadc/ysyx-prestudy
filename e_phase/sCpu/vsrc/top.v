module top(
    input           clk,     
    input           rst,

    output [6:0] seg0,
    output [6:0] seg1
);
    reg [3:0] npc;
    
    wire [3:0] jmp_addr;
    wire jmp;

    wire inst_bner0;
    wire inst_add;
    wire inst_li;
    wire inst_out;
    wire [3:0] imm;

    wire we;
    wire [1:0] waddr;
    wire [7:0] wdata;

    wire [1:0] raddr1;
    wire [1:0] raddr2;
    wire [7:0] rdata1;
    wire [7:0] rdata2;

    wire [7:0] inst;


    assign inst_bner0 = inst[7:6] == 2'b11;
    assign inst_add = inst[7:6] == 2'b00;
    assign inst_li = inst[7:6] == 2'b10;
    assign inst_out = inst[7:6] == 2'b01;

    assign imm = inst[3:0];
    assign raddr1 = inst_bner0 ? 2'b0 : inst[3:2];
    assign raddr2 = inst[1:0];
    assign waddr = inst[5:4];
    assign we = inst_add || inst_li;
    
    assign wdata = inst_add ? rdata1 + rdata2 : {4'b0, imm};

    assign jmp = inst_bner0 && rdata1 != rdata2;
    assign jmp_addr = inst[5:2];

    pc pc0(clk, rst, jmp, jmp_addr, npc);
    rom rom0(npc, inst);
    gpr grp0(clk, rst, we, waddr, wdata, raddr1, raddr2, rdata1, rdata2);

    wire [3:0] bcd0;
    wire [3:0] bcd1;
    reg  [7:0] out_data;

    always @(posedge clk) begin
        if(inst_out)
            out_data <= rdata1;
    end

    byte2bcd byte2bcd0(out_data, bcd0, bcd1);
    bcd7seg  bcd7seg0(bcd0, seg0);
    bcd7seg  bcd7seg1(bcd1, seg1);
endmodule

 