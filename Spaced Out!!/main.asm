;==[ iNES Header Flags ]================================================================
	.inesprg 1			; Two 8KB banks of PRG code (main game code)
	.ineschr 1			; One 8KB bank of CHR data	(sprite and nametable data)
	.inesmap 0			; No external memory mappers
	.inesmir 0			; Horizontal nametable mirroring for vertical scrolling

;==[ Console Initialization Routines ]==================================================
	.include "vars.asm"
	.bank 0
	.org $C000

vBlankWait:				; Burn cycles while waiting for PPU to initialize
	BIT PPU_STATUS		; Check PPU Status register
	BPL vBlankWait		; Loop until PPU responds
.done:
	RTS
	
RESET:
	SEI          		; Disable Interrupt Requests (IRQs)
	CLD          		; Disable Decimal Mode (2A03 lacks support)
	LDX #$FF
	TXS          		; Initialize stack
	INX          		; Overflow X to $00
	STX PPU_CTRL   		; Disable Non-Maskable Interrupt (NMI)
	STX PPU_MASK  		; Disable Picture Processing Unit (PPU) rendering
	STX $4010    		; Disable Delta Modulation Channel (DMC) IRQs

startUp:
	JSR vBlankWait
.clearRAM:
	LDA #$00
	STA $0000, x
	STA $0100, x
	STA $0200, x
	STA $0400, x		; $03XX is skipped until later since it needs to be
	STA $0500, x		; initialized with a different value to prevent the
	STA $0600, x		; Object Attribute Memory (OAM) from loading garbage
	STA $0700, x
	LDA #$FE
	STA $0300, x
	INX
	BNE .clearRAM		; Loop until RAM has been initialized
	JSR vBlankWait		; Second cycle burn, PPU should be ready after this
.done:
	JSR initScreen		; Load initial graphics and activate screen
	
;==[ Main Game Loop ]===================================================================
mainLoop:
.title:
	LDA game_state
	CMP #STATE_TITLE
	BNE .play			; Move on if not in title state
	JSR waitForNMI		; Wait for NMI to occur to avoid rendering conflicts
	JSR latchInput		; Poll controller to see if player has pressed Start
	LDA controller
	AND #PAD_START
	BEQ .play			; Loop until player has pressed Start
	JSR initGame
.play:
	LDA game_state
	CMP #STATE_PLAY
	BNE .over			; Move on if not in play state
	JSR waitForNMI
	JSR getRandom
	JSR latchInput
	JSR movePlayer
	JSR activateProjectiles
	JSR activateEnemies
	JSR updateProjectiles
	JSR updateEnemies
	JSR updateScore
.over:
	LDA game_state
	CMP #STATE_OVER
	BNE .done
	JSR waitForNMI
	JSR latchInput		; Poll controller to see if player has pressed Start
	LDA controller
	AND #PAD_START
	BEQ .done			; Loop until player has pressed Start
	JSR initGame
.done:
	JMP mainLoop		; Loop until reset or shutdown
	
;==[ Non-Maskable Interrupt ]===========================================================
NMI:
	PHA					; Push current register status onto stack
	TXA	
	PHA
	TYA	
	PHA
.system:
	INC frame_num		; Tells main loop that NMI has occurred
	LDA game_state
	CMP #STATE_PLAY
	BNE .refresh
	DEC scroll_num		; Increments each frame as nametable scrolls
.swap:
	LDA scroll_num
	CMP #$00
	BNE .refresh		; Swap nametables if scroll counter has overflowed
	LDA #$EF
	STA scroll_num
	LDA nametable		; Load current nametable value
	EOR #$02			; Flip nametable bit
	STA nametable		; If nametable was 0 it's now 1, or vice versa
.refresh:
	LDA #$00
	STA OAM_ADDR
	LDA #$02			; Write sprite address and begin DMA transfer
	STA OAM_DMA			; Once DMA transfer is finished sprites will be updated
	LDA #$00
	STA PPU_ADDR
	STA PPU_ADDR
	LDA #%10000000		; Enable NMI, assets from pattern table 0
	ORA nametable		; Set correct nametable bit
	STA PPU_CTRL
	LDA #%00011110		; Enable sprites, tiles | Disable left-side clipping
	STA PPU_MASK
	LDA #$00
	STA PPU_SCROLL		; Disable horizontal scrolling
	LDA scroll_num
	STA PPU_SCROLL		; Set current vertical scrolling position
.done:
	PLA					; Pull previous register status from stack
	TAY
	PLA
	TAX
	PLA
	RTI					; Return from interrupt

	.include "subs.asm"
	
;==[ Graphics Data ]====================================================================
	.bank 1
	.org $E000
	
gameColors:
	.db $0F,$2D,$30,$3D, $0F,$0C,$23,$20, $0F,$0C,$21,$11, $0F,$04,$24,$14	; tiles
	.db $0F,$21,$24,$30, $0F,$2D,$30,$3D, $0F,$16,$27,$36, $0F,$24,$3D,$22	; sprites
playSprites:
	.db $C9,$00,$00,$7F, $C9,$01,$00,$87, $D1,$10,$00,$7F, $D1,$11,$00,$87	; player
	.db $C9,$02,$02,$7F, $D1,$12,$02,$7F, $D1,$04,$02,$7F, $D1,$05,$02,$87	; effects
	.db $00,$42,$03,$00, $00,$43,$03,$08, $08,$52,$03,$00, $08,$53,$03,$08	; enemy 1
	.db $00,$42,$03,$00, $00,$43,$03,$08, $08,$52,$03,$00, $08,$53,$03,$08	; enemy 2
	.db $00,$06,$03,$00, $00,$07,$03,$08, $08,$16,$03,$00, $08,$17,$03,$08	; enemy 3
titleTiles:
	.incbin "title.nam"
playTiles_1:
	.incbin "play_1.nam"
playTiles_2:
	.incbin "play_2.nam"
gameOverTiles:
	.incbin "over.nam"
titleAttr:
	.incbin "title.atr"
playAttr_1:
	.incbin "play_1.atr"
playAttr_2:
	.incbin "play_2.atr"
gameOverAttr:
	.incbin "over.atr"
	
;==[ Interrupt Vectors ]================================================================	
	.org $FFFA
	.dw NMI				; Non-Maskable Interrupt Vector
	.dw RESET			; Boot/Reset Intterupt Vector
	.dw 0				; No external IRQ vectors
	
;==[ External Resources ]===============================================================
	.bank 2
	.org $0000
	.incbin "sprites.chr"