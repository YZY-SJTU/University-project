;--------------------------------------------------------------------------
;
;              Build this with the "Source" menu using
;                     "Build All" option
;
;--------------------------------------------------------------------------
;
;                           实验三程序通用框架
;
;--------------------------------------------------------------------------
; 功能： 程序框架					                            				   |
; 编写：《嵌入式系统原理与实验》课程组                   				   |
; 版本：3.5
; 修订：B
;--------------------------------------------------------------------------


		DOSSEG
		.MODEL	SMALL		; 设定8086汇编程序使用Small model
		.8086				; 设定采用8086汇编指令集

;-----------------------------------------------------------
;	定义堆栈段                                             |
;-----------------------------------------------------------
	.stack 100h				; 定义256字节容量的堆栈

;-------------------------------------------------------------------------
;	符号定义                                                              |
;-------------------------------------------------------------------------
;
;
; 8253芯片端口地址 （Port Address):
L8253T0			EQU	100H			; Timer0's port number in I/O space
L8253T1			EQU 	102H			; Timer1's port number in I/O space
L8253T2			EQU 	104H			; Timer2's port number in I/O space
L8253CS			EQU 	106H			; 8253 Control Register's port number in I/O space
;
; 8255芯片端口地址 （Port Address):
L8255PA			EQU	121H			; Port A's port number in I/O space
L8255PB			EQU 	123H			; Port B's port number in I/O space
L8255PC			EQU 	125H			; Port C's port number in I/O space
L8255CS			EQU 	127H			; 8255 Control Register's port number in I/O space
;
;  中断矢量号定义
IRQNum			EQU	0c8H			; 中断矢量号,要根据学号计算得到后更新此定义。

Patch_Protues	EQU	IN AL, 0	;	Simulation Patch for Proteus, please ignore this line

;=======================================================================
; 宏定义
;=======================================================================

; 修补Proteus仿真的BUG，参见程序段中的使用说明
    WaitForHWInt MACRO INTNum		; INTNum is the HW INT number
		MOV AL, INTNum   			;
		OUT 0,AL					;
		STI
		CLI
    ENDM



;-----------------------------------------------------------
;	定义数据段                                             |
;-----------------------------------------------------------
		.data					; 定义数据段;

DelayShort	dw	40				; 短延时参量	
DelayLong	dw	4000			; 长延时参量


; SEGTAB is the code for displaying "0-F", and some of the codes may not be correct. Find and correct the errors.
	SEGTAB  DB 3FH	; 7-Segment Tube
		DB 06H	;
		DB 5BH	;            a a a
		DB 4FH	;         f         b
		DB 66H	;         f         b
		DB 6DH	;         f         b
		DB 7DH	;            g g g 
		DB 07H	;         e         c
		DB 7FH	;         e         c
		DB 6FH	;         e         c
        	DB 77H	;            d d d     h h h
		DB 7CH	; ----------------------------------
		DB 39H	;       b7 b6 b5 b4 b3 b2 b1 b0
		DB 5EH	;       DP  g  f  e  d  c  b  a
		DB 79H	;
		DB 71H	;

;-----------------------------------------------------------
;	定义代码段                                             |
;-----------------------------------------------------------
		.code						; Code segment definition
		.startup					; Entrance of this program
;------------------------------------------------------------------------
		Patch_Protues					; Simulation Patch for Proteus,
								; Please ignore the above code line.
;------------------------------------------------------------------------

START:								; Modify the following codes accordingly
								; 
		CLI						; Disable interrupts
		MOV AX, @DATA					;
		MOV DS, AX					; Initialize DS

		CALL INIT8255					; Initialize 8255
		CALL INIT8253					; Initialize 8253
		
		MOV  BL, IRQNum					; BL is used as a parameter to call the procedure INT_INIT
		CALL INT_INIT					; Procedure INT_INIT is used to set up the IVT
		
		;software interruption
		;INT IRQNum
		;INT IRQNum
		;INT IRQNum
		;hardware interruption
		STI
		CALL DISPLAY8255
		;CLI
Display_Again:
		;CALL DISPLAY8255				; Procedure DISPLAY8255 is used to contrl 7-segment tubes
		;CALL SENDMESSAGE                                ; get the value of PC0 and send it to PC6
		; Put you code here


;===================================================================================
; Attention:
; The following codes is a Patching for Proteus 8086 Hardware Simulation Bug.
; Use these codes in the case you want the 8086 to halt and waiting for HW INT only! 
; You can treat it as if it doesn't exist. 
;
; If you need to use HW INT, please uncomment it, or
; Don't modify it, leave it here just as it is.
		WaitForHWInt IRQNum				
;====================================================================================
		JMP	Display_Again

		HLT						; 
;=====================================================================================





;--------------------------------------------
;                                           |
; INIT 8255 					            |
;                                           |
;--------------------------------------------
INIT8255 PROC

		; Init 8255 in Mode x,	L8255PA xPUT, L8255PB xPUT, L8255PCU xPUT, L8255PCL xPUT
		MOV DX, L8255CS
		;PA-OUTPUT PB-OUTPUT PCU-OUTPUT PUL-INPUT
		MOV AL, 10000001B		; Control Word
; 发送控制字到8255
		OUT DX, AL
		


		RET
INIT8255 ENDP

;get the value of PC0 and send it to PC6
SENDMESSAGE PROC
	       MOV DX, L8255PC
	       IN  AL, DX
	       AND AL, 10111111B	; 清除PC6,置为0		
	       MOV AH, AL		; Save data
	       AND AL, 00000001B	; Test bit 0
	       JZ  SEND			;判断PC0的值是否为0
	       OR  AH, 01000000B	; 置PC6为1
SEND:
	       MOV AL, AH			; Restore and Modify
	       OUT DX, AL			; 更新PC6
	       RET
SENDMESSAGE ENDP

;--------------------------------------------
;                                           |
; INIT 8253 					            |
;                                           |
;--------------------------------------------
INIT8253 PROC

; Set the mode and the initial count for Timer0
	       MOV AL,00110110B
	       MOV DX,L8253CS
	       OUT DX,AL
	       MOV AX,2710H	;时钟周期为0.000001s，2710h的十进制为10000，故时钟周期为10ms
	       MOV DX,L8253T0
	       OUT DX,AL
	       MOV AL,AH
	       OUT DX,AL

; Set the mode and the initial count for Timer1
	       MOV AL,01010110B
	       MOV DX,L8253CS
	       OUT DX,AL
	       MOV AL,64H    ;64h十进制是100，而CLK0的方波周期为10ms，则在CLK1中方波周期为1s
	       MOV DX,L8253T1
	       OUT DX,AL

; Set the mode and the initial count for Timer2


		RET
INIT8253 ENDP

;--------------------------------------------
;                                           |
; DISPLAY  STUDENTS ID				 		|
;                                           |
;--------------------------------------------

DISPLAY8255 PROC
; Put your code here
	        MOV CX,1			; Display one number at a time
	DISPLAY0:
		DEC CX				; CX--
		
		MOV DX, L8255PA		
		MOV AL, 0FEH		; 设定第一个七段管的PA值
		OUT DX, AL		
		MOV AL, SEGTAB		; 获取字模‘0’的值
		MOV DX, L8255PB		
		OUT DX, AL		

	DISPLAY1:
		JCXZ DISPLAY1	; Jump to DISPLAY1 if CX = 0
		
		DEC CX
		
		MOV DX, L8255PA		
		MOV AL, 0FDH		; 设定第二个七段管的PA值
		OUT DX, AL		
		MOV AL, SEGTAB+1	; 获取字模‘1’的值
		MOV DX, L8255PB		
		OUT DX, AL		
		OUT DX,AL
		
	DISPLAY6:
		JCXZ	DISPLAY6	; Jump to DISPLAY6 if CX = 0
		
		DEC CX
		
		MOV DX, L8255PA		
		MOV AL, 0FBH		; 设定第三个七段管的PA值
		OUT DX, AL		
		MOV AL, SEGTAB+6	; 获取字模‘6’的值
		MOV DX, L8255PB		
		OUT DX, AL	
		
	DISPLAY8:
		JCXZ DISPLAY8	; Jump to DISPLAY8 if CX = 0
		
		DEC CX
		
		MOV DX, L8255PA		
		MOV AL, 0F7H		; 设定第四个七段管的PA值
		OUT DX, AL			
		MOV AL, SEGTAB+8	; 获取字模‘8’的值
		MOV DX, L8255PB		
		OUT DX, AL
		
	DISPLAYRET:
		JCXZ	DISPLAYRET	; Jump to DISPLAYRET if CX = 0
		
		JMP	DISPLAY0
		
		RET
	
DISPLAY8255 ENDP


;--------------------------------------------------------------
;                                                             |                                                            |
; Function：DELAY FUNCTION                                    | 
; Input：None												  |
; Output: None                                                |
;--------------------------------------------------------------

DELAY 	PROC
    	PUSH CX
    	MOV CX, DelayShort
D1: 	LOOP D1
    	POP CX
    	RET
DELAY 	ENDP

;-------------------------------------------------------------
;                                                             |                                                            |
; Function：INTERRUPT Vector Table INIT						  |
; Input: BL = Interrupt number								  |
; Output: None			                                	  |
;                                                             |
;-------------------------------------------------------------	
INT_INIT	PROC FAR			; The code is not complete and you should finalize the procedure
		CLI				; Disable interrupt
		MOV AX, 0
		MOV ES, AX			; To set up the interrupt vector table
; Put your code here
		  ;终端类型号为0c8h，十进制为200（代表的矢量地址为从320h开始的4个连续存储单元）
	        MOV BX, 0320H
		MOV AX, OFFSET MYIRQ		;将中断服务程序偏移地址送中断向量表0320H和0321单元
		MOV ES:[BX], AX			;将中断服务程序MYIRQ所在段内的偏移地址送AX
		MOV AX, SEG MYIRQ		;将中断服务程序偏移地址送中断向量表0322H和0323单元
		MOV ES:[BX+2], AX 		;将中断服务程序MYIRQ所在段的段地址送AX
		
; Hint: you can use the directives such as SEGMENT,OFFSET to get the segment value and the offset of a label

	        STI
		RET				; Do not to forget to return back from a procedure		
INT_INIT	ENDP
		
		
;--------------------------------------------------------------
;                                                             |                                                            |
; FUNCTION: INTERRUPT SERVICE  Routine （ISR）				  | 
; Input::                                                     |
; Output:                                                     |
;                                                             |
;--------------------------------------------------------------	
		
MYIRQ 	PROC FAR				; The code is not complete and you should finalize the procedure
; Put your code here
	       CLI
	       PUSH AX
	       PUSH DX
	       INC CX
	       MOV DX, L8255PC
	       IN  AL, DX
	       MOV AH, AL
	       OR  AH, 10000000B  		; 置PC7为1
	       AND AL, 10000000B
	       JZ  INVERT			;判断PC7的值是否为0
	       AND AH, 01111111B		
INVERT:
	       MOV AL, AH			; Restore and Modify
	       OUT DX, AL			; 输出PC7的改变
	       
	       STI				; Do not forget to return back from a ISR
	       POP DX
	       POP AX
	       IRET
MYIRQ 	ENDP

	END