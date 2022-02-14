`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/04/07 11:33:06
// Design Name: 
// Module Name: Mux32bits
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


module Mux32bits(
    input [31:0] input1,
    input [31:0] input2,
    input sel,
    output [31:0] out
    );
    
assign out = sel ? input1 : input2;
endmodule
