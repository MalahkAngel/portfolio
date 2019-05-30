#pragma once

#include "globals.h"

struct Camera
{
	float left, right, top, bottom;
};

struct Sector
{
	int ID;
	float left, right, top, bottom;
	std::pair<int, int> leftExit;
	std::pair<int, int> rightExit;
	std::pair<int, int> topExit;
	std::pair<int, int> bottomExit;
};

struct Tile
{
	int type, graphics;
	float left, right, top, bottom;
	float slopeLeft, slopeRight;
};

struct WallDrop
{
	int type;
	bool active;
	float vSpeed, left, right, top, bottom;
};

struct Breakable
{
	int type, frames;
	bool active, broken;
	float left, right, top, bottom;
};

struct TileMap
{
	int ID, height, width;					// room dimensions
	std::vector<Tile> background;			// background graphics data
	std::vector<Tile> blocks;				// collision block data
	std::vector<Breakable> breakables;		// breakable object data
	std::vector<Sector> sectors;			// room sector data
	std::vector<WallDrop> wallDrops;		// breakable object drops
	ALLEGRO_BITMAP* tileSheet;				// room graphics
};

class MapHandler
{
	private:
		Camera cam;								// player tracking
		TileMap curMap;							// currently active map
		std::vector<TileMap> mapData;			// map data in totality
		ALLEGRO_BITMAP* resources;				// common drop graphics
		int cMapID;								// map iterator
	public:
		MapHandler();
		~MapHandler();

		// garbage collection
		void destroyTextures();

		// data and drawing
		void loadMapData(int mapID);
		void loadNewMap();
		void moveCamera(std::pair<float, float> pos);
		void updateMap();
		void drawMap();

		// getters
		float getCamX() { return cam.left; }
		float getCamY() { return cam.top; }
		TileMap& getMap() { return curMap; }
		Tile getBlock(int index) { return curMap.blocks[index]; }
};

