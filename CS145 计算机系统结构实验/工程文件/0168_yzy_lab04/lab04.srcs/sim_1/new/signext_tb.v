`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/04/07 10:11:43
// Design Name: 
// Module Name: signext_tb
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module signext_tb(

    );
    reg [15:0] Inst;
    wire [31:0] Data;
    
    signext c0(
    .inst(Inst),
    .data(Data)
    );
    
initial begin 
    Inst = 16'h0001;
    #100;
    Inst = 16'h8000;
    #100;
    Inst = 16'hffff;
    #100;
end
endmodule

