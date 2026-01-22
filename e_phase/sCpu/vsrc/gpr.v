module gpr(
    input clk,
    input rst,

    input we,
    input [1:0] waddr,
    input [7:0] wdata,

    input [1:0] raddr1,
    input [1:0] raddr2,

    output [7:0] rdata1,
    output [7:0] rdata2

);
    reg [7:0] gprs [0:3];

    always @(posedge clk) begin
        $display("grpr[0] %x", gprs[0]);
        $display("grpr[1] %x", gprs[1]);
        $display("grpr[2] %x", gprs[2]);
        $display("grpr[3] %x", gprs[3]);
        if(~rst) begin
            gprs[0] <= 8'b0;
            gprs[1] <= 8'b0;
            gprs[2] <= 8'b0;
            gprs[3] <= 8'b0;
        end
        else begin
            if(we) begin
                gprs[waddr] <= wdata;
            end
        end
    end

    
    assign rdata1 = gprs[raddr1];
    assign rdata2 = gprs[raddr2];

endmodule