#pragma once
#include "main.h"

class MapEditor
{
private:
	ALLEGRO_FONT* title;
	ALLEGRO_FONT* smallText;
	ALLEGRO_FONT* largeText;
	ALLEGRO_FONT* mapText;

	char typeGrid[GRID_SIZE][GRID_SIZE];	// wall types -- determines texture mapping and collision
	char wallGrid[GRID_SIZE][GRID_SIZE];	// wall textures
	char floorGrid[GRID_SIZE][GRID_SIZE];	// floor textures
	char skyGrid[GRID_SIZE][GRID_SIZE];		// sky textures

	bool saved, loaded;
	int msgCounter;
public:
	MapEditor();
	~MapEditor();

	bool loadFonts();
	void drawTypes();

	ALLEGRO_COLOR getColor(char value);
	int updateScreen(int state, ALLEGRO_EVENT ev, ALLEGRO_DISPLAY* window);
	void drawScreen(int state);

	bool saveMap(ALLEGRO_DISPLAY* window);
	bool loadMap(ALLEGRO_DISPLAY* window);

	void destroyEditor();
};

