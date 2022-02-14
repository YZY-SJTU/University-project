`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/03/31 09:53:14
// Design Name: 
// Module Name: ALU_Ctr_tb
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


module ALU_Ctr_tb(

    );
    reg [1:0] ALUOp;
    reg [5:0] Funct;
    wire [3:0] ALUCtrOut;
    
    ALU_Ctr c0(
    .aluOp(ALUOp),
    .funct(Funct),
    .aluCtrOut(ALUCtrOut)
    );
    
initial begin
    
    {ALUOp, Funct} = 8'b00000000;
    #100;
    {ALUOp, Funct} = 8'b01000000;
    #100;
    {ALUOp, Funct} = 8'b10000000;
    #100;
    {ALUOp, Funct} = 8'b10000010; 
    #100;
    {ALUOp, Funct} = 8'b10000100;
    #100;
    {ALUOp, Funct} = 8'b10000101;
    #100;
    {ALUOp, Funct} = 8'b10001010;
    end
endmodule
