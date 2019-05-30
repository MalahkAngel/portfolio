#pragma once

class IdleState;

#include "player.h"

class InitJumpState : public PlayerState
{
	public:
		InitJumpState() {}
		~InitJumpState() {}

		PlayerState* action(InputHandler input, MapHandler& map, Player& player);
		void update(ALLEGRO_BITMAP* tileSheet, MapHandler& map, Player& player);
		//void enter();
		//void exit();
};

class InitDblJumpState : public PlayerState
{
	private:
		int aFrames;
	public:
		InitDblJumpState() { aFrames = 0; }
		~InitDblJumpState() {}

		PlayerState* action(InputHandler input, MapHandler& map, Player& player);
		void update(ALLEGRO_BITMAP* tileSheet, MapHandler& map, Player& player);
		//void enter();
		//void exit();
};

class JumpingState : public PlayerState
{
	public:
		JumpingState() {}
		~JumpingState() {}

		PlayerState* action(InputHandler input, MapHandler& map, Player& player);
		void update(ALLEGRO_BITMAP* tileSheet, MapHandler& map, Player& player);
		//void enter();
		//void exit();
};

class FallingState : public PlayerState
{
	public:
		FallingState() {}
		~FallingState() {}

		PlayerState* action(InputHandler input, MapHandler& map, Player& player);
		void update(ALLEGRO_BITMAP* tileSheet, MapHandler& map, Player& player);
		//void enter();
		//void exit();
};