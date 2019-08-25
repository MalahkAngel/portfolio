;==[ Zero Page Pointers ]==============================================================
	.rsset $0000	
lowPtr			.rs 1		; Pointers stored in zero page of memory ($0000-$00FF)
highPtr			.rs 1		; for fast implementation of 16-bit math operations
seed			.rs 2		; Psuedo Random Number Generation seed

;==[ Variable and Constant Declarations ]==============================================
	.rsset $0010
	
;==[ General Variables ]===============================================================
frame_num		.rs 1		; Increments each time NMI occurs
sleep_flag		.rs 1		; Controls cycle burn during screen transitions
scroll_num		.rs 1		; Tracks when a nametable has exited the screen
mod_value		.rs 1		; Modulo operation variable
rng_value		.rs 1		; Psuedo RNG value
nametable		.rs 1		; Tracks currently active nametable
game_state		.rs 1		; Controls which screen to display and controls to use
controller		.rs 1		; Polling variable for player input
score			.rs 1		; Player score
score_temp		.rs 1
score_1			.rs 1
score_10		.rs 1
score_100		.rs 1
fail_count		.rs 1

;==[ Game Objects and Parameters ]=====================================================
ship_x1			.rs 1		; Player x-position (left)
ship_x2			.rs 1		; Player x-position (right)
ship_y			.rs 1		; Player y-position
boost_x			.rs 1		; Ship rocket booster effect x-position
boost_y			.rs 1		; Ship rocket booster effect y-position
boost_anim		.rs 1		; Frame counter for booster animation

proj1_x			.rs 1		; First projectile x-position
proj2_x			.rs 1		; Second projectile x-position
proj3_x			.rs 1		; Third projectile x-position
proj1_y			.rs 1		; First projectile y-position
proj2_y			.rs 1		; Second projectile y-position
proj3_y			.rs 1		; Third projectile y-position
proj1_on		.rs 1		; First projectile activity flag
proj2_on		.rs 1		; Second projectile activity flag
proj3_on		.rs 1		; Third projectile activity flag
proj_delay		.rs 1		; Counter preventing projectile grouping

enemy1_x		.rs 1		; First enemy type x-position
enemy2_x		.rs 1		; Second enemy type x-position
enemy3_x		.rs 1		; Third enemy type x-position
enemy1_y		.rs 1		; First enemy type y-position
enemy2_y		.rs 1		; Second enemy type y-position
enemy3_y		.rs 1		; Third enemy type y-position
enemy1_on		.rs 1		; First enemy type activity flag
enemy2_on		.rs 1		; Second enemy type activity flag
enemy3_on		.rs 1		; Third enemy type activity flag
enemy_speed		.rs 1		; Enemy velocity variable

enemyproj1_x	.rs 1		; First enemy projectile x-position
enemyproj2_x	.rs 1		; Second enemy projectile x-position
enemyproj1_y	.rs 1		; First enemy projectile y-position
enemyproj2_y	.rs 1		; Second enemy projectile y-position
enemyproj1_on	.rs 1		; First enemy projectile activity flag
enemyproj2_on	.rs 1		; Second enemy projectile activity flag
enemyproj_speed	.rs 1		; Enemy projectile velocity variable

collide_offset	.rs 1		; Comparison variable for collision detection
p1e1_collide	.rs 1		; Projectile 1 x Enemy 1
p1e2_collide	.rs 1		; Projectile 1 x Enemy 2
p1e3_collide	.rs 1		; Projectile 1 x Enemy 3
p2e1_collide	.rs 1		; Projectile 2 x Enemy 1
p2e2_collide	.rs 1		; Projectile 2 x Enemy 2
p2e3_collide	.rs 1		; Projectile 2 x Enemy 3
p3e1_collide	.rs 1		; Projectile 3 x Enemy 1
p3e2_collide	.rs 1		; Projectile 3 x Enemy 2
p3e3_collide	.rs 1		; Projectile 3 x Enemy 3


;==[ General Labels ]==================================================================
SPRITE_PLAYER	= $0200		; Base address for player sprite
SPRITE_BOOST	= $0214		; Base address for booster sprite
SPRITE_PROJ1	= $021C		; Base address for first player projectile
SPRITE_PROJ2	= $0220		; Base address for second player projectile
SPRITE_PROJ3	= $0224		; Base address for third player projectile
SPRITE_ENEMY1	= $0228		; Base address for first enemy type
SPRITE_ENEMY2	= $0238		; Base address for second enemy type
SPRITE_ENEMY3	= $0248		; Base address for third enemy type
SPRITE_SCORE1	= $0258		; Base address for score text

SPEED_PLAYER	= $02
SPEED_PROJ		= $04

DELAY_PROJ		= $08		; Projectile delay cap

BOUND_LEFT		= $10		; Collision boundaries for player
BOUND_RIGHT		= $F0
BOUND_TOP		= $08		; Collision boundary for player projectiles
BOUND_BOTTOM	= $F0		; Collision boundary for enemies and their projectiles
	
;==[ PPU Mnemonics ]===================================================================
PPU_CTRL		= $2000		; NMI | Asset declaration | Increment mode for scrolling
PPU_MASK		= $2001		; Color emphasis | Asset activity | Screen clipping
PPU_STATUS		= $2002		; vBlank | sprite0 | Sprite overflow | Reset asset latch
PPU_SCROLL		= $2005		; Fine scroll position register (x2 writes)
PPU_ADDR		= $2006		; Tells PPU where to write data (x2 writes)
PPU_DATA		= $2007		; Tells PPU what is visuals to display (data I/O)
OAM_ADDR		= $2003		; Object Attribute Memory address register
OAM_DATA		= $2004		; Object Attribute Memory data I/O register
OAM_DMA			= $4014		; Direct Memory Address transfer register

;==[ APU Mnemonics ]===================================================================
APU_SQ1			= $4000
APU_SQ1_LO		= $4002
APU_SQ1_HI		= $4003
APU_NOISE_V		= $400C
APU_NOISE_T		= $400E
APU_NOISE_L		= $400F
APU_CHAN		= $4015

;==[ Game States ]=====================================================================
STATE_TITLE		= $00		; Displays splash screen
STATE_PLAY		= $01		; Displays game screen
STATE_OVER		= $02		; Displays win screen

;==[ Button Mnemonics ]================================================================
PAD_A			= %10000000
PAD_B			= %01000000
PAD_SEL			= %00100000
PAD_START		= %00010000
PAD_UP			= %00001000
PAD_DOWN		= %00000100
PAD_LEFT		= %00000010
PAD_RIGHT		= %00000001

;==[ Decimal Representation ]==========================================================
NUM_0			= $08
NUM_1			= $09
NUM_2			= $0A
NUM_3			= $0B
NUM_4			= $0C
NUM_5			= $0D
NUM_6			= $0E
NUM_7			= $0F
NUM_8			= $18
NUM_9			= $19