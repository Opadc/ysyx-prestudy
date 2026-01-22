module rom(
    input [3:0] pc,
    output [7:0] inst
);
    reg [7:0] rom [15:0];

    initial begin
        $readmemb("vsrc/sCpu.inst", rom);
    end

    assign inst = rom[pc];
endmodule



