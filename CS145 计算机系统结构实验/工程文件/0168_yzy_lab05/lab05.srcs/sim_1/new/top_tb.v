`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/04/14 08:23:38
// Design Name: 
// Module Name: top_tb
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


module top_tb(
    
    );
    reg CLK, Reset;
    always #25 CLK = !CLK;
    Top top(
        .Clk(CLK),
        .reset(Reset)
    );
    initial begin
        $readmemh("Data.txt",Top.dataMem.memFile);
        $readmemh("Instruction.txt",Top.translate.InstFile);
        
        CLK = 1;
        Reset = 1;
        #15;
        Reset = 0;
        #2000;
    end
    
endmodule
