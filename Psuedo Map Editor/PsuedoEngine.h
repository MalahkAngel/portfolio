#pragma once
#include "main.h"
#include "MapEditor.h"

struct Display
{
	ALLEGRO_DISPLAY* window;
};

struct GameFlow
{
	ALLEGRO_EVENT_QUEUE* queue;
	ALLEGRO_TIMER* timer;
	bool quit, update;
};

class PsuedoEngine
{
private:
	Display display;
	GameFlow flow;
	MapEditor editor;
	int appState;

public:
	PsuedoEngine();
	~PsuedoEngine();

	void initAllegro();
	void createDisplay();
	void createGameFlow();

	bool isUpdating() { return flow.update && al_event_queue_is_empty(flow.queue); }

	bool processEvents();
	void updateScreen();
};

