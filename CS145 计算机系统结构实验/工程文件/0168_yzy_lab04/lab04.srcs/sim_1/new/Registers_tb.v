`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/04/07 10:11:13
// Design Name: 
// Module Name: Registers_tb
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


module Registers_tb(

    );
    reg CLK;
    reg [25:21] ReadReg1;
    reg [20:16] ReadReg2;
    reg [4:0] WriteReg;
    reg [31:0] WriteData;
    reg RegWrite;
    wire [31:0] ReadData1;
    wire [31:0] ReadData2;
    
    Registers c0(
    .Clk(CLK),
    .readReg1(ReadReg1),
    .readReg2(ReadReg2),
    .writeReg(WriteReg),
    .writeData(WriteData),
    .regWrite(RegWrite),
    .readData1(ReadData1),
    .readData2(ReadData2)
    ); 
    always #100 CLK = !CLK;
    
initial begin
    CLK = 0;
    ReadReg1 = 0;
    ReadReg2 = 0;
    RegWrite = 0;
    WriteReg = 0;
    WriteData = 0;
    
    #200;
    RegWrite = 1'b1;
    WriteReg = 5'b10000;
    WriteData = 55;
    
    #200;
    WriteReg = 5'b00001;
    WriteData = 66;
    #200;
    RegWrite = 1'b0;
    WriteReg = 5'b10100;
    WriteData = 77;
    #200;
    
    #80;
    ReadReg1 = 5'b10000;
    ReadReg2 = 5'b00001;
    
    end 
    
endmodule
