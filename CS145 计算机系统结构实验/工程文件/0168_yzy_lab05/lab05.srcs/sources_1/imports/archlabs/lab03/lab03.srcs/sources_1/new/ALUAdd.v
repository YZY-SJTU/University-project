`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/03/31 10:14:08
// Design Name: 
// Module Name: ALUAdd
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


module ALUAdd(
    input [31:0] input1,
    input [31:0] input2,
    input [3:0] aluCtr,
    output zero,
    output [31:0] aluRes
);
    
    reg Zero;
    reg [31:0] ALURes;
    integer tmp;
    always @(input1 or input2 or aluCtr)
    begin
        case(aluCtr)
        4'b0000: 
        begin
        Zero = 0;
        ALURes = input1 & input2;
        if(ALURes == 0)
            Zero = 1;
        else 
            Zero = 0;
        end
        4'b0001:
        begin
        Zero = 0;
        ALURes = input1 | input2;
        if(ALURes == 0)
            Zero = 1;
        else 
            Zero = 0;
        end
        4'b0010:
        begin
        Zero = 0;
        ALURes = input1 + input2;
        if(ALURes == 0)
            Zero = 1;
        else 
            Zero = 0;
        end
        4'b0110:
        begin
        Zero = 0;
        ALURes = input1 - input2;
        if(ALURes == 0)
            Zero = 1;
        else 
            Zero = 0;
        end
        4'b0111: 
        begin
        tmp = input1 - input2;
        if(tmp == 0)
            Zero = 1;
        else 
            Zero = 0;
        if(tmp < 0)
            ALURes = 1;
        else 
            ALURes = 0;
        end
        4'b1100:
        begin
        Zero = 0;
        ALURes = ~(input1 | input2);
        if(ALURes == 0)
            Zero = 1;
        else 
            Zero = 0;
        end
    endcase
end

    assign zero = Zero;
    assign aluRes = ALURes;                

endmodule
