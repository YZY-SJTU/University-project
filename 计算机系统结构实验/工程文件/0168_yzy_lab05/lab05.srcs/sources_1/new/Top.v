`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/04/07 10:30:09
// Design Name: 
// Module Name: Top
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


module Top(
    input Clk,
    input reset
    );
   
    reg [31:0] PC;
    wire [31:0] Inst;
    
    wire RegDst,Jump,Branch,MemRead,MemToReg,MemWrite;
    wire [1:0] ALUOp;
    wire ALUSrc,RegWrite;
   //main controller
    Ctr mainCtr(
        .opCode(Inst[31:26]),
        .regDst(RegDst),
        .jump(Jump),
        .branch(Branch),
        .memRead(MemRead),
        .memToReg(MemToReg),
        .aluOp(ALUOp),
        .memWrite(MemWrite),
        .aluSrc(ALUSrc),
        .regWrite(RegWrite)  
    );
   //instance to memory
   InstMemory translate(
    .address(PC),
    .instruction(Inst)
   );
   
   wire [4:0] WriteReg;
   wire [31:0] WriteData;
   wire [31:0] ReadData1;
   wire [31:0] ReadData2;
   
    //choose instance
    Mux5bits FindWriteReg(
        .input1(Inst[15:11]),
        .input2(Inst[20:16]),
        .sel(RegDst),
        .out(WriteReg)
    );
    //registers
    Registers Regs(
         .Clk(Clk),
        .readReg1(Inst[25:21]),
        .readReg2(Inst[20:16]),
        .writeReg(WriteReg),
        .writeData(WriteData),
        .regWrite(RegWrite),
        .readData1(ReadData1),
        .readData2(ReadData2),
        .reset(reset)
    );
    
    wire [31:0] ExtRes;
    wire [31:0] ALUSrc2;//mux产生的结果
    wire [31:0] ALURes;
    wire Zero;
    wire [3:0] ALUCtrOut;
    //immideate extension
    signext sext(
        .inst(Inst[15:0]),
        .data(ExtRes)
    );
    //choose input
    Mux32bits ResToALU(
        .input1(ExtRes),
        .input2(ReadData2),
        .sel(ALUSrc),
        .out(ALUSrc2)
    );
    //ALU controller
    ALU_Ctr ALU_Ctr(
    .aluCtrOut(ALUCtrOut),
    .aluOp(ALUOp),
    .funct(Inst[5:0])
    );
    
    //ALU Adder
    ALUAdd ALUAdd(
        .input1(ReadData1),
        .input2(ALUSrc2),
        .aluCtr(ALUCtrOut),
        .zero(Zero),
        .aluRes(ALURes)
    );
   
   //read data
    wire [31:0] ReadRes;
    dataMemory dataMem(
        .Clk(Clk),
        .address(ALURes),
        .writeData(ReadData2),
        .memWrite(MemWrite),
        .memRead(MemRead),
        .readData(ReadRes)
    );
    Mux32bits WriteWhich(
        .input1(ReadRes),
        .input2(ALURes),
        .sel(MemToReg),
        .out(WriteData)
    );
    
//move PC
    wire [31:0] PC_Plus_4, JumpAddress, ExtShift, BranchAdd, BranchRes, NextPC;
    assign PC_Plus_4 = PC + 4;
    assign JumpAddress = {PC_Plus_4[31:28], Inst[25:0] << 2};
    assign ExtShift = ExtRes << 2;
    assign BranchAdd = ExtShift + PC_Plus_4;
    Mux32bits branchMux(
        .input1(BranchAdd),
        .input2(PC_Plus_4),
        .sel(Branch & Zero),
        .out(BranchRes)
    );
    Mux32bits jumpMux(
        .input1(JumpAddress),
        .input2(BranchRes),
        .sel(Jump),
        .out(NextPC)
    );
    
    //change PC at down clock
    always @ (posedge Clk)
    begin
        if(reset)
            PC <= 0;
        else 
            PC <= NextPC;
    end
     
endmodule
