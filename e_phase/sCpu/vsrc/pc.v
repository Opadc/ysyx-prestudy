module pc(
    input clk,
    input rst,

    input load,
    input [3:0] addr,

    output [3:0] npc
);
    reg [3:0] pc_reg;
    wire [3:0] next_pc;

    assign next_pc = load ? {addr} : pc_reg + 4'b1;
    always @(posedge clk) begin
        if(~rst) begin
            pc_reg <= 0;
        end
        else begin
            pc_reg <= next_pc;
        end
    end

    assign npc = pc_reg;

endmodule