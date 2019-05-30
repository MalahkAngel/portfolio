;========================================
;== Pong Optimization - 6502 ASM - NES ==
;========================================
;== iNES Header Flags ==
;=======================
	.inesprg 1			; 16KB of PRG code
	.ineschr 1			; 8KB of CHR data
	.inesmap 0			; No bank swapping
	.inesmir 1			; BKG mirroring
	
;===========================
;== Variable Declarations ==
;===========================
	.rsset $0000		; Begin storing variable data at $0000 (zero page)
	
lowptr		.rs 1		; 16-bit math pointers
highptr		.rs 1		; Held in zero page to allow indirect indexing

gamestate	.rs 1		; $00 - Title Screen, $01 - Play Screen, $02 - Game Over
framecount	.rs 1		; Increments each time NMI occurs
delaycount	.rs 1		; Delay counter for interstitials

ballxpos	.rs 1		; Ball movement
ballxspeed	.rs 1
ballypos	.rs 1
ballyspeed	.rs 1

ballup		.rs 1		; Ball states
balldown	.rs 1
ballleft	.rs 1
ballright	.rs 1

padtop1		.rs 1		; Paddle y-boundaries
padtop2		.rs 1
padbot1		.rs 1
padbot2		.rs 1

score1		.rs 1		; Score counters
score2		.rs 1

input1		.rs 1		; Controller status
input2		.rs 1

;===========================
;== Constant Declarations ==
;===========================
STATETITLE		= $00	; Game states
STATEPLAY		= $01
STATEOVER		= $02

WALLTOP			= $20	; Playing field boundaries
WALLBOTTOM		= $D8
WALLLEFT		= $04
WALLRIGHT		= $F8

PADFRONT1		= $18	; Paddle constants
PADFRONT2		= $E6
PADFRONT3		= $DE
PADBACK1		= $10
PADBACK2		= $EE
PADSPEED		= $02

;=============================
;== Initialization Routines ==
;=============================
	.bank 0				; First bank of memory
	.org $C000			; Startup and reset routines
	
vBlankWait:				; Loop until vertical blanking interval
	BIT $2002
	BPL vBlankWait
	RTS
	
RESET:						; Routine run on power-up or reset
	SEI						; Disable IRQs
	CLD						; Disable decimal mode
	LDX #$40
	STX $4017				; Disable APU frame IRQ
	
	LDX #$FF
	TXS						; Initialize stack
	INX						; Set X to 0
	
	STX $2000				; Disable NMI
	STX $2001				; Disable rendering
	STX $4010				; Disable DMC IRQs

	;LDA #%00000001			; Enable Square 1 channel
	;STA $4015
	;LDA #%10110001			; Silence Square 1 channel
	;STA $4000
	
	;LDA #$C9				; Play a C# note
	;STA $4002
	;LDA #$00
	;STA $4003
	
	JSR vBlankWait			; Wait for PPU to warm up
	
clearMem:					; Initialize RAM
	LDA #$00
	STA $0000, x
	STA $0100, x
	STA $0300, x
	STA $0400, x
	STA $0500, x
	STA $0600, x
	STA $0700, x
	LDA #$FE
	STA $0200, x			; Initalize sprite addresses
	INX
	BNE clearMem			; RAM still has excess data
	
	JSR vBlankWait			; PPU should be ready after this
	JSR initTitleScreen		; Load and display title screen
	
;====================
;== Main Game Loop ==
;====================
mainLoop:
titleState:
	LDA gamestate			; Check game state, branch if not in title state
	CMP #STATETITLE
	BNE playState
	
	JSR waitForNMI			; Wait for NMI so logic runs during rendering
	JSR latchPlayer1		; Poll player 1 controller
	LDA input1
	AND #%00010000
	BEQ playState			; If start isn't pressed, move on
	
	JSR initGame			; If start is pressed, init play screen
	
playState:
	LDA gamestate			; Check game state, branch if not in play state
	CMP #STATEPLAY
	BNE failState
	
	JSR waitForNMI			; Wait for NMI so logic runs during rendering
	JSR latchPlayer1		; Poll player 1 controller
	JSR latchPlayer2		; Poll player 2 controller
	JSR moveBall			; Update ball position
	JSR movePaddles			; Update paddle position
	
failState:
	LDA gamestate			; Check game state, branch if not in game over state
	CMP #STATEOVER
	BNE mainLoop
	
	JSR waitForNMI			; Wait for NMI so logic runs during rendering
	JSR latchPlayer1		; Poll player 1 controller
	LDA input1
	AND #%00010000
	BEQ mainLoop			; If start isn't pressed, move on
	
	JSR initGame			; Repeat main loop
	JMP mainLoop
	
;===================
;== Update Screen ==
;===================
NMI:
pushRegisters:
	PHA					; Push previous register values onto stack
	TXA					; Done to ensure NMI doesn't corrupt other routines
	PHA
	TYA
	PHA
	
engineDelays:
	INC framecount		; Used in waitForNMI loop
	
	LDA delaycount
	CMP #$00
	BEQ spriteCheck
	DEC delaycount		; Creates delay between screens
	JMP pullRegisters
	
spriteCheck:
	LDA gamestate
	CMP #STATEPLAY
	BNE spriteDMA
	JSR updateSprites
	
spriteDMA:
	LDA #$00			; Sprite DMA
	STA $2003			; Write low byte of RAM address
	LDA #$02
	STA $4014			; Write high byte of RAM address, start transfer
	
	LDA #%00011110		; Enable sprites, background, no left-side clipping
	STA $2001
	
	LDA #$00			; Disable background scrolling
	STA $2005
	STA $2005
	
pullRegisters
	PLA					; Pull (Pop) values to restore register status
	TAY	
	PLA
	TAX
	PLA
	
	RTI
	
;============================
;== Game Logic Subroutines ==
;============================
	.include "subs.asm"
	
;===================
;== Graphics Data ==
;===================
	.bank 1
	.org $E000
	
	.include "gfx.asm"

;=======================
;== Interrupt Vectors ==
;=======================
	.org $FFFA
	.dw NMI				; Jump to NMI once per frame
	.dw RESET			; Jump to RESET on either power-up or system reset
	.dw 0				; No external interrupts
	
;========================
;== External Resources ==
;========================
	.bank 2
	.org $0000
	.incbin "sprites.chr"