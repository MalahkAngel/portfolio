#pragma once

#include "player.h"
#include "runningstate.h"
#include "jumpingstate.h"
#include "meleestate.h"
#include "rangedstate.h"
#include "evasionstate.h"

class IdleState : public PlayerState
{
	private:
		int aFrames;
	public:
		IdleState() { aFrames = 0; }
		~IdleState() {}

		PlayerState* action(InputHandler input, MapHandler& map, Player& player);
		void update(ALLEGRO_BITMAP* tileSheet, MapHandler& map, Player& player);
};

class TurningState : public PlayerState
{
	private:
		int aFrames;
	public:
		TurningState() { aFrames = 0; }
		~TurningState() {}

		PlayerState* action(InputHandler input, MapHandler& map, Player& player);
		void update(ALLEGRO_BITMAP* tileSheet, MapHandler& map, Player& player);
};

class DuckingState : public PlayerState
{
	public:
		DuckingState() {}
		~DuckingState() {}

		PlayerState* action(InputHandler input, MapHandler& map, Player& player);
		void update(ALLEGRO_BITMAP* tileSheet, MapHandler& map, Player& player);
};

