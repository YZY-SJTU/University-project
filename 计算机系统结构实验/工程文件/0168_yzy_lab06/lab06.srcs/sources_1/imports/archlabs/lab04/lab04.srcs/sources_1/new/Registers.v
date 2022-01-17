`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/04/07 10:10:31
// Design Name: 
// Module Name: Registers
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


module Registers(
    input Clk,
    input [25:21] readReg1,
    input [20:16] readReg2,
    input [4:0] writeReg,
    input [31:0] writeData,
    input regWrite,
    output [31:0] readData1,
    output [31:0] readData2,
    input reset
    );
    reg [31:0] regFile[31:0];
    reg [31:0] ReadData1;
    reg [31:0] ReadData2;
    integer i;
    always @(readReg1 or readReg2 or writeReg)//read
        begin
        if(readReg1)
            ReadData1 = regFile[readReg1];
        else 
            ReadData1 = 0;
        if(readReg2)
            ReadData2 = regFile[readReg2];
        else
            ReadData2 = 0;
        end
        
    always @ (negedge Clk)//write
        begin
        if(regWrite)
            regFile[writeReg] = writeData;
        end
    always @ (reset)
        begin
        if(reset)
            for(i=0; i<32; i=i+1)
            regFile[i] = 0;
        end

assign readData1 = ReadData1;
assign readData2 = ReadData2;
    
endmodule

