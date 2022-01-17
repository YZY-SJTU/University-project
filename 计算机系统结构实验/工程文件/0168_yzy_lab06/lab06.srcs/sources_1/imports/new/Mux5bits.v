`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/04/07 11:33:19
// Design Name: 
// Module Name: Mux5bits
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


module Mux5bits(
    input [4:0] input1,
    input [4:0] input2,
    input sel,
    output [4:0] out
    );

assign out = sel ? input1 :input2; 
    
endmodule
