#include "MapEditor.h"

MapEditor::MapEditor()
{
	title = NULL;
	smallText = NULL;
	largeText = NULL;
	mapText = NULL;

	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{
			typeGrid[i][j] = 0x30;
			wallGrid[i][j] = 0x30;
			floorGrid[i][j] = 0x30;
			skyGrid[i][j] = 0x30;
		}
	}

	saved = false;
	loaded = false;
	msgCounter = 0;
}

MapEditor::~MapEditor()
{
	destroyEditor();
}

bool MapEditor::loadFonts()
{
	title = al_load_ttf_font("assets/fonts/manaspc.ttf", 30, 0);
	smallText = al_load_ttf_font("assets/fonts/retganon.ttf", 24, 0);
	largeText = al_load_ttf_font("assets/fonts/retganon.ttf", 48, 0);
	mapText = al_load_ttf_font("assets/fonts/prstart.ttf", 12, 0);

	if (!title || !smallText || !largeText || !mapText)
	{
		return false;
	}

	return true;
}

void MapEditor::drawTypes()
{
	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{
			std::cout << typeGrid[i][j] << " ";
		}

		std::cout << std::endl;
	}
}

ALLEGRO_COLOR MapEditor::getColor(char value)
{
	ALLEGRO_COLOR color;

	if (value == 0x30) color = al_map_rgb(255, 255, 255);
	else if (value == 0x31) color = al_map_rgb(100, 100, 255);
	else if (value == 0x32) color = al_map_rgb(100, 255, 100);
	else if (value == 0x33) color = al_map_rgb(255, 100, 100);
	else if (value == 0x34) color = al_map_rgb(50, 50, 255);
	else if (value == 0x35) color = al_map_rgb(50, 255, 50);
	else if (value == 0x36) color = al_map_rgb(255, 50, 50);
	else if (value == 0x37) color = al_map_rgb(0, 0, 255);
	else if (value == 0x38) color = al_map_rgb(0, 255, 0);
	else if (value == 0x39) color = al_map_rgb(255, 0, 0);
	else if (value == 0x41) color = al_map_rgb(0, 255, 255);
	else if (value == 0x42) color = al_map_rgb(255, 0, 255);
	else if (value == 0x43) color = al_map_rgb(255, 255, 0);
	else if (value == 0x44) color = al_map_rgb(64, 128, 255);

	return color;
}

int MapEditor::updateScreen(int state, ALLEGRO_EVENT ev, ALLEGRO_DISPLAY* window)
{
	int newState = state;

	if (state == STATE_TYPEEDIT)		// user can click numbers to change their value
	{
		for (int i = 0; i < GRID_SIZE; i++)
		{
			for (int j = 0; j < GRID_SIZE; j++)
			{
				if (ev.mouse.x > 16 + (i * 20) && ev.mouse.x < 36 + (i * 20) &&
					ev.mouse.y > 16 + (j * 20) && ev.mouse.y < 36 + (j * 20))
				{
					typeGrid[i][j]++;

					if (typeGrid[i][j] == 0x3A) typeGrid[i][j] = 0x41;
					else if (typeGrid[i][j] == 0x45) typeGrid[i][j] = 0x30;
				}
			}
		}

		// clicking side boxes changes active grid
		if (ev.mouse.x > 763 && ev.mouse.x < 836 && ev.mouse.y > 81 && ev.mouse.y < 109)
		{
			newState = STATE_WALLEDIT;
		}
		else if (ev.mouse.x > 850 && ev.mouse.x < 923 && ev.mouse.y > 81 && ev.mouse.y < 109)
		{
			newState = STATE_FLOOREDIT;
		}
		else if (ev.mouse.x > 937 && ev.mouse.x < 1010 && ev.mouse.y > 81 && ev.mouse.y < 109)
		{
			newState = STATE_SKYEDIT;
		}
	}
	else if (state == STATE_WALLEDIT)
	{
		for (int i = 0; i < GRID_SIZE; i++)
		{
			for (int j = 0; j < GRID_SIZE; j++)
			{
				if (ev.mouse.x > 16 + (i * 20) && ev.mouse.x < 36 + (i * 20) &&
					ev.mouse.y > 16 + (j * 20) && ev.mouse.y < 36 + (j * 20))
				{
					wallGrid[i][j]++;

					if (wallGrid[i][j] == 0x3A) wallGrid[i][j] = 0x41;
					else if (wallGrid[i][j] == 0x45) wallGrid[i][j] = 0x30;
				}
			}
		}

		if (ev.mouse.x > 676 && ev.mouse.x < 749 && ev.mouse.y > 81 && ev.mouse.y < 109)
		{
			newState = STATE_TYPEEDIT;
		}
		else if (ev.mouse.x > 850 && ev.mouse.x < 923 && ev.mouse.y > 81 && ev.mouse.y < 109)
		{
			newState = STATE_FLOOREDIT;
		}
		else if (ev.mouse.x > 937 && ev.mouse.x < 1010 && ev.mouse.y > 81 && ev.mouse.y < 109)
		{
			newState = STATE_SKYEDIT;
		}
	}
	else if (state == STATE_FLOOREDIT)
	{
		for (int i = 0; i < GRID_SIZE; i++)
		{
			for (int j = 0; j < GRID_SIZE; j++)
			{
				if (ev.mouse.x > 16 + (i * 20) && ev.mouse.x < 36 + (i * 20) &&
					ev.mouse.y > 16 + (j * 20) && ev.mouse.y < 36 + (j * 20))
				{
					floorGrid[i][j]++;

					if (floorGrid[i][j] == 0x3A) floorGrid[i][j] = 0x41;
					else if (floorGrid[i][j] == 0x45) floorGrid[i][j] = 0x30;
				}
			}
		}

		if (ev.mouse.x > 676 && ev.mouse.x < 749 && ev.mouse.y > 81 && ev.mouse.y < 109)
		{
			newState = STATE_TYPEEDIT;
		}
		else if (ev.mouse.x > 763 && ev.mouse.x < 836 && ev.mouse.y > 81 && ev.mouse.y < 109)
		{
			newState = STATE_WALLEDIT;
		}
		else if (ev.mouse.x > 937 && ev.mouse.x < 1010 && ev.mouse.y > 81 && ev.mouse.y < 109)
		{
			newState = STATE_SKYEDIT;
		}
	}
	else if (state == STATE_SKYEDIT)
	{
		for (int i = 0; i < GRID_SIZE; i++)
		{
			for (int j = 0; j < GRID_SIZE; j++)
			{
				if (ev.mouse.x > 16 + (i * 20) && ev.mouse.x < 36 + (i * 20) &&
					ev.mouse.y > 16 + (j * 20) && ev.mouse.y < 36 + (j * 20))
				{
					skyGrid[i][j]++;

					if (skyGrid[i][j] == 0x3A) skyGrid[i][j] = 0x41;
					else if (skyGrid[i][j] == 0x45) skyGrid[i][j] = 0x30;
				}
			}
		}

		if (ev.mouse.x > 676 && ev.mouse.x < 749 && ev.mouse.y > 81 && ev.mouse.y < 109)
		{
			newState = STATE_TYPEEDIT;
		}
		else if (ev.mouse.x > 763 && ev.mouse.x < 836 && ev.mouse.y > 81 && ev.mouse.y < 109)
		{
			newState = STATE_WALLEDIT;
		}
		else if (ev.mouse.x > 850 && ev.mouse.x < 923 && ev.mouse.y > 81 && ev.mouse.y < 109)
		{
			newState = STATE_FLOOREDIT;
		}
	}

	// clicking bottom boxes saves or loads active map file
	if (ev.mouse.x > 676 && ev.mouse.x < 836 && ev.mouse.y > 616 && ev.mouse.y < 661)
	{
		if (!saveMap(window))
		{
			exit(-1);
		}
	}
	else if (ev.mouse.x > 850 && ev.mouse.x < 1010 && ev.mouse.y > 616 && ev.mouse.y < 661)
	{
		if (!loadMap(window))
		{
			exit(-1);
		}
	}

	return newState;
}

void MapEditor::drawScreen(int state)
{
	// draw map grid
	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{
			al_draw_rectangle(16 + (i * 20), 16 + (j * 20), 36 + (i * 20), 36 + (j * 20), al_map_rgb(255, 255, 255), 1.0f);
			
			if (state == STATE_TYPEEDIT)
			{
				al_draw_textf(mapText, getColor(typeGrid[i][j]), 20 + (i * 20), 20 + (j * 20), 0, "%c", typeGrid[i][j]);
			}
			else if (state == STATE_WALLEDIT)
			{
				al_draw_textf(mapText, getColor(wallGrid[i][j]), 20 + (i * 20), 20 + (j * 20), 0, "%c", wallGrid[i][j]);
			}
			else if (state == STATE_FLOOREDIT)
			{
				al_draw_textf(mapText, getColor(floorGrid[i][j]), 20 + (i * 20), 20 + (j * 20), 0, "%c", floorGrid[i][j]);
			}
			else if (state == STATE_SKYEDIT)
			{
				al_draw_textf(mapText, getColor(skyGrid[i][j]), 20 + (i * 20), 20 + (j * 20), 0, "%c", skyGrid[i][j]);
			}

			// nice
			if ((typeGrid[i][j] == 0x34 && typeGrid[i + 1][j] == 0x32 && typeGrid[i + 2][j] == 0x30) ||
				(typeGrid[i][j] == 0x34 && typeGrid[i][j + 1] == 0x32 && typeGrid[i][j + 2] == 0x30) ||
				(typeGrid[i][j] == 0x36 && typeGrid[i + 1][j] == 0x39) ||
				(typeGrid[i][j] == 0x36 && typeGrid[i][j + 1] == 0x39))
			{
				al_draw_text(smallText, al_map_rgb(255, 0, 0), 687, 590, 0, "nice");
			}
		}
	}

	// draw UI
	al_draw_rectangle(12, 12, 660, 660, al_map_rgb(255, 64, 64), 4.0f);
	al_draw_text(title, al_map_rgb(255, 255, 255), 844, 16, ALLEGRO_ALIGN_CENTER, "A Useless Emotion");
	al_draw_text(mapText, al_map_rgb(255, 255, 255), 844, 48, ALLEGRO_ALIGN_CENTER, "M A P   E D I T O R");
	al_draw_line(670, 70, 1015, 70, al_map_rgb(255, 255, 255), 2.0f);

	al_draw_rectangle(675, 80, 750, 110, al_map_rgb(255, 255, 255), 1.0f);
	al_draw_rectangle(762, 80, 837, 110, al_map_rgb(255, 255, 255), 1.0f);
	al_draw_rectangle(849, 80, 924, 110, al_map_rgb(255, 255, 255), 1.0f);
	al_draw_rectangle(936, 80, 1011, 110, al_map_rgb(255, 255, 255), 1.0f);
	al_draw_text(smallText, al_map_rgb(255, 255, 255), 692, 85, 0, "Type");
	al_draw_text(smallText, al_map_rgb(255, 255, 255), 781, 85, 0, "Walls");
	al_draw_text(smallText, al_map_rgb(255, 255, 255), 863, 85, 0, "Floors");
	al_draw_text(smallText, al_map_rgb(255, 255, 255), 955, 85, 0, "Skies");

	al_draw_text(mapText, al_map_rgb(255, 255, 255), 844, 130, ALLEGRO_ALIGN_CENTER, "L E G E N D");
	al_draw_line(770, 150, 917, 150, al_map_rgb(255, 255, 255), 2.0f);
	al_draw_text(mapText, al_map_rgb(255, 255, 255), 844, 170, ALLEGRO_ALIGN_CENTER, "0 ----------- No Wall");
	al_draw_text(mapText, al_map_rgb(255, 255, 255), 844, 190, ALLEGRO_ALIGN_CENTER, "1 -------- Basic Wall");
	al_draw_text(mapText, al_map_rgb(255, 255, 255), 844, 210, ALLEGRO_ALIGN_CENTER, "2 - North Facing Wall");
	al_draw_text(mapText, al_map_rgb(255, 255, 255), 844, 230, ALLEGRO_ALIGN_CENTER, "3 - North / East Wall");
	al_draw_text(mapText, al_map_rgb(255, 255, 255), 844, 250, ALLEGRO_ALIGN_CENTER, "4 - North / West Wall");
	al_draw_text(mapText, al_map_rgb(255, 255, 255), 844, 270, ALLEGRO_ALIGN_CENTER, "5 - South Facing Wall");
	al_draw_text(mapText, al_map_rgb(255, 255, 255), 844, 290, ALLEGRO_ALIGN_CENTER, "6 - South / East Wall");
	al_draw_text(mapText, al_map_rgb(255, 255, 255), 844, 310, ALLEGRO_ALIGN_CENTER, "7 - South / West Wall");
	al_draw_text(mapText, al_map_rgb(255, 255, 255), 844, 330, ALLEGRO_ALIGN_CENTER, "8 -- West Facing Wall");
	al_draw_text(mapText, al_map_rgb(255, 255, 255), 844, 350, ALLEGRO_ALIGN_CENTER, "9 -- East Facing Wall");
	al_draw_text(mapText, al_map_rgb(255, 255, 255), 844, 370, ALLEGRO_ALIGN_CENTER, "A -------------- Door");
	al_draw_text(mapText, al_map_rgb(255, 255, 255), 844, 390, ALLEGRO_ALIGN_CENTER, "B -------------- Exit");
	al_draw_text(mapText, al_map_rgb(255, 255, 255), 844, 410, ALLEGRO_ALIGN_CENTER, "C ------ Solid Object");
	al_draw_text(mapText, al_map_rgb(255, 255, 255), 844, 430, ALLEGRO_ALIGN_CENTER, "D -------- Item Chest");
	al_draw_text(smallText, al_map_rgb(255, 255, 255), 844, 460, ALLEGRO_ALIGN_CENTER, "Applies only to -TYPE- grid.");
	al_draw_text(smallText, al_map_rgb(255, 255, 255), 844, 485, ALLEGRO_ALIGN_CENTER, "-WALL-, -FLOOR-, and -SKY- grids");
	al_draw_text(smallText, al_map_rgb(255, 255, 255), 844, 510, ALLEGRO_ALIGN_CENTER, "only contain texture IDs.");

	if (saved && msgCounter != 0)
	{
		al_draw_text(largeText, al_map_rgb(255, 0, 0), 844, 570, ALLEGRO_ALIGN_CENTER, "Map Saved!");
		msgCounter--;
		if (msgCounter == 0) saved = false;
	}

	if (loaded && msgCounter != 0)
	{
		al_draw_text(largeText, al_map_rgb(255, 0, 0), 844, 570, ALLEGRO_ALIGN_CENTER, "Map Loaded!");
		msgCounter--;
		if (msgCounter == 0) loaded = false;
	}

	al_draw_rectangle(675, 615, 837, 662, al_map_rgb(255, 255, 255), 2.0f);
	al_draw_rectangle(849, 615, 1011, 662, al_map_rgb(255, 255, 255), 2.0f);
	al_draw_text(largeText, al_map_rgb(255, 255, 255), 687, 618, 0, "Save Map");
	al_draw_text(largeText, al_map_rgb(255, 255, 255), 862, 618, 0, "Load Map");
}

bool MapEditor::saveMap(ALLEGRO_DISPLAY* window)
{
	const char* fileName;
	ALLEGRO_FILECHOOSER* fileChooser;
	fileChooser = al_create_native_file_dialog("maps/", "Save Map", "*.*;*.map", ALLEGRO_FILECHOOSER_SAVE);

	if (fileChooser)
	{
		if (al_show_native_file_dialog(window, fileChooser))
		{
			fileName = al_get_native_file_dialog_path(fileChooser, 0);

			if (fileName != NULL)
			{
				std::ofstream mapFile(fileName, std::ios::out | std::ios::binary);
				
				if (mapFile.is_open())
				{
					set32_t(mapFile, (0x47 | (0x4D << 8) | (0x41 << 16) | (0x50 << 24)));
					set32_t(mapFile, (0x00 | (0x00 << 8) | (0x00 << 16) | (0x01 << 24)));

					for (int i = 0; i < GRID_SIZE; i++)
					{
						for (int j = 0; j < GRID_SIZE; j++)
						{
							if (typeGrid[j][i] == 0x30) mapFile.put(0x00);
							else if (typeGrid[j][i] == 0x31) mapFile.put(0x01);
							else if (typeGrid[j][i] == 0x32) mapFile.put(0x02);
							else if (typeGrid[j][i] == 0x33) mapFile.put(0x03);
							else if (typeGrid[j][i] == 0x34) mapFile.put(0x04);
							else if (typeGrid[j][i] == 0x35) mapFile.put(0x05);
							else if (typeGrid[j][i] == 0x36) mapFile.put(0x06);
							else if (typeGrid[j][i] == 0x37) mapFile.put(0x07);
							else if (typeGrid[j][i] == 0x38) mapFile.put(0x08);
							else if (typeGrid[j][i] == 0x39) mapFile.put(0x09);
							else if (typeGrid[j][i] == 0x41) mapFile.put(0x0A);
							else if (typeGrid[j][i] == 0x42) mapFile.put(0x0B);
							else if (typeGrid[j][i] == 0x43) mapFile.put(0x0C);
							else if (typeGrid[j][i] == 0x44) mapFile.put(0x0D);
						}
					}

					for (int i = 0; i < GRID_SIZE; i++)
					{
						for (int j = 0; j < GRID_SIZE; j++)
						{
							if (wallGrid[j][i] == 0x30) mapFile.put(0x00);
							else if (wallGrid[j][i] == 0x31) mapFile.put(0x01);
							else if (wallGrid[j][i] == 0x32) mapFile.put(0x02);
							else if (wallGrid[j][i] == 0x33) mapFile.put(0x03);
							else if (wallGrid[j][i] == 0x34) mapFile.put(0x04);
							else if (wallGrid[j][i] == 0x35) mapFile.put(0x05);
							else if (wallGrid[j][i] == 0x36) mapFile.put(0x06);
							else if (wallGrid[j][i] == 0x37) mapFile.put(0x07);
							else if (wallGrid[j][i] == 0x38) mapFile.put(0x08);
							else if (wallGrid[j][i] == 0x39) mapFile.put(0x09);
							else if (wallGrid[j][i] == 0x41) mapFile.put(0x0A);
							else if (wallGrid[j][i] == 0x42) mapFile.put(0x0B);
							else if (wallGrid[j][i] == 0x43) mapFile.put(0x0C);
							else if (wallGrid[j][i] == 0x44) mapFile.put(0x0D);
						}
					}

					for (int i = 0; i < GRID_SIZE; i++)
					{
						for (int j = 0; j < GRID_SIZE; j++)
						{
							if (floorGrid[j][i] == 0x30) mapFile.put(0x00);
							else if (floorGrid[j][i] == 0x31) mapFile.put(0x01);
							else if (floorGrid[j][i] == 0x32) mapFile.put(0x02);
							else if (floorGrid[j][i] == 0x33) mapFile.put(0x03);
							else if (floorGrid[j][i] == 0x34) mapFile.put(0x04);
							else if (floorGrid[j][i] == 0x35) mapFile.put(0x05);
							else if (floorGrid[j][i] == 0x36) mapFile.put(0x06);
							else if (floorGrid[j][i] == 0x37) mapFile.put(0x07);
							else if (floorGrid[j][i] == 0x38) mapFile.put(0x08);
							else if (floorGrid[j][i] == 0x39) mapFile.put(0x09);
							else if (floorGrid[j][i] == 0x41) mapFile.put(0x0A);
							else if (floorGrid[j][i] == 0x42) mapFile.put(0x0B);
							else if (floorGrid[j][i] == 0x43) mapFile.put(0x0C);
							else if (floorGrid[j][i] == 0x44) mapFile.put(0x0D);
						}
					}

					for (int i = 0; i < GRID_SIZE; i++)
					{
						for (int j = 0; j < GRID_SIZE; j++)
						{
							if (skyGrid[j][i] == 0x30) mapFile.put(0x00);
							else if (skyGrid[j][i] == 0x31) mapFile.put(0x01);
							else if (skyGrid[j][i] == 0x32) mapFile.put(0x02);
							else if (skyGrid[j][i] == 0x33) mapFile.put(0x03);
							else if (skyGrid[j][i] == 0x34) mapFile.put(0x04);
							else if (skyGrid[j][i] == 0x35) mapFile.put(0x05);
							else if (skyGrid[j][i] == 0x36) mapFile.put(0x06);
							else if (skyGrid[j][i] == 0x37) mapFile.put(0x07);
							else if (skyGrid[j][i] == 0x38) mapFile.put(0x08);
							else if (skyGrid[j][i] == 0x39) mapFile.put(0x09);
							else if (skyGrid[j][i] == 0x41) mapFile.put(0x0A);
							else if (skyGrid[j][i] == 0x42) mapFile.put(0x0B);
							else if (skyGrid[j][i] == 0x43) mapFile.put(0x0C);
							else if (skyGrid[j][i] == 0x44) mapFile.put(0x0D);
						}
					}

					mapFile.close();
				}
				else
				{
					al_destroy_native_file_dialog(fileChooser);
					return false;
				}
			}
			else
			{
				al_destroy_native_file_dialog(fileChooser);
				return false;
			}
		}
		else
		{
			al_destroy_native_file_dialog(fileChooser);
			return false;
		}
	}
	else
	{
		al_destroy_native_file_dialog(fileChooser);
		return false;
	}
	
	al_destroy_native_file_dialog(fileChooser);
	saved = true;
	msgCounter = 30;
	return true;
}

bool MapEditor::loadMap(ALLEGRO_DISPLAY* window)
{
	const char* fileName;
	ALLEGRO_FILECHOOSER* fileChooser;
	fileChooser = al_create_native_file_dialog("maps/", "Load Map", "*.*;*.map", 0);

	if (fileChooser)
	{
		if (al_show_native_file_dialog(window, fileChooser))
		{
			fileName = al_get_native_file_dialog_path(fileChooser, 0);

			if (fileName != NULL)
			{
				std::ifstream mapFile(fileName, std::ios::in | std::ios::binary);

				if (mapFile.is_open())
				{
					if (get32_t(mapFile) == (0x47 | (0x4D << 8) | (0x41 << 16) | (0x50 << 24)))
					{
						if (get32_t(mapFile) == (0x00 | (0x00 << 8) | (0x00 << 16) | (0x01 << 24)))
						{
							for (int i = 0; i < GRID_SIZE; i++)
							{
								for (int j = 0; j < GRID_SIZE; j++)
								{
									char next = mapFile.get();

									if (next == 0x00) typeGrid[j][i] = 0x30;
									else if (next == 0x01) typeGrid[j][i] = 0x31;
									else if (next == 0x02) typeGrid[j][i] = 0x32;
									else if (next == 0x03) typeGrid[j][i] = 0x33;
									else if (next == 0x04) typeGrid[j][i] = 0x34;
									else if (next == 0x05) typeGrid[j][i] = 0x35;
									else if (next == 0x06) typeGrid[j][i] = 0x36;
									else if (next == 0x07) typeGrid[j][i] = 0x37;
									else if (next == 0x08) typeGrid[j][i] = 0x38;
									else if (next == 0x09) typeGrid[j][i] = 0x39;
									else if (next == 0x0A) typeGrid[j][i] = 0x41;
									else if (next == 0x0B) typeGrid[j][i] = 0x42;
									else if (next == 0x0C) typeGrid[j][i] = 0x43;
									else if (next == 0x0D) typeGrid[j][i] = 0x44;
								}
							}

							for (int i = 0; i < GRID_SIZE; i++)
							{
								for (int j = 0; j < GRID_SIZE; j++)
								{
									char next = mapFile.get();

									if (next == 0x00) wallGrid[j][i] = 0x30;
									else if (next == 0x01) wallGrid[j][i] = 0x31;
									else if (next == 0x02) wallGrid[j][i] = 0x32;
									else if (next == 0x03) wallGrid[j][i] = 0x33;
									else if (next == 0x04) wallGrid[j][i] = 0x34;
									else if (next == 0x05) wallGrid[j][i] = 0x35;
									else if (next == 0x06) wallGrid[j][i] = 0x36;
									else if (next == 0x07) wallGrid[j][i] = 0x37;
									else if (next == 0x08) wallGrid[j][i] = 0x38;
									else if (next == 0x09) wallGrid[j][i] = 0x39;
									else if (next == 0x0A) wallGrid[j][i] = 0x41;
									else if (next == 0x0B) wallGrid[j][i] = 0x42;
									else if (next == 0x0C) wallGrid[j][i] = 0x43;
									else if (next == 0x0D) wallGrid[j][i] = 0x44;
								}
							}

							for (int i = 0; i < GRID_SIZE; i++)
							{
								for (int j = 0; j < GRID_SIZE; j++)
								{
									char next = mapFile.get();

									if (next == 0x00) floorGrid[j][i] = 0x30;
									else if (next == 0x01) floorGrid[j][i] = 0x31;
									else if (next == 0x02) floorGrid[j][i] = 0x32;
									else if (next == 0x03) floorGrid[j][i] = 0x33;
									else if (next == 0x04) floorGrid[j][i] = 0x34;
									else if (next == 0x05) floorGrid[j][i] = 0x35;
									else if (next == 0x06) floorGrid[j][i] = 0x36;
									else if (next == 0x07) floorGrid[j][i] = 0x37;
									else if (next == 0x08) floorGrid[j][i] = 0x38;
									else if (next == 0x09) floorGrid[j][i] = 0x39;
									else if (next == 0x0A) floorGrid[j][i] = 0x41;
									else if (next == 0x0B) floorGrid[j][i] = 0x42;
									else if (next == 0x0C) floorGrid[j][i] = 0x43;
									else if (next == 0x0D) floorGrid[j][i] = 0x44;
								}
							}

							for (int i = 0; i < GRID_SIZE; i++)
							{
								for (int j = 0; j < GRID_SIZE; j++)
								{
									char next = mapFile.get();

									if (next == 0x00) skyGrid[j][i] = 0x30;
									else if (next == 0x01) skyGrid[j][i] = 0x31;
									else if (next == 0x02) skyGrid[j][i] = 0x32;
									else if (next == 0x03) skyGrid[j][i] = 0x33;
									else if (next == 0x04) skyGrid[j][i] = 0x34;
									else if (next == 0x05) skyGrid[j][i] = 0x35;
									else if (next == 0x06) skyGrid[j][i] = 0x36;
									else if (next == 0x07) skyGrid[j][i] = 0x37;
									else if (next == 0x08) skyGrid[j][i] = 0x38;
									else if (next == 0x09) skyGrid[j][i] = 0x39;
									else if (next == 0x0A) skyGrid[j][i] = 0x41;
									else if (next == 0x0B) skyGrid[j][i] = 0x42;
									else if (next == 0x0C) skyGrid[j][i] = 0x43;
									else if (next == 0x0D) skyGrid[j][i] = 0x44;
								}
							}

							mapFile.close();
						}
						else
						{
							al_destroy_native_file_dialog(fileChooser);
							return false;
						}
					}
					else
					{
						al_destroy_native_file_dialog(fileChooser);
						return false;
					}
				}
				else
				{
					al_destroy_native_file_dialog(fileChooser);
					return false;
				}
			}
			else
			{
				al_destroy_native_file_dialog(fileChooser);
				return false;
			}
		}
		else
		{
			al_destroy_native_file_dialog(fileChooser);
			return false;
		}
	}
	else
	{
		al_destroy_native_file_dialog(fileChooser);
		return false;
	}

	al_destroy_native_file_dialog(fileChooser);
	loaded = true;
	msgCounter = 30;
	return true;
}

void MapEditor::destroyEditor()
{
	al_destroy_font(title);
	al_destroy_font(smallText);
	al_destroy_font(largeText);
	al_destroy_font(mapText);
}