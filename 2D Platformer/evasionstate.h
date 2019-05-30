#pragma once

class IdleState;

#include "player.h"

class EvasionState : public PlayerState
{
private:
	int aFrames;
public:
	EvasionState() { aFrames = 0; }
	~EvasionState() {}

	PlayerState* action(InputHandler input, MapHandler& map, Player& player);
	void update(ALLEGRO_BITMAP* tileSheet, MapHandler& map, Player& player);
};

class HitStunState : public PlayerState
{
private:
	int aFrames;
public:
	HitStunState() { aFrames = 0; }
	~HitStunState() {}

	PlayerState* action(InputHandler input, MapHandler& map, Player& player);
	void update(ALLEGRO_BITMAP* tileSheet, MapHandler& map, Player& player);
};

class AirHitStunState : public PlayerState
{
private:
	int aFrames;
public:
	AirHitStunState() { aFrames = 0; }
	~AirHitStunState() {}

	PlayerState* action(InputHandler input, MapHandler& map, Player& player);
	void update(ALLEGRO_BITMAP* tileSheet, MapHandler& map, Player& player);
};

