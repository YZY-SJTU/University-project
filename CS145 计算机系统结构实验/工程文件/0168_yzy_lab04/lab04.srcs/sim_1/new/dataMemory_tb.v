`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/04/07 10:11:29
// Design Name: 
// Module Name: dataMemory_tb
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


module dataMemory_tb(

    );
    reg CLK;
    reg [31:0] Address;
    reg [31:0] WriteData;
    reg MemWrite;
    reg MemRead;
    wire [31:0] ReadData;
    
    dataMemory c0(
    .Clk(CLK),
    .address(Address),
    .writeData(WriteData),
    .memWrite(MemWrite),
    .memRead(MemRead),
    .readData(ReadData)
    );
    always #100 CLK = !CLK;
initial begin
    //initialize inputs
    CLK = 0;
    Address = 0;
    WriteData = 0;
    MemWrite = 0;
    MemRead = 0;
    //cuurent time: 185ns
    #185;
    MemWrite = 1'b1;
    Address = 7;
    WriteData = 185;
    
    #100;
    MemWrite = 1'b1;
    WriteData = 32'hffffffff;
    Address =  6;
    
    #185;
    MemRead = 1'b1;
    MemWrite = 1'b0;;
    
    #200;
    MemWrite = 1;
    Address = 8;
    WriteData = 550;
    
    #80;
    MemWrite = 0;
    MemRead = 1;

end

endmodule

