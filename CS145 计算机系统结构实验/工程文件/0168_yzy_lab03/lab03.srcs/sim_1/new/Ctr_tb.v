`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/03/31 08:45:42
// Design Name: 
// Module Name: Ctr_tb
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

module Ctr_tb(
);
  reg [5:0] OpCode;
  wire RegDst;
  wire ALUSrc;
  wire MemToReg;
  wire RegWrite;
  wire MemRead;
  wire MemWrite;
  wire Branch;
  wire [1:0] ALUOp;
  wire Jump;
  
  Ctr c0(
    .opCode(OpCode),
    .regDst(RegDst),
    .aluSrc(ALUSrc),
    .memToReg(MemToReg),
    .regWrite(RegWrite),
    .memRead(MemRead),
    .memWrite(MemWrite),
    .branch(Branch),
    .aluOp(ALUOp),
    .jump(Jump)
  );  
    
initial begin
    //Initialize Inputs
    OpCode = 6'b000000;
    //wait 100 ns for global reset to finish
    #100;
    
    #100;
     OpCode = 6'b000000;//R-type
    #100;
    OpCode = 6'b000100;//beq
    #100;
    OpCode = 6'b100011;//lw
    #100;
    OpCode = 6'b101011;//sw
    #100; 
    OpCode = 6'b000010;//R-type
    
    end
endmodule
