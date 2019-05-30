;=========================
;== Controller Latching ==
;=========================
latchPlayer1:
	LDA #$01
	STA $4016			; Write low byte of controller address
	LDA #$00
	STA $4016			; Write high byte of controller address,
	LDX #$08			; Initialize loop counter
	
latchLoop1:
	LDA $4016			; Read controller status
	LSR A				; Shift controller byte right
	ROL input1			; Roll controller variable left
	
	DEX					; If X = 0, all buttons read
	BNE	latchLoop1
	
	RTS
	
latchPlayer2:
	LDA #$01
	STA $4016			; Write low byte of controller address
	LDA #$00
	STA $4016			; Write high byte of controller address,
	LDX #$08			; Initialize loop counter
	
latchLoop2:
	LDA $4017			; Read controller status
	LSR A				; Shift controller byte right
	ROL input2			; Roll controller variable left
	
	DEX					; If X = 0, all buttons read
	BNE	latchLoop2
	
	RTS
	
;===================
;== Ball Routines ==
;===================
moveBall:
moveBallRight:
	LDA ballright			; Check if ball is moving right
	BEQ moveBallRightDone	; Branch if not moving right
	
	LDA ballxpos
	CLC						; Clear carry flag
	ADC ballxspeed			; Add ball x-speed to x-position
	STA ballxpos			; Update new ball position
	
	LDA ballxpos			
	CMP #WALLRIGHT			; Check if ball has hit the right wall
	BCS rightWallHit		; Adjust score and reset ball if wall hit
	
rightCollision:
	LDA ballxpos
	CMP #PADFRONT3
	BCC moveBallRightDone
	
	LDA ballxpos
	CMP #PADFRONT2
	BCS moveBallRightDone
	
	LDA ballypos
	CMP padtop2
	BCC moveBallRightDone
	
	LDA ballypos
	CMP padbot2
	BCS moveBallRightDone
	
	LDA #$00
	STA	ballright
	LDA #$01
	STA ballleft
	JMP moveBallRightDone
	
rightWallHit:	
	INC score1				; Add to player 1's score
	JSR updateScore1		; Reset playfield and update score
moveBallRightDone:

moveBallLeft:
	LDA ballleft			; Check if ball is moving left
	BEQ moveBallLeftDone	; Branch if not moving left
	
	LDA ballxpos
	SEC						; Clear carry flag
	SBC ballxspeed			; Subtract ball x-speed from x-position
	STA ballxpos			; Update new ball position
	
	LDA ballxpos			
	CMP #WALLLEFT			; Check if ball has hit left wall
	BCC leftWallHit			; Adjust score and reset ball if wall hit

leftCollision:
	LDA ballxpos
	CMP #PADFRONT1
	BCS moveBallLeftDone
	
	LDA ballxpos
	CMP #PADBACK1
	BCC moveBallLeftDone
	
	LDA ballypos
	CMP padtop1
	BCC moveBallLeftDone
	
	LDA ballypos
	CMP padbot1
	BCS moveBallLeftDone
	
	LDA #$00
	STA	ballleft
	LDA #$01
	STA ballright
	JMP moveBallLeftDone
	
leftWallHit:
	INC score2				; Add to player 2's score
	JSR updateScore2		; Reset playfield and update score
moveBallLeftDone:

moveBallUp:
	LDA ballup				; Check if ball is moving up
	BEQ moveBallUpDone		; Branch if not moving up
	
	LDA ballypos
	SEC						; Clear carry flag
	SBC ballyspeed			; Subtract ball y-speed from y-position
	STA ballypos			; Update new ball position
	
	LDA ballypos
	CMP #WALLTOP
	BCS moveBallUpDone
	
	LDA #$00				; Stop upward movement
	STA ballup
	LDA #$01				; Bounce downward
	STA balldown
moveBallUpDone:

moveBallDown:
	LDA balldown			; Check if ball is moving up
	BEQ moveBallDownDone	; Branch if not moving up
	
	LDA ballypos
	CLC						; Clear carry flag
	ADC ballyspeed			; Add ball y-speed to y-position
	STA ballypos			; Update new ball position
	
	LDA ballypos
	CMP #WALLBOTTOM
	BCC moveBallDownDone
	
	LDA #$00				; Stop downward movement
	STA balldown
	LDA #$01				; Bounce upward
	STA ballup
moveBallDownDone:

	RTS						; Done with ball processing
	
;=====================
;== Paddle Routines ==
;=====================
movePaddles:
movePaddleUp1:
	LDA input1				; Read controller state
	AND #%00001000			; Isolate "up" bit
	BEQ movePaddleUp1Done	; Branch is up is not pressed
	
	LDA padtop1	
	CMP #WALLTOP			; Check if paddle is at boundary
	BEQ movePaddleUp1Done	; Branch if paddle is at boundary
	
	LDA padtop1				; Subtract paddle speed
	SEC
	SBC #PADSPEED
	STA padtop1
	LDA padbot1
	SEC
	SBC #PADSPEED
	STA padbot1
movePaddleUp1Done:

movePaddleUp2:
	LDA input2				; Read controller state
	AND #%00001000			; Isolate "up" bit
	BEQ movePaddleUp2Done	; Branch is up is not pressed
	
	LDA padtop2
	CMP #WALLTOP			; Check if paddle is at boundary
	BEQ movePaddleUp2Done	; Branch if paddle is at boundary
	
	LDA padtop2				; Subtract paddle speed
	SEC
	SBC #PADSPEED
	STA padtop2
	LDA padbot2
	SEC
	SBC #PADSPEED
	STA padbot2
movePaddleUp2Done:

movePaddleDown1:
	LDA input1				; Read controller state
	AND #%00000100			; Isolate "down" bit
	BEQ movePaddleDown1Done	; Branch is up is not pressed
	
	LDA padbot1	
	CMP #WALLBOTTOM		; Check if paddle is at boundary
	BEQ movePaddleDown1Done	; Branch if paddle is at boundary
	
	LDA padtop1				; Add paddle speed
	CLC
	ADC #PADSPEED
	STA padtop1
	LDA padbot1
	CLC
	ADC #PADSPEED
	STA padbot1
movePaddleDown1Done:

movePaddleDown2:
	LDA input2				; Read controller state
	AND #%00000100			; Isolate "down" bit
	BEQ movePaddleDown2Done	; Branch is up is not pressed
	
	LDA padbot2	
	CMP #WALLBOTTOM			; Check if paddle is at boundary
	BEQ movePaddleDown2Done	; Branch if paddle is at boundary
	
	LDA padtop2				; Add paddle speed
	CLC
	ADC #PADSPEED
	STA padtop2
	LDA padbot2
	CLC
	ADC #PADSPEED
	STA padbot2
movePaddleDown2Done:
	RTS						; Done processing paddle movement

;===========================
;== Title Screen Routines ==
;===========================
initTitleScreen:
openPalettes:
	LDA $2002			; Read PPU to reset high/low latch
	LDA #$3F
	STA $2006			; Write high byte of $3F00
	LDA #$00
	STA $2006			; Write low byte of $3F00
	LDX #$00			; Initialize loop counter
	
copyPalettes:
	LDA paletteData, x	; Load data from $(paletteData + X)
	STA $2007			; Write to PPU at $(3F00 + X)
	INX
	CPX #$20			; If X = 32, all bytes are copied
	BNE copyPalettes
	
loadTitleBKG:
	LDA $2002			; Read PPU to reset high/low latch
	LDA #$20
	STA $2006			; Write high byte of $2000
	LDA #$00
	STA $2006			; Write low byte of $2000
	
	LDA #LOW(titleBackground)
	STA lowptr			; Write low byte of nametable address
	LDA #HIGH(titleBackground)
	STA highptr			; Write high byte of nametable address
	
	LDX #$00			; Initialize loop counters
	LDY #$00
	
titleLoopOuter:			; Nested loop to fill entire background
titleLoopInner:
	LDA [lowptr], y		; Load nametable low byte + Y
	STA $2007			; Write to PPU at $(#HIGH + Y)
	
	INY
	CPY #$00			; Loop until Y overflows
	BNE titleLoopInner
	
	INC highptr			; Increment high byte for next 256 byte chunk
	INX
	CPX #$04			; If X = 4, all background tiles copied
	BNE titleLoopOuter
	
loadTitleAttributes:
	LDA $2002			; Read PPU Status to reset high/low latch
	LDA #$23
	STA $2006			; Write high byte of $23C0
	LDA #$C0
	STA $2006			; Write low byte of $23C0
	LDX #$00			; Initialize loop counter
	
titleAttributesLoop:
	LDA titleAttribute, x	; Load data from $(titleAttribute + X)
	STA $2007				; Write to PPU
	INX
	CPX #$40				; If X = 64, all bytes copied
	BNE titleAttributesLoop
	
activateScreen:
	LDA #STATETITLE		; Boot to Title Screen
	STA gamestate
	
	LDA #%10010000		; Enable NMI, declare asset tables
	STA $2000
	LDA #%00011110		; Enable sprites, background, no left-side clipping
	STA $2001
	
	RTS					; Return to main loop
	
;==========================
;== Play Screen Routines ==
;==========================
initGame:
	LDA #$00			; Disable screen for bulk drawing
	STA $2000
	STA $2001
	
loadPlayBKG:
	LDA $2002			; Read PPU status to reset high/low latch
	LDA #$20
	STA $2006			; Write high byte of $2000
	LDA #$00
	STA $2006			; Write low byte of $2000
	
	LDA #LOW(playBackground)
	STA lowptr			; Write low byte of background address
	LDA #HIGH(playBackground)
	STA highptr			; Write high byte of background address
	
	LDX #$00
	LDY #$00
	
playLoopOuter:
playLoopInner:
	LDA [lowptr], y		; Load nametable low byte + Y
	STA $2007			; Write to PPU at $(#HIGH + Y)
	INY
	CPY #$00			; Loop until Y overflows
	BNE playLoopInner
	
	INC highptr			; Increment high byte for next 256 byte chunk
	INX
	CPX #$04			; If X = 4, all background tiles copied
	BNE playLoopOuter
	
loadPlayAttributes:
	LDA $2002			; Read PPU Status to reset high/low latch
	LDA #$23
	STA $2006			; Write high byte of $23C0
	LDA #$C0
	STA $2006			; Write low byte of $23C0
	LDX #$00			; Initialize loop counter
	
playAttributesLoop:
	LDA playAttribute, x	; Load data from $(titleAttribute + X)
	STA $2007				; Write to PPU
	INX
	CPX #$40				; If X = 64, all bytes copied
	BNE playAttributesLoop
	
initObjects:
	LDA #$01			; Start ball moving down and right
	STA balldown
	STA ballright
	LDA #$00			; Ball is not moving up or left
	STA ballup
	STA ballleft
	
	LDA #$80			; Initial ball x and y-position
	STA ballxpos
	LDA #$78
	STA ballypos
	STA padtop1			; Initial paddle boundaries
	STA padtop2
	
	LDA #$02			; Initial ball speed
	STA ballxspeed
	STA ballyspeed
				
	LDA #$90			; Initial paddle boundaries
	STA padbot1
	STA padbot2
	
	LDA #$00
	STA score1			; Initialize scores
	STA score2

initSprites:
	LDA ballypos		; Ball sprite
	STA $0200
	LDA #$75
	STA $0201
	LDA #$00
	STA $0202
	LDA ballxpos
	STA $0203
	
	LDA padtop1			; Paddle 1 top sprite
	STA $0204
	LDA #$7F
	STA	$0205
	LDA #$00
	STA $0206
	LDA #PADBACK1
	STA $0207
	
	LDA padtop1			; Paddle 1 high center sprite
	CLC
	ADC #$08
	STA $0208
	LDA #$7F
	STA	$0209
	LDA #$00
	STA $020A
	LDA #PADBACK1
	STA $020B
	
	LDA padtop1			; Paddle 1 low center sprite
	CLC
	ADC #$10
	STA $020C
	LDA #$7F
	STA	$020D
	LDA #$00
	STA $020E
	LDA #PADBACK1
	STA $020F
	
	LDA padtop1			; Paddle 1 bottom sprite
	CLC
	ADC #$18
	STA $0210
	LDA #$7F
	STA	$0211
	LDA #$00
	STA $0212
	LDA #PADBACK1
	STA $0213
	
	LDA padtop2			; Paddle 2 top sprite
	STA $0214
	LDA #$7F
	STA $0215
	LDA #$00
	STA $0216
	LDA #PADFRONT2
	STA $0217
	
	LDA padtop2			; Paddle 2 high center sprite
	CLC
	ADC #$08
	STA $0218
	LDA #$7F
	STA $0219
	LDA #$00
	STA $021A
	LDA #PADFRONT2
	STA $021B
	
	LDA padtop2			; Paddle 2 low center sprite
	CLC
	ADC #$10
	STA $021C
	LDA #$7F
	STA $021D
	LDA #$00
	STA $021E
	LDA #PADFRONT2
	STA $021F
	
	LDA padtop2			; Paddle 2 bottom sprite
	CLC
	ADC #$18
	STA $0220
	LDA #$7F
	STA $0221
	LDA #$00
	STA $0222
	LDA #PADFRONT2
	STA $0223
	
displayPlayScreen:
	LDA #STATEPLAY		; Activate Play game state
	STA gamestate
	
	LDA #%10010000		; Re-enable NMI, declare asset tables
	STA $2000
	
	RTS					; Game has finished initalizing
	
;==================
;== Update Score ==
;==================
updateScore1:
	LDA score1			; Check for a win
	CMP #$07			; If score is 7, player 1 wins
	BNE continueScore1	; Branch to game over routine
	JMP showResult
	
continueScore1:
	LDA #$00			; Disable screen to update playfield
	STA $2000
	STA $2001
	
	LDA #$01			; Re-initalize ball states
	STA balldown
	STA ballright
	LDA #$00			
	STA ballup
	STA ballleft
	
	LDA #$80			; Re-initialize ball and paddle position
	STA ballxpos
	LDA #$78
	STA ballypos
	STA padtop1
	STA padtop2
	LDA #$90
	STA padbot1
	STA padbot2
	
	LDA $2002			; Read PPU status to reset high/low latch
	LDA #$20
	STA $2006			; Write high byte of score tile
	LDA #$44
	STA $2006			; Write low byte of score tile
	LDA score1
	STA $2007			; Update score tile in nametable
	
	LDA #%10010000		; Re-enable NMI, declare asset tables
	STA $2000
	
	RTS
	
updateScore2:
	LDA score2			; Check for a win
	CMP #$07			; If score is 7, player 1 wins
	BNE continueScore2	; Branch to game over routine
	JMP showResult
	
continueScore2:
	LDA #$00			; Disable screen to update playfield
	STA $2000
	STA $2001
	
	LDA #$01			; Re-initalize ball states, reverse direction
	STA balldown
	STA ballleft
	LDA #$00			
	STA ballup
	STA ballright
	
	LDA #$80			; Re-initialize ball and paddle position
	STA ballxpos
	LDA #$78
	STA ballypos
	STA padtop1
	STA padtop2
	LDA #$90
	STA padbot1
	STA padbot2
	
	LDA $2002			; Read PPU status to reset high/low latch
	LDA #$20
	STA $2006			; Write high byte of score tile
	LDA #$5B
	STA $2006			; Write low byte of score tile
	LDA score2
	STA $2007			; Update score tile in nametable
	
	LDA #%10010000		; Re-enable NMI, declare asset tables
	STA $2000
	
	RTS
	
showResult:
	LDA #$00			; Disable screen to change background
	STA $2000
	STA $2001
	
	LDA #STATEOVER		; Change to game over state
	STA gamestate
	
clearSprites:			; Clear sprites from VRAM
	LDX #$00
	LDA #$FE
clearSpritesLoop:
	STA $0200, x
	INX
	BNE clearSpritesLoop
	
loadFailAttributes:
	LDA $2002			; Read PPU Status to reset high/low latch
	LDA #$23
	STA $2006			; Write high byte of $23C0
	LDA #$C0
	STA $2006			; Write low byte of $23C0
	LDX #$00			; Initialize loop counter
	
failAttributesLoop:
	LDA failAttribute, x	; Load data from $(titleAttribute + X)
	STA $2007				; Write to PPU
	INX
	CPX #$40				; If X = 64, all bytes copied
	BNE failAttributesLoop
	
loadFailBKG:
	LDA $2002			; Read PPU status to reset high/low latch
	LDA #$20
	STA $2006			; Write high byte of $2000
	LDA #$00
	STA $2006			; Write low byte of $2000
	
	LDA #LOW(failBackground)
	STA lowptr			; Write low byte of background address
	LDA #HIGH(failBackground)
	STA highptr			; Write high byte of background address
	
	LDX #$00
	LDY #$00
	
failLoopOuter:
failLoopInner:
	LDA [lowptr], y		; Load nametable low byte + Y
	STA $2007			; Write to PPU at $(#HIGH + Y)
	INY
	CPY #$00			; Loop until Y overflows
	BNE failLoopInner
	
	INC highptr			; Increment high byte for next 256 byte chunk
	INX
	CPX #$04			; If X = 4, all background tiles copied
	BNE failLoopOuter
	
	LDA #%10010000		; Re-enable NMI, declare asset tables
	STA $2000
	
	JMP failState
	
;====================
;== Update Sprites ==
;====================
updateSprites:
	LDA ballypos		; Ball sprite
	STA $0200
	LDA #$75
	STA $0201
	LDA #$00
	STA $0202
	LDA ballxpos
	STA $0203
	
	LDA padtop1			; Paddle 1 top sprite
	STA $0204
	LDA #$7F
	STA	$0205
	LDA #$00
	STA $0206
	LDA #PADBACK1
	STA $0207
	
	LDA padtop1			; Paddle 1 high center sprite
	CLC
	ADC #$08
	STA $0208
	LDA #$7F
	STA	$0209
	LDA #$00
	STA $020A
	LDA #PADBACK1
	STA $020B
	
	LDA padtop1			; Paddle 1 low center sprite
	CLC
	ADC #$10
	STA $020C
	LDA #$7F
	STA	$020D
	LDA #$00
	STA $020E
	LDA #PADBACK1
	STA $020F
	
	LDA padtop1			; Paddle 1 bottom sprite
	CLC
	ADC #$18
	STA $0210
	LDA #$7F
	STA	$0211
	LDA #$00
	STA $0212
	LDA #PADBACK1
	STA $0213
	
	LDA padtop2			; Paddle 2 top sprite
	STA $0214
	LDA #$7F
	STA $0215
	LDA #$00
	STA $0216
	LDA #PADFRONT2
	STA $0217
	
	LDA padtop2			; Paddle 2 high center sprite
	CLC
	ADC #$08
	STA $0218
	LDA #$7F
	STA $0219
	LDA #$00
	STA $021A
	LDA #PADFRONT2
	STA $021B
	
	LDA padtop2			; Paddle 2 low center sprite
	CLC
	ADC #$10
	STA $021C
	LDA #$7F
	STA $021D
	LDA #$00
	STA $021E
	LDA #PADFRONT2
	STA $021F
	
	LDA padtop2			; Paddle 2 bottom sprite
	CLC
	ADC #$18
	STA $0220
	LDA #$7F
	STA $0221
	LDA #$00
	STA $0222
	LDA #PADFRONT2
	STA $0223
	
	RTS
	
;===================
;== Sleep Routine ==
;===================
waitForNMI:
	LDA framecount		; Store old framecount in accumulator

waitForNMILoop:
	CMP framecount		; Check if NMI has occurred
	BEQ	waitForNMILoop	; Loop until NMI occurs
	
	RTS					; Return to main loop