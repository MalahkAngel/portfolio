#pragma once

class IdleState;
class JumpingState;
class MeleeState;

#include "player.h"

class InitRunState : public PlayerState
{
private:
	int aFrames;
public:
	InitRunState() { aFrames = 0; }
	~InitRunState() {}

	PlayerState* action(InputHandler input, MapHandler& map, Player& player);
	void update(ALLEGRO_BITMAP* tileSheet, MapHandler& map, Player& player);
	//void enter();
	//void exit();
};

class RunningState : public PlayerState
{
	private:
		int aFrames;
	public:
		RunningState() { aFrames = 0; }
		~RunningState() {}

		void lateralCollision(int xBlock, int yBlock, Player& player);

		PlayerState* action(InputHandler input, MapHandler& map, Player& player);
		void update(ALLEGRO_BITMAP* tileSheet, MapHandler& map, Player& player);
		//void enter();
		//void exit();
};