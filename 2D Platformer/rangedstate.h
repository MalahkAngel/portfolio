#pragma once

class IdleState;

#include "player.h"

class RangedState : public PlayerState
{
	private:
		int aFrames;
	public:
		RangedState() { aFrames = 0; }
		~RangedState() {}

		PlayerState* action(InputHandler input, MapHandler& map, Player& player);
		void update(ALLEGRO_BITMAP* tileSheet, MapHandler& map, Player& player);
};

class MidairRangedState : public PlayerState
{
private:
	int aFrames;
public:
	MidairRangedState() { aFrames = 0; }
	~MidairRangedState() {}

	PlayerState* action(InputHandler input, MapHandler& map, Player& player);
	void update(ALLEGRO_BITMAP* tileSheet, MapHandler& map, Player& player);
};

class DuckingRangedState : public PlayerState
{
private:
	int aFrames;
public:
	DuckingRangedState() { aFrames = 0; }
	~DuckingRangedState() {}

	PlayerState* action(InputHandler input, MapHandler& map, Player& player);
	void update(ALLEGRO_BITMAP* tileSheet, MapHandler& map, Player& player);
};

