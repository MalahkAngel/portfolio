#pragma once

// C++ libraries
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>

// Allegro 5 libraries
#include <allegro5/allegro5.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>

// constants
#define FPS 1.0f / 60.0f
#define WINDOW_W 1024
#define WINDOW_H 672
#define GRID_SIZE 32

enum numKeys { KEY_W, KEY_A, KEY_S, KEY_D, KEY_UP, KEY_LEFT, KEY_DOWN, KEY_RIGHT, KEY_E, KEY_SPACE, KEY_TAB, KEY_ESC, NUM_KEYS };
enum appStates { STATE_TYPEEDIT, STATE_WALLEDIT, STATE_FLOOREDIT, STATE_SKYEDIT, NUM_APPSTATES };

// global functions
inline void init(bool function, const char* error)	// error checking function
{
	if (!function)
	{
		std::cout << error << std::endl;
		system("pause");
		exit(-1);
	}
}

// file I/O functions
inline uint32_t get32_t(std::istream& file)
{
	uint32_t value;
	uint8_t bytes[4];
	file.read((char*)bytes, 4);
	value = bytes[0] | bytes[1] << 8 | bytes[2] << 16 | bytes[3] << 24;

	return value;
}

inline void set32_t(std::ostream& file, uint32_t value)
{
	uint8_t bytes[4];
	bytes[0] = (value) & 0xFF;
	bytes[1] = (value >> 8) & 0xFF;
	bytes[2] = (value >> 16) & 0xFF;
	bytes[3] = (value >> 24) & 0xFF;
	file.write((char*)bytes, 4);
}