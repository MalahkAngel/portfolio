#include "main.h"
#include "PsuedoEngine.h"

/* Psuedo Engine Map Editor
===========================
A visual map editor for the Psuedo Engine powering the game "A Useless Emotion".
Creates 32 x 32 map grids containing wall type data and texture IDs for walls,
floors, and ceiling tiles by allowing a user to click individual nodes. Actual
texture data is loaded from external scripts in the main game engine. Texture IDs
defined within this utility only point to which loaded texture to use.
Accepts and returns *.map files. */

int main()
{
	PsuedoEngine engine;			// init Allegro 5 wrapper
	engine.initAllegro();			// init Allegro 5 add-ons
	engine.createDisplay();			// activate and init display
	engine.createGameFlow();		// activate timer and event queue

	while (!engine.processEvents())		// handle input and other events
	{
		if (engine.isUpdating())		// run after event processing
		{
			engine.updateScreen();		// draw to screen
		}
	}

	return 0;
}