`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/04/07 11:41:25
// Design Name: 
// Module Name: InstMemory
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


module InstMemory(
    input [31:0] address,
    output [31:0] instruction
    );
    reg [31:0] InstFile[0:31];
    reg [31:0] Instruction;
    always @ (address)
    begin
        Instruction = InstFile[address >> 2];
    end
    assign  instruction = Instruction;
endmodule
