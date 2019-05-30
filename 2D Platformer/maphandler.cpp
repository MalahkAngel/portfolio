#include "maphandler.h"

MapHandler::MapHandler()
{
	cam.left = 0.0;
	cam.right = SCREEN_W;
	cam.top = 0.0;
	cam.bottom = SCREEN_H;

	mapData.resize(0);

	curMap.ID = 0;
	curMap.height = 0;
	curMap.width = 0;
	curMap.background.resize(0);
	curMap.blocks.resize(0);
	curMap.breakables.resize(0);
	curMap.sectors.resize(0);
	curMap.wallDrops.resize(0);
	curMap.tileSheet = NULL;

	resources = al_load_bitmap("assets/tiles/resources.png");
	al_convert_mask_to_alpha(resources, al_map_rgb(255, 0, 255));

	cMapID = 0;
}

MapHandler::~MapHandler() 
{
	mapData.resize(0);
}

// garbage collection
void MapHandler::destroyTextures()
{
	al_destroy_bitmap(resources);
	al_destroy_bitmap(curMap.tileSheet);

	mapData.resize(0);
}

// data management
void MapHandler::loadMapData(int mapID)
{
	// initialize iteration variables
	int cNum = 0;			// current iteration limit
	int pNum = 0;			// previous iteration limit
	int bufferLength = 0;	// length of recieved file
	int bufferIndex = 0;	// current index of buffer
	int numSectors = 0;
	int numBreakables = 0;
	TileMap newMap;

	// initialize programtic file name extraction
	std::string gfxName;	// unique identifier of graphics file
	std::string gfxFile;	// full path of graphics file
	std::string dataBin = "assets/maps/room" + std::to_string(mapID) + ".bin";
	std::string gfxBin = "assets/maps/room" + std::to_string(mapID) + "gfx.bin";
	std::ifstream stream;

	// re-initialize room data
	newMap.ID = mapID;
	newMap.width = 0;
	newMap.height = 0;
	newMap.sectors.resize(0);
	newMap.background.resize(0);
	newMap.breakables.resize(0);
	newMap.wallDrops.resize(0);
	newMap.blocks.resize(0);

	// begin collision data deceryption
	stream.open(dataBin.c_str(), std::ifstream::binary);

	if (stream.is_open())
	{
		bufferIndex = 0;
		stream.seekg(0, stream.end);
		bufferLength = stream.tellg();
		char* dataBuffer = new char[bufferLength];
		stream.seekg(0, stream.beg);
		stream.read(dataBuffer, bufferLength);
		newMap.width = int(dataBuffer[bufferIndex]);
		bufferIndex++;
		newMap.height = int(dataBuffer[bufferIndex]);
		bufferIndex++;
		bufferIndex++;

		for (int i = 0; i < newMap.height; i++)
		{
			while (int(dataBuffer[bufferIndex]) != -1)
			{
				pNum += cNum;
				cNum = int(dataBuffer[bufferIndex]);
				bufferIndex++;

				for (int j = pNum; j < pNum + cNum; j++)
				{
					Tile newTile;
					newTile.type = int(dataBuffer[bufferIndex]);
					
					if (newTile.type != 0)
					{
						newTile.left = j * TILE_SIZE;
						newTile.right = (j * TILE_SIZE) + TILE_SIZE;
						newTile.top = i * TILE_SIZE;
						newTile.bottom = (i * TILE_SIZE) + TILE_SIZE;
						newTile.graphics = 0;

						switch (newTile.type)
						{
						case 5:
							newTile.slopeLeft = 16;
							newTile.slopeRight = 13;
							break;
						case 6:
							newTile.slopeLeft = 12;
							newTile.slopeRight = 9;
							break;
						case 7:
							newTile.slopeLeft = 8;
							newTile.slopeRight = 5;
							break;
						case 8:
							newTile.slopeLeft = 4;
							newTile.slopeRight = 1;
							break;
						case 9:
							newTile.slopeLeft = 16;
							newTile.slopeRight = 9;
							break;
						case 10:
							newTile.slopeLeft = 8;
							newTile.slopeRight = 1;
							break;
						case 11:
							newTile.slopeLeft = 16;
							newTile.slopeRight = 1;
							break;
						case 12:
							newTile.slopeLeft = 1;
							newTile.slopeRight = 4;
							break;
						case 13:
							newTile.slopeLeft = 5;
							newTile.slopeRight = 8;
							break;
						case 14:
							newTile.slopeLeft = 9;
							newTile.slopeRight = 12;
							break;
						case 15:
							newTile.slopeLeft = 13;
							newTile.slopeRight = 16;
							break;
						case 16:
							newTile.slopeLeft = 1;
							newTile.slopeRight = 8;
							break;
						case 17:
							newTile.slopeLeft = 9;
							newTile.slopeRight = 16;
							break;
						case 18:
							newTile.slopeLeft = 1;
							newTile.slopeRight = 16;
							break;
						case 19:
							newTile.slopeLeft = 1;
							newTile.slopeRight = 4;
							break;
						case 20:
							newTile.slopeLeft = 5;
							newTile.slopeRight = 8;
							break;
						case 21:
							newTile.slopeLeft = 9;
							newTile.slopeRight = 12;
							break;
						case 22:
							newTile.slopeLeft = 13;
							newTile.slopeRight = 16;
							break;
						case 23:
							newTile.slopeLeft = 1;
							newTile.slopeRight = 8;
							break;
						case 24:
							newTile.slopeLeft = 9;
							newTile.slopeRight = 16;
							break;
						case 25:
							newTile.slopeLeft = 1;
							newTile.slopeRight = 16;
							break;
						case 26:
							newTile.slopeLeft = 16;
							newTile.slopeRight = 13;
							break;
						case 27:
							newTile.slopeLeft = 12;
							newTile.slopeRight = 9;
							break;
						case 28:
							newTile.slopeLeft = 8;
							newTile.slopeRight = 5;
							break;
						case 29:
							newTile.slopeLeft = 4;
							newTile.slopeRight = 1;
							break;
						case 30:
							newTile.slopeLeft = 16;
							newTile.slopeRight = 9;
							break;
						case 31:
							newTile.slopeLeft = 8;
							newTile.slopeRight = 1;
							break;
						case 32:
							newTile.slopeLeft = 16;
							newTile.slopeRight = 1;
							break;
						default:
							newTile.slopeLeft = 16;
							newTile.slopeRight = 16;
							break;
						}

						newMap.blocks.push_back(newTile);
					}
				}

				bufferIndex++;
			}

			bufferIndex++;
			pNum = 0;
			cNum = 0;
		}

		numSectors = int(dataBuffer[bufferIndex]);
		bufferIndex++;
		bufferIndex++;

		for (int i = 0; i < numSectors; i++)
		{
			Sector newSector;
			newSector.ID = i;
			newSector.left = int(dataBuffer[bufferIndex]) * TILE_SIZE;
			bufferIndex++;
			newSector.right = int(dataBuffer[bufferIndex]) * TILE_SIZE;
			bufferIndex++;
			newSector.top = int(dataBuffer[bufferIndex]) * TILE_SIZE;
			bufferIndex++;
			newSector.bottom = int(dataBuffer[bufferIndex]) * TILE_SIZE;
			bufferIndex++;
			newSector.leftExit.first = int(dataBuffer[bufferIndex]);
			bufferIndex++;
			newSector.leftExit.second = int(dataBuffer[bufferIndex]);
			bufferIndex++;
			newSector.rightExit.first = int(dataBuffer[bufferIndex]);
			bufferIndex++;
			newSector.rightExit.second = int(dataBuffer[bufferIndex]);
			bufferIndex++;
			newSector.topExit.first = int(dataBuffer[bufferIndex]);
			bufferIndex++;
			newSector.topExit.second = int(dataBuffer[bufferIndex]);
			bufferIndex++;
			newSector.bottomExit.first = int(dataBuffer[bufferIndex]);
			bufferIndex++;
			newSector.bottomExit.second = int(dataBuffer[bufferIndex]);
			bufferIndex++;
			newMap.sectors.push_back(newSector);
		}

		bufferIndex++;
		numBreakables = int(dataBuffer[bufferIndex]);
		bufferIndex++;
		bufferIndex++;

		for (int i = 0; i < numBreakables; i++)
		{
			Breakable newBreak;
			newBreak.type = int(dataBuffer[bufferIndex]);
			newBreak.frames = 0;
			bufferIndex++;
			newBreak.left = int(dataBuffer[bufferIndex]) * TILE_SIZE;
			newBreak.right = newBreak.left + TILE_SIZE;
			bufferIndex++;
			newBreak.top = int(dataBuffer[bufferIndex]) * TILE_SIZE;
			newBreak.bottom = newBreak.top + TILE_SIZE;
			newBreak.active = true;
			newBreak.broken = false;
			newMap.breakables.push_back(newBreak);
			bufferIndex++;
		}

		//std::cout << blocks.size() << std::endl;
		stream.close();
		delete[] dataBuffer;
	}

	// begin graphics deceryption
	stream.open(gfxBin.c_str(), std::ifstream::binary);

	if (stream.is_open())
	{
		bufferIndex = 0;
		stream.seekg(0, stream.end);
		bufferLength = stream.tellg();
		char* gfxBuffer = new char[bufferLength];
		stream.seekg(0, stream.beg);
		stream.read(gfxBuffer, bufferLength);
		
		while (int(gfxBuffer[bufferIndex]) != -1)	// get tile sheet filename
		{
			char info = gfxBuffer[bufferIndex];
			gfxName += info;
			bufferIndex++;
		}

		gfxFile = "assets/tiles/" + gfxName + ".png";
		newMap.tileSheet = al_load_bitmap(gfxFile.c_str());
		assert(newMap.tileSheet);
		al_convert_mask_to_alpha(newMap.tileSheet, al_map_rgb(255, 0, 255));
		bufferIndex++;

		for (int i = 0; i < newMap.height; i++)		// store background graphics data
		{
			while (int(gfxBuffer[bufferIndex]) != -1)
			{
				pNum += cNum;
				cNum = int(gfxBuffer[bufferIndex]);
				bufferIndex++;

				for (int j = pNum; j < pNum + cNum; j++)
				{
					Tile newTile;
					newTile.type = 0;
					newTile.graphics = int(gfxBuffer[bufferIndex]);
					newTile.left = j * TILE_SIZE;
					newTile.right = newTile.left + TILE_SIZE;
					newTile.top = i * TILE_SIZE;
					newTile.bottom = newTile.top + TILE_SIZE;
					newTile.slopeLeft = TILE_SIZE;
					newTile.slopeRight = TILE_SIZE;

					newMap.background.push_back(newTile);
				}

				bufferIndex++;
			}

			bufferIndex++;
			pNum = 0;
			cNum = 0;
		}

		while (int(gfxBuffer[bufferIndex]) != -1)
		{
			pNum += cNum;
			cNum = int(gfxBuffer[bufferIndex]);
			bufferIndex++;

			for (int i = pNum; i < pNum + cNum; i++)
			{
				newMap.blocks[i].graphics = int(gfxBuffer[bufferIndex]);
			}

			bufferIndex++;
		}

		mapData.push_back(newMap);
		stream.close();
		delete[] gfxBuffer;
	}
}

void MapHandler::loadNewMap()
{
	curMap = mapData[cMapID];
}

void MapHandler::moveCamera(std::pair<float, float> pos)
{
	int camTopPrev = cam.top;
	int camBottomPrev = cam.bottom;
	int camLeftPrev = cam.left;
	int camRightPrev = cam.right;

	cam.top = pos.second - (SCREEN_H / 2);
	cam.bottom = pos.second + (SCREEN_H / 2);
	cam.left = pos.first - (SCREEN_W / 2);
	cam.right = pos.first + (SCREEN_W / 2);

	if (cam.left <= 0.0)
	{
		cam.left = 0.0;
		cam.right = camRightPrev;
	}

	if (cam.right >= curMap.width * TILE_SIZE)
	{
		cam.right = curMap.width * TILE_SIZE;
		cam.left = camLeftPrev;
	}

	if (cam.top <= 0.0)
	{
		cam.top = 0.0;
		cam.bottom = camBottomPrev;
	}

	if (cam.bottom >= curMap.height * TILE_SIZE)
	{
		cam.bottom = curMap.height * TILE_SIZE;
		cam.top = camTopPrev;
	}
}

void MapHandler::updateMap()
{
	for (std::vector<Breakable>::iterator i = curMap.breakables.begin(); i != curMap.breakables.end(); i++)
	{
		if (i->active && !i->broken)
		{
			i->frames++;

			if (i->frames > 27)
			{
				i->frames = 0;
			}
		}
		else if (i->broken && !i->active)
		{
			i->frames++;

			if (i->frames > 3)
			{
				i->frames = 0;
				i->broken = false;
			}
		}
	}
}

void MapHandler::drawMap()
{
	// begin drawing background tiles
	for (std::vector<Tile>::iterator i = curMap.background.begin(); i != curMap.background.end(); i++)
	{
		if (i->left >= cam.left - 16 || i->right <= cam.right + 16 || i->top >= cam.top - 16 || i->bottom <= cam.bottom + 16)
		{
			al_draw_bitmap_region(curMap.tileSheet, (i->graphics % 8) * 16, (i->graphics / 8) * 16, TILE_SIZE,
				TILE_SIZE, i->left - cam.left, i->top - cam.top, 0);
		}
	}

	// begin drawing collision tiles
	for (std::vector<Tile>::iterator i = curMap.blocks.begin(); i != curMap.blocks.end(); i++)
	{
		if (i->left >= cam.left - 16 || i->right <= cam.right + 16 || i->top >= cam.top - 16 || i->bottom <= cam.bottom + 16)
		{
			al_draw_bitmap_region(curMap.tileSheet, (i->graphics % 8) * 16, (i->graphics / 8) * 16, TILE_SIZE,
				TILE_SIZE, i->left - cam.left, i->top - cam.top, 0);
		}
	}

	// begin drawing breakable objects
	for (std::vector<Breakable>::iterator i = curMap.breakables.begin(); i != curMap.breakables.end(); i++)
	{
		if (i->type == 0)
		{
			if (i->active && !i->broken)
			{
				if (i->frames < 7)
				{
					al_draw_bitmap_region(curMap.tileSheet, 0 * TILE_SIZE, 7 * TILE_SIZE, TILE_SIZE,
						TILE_SIZE, i->left - cam.left, i->top - cam.top, 0);
				}
				else if (i->frames > 6 && i->frames < 14)
				{
					al_draw_bitmap_region(curMap.tileSheet, 1 * TILE_SIZE, 7 * TILE_SIZE, TILE_SIZE,
						TILE_SIZE, i->left - cam.left, i->top - cam.top, 0);
				}
				else if (i->frames > 13 && i->frames < 21)
				{
					al_draw_bitmap_region(curMap.tileSheet, 2 * TILE_SIZE, 7 * TILE_SIZE, TILE_SIZE,
						TILE_SIZE, i->left - cam.left, i->top - cam.top, 0);
				}
				else if (i->frames > 20 && i->frames < 28)
				{
					al_draw_bitmap_region(curMap.tileSheet, 3 * TILE_SIZE, 7 * TILE_SIZE, TILE_SIZE,
						TILE_SIZE, i->left - cam.left, i->top - cam.top, 0);
				}
			}
			else if (i->broken && !i->active)
			{
				if (i->frames < 3)
				{
					al_draw_bitmap_region(curMap.tileSheet, 4 * TILE_SIZE, 7 * TILE_SIZE, TILE_SIZE, TILE_SIZE, i->left - cam.left, i->top - cam.top, 0);
				}
			}
		}
		else if (i->type == 1)
		{
			if (i->active)
			{
				al_draw_bitmap_region(curMap.tileSheet, 6 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE, i->left - cam.left, i->top - cam.top, 0);
			}
		}
	}
}