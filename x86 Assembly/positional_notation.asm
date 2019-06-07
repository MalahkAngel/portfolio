; Extract digits from an integer and display the ASCII
; representations of each digit.
; Starting ASCII value = 0x30
; Starting output address = 0xE8
	JMP start

start:
	MOV D, 0x00	; Initialize loop counter to 0
.loop:
	MOV A, D	; Load current loop count into A
	DIV 0x0A	; Divide A by 10
	MOV B, A	; Store result in B
	MUL 0x0A	; Multiply A by 10
	MOV C, A	; Store result in C
	MOV A, D	; Reload loop count into A
	SUB A, C	; Subtract C from A
	ADD A, 0x30	; Add starting point for ASCII digits
	PUSH A		; Push ones digit onto stack

	MOV A, B	; Load B (loop count / 10) into A
	DIV 0x0A	; Divide A by 10
	MOV C, A	; Store new value in C
	MUL 0x0A	; Multiply A by 10
	SUB B, A	; Subtract A from B
	MOV A, B	; Store result in A
	MOV B, C	; Store new value into B
	ADD A, 0x30	; Add starting point for ASCII digits
	PUSH A		; Push tens digit onto stack

	MOV A, B	; Load B (loop count / 10) into A
	DIV 0x0A	; Divide A by 10
	MOV C, A	; Store new value in C
	MUL 0x0A	; Multiply A by 10
	SUB B, A	; Subtract A from B
	MOV A, B	; Store result in A
	MOV B, C	; Store new value into B
	ADD A, 0x30	; Add starting point for ASCII digits
	MOV [0xE8], A	; Begin writing ASCII values to console
	POP A
	MOV [0xE9], A
	POP A
	MOV [0xEA], A
	INC D
	CMP D, 0x00	; Check if loop counter has overflowed
	JNZ .loop	; Loop until counter overflowed
.done:
	HLT		; End program