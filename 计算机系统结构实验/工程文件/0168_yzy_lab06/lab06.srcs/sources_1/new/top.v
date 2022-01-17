`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/04/21 08:08:29
// Design Name: 
// Module Name: top
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


module top(
    input Clk,
    input reset
    );
    
    //Additional Registers
    //IF/ID
    reg [31:0] IFID_PC_Plus_4, IFID_Inst;
    wire [4:0] IFID_Inst_high = IFID_Inst[25:21];
    wire [4:0] IFID_Inst_mid = IFID_Inst[20:16];
    wire [4:0] IFID_Inst_low = IFID_Inst[15:11];
    wire Jump;
    wire Branch;
    //ID/EX
    reg [31:0] IDEX_ReadData1, IDEX_ReadData2,IDEX_ExtRes;
    reg [4:0] IDEX_Inst_high, IDEX_Inst_mid, IDEX_Inst_low;
    reg [8:0] IDEX_Ctrl;//9位控制信号
    wire IDEX_RegDst = IDEX_Ctrl[8];
    wire [1:0] IDEX_ALUOp = IDEX_Ctrl[7:6];
    wire IDEX_ALUSrc = IDEX_Ctrl[5];
    wire IDEX_Branch = IDEX_Ctrl[4],IDEX_MemRead = IDEX_Ctrl[3],
         IDEX_MemWrite = IDEX_Ctrl[2], IDEX_RegWrite = IDEX_Ctrl[1],
          IDEX_MemToReg = IDEX_Ctrl[0];
    //EX/MEM
    reg [31:0] EXMEM_ALURes, EXMEM_WriteData;
    reg [4:0] EXMEM_DstReg;
    reg [4:0] EXMEM_Ctrl;
    reg EXMEM_Zero;
    wire EXMEM_Branch = EXMEM_Ctrl[4], EXMEM_MemRead = EXMEM_Ctrl[3], EXMEM_MemWrite = EXMEM_Ctrl[2];
    wire EXMEM_RegWrite = EXMEM_Ctrl[1], EXMEM_MemToReg = EXMEM_Ctrl[0];
    //MEM/WB
    reg [31:0] MEMWB_ReadData, MEMWB_ALURes;
    reg [4:0] MEMWB_DstReg;
    reg [1:0] MEMWB_Ctrl;
    wire MEMWB_RegWrite = MEMWB_Ctrl[1], MEMWB_MemToReg = MEMWB_Ctrl[0];
    
    //STALL检测
    wire STALL = IDEX_MemRead & (IDEX_Inst_mid == IFID_Inst_high | IDEX_Inst_mid == IFID_Inst_mid);
    //IF completment
    reg [31:0] PC;
    wire [31:0] PC_Plus_4, BranchAdd, JumpAdd, NextPC, IF_Inst, BranchRes;
    assign PC_Plus_4 = PC + 4;
    Mux32bits branchMux(
        .input1(BranchAdd),
        .input2(PC_Plus_4),
        .sel(Branch),
        .out(BranchRes)
    );
    Mux32bits jumpMux(
        .input1(JumpAdd),
        .input2(BranchRes),
        .sel(Jump),
        .out(NextPC)
    );
    InstMemory translate(
        .address(PC),
        .instruction(IF_Inst)
    );
    
    always @ (posedge Clk)
    begin
        if(!STALL)//STALL时停顿，在这个时钟下降沿不写入寄存器
        begin
            IFID_PC_Plus_4 = PC_Plus_4;
            IFID_Inst <= IF_Inst;
            PC <= NextPC;
        end
        if(Branch | Jump)
            IFID_Inst <= 0; //转移错误，flush清除在执行的指令
    end
   
    //ID completment
    wire [9:0] Ctr_Out;    
     Ctr mainCtr(
        .opCode(IFID_Inst[31:26]),
        .regDst(Ctr_Out[8]),
        .branch(Ctr_Out[4]),
        .memRead(Ctr_Out[3]),
        .memToReg(Ctr_Out[0]),
        .aluOp(Ctr_Out[7:6]),
        .memWrite(Ctr_Out[2]),
        .aluSrc(Ctr_Out[5]),
        .regWrite(Ctr_Out[1]),
        .jump(Ctr_Out[9])  
    );
    
    wire [31:0] ReadData1, ReadData2, WriteData;
     Registers Regs(
         .Clk(Clk),
        .readReg1(IFID_Inst_high),
        .readReg2(IFID_Inst_mid),
        .writeReg(MEMWB_DstReg),
        .writeData(WriteData),
        .regWrite(MEMWB_RegWrite),
        .readData1(ReadData1),
        .readData2(ReadData2),
        .reset(reset)
    );
    wire [31:0] ExtRes;
    signext sext(
        .inst(IFID_Inst[15:0]),
        .data(ExtRes)
    );
    assign BranchAdd = (ExtRes << 2) + IFID_PC_Plus_4;
    assign JumpAdd = {IFID_PC_Plus_4[31:28], IFID_Inst[25:0] << 2};
    assign Jump = Ctr_Out[9];
    assign Branch = (ReadData1 == ReadData2) & Ctr_Out[4];//提前判断是否branch跳转
    
   
    
    always @ (posedge Clk)
    begin
        //IDEX_Ctrl <= STALL ? 0:Ctr_Out;
        IDEX_Ctrl <= Ctr_Out;
        IDEX_ReadData1 <= ReadData1;
        IDEX_ReadData2 <= ReadData2;
        IDEX_ExtRes <= ExtRes;
        IDEX_Inst_high <= IFID_Inst_high;
        IDEX_Inst_mid <= IFID_Inst_mid;
        IDEX_Inst_low <= IFID_Inst_low;
    end
    
//    //Forward 四种情况
    wire Forward_EX1 = EXMEM_RegWrite & EXMEM_DstReg != 0 & EXMEM_DstReg == IDEX_Inst_high;
    wire Forward_EX2 =  EXMEM_RegWrite & EXMEM_DstReg != 0 & EXMEM_DstReg == IDEX_Inst_mid;
    wire Forward_MEM1 = MEMWB_RegWrite & MEMWB_DstReg != 0 & !(EXMEM_RegWrite & EXMEM_DstReg != 0 & MEMWB_DstReg != IDEX_Inst_high) & MEMWB_DstReg == IDEX_Inst_high; 
    wire Forward_MEM2 = MEMWB_RegWrite & MEMWB_DstReg != 0 & (!(EXMEM_RegWrite & EXMEM_DstReg != 0 & MEMWB_DstReg != IDEX_Inst_mid)) & MEMWB_DstReg == IDEX_Inst_mid; 
    //EX completment
    wire [4:0] Dst_Reg; 
    wire [3:0] ALUCtrOut;
    wire [31:0] ALURes;
    wire Zero;
    
    wire [31:0] ALUSrc1 = Forward_EX1 ? EXMEM_ALURes : Forward_MEM1 ? WriteData : IDEX_ReadData1;
    wire [31:0] ALUSrc2 = IDEX_ALUSrc ? IDEX_ExtRes : Forward_EX2 ? EXMEM_ALURes : Forward_MEM2 ? WriteData : IDEX_ReadData2;
    wire [31:0] MemWriteData = Forward_EX2 ? EXMEM_ALURes : Forward_MEM2 ? WriteData : IDEX_ReadData2;

    Mux5bits FindWriteReg(
        .input1(IDEX_Inst_low),
        .input2(IDEX_Inst_mid),
        .sel(IDEX_RegDst),
        .out(Dst_Reg)
    );
    
    ALU_Ctr ALU_Ctr(
    .aluCtrOut(ALUCtrOut),
    .aluOp(IDEX_ALUOp),
    .funct(IDEX_ExtRes[5:0])
    );
   
     ALUAdd ALUAdd(
        .input1(ALUSrc1),
        .input2(ALUSrc2),
        .aluCtr(ALUCtrOut),
        .zero(Zero),
        .aluRes(ALURes)
    );
    
    always @ (posedge Clk)
    begin
        EXMEM_ALURes <= ALURes;
        EXMEM_WriteData <= MemWriteData;
        EXMEM_DstReg <= Dst_Reg;
        EXMEM_Ctrl <= IDEX_Ctrl[4:0];
        EXMEM_Zero <= Zero;
    end
    
    //MEM completment
    wire [31:0] ReadRes;
    dataMemory dataMem(
        .Clk(Clk),
        .address(EXMEM_ALURes),
        .writeData(EXMEM_WriteData),
        .memWrite(EXMEM_MemWrite),
        .memRead(EXMEM_MemRead),
        .readData(ReadRes)
    );
    always @ (posedge Clk)
    begin
        MEMWB_ReadData <= ReadRes;
        MEMWB_ALURes <= EXMEM_ALURes;
        MEMWB_DstReg <= EXMEM_DstReg;
        MEMWB_Ctrl <= EXMEM_Ctrl[1:0];
    end    
    
    //WB completment
    Mux32bits WriteWhich(
        .input1(MEMWB_ReadData),
        .input2(MEMWB_ALURes),
        .sel(MEMWB_MemToReg),
        .out(WriteData)
    );
    
    always @ (reset)
    begin
        PC = 0;
        IFID_PC_Plus_4 = 0;
        IFID_Inst = 0;
        IDEX_ReadData1 = 0;
        IDEX_ReadData2 = 0;
        IDEX_ExtRes = 0;
        IDEX_Inst_high = 0;
        IDEX_Inst_mid = 0;
        IDEX_Inst_low = 0;
        IDEX_Ctrl = 0;
        EXMEM_ALURes = 0;
        EXMEM_WriteData = 0;
        EXMEM_DstReg = 0;
        EXMEM_Ctrl = 0;
        EXMEM_Zero = 0;
        MEMWB_ReadData = 0;
        MEMWB_ALURes = 0;
        MEMWB_DstReg = 0;
        MEMWB_Ctrl = 0;
    end
    
endmodule

