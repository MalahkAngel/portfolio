#pragma once

class IdleState;

#include "player.h"

class MeleeState : public PlayerState
{
	private:
		int aFrames;
	public:
		MeleeState() { aFrames = 0; }
		~MeleeState() {}

		PlayerState* action(InputHandler input, MapHandler& map, Player& player);
		void update(ALLEGRO_BITMAP* tileSheet, MapHandler& map, Player& player);
};

class MidairMeleeState : public PlayerState
{
	private:
		int aFrames;
	public:
		MidairMeleeState() { aFrames = 0; }
		~MidairMeleeState() {}

		PlayerState* action(InputHandler input, MapHandler& map, Player& player);
		void update(ALLEGRO_BITMAP* tileSheet, MapHandler& map, Player& player);
};

class DuckingMeleeState : public PlayerState
{
	private:
		int aFrames;
	public:
		DuckingMeleeState() { aFrames = 0; }
		~DuckingMeleeState() {}

		PlayerState* action(InputHandler input, MapHandler& map, Player& player);
		void update(ALLEGRO_BITMAP* tileSheet, MapHandler& map, Player& player);
};

