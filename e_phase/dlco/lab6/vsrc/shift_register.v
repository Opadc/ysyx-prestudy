module shift_register(
    input clk,
    input [7:0] i_data,
    input [2:0] ctrl,

    output [7:0] o_data,
    output reg o_valid
);

    reg [7:0] reg0;
    reg [7:0] next_reg0;

    reg [2:0] bit_counts;


    always @(posedge clk) begin
        // reset 
        if(ctrl == 3'b000) begin
            bit_counts <= 3'b0;
        end
        else begin
            if(bit_counts == 3'h7) 
                bit_counts <= 3'h0;
            else
                bit_counts <= bit_counts + 1; 
        end
    end

    
    always @(*) begin
        case(ctrl)
            3'b000: next_reg0 = 8'b000;     // reset     
            3'b001: next_reg0 = i_data;     // load
            3'b010: next_reg0 = { 1'b0, reg0[7:1]};  // logic right
            3'b011: next_reg0 = { reg0[6:0], 1'b0};  // logic left
            3'b100: next_reg0 = { reg0[7], reg0[7:1]}; // arch right;
            3'b101: next_reg0 = { i_data[0], reg0 [7:1]};  //
            3'b110: next_reg0 = { reg0[0], reg0[7:1] };  // rotate right
            3'b111: next_reg0 = { reg0[6:0], reg0[7] };  // rotate left
        endcase
    end

    always @(posedge clk) begin
        reg0 <= next_reg0;
    end

    assign o_data = reg0;

    always @(posedge clk) begin
        case(ctrl)
            3'b101: o_valid <= bit_counts == 3'h7;
            default: o_valid <= 1'b1;
        endcase
    end
endmodule