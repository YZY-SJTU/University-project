`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/04/07 10:10:43
// Design Name: 
// Module Name: dataMemory
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


module dataMemory(
    input Clk,
    input [31:0] address,
    input [31:0] writeData,
    input memWrite,
    input memRead,
    output [31:0] readData
    );
    
    reg [31:0] memFile[0:63];
    reg [31:0] ReadData;
    
    always @(memRead or address)
    begin
        if(memRead && !memWrite)
            ReadData = memFile[address >> 2];
        else 
            ReadData = 0;
    end
    
    always @(negedge Clk)
    begin
        if(memWrite)
        memFile[address >> 2] = writeData;
    end
    
assign readData = ReadData;

endmodule

