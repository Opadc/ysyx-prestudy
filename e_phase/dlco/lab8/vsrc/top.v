module top(
    input           clk,     //25MHz时钟
    input           reset,    //置位

    output          hsync,    //行同步和列同步信号
    output          vsync,
    output          valid,    //消隐信号
    output [7:0]    vga_r,    //红绿蓝颜色信号
    output [7:0]    vga_g,
    output [7:0]    vga_b
    );


    reg     [23:0]   vga_data; //上层模块提供的VGA颜色数据
    reg     [9:0]    h_addr;   //提供给上层模块的当前扫描像素点坐标
    reg     [9:0]    v_addr;

    assign vga_data = 24'h00ff00;
    vga_ctrl vga_ctrl0( clk,    
                        reset,   
                        vga_data,
                        h_addr,  
                        v_addr,
                        hsync,   
                        vsync,
                        valid,   
                        vga_r,   
                        vga_g,
                        vga_b);

endmodule