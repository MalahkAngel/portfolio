#pragma once

// C++ libraries
#include <cstdlib>			// random number generation
#include <cmath>			// trig functions
#include <string>
#include <vector>			// dynamic array support
#include <iostream>			// debugging and player input
#include <fstream>			// file I/O
#include <algorithm>
#include <thread>			// delay functions
#include <chrono>

// Allegro 5 libraries
#include <allegro5/allegro.h>					// main Allegro 5 library
#include <allegro5/allegro_native_dialog.h>		// native dialog interface
#include <allegro5/allegro_primitives.h>		// basic shape drawing
#include <allegro5/allegro_image.h>				// adds PNG support
#include <allegro5/allegro_font.h>				// bitmap font support
#include <allegro5/allegro_ttf.h>				// True-Type font support
#include <allegro5/allegro_audio.h>				// adds OGG audio support

// constants
#define SCREEN_W 384				// screen dimensions
#define SCREEN_H 240
#define WINDOW_W 768
#define WINDOW_H 480
#define SECTOR_W 24					// sector dimensions in tiles
#define SECTOR_H 15
#define TILE_SIZE 16				// tile size in pixels
#define NUM_MAPS 1
#define PLAYER_W 16					// player hitbox dimensions
#define PLAYER_H 32
#define PLAYER_SIZE 32				// player graphics dimensions
#define RUN_SPEED 2.0
#define JUMP_SPEED 3.0
#define GRAVITY (9.8 / 60.0) / 1.5	// downward force of gravity

enum LOAD_STATES { L_FIELD, L_ROOM, L_MENU, NUM_LOAD_STATES };
enum GAME_STATES { G_SPLASH, G_FIELD, G_MENU, G_CUTSCENE, NUM_GAME_STATES };
enum MENU_BUTTONS { MB_UP, MB_DOWN, MB_CONFIRM, MB_CANCEL, NUM_MENU_BUTTONS };
enum FIELD_BUTTONS
{
	FB_LEFT, FB_RIGHT, FB_UP, FB_DOWN, FB_MAGIC,
	FB_M_ATK, FB_IMBUE, FB_SHOOT, FB_EVADE,
	FB_JUMP, FB_BOOST, FB_ITEM, FB_MAP,
	FB_MENU, NUM_FIELD_BUTTONS
};
enum DS4_BUTTONS
{
	DS4_SQUARE, DS4_CROSS, DS4_CIRCLE, DS4_TRIANGLE,
	DS4_L1, DS4_R1, DS4_L2, DS4_R2, DS4_SHARE, DS4_OPTIONS,
	DS4_L3, DS4_R3, DS4_TOUCH, DS4_HOME, NUM_DS4_BUTTONS
};
enum DS4_AXES {DS4_STICKS, DS4_TRIGGERS, DS4_DPAD, NUM_DS4_AXES};
enum BREAK_TYPES { B_PASSIVE, B_SOLID, B_SCRIPTED, NUM_BREAK_TYPES };
enum MELEE_TYPES
{
	ONE_HAND_DAGGER, ONE_HAND_SWORD, ONE_HAND_AXE, ONE_HAND_BLUNT,
	TWO_HAND_SWORD, TWO_HAND_AXE, TWO_HAND_BLUNT, TWO_HAND_KATANA,
	NUM_MELEE_TYPES
};
enum RANGED_TYPES
{
	ONE_HAND_PROJECTILE, ONE_HAND_PISTOL, ONE_HAND_MAGNUM,
	TWO_HAND_12_GAUGE, TWO_HAND_COMBAT_SHOTGUN,
	NUM_RANGED_TYPES
};