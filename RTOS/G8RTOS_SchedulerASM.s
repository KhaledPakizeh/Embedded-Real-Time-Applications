; G8RTOS_SchedulerASM.s
; Holds all ASM functions needed for the scheduler
; Note: If you have an h file, do not have a C file and an S file of the same name

	; Functions Defined
	.def G8RTOS_Start, PendSV_Handler

	; Dependencies
	.ref CurrentlyRunningThread, G8RTOS_Scheduler

	.thumb		; Set to thumb mode
	.align 2	; Align by 2 bytes (thumb mode uses allignment by 2 or 4)
	.text		; Text section

; Need to have the address defined in file 
; (label needs to be close enough to asm code to be reached with PC relative addressing)
RunningPtr: .field CurrentlyRunningThread, 32

; G8RTOS_Start
;	Sets the first thread to be the currently running thread
;	Starts the currently running thread by setting Link Register to tcb's Program Counter
G8RTOS_Start:

	.asmfunc
;	CPSID I
	LDR R0,RunningPtr ; Load into R0 the pointer to currently running TCB -> Pointer1 (Holds address  -> Pointer
	LDR R1,[R0]		; Get the Actual currently running TCB
	LDR SP,[R1]		; Place its value into the stack pointer
	POP {R4-R11}    ; Get the Register values of this stack
	POP {R0-R3}		;	Restore the scratch resigter
	POP {R12}		;
	ADD SP,SP,#4	;	 GET THE NEW LR
	POP {LR}		;	 Get the start location
	ADD SP,SP,#4	;
	CPSIE I 		;
	BX LR    		;




;-  PendSV_Handler
; - Performs a context switch in G8RTOS
; 	- Saves remaining registers into thread stack
;	- Saves current stack pointer to tcb
;	- Calls G8RTOS_Scheduler to get new tcb
;	- Set stack pointer to new stack pointer from new tcb
;	- Pops registers from thread stack


PendSV_Handler:
						; Saves R0-R3-R12 (Scratch Reigsters) , LR, PC, and PSR.
	CPSID I
	PUSH {R4-R11}
	LDR R0,RunningPtr
	LDR R1,[R0]
	STR SP,[R1]
	PUSH {LR}
	BL G8RTOS_Scheduler
	pop {LR}
	LDR R0,RunningPtr
	LDR R1,[R0]
	LDR SP, [R1]
	POP {R4-R11}
    CPSIE I
	BX LR
	.endasmfunc
	
	; end of the asm file
	.align
	.end

