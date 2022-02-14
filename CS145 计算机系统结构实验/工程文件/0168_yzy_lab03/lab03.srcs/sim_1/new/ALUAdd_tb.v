`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/03/31 10:39:14
// Design Name: 
// Module Name: ALUAdd_tb
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


module ALUAdd_tb(

    );
    wire Zero;
    wire [31:0] ALURes;
    reg [31:0] Input1;
    reg [31:0] Input2;
    reg [3:0]ALUCtr;
    
    ALUAdd c0(
    .zero(Zero),
    .aluRes(ALURes),
    .input1(Input1),
    .input2(Input2),
    .aluCtr(ALUCtr)
    );
    
initial begin

    ALUCtr = 4'b0000;
    Input1 = 0;
    Input2 = 0;
    #100;
    Input1 = 15;
    Input2 = 10;
    #100;
    ALUCtr = 4'b0001;
    #100;
    ALUCtr = 4'b0010;
    #100;
    ALUCtr = 4'b0110;
    #100;
    Input1 = 10;
    Input2 = 15;
    #100;
    Input1 = 15;
    Input2 = 10;
    ALUCtr = 4'b0111;
    #100;
    Input1 = 10;
    Input2 = 15;
    #100;
    Input1 = 1;
    Input2 = 1;
    ALUCtr = 4'b1100;
    #100;
    Input1 = 16;
end
    
endmodule
