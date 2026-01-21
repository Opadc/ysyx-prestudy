

module top(
    input clk,clrn,ps2_clk,ps2_data,

    output reg ready,
    output reg overflow,     // fifo overflow
    output sampling,
    output [6:0] seg0,
    output [6:0] seg1,
    output [6:0] seg2,
    output [6:0] seg3,
    output [6:0] seg4,
    output [6:0] seg5
);
    //       ready       auto 
    // wait  --- > read ---> notify --- wait
    reg [7:0] buffer [0:2];
    reg [7:0] data;
    wire nextdata_n;
    wire [3:0] bcd0;
    wire [3:0] bcd1;
    wire [3:0] bcd2;
    wire [3:0] bcd3;
    wire [3:0] bcd4;
    wire [3:0] bcd5;

    reg [7:0]  last_key;
    reg [7:0]  counts;
    
    reg [7:0]  scancode_data;
    scancode scancode0(data, scancode_data);

    wire counts_add;
    assign counts_add = ~nextdata_n && ready;

    always @(posedge clk) begin
        if(~clrn) begin
            counts <= 8'd0;
            last_key <= 8'd0;
        end
        else if(counts_add) begin
            $display("data >>> %x", data);
            if(data == 8'hf0)
                counts <= counts;
            else
                counts <= counts + ((buffer[0] != data) ? 8'd1 : 8'd0);
        end
    end



    ps2_keyboard ps2_keyboard0(clk,clrn,ps2_clk,ps2_data,data,ready,nextdata_n,overflow,sampling);

    //  t1   t2   t3           t4
    // ready read nextdata_n  read 
    kbd_reader kbd_reader0 (clk, clrn, data, ready, nextdata_n);


    byte2bcd byte2bcd0(buffer[0], bcd0, bcd1);
    byte2bcd byte2bcd1(scancode_data, bcd2, bcd3);
    byte2bcd byte2bcd2(counts, bcd4, bcd5);
    bcd7seg bcd7seg0(bcd0, seg0);
    bcd7seg bcd7seg1(bcd1, seg1);
    bcd7seg bcd7seg2(bcd2, seg2);
    bcd7seg bcd7seg3(bcd3, seg3);
    bcd7seg bcd7seg4(bcd4, seg4);
    bcd7seg bcd7seg5(bcd5, seg5);

    always @(posedge clk) begin

        if(~clrn) begin
            buffer[0] <= 8'b0;
            buffer[1] <= 8'b0;
            buffer[2] <= 8'b0;
        end
        else if(~nextdata_n && ready) begin
        $display("begin >>> ");
        $display("buffer[0] %x", buffer[0]);
        $display("buffer[1] %x", buffer[1]);
        $display("buffer[2] %x", buffer[2]);
        $display("end >>>");
            buffer[2] <= buffer[1];
            buffer[1] <= buffer[0];
            buffer[0] <= data;
        end
    end

endmodule   

module kbd_reader(
    input clk,
    input clrn,
    input [7:0] data,
    input ready,
    output next_data_n

);
    reg [1:0] state;
    reg [1:0] next_state;
    parameter WAIT = 0, READ = 1, NOTIFY = 2;

    always @(*) begin
        case(state)
            WAIT: next_state = ready ? READ : WAIT;
            READ: next_state = NOTIFY;
            NOTIFY: next_state = ready ? READ : WAIT;
            default:
                next_state = WAIT;
        endcase
    end

    always @(posedge clk) begin
        if(~clrn)
            state <= WAIT;
        else
            state <= next_state;
    end

    assign next_data_n = state == NOTIFY ? 0 : 1;

endmodule   
