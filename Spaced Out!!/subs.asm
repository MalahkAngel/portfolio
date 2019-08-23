;==[ System Subroutines ]===============================================================
;==[ latchInput ]== Polls controller port and checks for player input ==================
latchInput:
	LDA #$01
	STA $4016
	LDA #$00
	STA $4016				; Tell input register that controller is being accessed
	LDX #$08				; Initialize loop counter
.loop:
	LDA $4016				; Read controller status
	LSR A					; Shift controller byte right
	ROL controller			; Roll controller byte left into polling variable
	DEX						; If X = $00, all buttons have been read
	BNE .loop				; Else, loop until controller has been fully read
.done:
	RTS						; Return to main loop
	
;==[ getRandom ]== Use frame counter to produce a psuedo random number =================
getRandom:
	LDX #$08
	LDA seed+0
.shiftHigh:
	ASL A
	ROL seed+1
	BCC .shiftLow
	EOR #$2D
.shiftLow:
	DEX
	BNE .shiftHigh
	STA seed+0
	CMP #$00
.done:
	LDA seed+0
	STA rng_value
	RTS

;==[ Graphical Subroutines ]============================================================
;==[ initScreen ]== Loads initial graphics and activates title screen ==================
initScreen:
	LDA #$00	
	STA PPU_CTRL	
	STA PPU_MASK			; Clear screen for bulk rendering
.clearSprites:				; Clear sprites from VRAM
	LDX #$00
	LDA #$FE
.clearSpritesLoop:
	STA $0200, x
	INX
	BNE .clearSpritesLoop
loadTitleColors:
	LDA PPU_STATUS			; Read PPU status to reset latch
	LDA #$3F
	STA PPU_ADDR
	LDA #$00
	STA PPU_ADDR			; Tell PPU to write values to $3F00
	LDX #$00				; Initialize loop counter
.loop:
	LDA gameColors, x		; Load current palette byte
	STA PPU_DATA			; Store at $3FXX
	INX
	CPX #$20				; If X = $20, all bytes copied
	BNE .loop				; Else, loop until X = $20
loadTitleTiles:
	LDA PPU_STATUS			; Read PPU status to reset latch
	LDA #$20
	STA PPU_ADDR
	LDA	#$00				; Tell PPU to write values to $2000
	STA PPU_ADDR
	LDA #LOW(titleTiles)
	STA lowPtr
	LDA #HIGH(titleTiles)
	STA highPtr				; Pull nametable address
	LDX #$00				; Initialize nested loop counters
	LDY #$00
.outerLoop:
.innerLoop:
	LDA [lowPtr], y			; Load low byte address + Y	
	STA PPU_DATA
	INY
	CPY #$00				; If Y has overflowed, move to outer loop
	BNE .innerLoop			; Else, loop until Y overflows
	INC highPtr				; Increment high byte address
	INX
	CPX #$04				; If X = $04, nametable has been copied
	BNE .outerLoop			; Else, loop until X = $04
loadTitleAttributes:
	LDA PPU_STATUS			; Read PPU status to reset latch
	LDA #$23
	STA PPU_ADDR
	LDA #$C0
	STA PPU_ADDR			; Tell PPU to write values to $23C0
	LDX #$00				; Initialize loop counter
.loop:
	LDA titleAttr, x		; Load attribute data
	STA PPU_DATA
	INX		
	CPX #$40				; If X = $40, all attribute bytes copied
	BNE .loop				; Else, loop until X = $40
activateTitleScreen:
	LDA #STATE_TITLE		; Boot to Title Screen	
	STA game_state
	LDA #$40				; Initialize RNG seed variable
	STA seed
	LDA #$00				; Initialize RNG seed variable
	STA seed+1
	LDA #%10000000			; Enable NMI, pull sprites and tiles from Pattern Table 0
	STA PPU_CTRL
	LDA #%00011110			; Enable sprites, tiles | Disable left-side clipping
	STA PPU_MASK
.done:
	RTS						; Return to main loop
	
;==[ initGameOver ]== Ends game and reinitializes screen =====================
initGameOver:
	LDA #$00	
	STA PPU_CTRL	
	STA PPU_MASK			; Clear screen for bulk rendering
.clearSprites:				; Clear sprites from VRAM
	LDX #$00
	LDA #$FE
.clearSpritesLoop:
	STA $0200, x
	INX
	CPX #$56
	BNE .clearSpritesLoop
loadGameOverTiles:
	LDA PPU_STATUS			; Read PPU status to reset latch
	LDA #$20
	STA PPU_ADDR
	LDA	#$00				; Tell PPU to write values to $2000
	STA PPU_ADDR
	LDA #LOW(gameOverTiles)
	STA lowPtr
	LDA #HIGH(gameOverTiles)
	STA highPtr				; Pull nametable address
	LDX #$00				; Initialize nested loop counters
	LDY #$00
.outerLoop:
.innerLoop:
	LDA [lowPtr], y			; Load low byte address + Y	
	STA PPU_DATA
	INY
	CPY #$00				; If Y has overflowed, move to outer loop
	BNE .innerLoop			; Else, loop until Y overflows
	INC highPtr				; Increment high byte address
	INX
	CPX #$04				; If X = $04, nametable has been copied
	BNE .outerLoop			; Else, loop until X = $04
loadGameOverAttributes:
	LDA PPU_STATUS			; Read PPU status to reset latch
	LDA #$23
	STA PPU_ADDR
	LDA #$C0
	STA PPU_ADDR			; Tell PPU to write values to $23C0
	LDX #$00				; Initialize loop counter
.loop:
	LDA gameOverAttr, x		; Load attribute data
	STA PPU_DATA
	INX		
	CPX #$40				; If X = $40, all attribute bytes copied
	BNE .loop				; Else, loop until X = $40
activateGameOverScreen:
	LDA #$00
	STA scroll_num
	STA nametable
	LDA #STATE_OVER
	STA game_state
	LDA #%10000000			; Enable NMI, pull sprites and tiles from Pattern Table 0
	STA PPU_CTRL
.done:
	RTS						; Return to main loop
	
;==[ Game Logic Subroutines ]===========================================================
;==[ initGame ]== Load initial game graphics and object parameters =====================
initGame:
	LDA #$00	
	STA PPU_CTRL	
	STA PPU_MASK			; Clear screen for bulk rendering
loadPlaySprites:
	LDX #$00
.loop:
	LDA playSprites, x
	STA SPRITE_PLAYER, x
	INX
	CPX #$1B
	BNE .loop
loadPlayTiles_1:
	LDA PPU_STATUS			; Read PPU status to reset latch
	LDA #$20
	STA PPU_ADDR
	LDA	#$00				; Tell PPU to write values to $2000
	STA PPU_ADDR
	LDA #LOW(playTiles_1)
	STA lowPtr
	LDA #HIGH(playTiles_1)
	STA highPtr				; Pull nametable address
	LDX #$00				; Initialize nested loop counters
	LDY #$00
.outerLoop:
.innerLoop:
	LDA [lowPtr], y			; Load low byte address + Y	
	STA PPU_DATA
	INY
	CPY #$00				; If Y has overflowed, move to outer loop
	BNE .innerLoop			; Else, loop until Y overflows
	INC highPtr				; Increment high byte address
	INX
	CPX #$04				; If X = $04, nametable has been copied
	BNE .outerLoop			; Else, loop until X = $04
loadPlayAttributes_1:
	LDA PPU_STATUS			; Read PPU status to reset latch
	LDA #$23
	STA PPU_ADDR
	LDA #$C0
	STA PPU_ADDR			; Tell PPU to write values to $23C0
	LDX #$00				; Initialize loop counter
.loop:
	LDA playAttr_1, x		; Load attribute data
	STA PPU_DATA
	INX
	CPX #$40				; If X = $40, all attribute bytes copied
	BNE .loop
loadPlayTiles_2:
	LDA PPU_STATUS			; Read PPU status to reset latch
	LDA #$28
	STA PPU_ADDR
	LDA	#$00				; Tell PPU to write values to $2000
	STA PPU_ADDR
	LDA #LOW(playTiles_2)
	STA lowPtr
	LDA #HIGH(playTiles_2)
	STA highPtr				; Pull nametable address
	LDX #$00				; Initialize nested loop counters
	LDY #$00
.outerLoop:
.innerLoop:
	LDA [lowPtr], y			; Load low byte address + Y	
	STA PPU_DATA
	INY
	CPY #$00				; If Y has overflowed, move to outer loop
	BNE .innerLoop			; Else, loop until Y overflows
	INC highPtr				; Increment high byte address
	INX
	CPX #$04				; If X = $04, nametable has been copied
	BNE .outerLoop			; Else, loop until X = $04
loadPlayAttributes_2:
	LDA PPU_STATUS			; Read PPU status to reset latch
	LDA #$2B
	STA PPU_ADDR
	LDA #$C0
	STA PPU_ADDR			; Tell PPU to write values to $23C0
	LDX #$00				; Initialize loop counter
.loop:
	LDA playAttr_2, x		; Load attribute data
	STA PPU_DATA
	INX
	CPX #$40				; If X = $40, all attribute bytes copied
	BNE .loop
initObjects:
	LDA #$7F
	STA ship_x1				; Initialize ship x-position (left)
	STA boost_x				; Initialize booster x-position
	LDA #$8F
	STA ship_x2				; Initialize ship x-position (right)
	LDA #$C9
	STA ship_y				; Initialize ship y-position
	LDA #$D1
	STA boost_y				; Initialize booster y-position
	LDA #$01
	STA enemy_speed			; Initialize enemy speed variable
	LDA #$00
	STA score
	STA score_temp
	STA score_100
	STA score_10
	STA score_1
	STA p1e1_collide
	STA p1e2_collide
	STA p1e3_collide
	STA p2e1_collide
	STA p2e2_collide
	STA p2e3_collide
	STA p3e1_collide
	STA p3e2_collide
	STA p3e3_collide
	LDA #$09
	STA fail_count
.done:
	LDA #STATE_PLAY
	STA game_state
	LDA #$EF
	STA scroll_num
	LDA #%10000000			; Re-enable NMI
	STA PPU_CTRL
	RTS						; Return to main loop
	
;==[movePlayer]== Process player input and update related variables ====================
movePlayer:
.left:
	LDA controller
	AND #PAD_LEFT			; Poll controller for left button press
	BEQ .right				; Move on if not pressed
	LDA ship_x1
	CMP #BOUND_LEFT			; Check leftward x-position for collision
	BCC .right				; Move on if colliding with leftmost boundary
	LDA ship_x1
	SEC
	SBC #SPEED_PLAYER
	STA ship_x1				; Subtract player speed from leftward x-position
	LDA ship_x2
	SEC
	SBC #SPEED_PLAYER
	STA ship_x2				; Subtract player speed from rightward x-position
.right:
	LDA controller
	AND #PAD_RIGHT			; Poll controller for right button press
	BEQ .update				; Move on if not pressed
	LDA ship_x2
	CMP #BOUND_RIGHT		; Check rightward x-position for collision
	BCS .update				; Move on if colliding with rightmost boundary
	LDA ship_x1
	CLC
	ADC #SPEED_PLAYER
	STA ship_x1				; Add player speed to leftward x-position
	LDA ship_x2
	CLC
	ADC #SPEED_PLAYER
	STA ship_x2				; Add player speed to rightward x-position
.update:					; Update player sprites relative to main sprite
	LDA ship_x1				; Load current position of main sprite
	STA SPRITE_PLAYER+3		; Update left-aligned sprites
	STA SPRITE_PLAYER+11
	STA SPRITE_PLAYER+19
	STA SPRITE_PLAYER+23
	STA SPRITE_BOOST+3
	CLC
	ADC #$08				; Add #$08 to the main sprite location
	STA SPRITE_PLAYER+7		; Update right-aligned sprites relative to
	STA SPRITE_PLAYER+15	; left-aligned sprites
	STA SPRITE_BOOST+7
	INC boost_anim			; Increment booster animation counter
	LDA boost_anim
	CMP #$08				; If A < #$08 display first frame
	BCC .swap_1
	LDA boost_anim
	CMP #$08				; If A > #$08 display second frame
	BCS .swap_2
.swap_1:
	LDA #$14
	STA SPRITE_BOOST+1
	LDA #$15
	STA SPRITE_BOOST+5
	JMP .done
.swap_2:
	LDA #$04
	STA SPRITE_BOOST+1
	LDA #$05
	STA SPRITE_BOOST+5
.reset_boost:
	LDA boost_anim
	CMP #$10				; If A = #$10, reset counter
	BNE .done
	LDA #$00
	STA boost_anim
.done:
	RTS
	
;==[ activateProjectiles ]== Handles activating player projectiles =====================
activateProjectiles:
	LDA controller
	AND #PAD_A				; Check is A button has been pressed
	BEQ .done				; If not, we're done
	LDA proj_delay			; See if delay is active
	CMP #$00
	BEQ .first				; If not, begin checking for active projectiles
	DEC proj_delay			; If delay is active, decrement until it initializes
	JMP .done
.first:
	LDA proj1_on			; Check if first projectile is active
	CMP #$01
	BEQ .second				; If active, move on to next projectile
	LDA #$01
	STA proj1_on			; If not, activate first projectile
	LDA #DELAY_PROJ			; and set projectile delay to keep
	STA proj_delay			; projectiles from grouping too closely
	LDA ship_x1				; Position projectile at top-center of ship sprite
	CLC
	ADC #$04
	STA proj1_x
	LDA ship_y
	SEC
	SBC #$04
	STA proj1_y
	JMP .done
.second:
	LDA proj2_on			; Check if second projectile is active
	CMP #$01
	BEQ .third				; If active, move on to next projectile
	LDA #$01
	STA proj2_on			; If not, activate second projectile
	LDA #DELAY_PROJ			; and set projectile delay
	STA proj_delay
	LDA ship_x1
	CLC
	ADC #$04
	STA proj2_x
	LDA ship_y
	SEC
	SBC #$04
	STA proj2_y
	JMP .done
.third:
	LDA proj3_on			; Check if third projectile is active
	CMP #$01
	BEQ .done				; If active, all projectiles are active
	LDA #$01
	STA proj3_on			; If not, activate third projectile
	LDA #DELAY_PROJ			; and set projectile delay
	STA proj_delay
	LDA ship_x1
	CLC
	ADC #$04
	STA proj3_x
	LDA ship_y
	SEC
	SBC #$04
	STA proj3_y
.done:
	RTS
	
;==[ updateProjectiles ]== Update fired player projectiles =============================
updateProjectiles:
.first:
	LDA proj1_on			; Check if first projectile is active
	CMP #$01
	BEQ .firstTopCheck
	JMP .second					; If not, move on to next projectile
.firstTopCheck:	
	LDA proj1_y
	CMP #BOUND_TOP				; Check if projectile has reached top
	BCS .firstEnemy1Check		; If it hasn't, update its position
	JMP .firstClear
.firstEnemy1Check:
	LDA proj1_x
	CLC
	ADC #$02
	CMP enemy1_x
	BCC .firstEnemy2Check
	LDA enemy1_x
	CLC
	ADC #$10
	STA collide_offset
	LDA proj1_x
	CLC
	ADC #$06
	CMP collide_offset
	BCS .firstEnemy2Check
	LDA proj1_y
	CLC
	ADC #$02
	CMP enemy1_y
	BCC .firstEnemy2Check
	LDA enemy1_y
	CLC
	ADC #$10
	STA collide_offset
	LDA proj1_y
	CLC
	ADC #$06
	CMP collide_offset
	BCS .firstEnemy3Check
	INC score
	LDA #$01
	STA p1e1_collide
	JMP .firstClear
.firstEnemy2Check:
	LDA proj1_x
	CLC
	ADC #$02
	CMP enemy2_x
	BCC .firstEnemy3Check
	LDA enemy2_x
	CLC
	ADC #$10
	STA collide_offset
	LDA proj1_x
	CLC
	ADC #$06
	CMP collide_offset
	BCS .firstEnemy3Check
	LDA proj1_y
	CLC
	ADC #$02
	CMP enemy2_y
	BCC .firstEnemy3Check
	LDA enemy2_y
	CLC
	ADC #$10
	STA collide_offset
	LDA proj1_y
	CLC
	ADC #$06
	CMP collide_offset
	BCS .firstEnemy3Check
	INC score
	LDA #$01
	STA p1e2_collide
	JMP .firstClear
.firstEnemy3Check:
	LDA proj1_x
	CLC
	ADC #$02
	CMP enemy3_x
	BCC .updateFirst
	LDA enemy3_x
	CLC
	ADC #$10
	STA collide_offset
	LDA proj1_x
	CLC
	ADC #$06
	CMP collide_offset
	BCS .updateFirst
	LDA proj1_y
	CLC
	ADC #$02
	CMP enemy3_y
	BCC .updateFirst
	LDA enemy3_y
	CLC
	ADC #$10
	STA collide_offset
	LDA proj1_y
	CLC
	ADC #$06
	CMP collide_offset
	BCS .updateFirst
	INC score
	LDA #$01
	STA p1e3_collide
.firstClear:
	LDA #$FE				; If it has, clear sprite from memory
	STA SPRITE_PROJ1		; and its clear activity flag
	STA SPRITE_PROJ1+1
	STA SPRITE_PROJ1+2
	STA SPRITE_PROJ1+3
	LDA #$00
	STA proj1_on
	JMP .done
.updateFirst:
	LDA proj1_y				; Apply velocity constant to projectile
	SEC
	SBC	#SPEED_PROJ
	STA proj1_y
	LDA proj1_y
	STA SPRITE_PROJ1
	LDA #$03
	STA SPRITE_PROJ1+1
	LDA #$02
	STA SPRITE_PROJ1+2
	LDA proj1_x
	STA SPRITE_PROJ1+3
.second:
	LDA proj2_on			; Check if second projectile is active
	CMP #$01
	BEQ .secondTopCheck
	JMP .third				; If not, move on to next projectile
.secondTopCheck:	
	LDA proj2_y
	CMP #BOUND_TOP				; Check if projectile has reached top
	BCS .secondEnemy1Check		; If it hasn't, update its position
	JMP .secondClear
.secondEnemy1Check:
	LDA proj2_x
	CLC
	ADC #$02
	CMP enemy1_x
	BCC .secondEnemy2Check
	LDA enemy1_x
	CLC
	ADC #$10
	STA collide_offset
	LDA proj2_x
	CLC
	ADC #$06
	CMP collide_offset
	BCS .secondEnemy2Check
	LDA proj1_y
	CLC
	ADC #$02
	CMP enemy1_y
	BCC .secondEnemy2Check
	LDA enemy1_y
	CLC
	ADC #$10
	STA collide_offset
	LDA proj2_y
	CLC
	ADC #$06
	CMP collide_offset
	BCS .secondEnemy3Check
	INC score
	LDA #$01
	STA p2e1_collide
	JMP .secondClear
.secondEnemy2Check:
	LDA proj2_x
	CLC
	ADC #$02
	CMP enemy2_x
	BCC .secondEnemy3Check
	LDA enemy2_x
	CLC
	ADC #$10
	STA collide_offset
	LDA proj2_x
	CLC
	ADC #$06
	CMP collide_offset
	BCS .secondEnemy3Check
	LDA proj2_y
	CLC
	ADC #$02
	CMP enemy2_y
	BCC .secondEnemy3Check
	LDA enemy2_y
	CLC
	ADC #$10
	STA collide_offset
	LDA proj2_y
	CLC
	ADC #$06
	CMP collide_offset
	BCS .secondEnemy3Check
	INC score
	LDA #$01
	STA p2e2_collide
	JMP .secondClear
.secondEnemy3Check:
	LDA proj2_x
	CLC
	ADC #$02
	CMP enemy3_x
	BCC .updateSecond
	LDA enemy3_x
	CLC
	ADC #$10
	STA collide_offset
	LDA proj2_x
	CLC
	ADC #$06
	CMP collide_offset
	BCS .updateSecond
	LDA proj2_y
	CLC
	ADC #$02
	CMP enemy3_y
	BCC .updateSecond
	LDA enemy3_y
	CLC
	ADC #$10
	STA collide_offset
	LDA proj2_y
	CLC
	ADC #$06
	CMP collide_offset
	BCS .updateSecond
	INC score
	LDA #$01
	STA p2e3_collide
.secondClear:
	LDA #$FE				; If it has, clear sprite from memory
	STA SPRITE_PROJ2		; and clear its activity flag
	STA SPRITE_PROJ2+1
	STA SPRITE_PROJ2+2
	STA SPRITE_PROJ2+3
	LDA #$00
	STA proj2_on
	JMP .done
.updateSecond:
	LDA proj2_y				; Apply velocity constant to projectile
	SEC
	SBC	#SPEED_PROJ
	STA proj2_y
	LDA proj2_y
	STA SPRITE_PROJ2
	LDA #$03
	STA SPRITE_PROJ2+1
	LDA #$02
	STA SPRITE_PROJ2+2
	LDA proj2_x
	STA SPRITE_PROJ2+3
.third:
	LDA proj3_on			; Check if third projectile is active
	CMP #$01
	BEQ .thirdTopCheck
	JMP .done				; If not, do nothing
.thirdTopCheck:	
	LDA proj3_y
	CMP #BOUND_TOP				; Check if projectile has reached top
	BCS .thirdEnemy1Check		; If it hasn't, update its position
	JMP .thirdClear
.thirdEnemy1Check:
	LDA proj3_x
	CLC
	ADC #$02
	CMP enemy1_x
	BCC .thirdEnemy2Check
	LDA enemy1_x
	CLC
	ADC #$10
	STA collide_offset
	LDA proj3_x
	CLC
	ADC #$06
	CMP collide_offset
	BCS .thirdEnemy2Check
	LDA proj3_y
	CLC
	ADC #$02
	CMP enemy1_y
	BCC .thirdEnemy2Check
	LDA enemy1_y
	CLC
	ADC #$10
	STA collide_offset
	LDA proj3_y
	CLC
	ADC #$06
	CMP collide_offset
	BCS .thirdEnemy3Check
	INC score
	LDA #$01
	STA p3e1_collide
	JMP .thirdClear
.thirdEnemy2Check:
	LDA proj3_x
	CLC
	ADC #$02
	CMP enemy2_x
	BCC .thirdEnemy3Check
	LDA enemy2_x
	CLC
	ADC #$10
	STA collide_offset
	LDA proj3_x
	CLC
	ADC #$06
	CMP collide_offset
	BCS .thirdEnemy3Check
	LDA proj3_y
	CLC
	ADC #$02
	CMP enemy2_y
	BCC .thirdEnemy3Check
	LDA enemy2_y
	CLC
	ADC #$10
	STA collide_offset
	LDA proj3_y
	CLC
	ADC #$06
	CMP collide_offset
	BCS .thirdEnemy3Check
	INC score
	LDA #$01
	STA p3e2_collide
	JMP .thirdClear
.thirdEnemy3Check:
	LDA proj3_x
	CLC
	ADC #$02
	CMP enemy3_x
	BCC .updateThird
	LDA enemy3_x
	CLC
	ADC #$10
	STA collide_offset
	LDA proj3_x
	CLC
	ADC #$06
	CMP collide_offset
	BCS .updateThird
	LDA proj3_y
	CLC
	ADC #$02
	CMP enemy3_y
	BCC .updateThird
	LDA enemy3_y
	CLC
	ADC #$10
	STA collide_offset
	LDA proj3_y
	CLC
	ADC #$06
	CMP collide_offset
	BCS .updateThird
	INC score
	LDA #$01
	STA p3e3_collide
.thirdClear:
	LDA #$FE				; If it has, clear sprite from memory
	STA SPRITE_PROJ3		; and clear its activity flag
	STA SPRITE_PROJ3+1
	STA SPRITE_PROJ3+2
	STA SPRITE_PROJ3+3
	LDA #$00
	STA proj3_on
	JMP .done
.updateThird:
	LDA proj3_y				; Apply velocity constant to projectile
	SEC
	SBC	#SPEED_PROJ		
	STA proj3_y
	LDA proj3_y
	STA SPRITE_PROJ3
	LDA #$03
	STA SPRITE_PROJ3+1
	LDA #$02
	STA SPRITE_PROJ3+2
	LDA proj3_x
	STA SPRITE_PROJ3+3
.done:
	RTS
	
;==[ activateEnemies ]== Randomly distribute enemy types ==============================-
activateEnemies:
.checkActvity:
	LDA enemy1_on			; If any enemy flag is active, end subroutine
	CMP #$01
	BEQ .done
	LDA enemy2_on
	CMP #$01
	BEQ .done
	LDA enemy3_on
	CMP #$01
	BEQ .done
.randomize:
	JSR getRandom
	LDA rng_value
	CMP #$55
	BCC .first				; If 0 <= frame_num < 85 activate first enemy type
	CMP #$AA
	BCC .second				; If 85 < frame_num < 170 activate second enemy type
	JMP .third				; Else activate third enemy type
.first:
	LDA #$01
	STA enemy1_on			; Activate enemy flag
	LDA #$08
	STA enemy1_x
	STA enemy1_y			; Initialize enemy coordinates
	JMP .done
.second:
	LDA #$01
	STA enemy2_on			; Activate enemy flag
	LDA #$08
	STA enemy2_y
	LDA #$F0
	STA enemy2_x			; Initialize enemy coordinates
	JMP .done
.third:
	LDA #$01
	STA enemy3_on			; Activate enemy flag
	LDA #$08
	STA enemy3_y			; Initialize enemy y-position
	JSR getRandom			; Determine x-position randomly
	LDA rng_value			; Check rng value against boundaries
	CMP #$10
	BCC	.thirdLeft
	CMP #$E0
	BCS .thirdRight
	STA enemy3_x			; If within bounds, store and move on
	JMP .done
.thirdLeft:					; Else adjust to closest boundary
	LDA #$10
	STA enemy3_x
	JMP .done
.thirdRight:
	LDA #$E0
	STA enemy3_x
.done:
	RTS						; Return to main loop
	
;==[ updateEnemies ]== Update enemy position and activity ==============================
updateEnemies:
.type1:
	LDA enemy1_on
	CMP #$01
	BEQ .type1BoundCheck
	JMP .type2
.type1BoundCheck:
	LDA enemy1_x
	CMP #BOUND_RIGHT
	BCC .type1Proj1Check
	DEC fail_count
	JMP .type1Prep
.type1Proj1Check:
	LDA p1e1_collide
	CMP #$01
	BNE .type1Proj2Check
	LDA #$00
	STA p1e1_collide
	JMP .type1Prep
.type1Proj2Check:
	LDA p2e1_collide
	CMP #$01
	BNE .type1Proj3Check
	LDA #$00
	STA p2e1_collide
	JMP .type1Prep
.type1Proj3Check:
	LDA p3e1_collide
	CMP #$01
	BNE .type1Update
	LDA #$00
	STA p3e1_collide
.type1Prep:
	LDX #$00
.type1Clear:
	LDA #$FE				; Clear sprite from memory
	STA SPRITE_ENEMY1, x	; and its clear activity flag
	INX
	CPX #$10
	BNE .type1Clear
	LDA #$00
	STA enemy1_on
	STA enemy1_x
	STA enemy1_y
	JMP .done
.type1Update:
	LDA enemy1_y
	STA SPRITE_ENEMY1
	STA SPRITE_ENEMY1+4
	CLC
	ADC #$08
	STA SPRITE_ENEMY1+8
	STA SPRITE_ENEMY1+12
	LDA #$06
	STA SPRITE_ENEMY1+1
	LDA #$07
	STA SPRITE_ENEMY1+5
	LDA #$16
	STA SPRITE_ENEMY1+9
	LDA #$17
	STA SPRITE_ENEMY1+13
	LDA #$03
	STA SPRITE_ENEMY1+2
	STA SPRITE_ENEMY1+6
	STA SPRITE_ENEMY1+10
	STA SPRITE_ENEMY1+14
	LDA enemy1_x
	CLC
	ADC enemy_speed
	STA enemy1_x
	STA SPRITE_ENEMY1+3
	STA SPRITE_ENEMY1+11
	CLC
	ADC #$08
	STA SPRITE_ENEMY1+7
	STA SPRITE_ENEMY1+15
	JMP .done
.type2:
	LDA enemy2_on
	CMP #$01
	BEQ .type2BoundCheck
	JMP .type3
.type2BoundCheck:
	LDA enemy2_x
	CMP #BOUND_LEFT
	BCS .type2Proj1Check
	DEC fail_count
	JMP .type2Prep
.type2Proj1Check:
	LDA p1e2_collide
	CMP #$01
	BNE .type2Proj2Check
	LDA #$00
	STA p1e2_collide
	JMP .type2Prep
.type2Proj2Check:
	LDA p2e2_collide
	CMP #$01
	BNE .type2Proj3Check
	LDA #$00
	STA p2e2_collide
	JMP .type2Prep
.type2Proj3Check:
	LDA p3e2_collide
	CMP #$01
	BNE .type2Update
	LDA #$00
	STA p3e2_collide
.type2Prep:
	LDX #$00
.type2Clear:
	LDA #$FE				; Clear sprite from memory
	STA SPRITE_ENEMY2, x	; and its clear activity flag
	INX
	CPX #$10
	BNE .type2Clear
	LDA #$00
	STA enemy2_on
	STA enemy2_x
	STA enemy2_y
	JMP .done
.type2Update:
	LDA enemy2_y
	STA SPRITE_ENEMY2
	STA SPRITE_ENEMY2+4
	CLC
	ADC #$08
	STA SPRITE_ENEMY2+8
	STA SPRITE_ENEMY2+12
	LDA #$06
	STA SPRITE_ENEMY2+1
	LDA #$07
	STA SPRITE_ENEMY2+5
	LDA #$16
	STA SPRITE_ENEMY2+9
	LDA #$17
	STA SPRITE_ENEMY2+13
	LDA #$03
	STA SPRITE_ENEMY2+2
	STA SPRITE_ENEMY2+6
	STA SPRITE_ENEMY2+10
	STA SPRITE_ENEMY2+14
	LDA enemy2_x
	SEC
	SBC enemy_speed
	STA enemy2_x
	STA SPRITE_ENEMY2+3
	STA SPRITE_ENEMY2+11
	CLC
	ADC #$08
	STA SPRITE_ENEMY2+7
	STA SPRITE_ENEMY2+15
	JMP .done
.type3:
	LDA enemy3_on
	CMP #$01
	BEQ .type3BoundCheck
	JMP .done
.type3BoundCheck:
	LDA enemy3_y
	CMP #BOUND_BOTTOM
	BCC .type3Proj1Check
	DEC fail_count
	JMP .type3Prep
.type3Proj1Check:
	LDA p1e3_collide
	CMP #$01
	BNE .type3Proj2Check
	LDA #$00
	STA p1e3_collide
	JMP .type3Prep
.type3Proj2Check:
	LDA p2e3_collide
	CMP #$01
	BNE .type3Proj3Check
	LDA #$00
	STA p2e3_collide
	JMP .type3Prep
.type3Proj3Check:
	LDA p3e3_collide
	CMP #$01
	BNE .type3Update
	LDA #$00
	STA p3e3_collide
.type3Prep:
	LDX #$00
.type3Clear:
	LDA #$FE				; Clear sprite from memory
	STA SPRITE_ENEMY3, x	; and its clear activity flag
	INX
	CPX #$10
	BNE .type3Clear
	LDA #$00
	STA enemy3_on
	STA enemy3_x
	STA enemy3_y
	JMP .done
.type3Update:
	LDA enemy3_y
	CLC
	ADC enemy_speed
	STA enemy3_y
	STA SPRITE_ENEMY3
	STA SPRITE_ENEMY3+4
	CLC
	ADC #$08
	STA SPRITE_ENEMY3+8
	STA SPRITE_ENEMY3+12
	LDA #$42
	STA SPRITE_ENEMY3+1
	LDA #$43
	STA SPRITE_ENEMY3+5
	LDA #$52
	STA SPRITE_ENEMY3+9
	LDA #$53
	STA SPRITE_ENEMY3+13
	LDA #$03
	STA SPRITE_ENEMY3+2
	STA SPRITE_ENEMY3+6
	STA SPRITE_ENEMY3+10
	STA SPRITE_ENEMY3+14
	LDA enemy3_x
	STA SPRITE_ENEMY3+3
	STA SPRITE_ENEMY3+11
	CLC
	ADC #$08
	STA SPRITE_ENEMY3+7
	STA SPRITE_ENEMY3+15
	JMP .done
.done:
	RTS

;==[ updateScore ]== Update player score and enemy speed ===============================
updateScore:
.modifySpeed:
	LDA score
	CMP #$32
	BCS .level2
	LDA #$01
	STA enemy_speed
	JMP .convert
.level2:
	LDA score
	CMP #$64
	BCS .level3
	LDA #$02
	STA enemy_speed
	JMP .convert
.level3:
	LDA score
	CMP #$96
	BCS .level4
	LDA #$03
	STA enemy_speed
	JMP .convert
.level4:
	LDA #$04
	STA enemy_speed
.convert:
	LDA #$00
	STA score_100
	STA score_10
	STA score_1
	LDA score
	STA score_temp
.hundreds:
	LDA score_temp
	CMP #$64
	BCC .tens
	LDA score_temp
	SEC
	SBC #$64
	STA score_temp
	INC score_100
	JMP .hundreds
.tens:
	LDA score_temp
	CMP #$0A
	BCC .ones
	LDA score_temp
	SEC
	SBC #$0A
	STA score_temp
	INC score_10
	JMP .tens
.ones:
	LDA score_temp
	STA score_1
.display:
	LDA #$E0
	STA SPRITE_SCORE1
	LDA #$32
	STA SPRITE_SCORE1+1
	LDA #$02
	STA SPRITE_SCORE1+2
	LDA #$08
	STA SPRITE_SCORE1+3
	LDA #$E0
	STA SPRITE_SCORE1+4
	LDA #$22
	STA SPRITE_SCORE1+5
	LDA #$02
	STA SPRITE_SCORE1+6
	LDA #$10
	STA SPRITE_SCORE1+7
	LDA #$E0
	STA SPRITE_SCORE1+8
	LDA #$2E
	STA SPRITE_SCORE1+9
	LDA #$02
	STA SPRITE_SCORE1+10
	LDA #$18
	STA SPRITE_SCORE1+11
	LDA #$E0
	STA SPRITE_SCORE1+12
	LDA #$31
	STA SPRITE_SCORE1+13
	LDA #$02
	STA SPRITE_SCORE1+14
	LDA #$20
	STA SPRITE_SCORE1+15
	LDA #$E0
	STA SPRITE_SCORE1+16
	LDA #$24
	STA SPRITE_SCORE1+17
	LDA #$02
	STA SPRITE_SCORE1+18
	LDA #$28
	STA SPRITE_SCORE1+19
.digits:
	LDA #$E0
	STA SPRITE_SCORE1+20
	LDA #$60
	CLC
	ADC score_100
	STA SPRITE_SCORE1+21
	LDA #$02
	STA SPRITE_SCORE1+22	
	LDA #$38
	STA SPRITE_SCORE1+23
	LDA #$E0
	STA SPRITE_SCORE1+24
	LDA #$60
	CLC
	ADC score_10
	STA SPRITE_SCORE1+25
	LDA #$02
	STA SPRITE_SCORE1+26
	LDA #$40
	STA SPRITE_SCORE1+27
	LDA #$E0
	STA SPRITE_SCORE1+28
	LDA #$60
	CLC
	ADC score_1
	STA SPRITE_SCORE1+29
	LDA #$02
	STA SPRITE_SCORE1+30
	LDA #$48
	STA SPRITE_SCORE1+31
.lives:
	LDA #$D8
	STA SPRITE_SCORE1+32
	LDA #$2B
	STA SPRITE_SCORE1+33
	LDA #$02
	STA SPRITE_SCORE1+34
	LDA #$08
	STA SPRITE_SCORE1+35
	LDA #$D8
	STA SPRITE_SCORE1+36
	LDA #$28
	STA SPRITE_SCORE1+37
	LDA #$02
	STA SPRITE_SCORE1+38
	LDA #$10
	STA SPRITE_SCORE1+39
	LDA #$D8
	STA SPRITE_SCORE1+40
	LDA #$35
	STA SPRITE_SCORE1+41
	LDA #$02
	STA SPRITE_SCORE1+42
	LDA #$18
	STA SPRITE_SCORE1+43
	LDA #$D8
	STA SPRITE_SCORE1+44
	LDA #$24
	STA SPRITE_SCORE1+45
	LDA #$02
	STA SPRITE_SCORE1+46
	LDA #$20
	STA SPRITE_SCORE1+47
	LDA #$D8
	STA SPRITE_SCORE1+48
	LDA #$32
	STA SPRITE_SCORE1+49
	LDA #$02
	STA SPRITE_SCORE1+50
	LDA #$28
	STA SPRITE_SCORE1+51
.livesLeft:
	LDA #$D8
	STA SPRITE_SCORE1+52
	LDA #$60
	CLC
	ADC fail_count
	STA SPRITE_SCORE1+53
	LDA #$02
	STA SPRITE_SCORE1+54
	LDA #$38
	STA SPRITE_SCORE1+55
.win:
	LDA score
	CMP #$FF
	BNE .lose
	JSR initGameOver
.lose:
	LDA fail_count
	CMP #$00
	BNE .done
	JSR initGameOver
.done:
	RTS
	
;==[ waitForNMI ]== Burns cycles waiting for NMI to occur for smooth frame updating ====
waitForNMI:
	LDA frame_num			; Store current frame count in Accumulator
.loop:
	CMP frame_num			; If frame count has changed, NMI has occured
	BEQ .loop				; Loop until NMI occurs
	RTS						; Return to main loop