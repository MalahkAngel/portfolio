#include "runningstate.h"
#include "idlestate.h"

PlayerState* InitRunState::action(InputHandler input, MapHandler& map, Player& player)
{
	aFrames++;

	if (aFrames >= 6)
	{
		return new RunningState;
	}

	if (!input.getFieldInput(FB_RIGHT) && !input.getFieldInput(FB_LEFT))
	{
		return new IdleState;
	}

	if (input.getFieldInput(FB_JUMP))
	{
		return new InitJumpState;
	}

	if (input.getFieldInput(FB_DOWN))
	{
		player.setXSpeed(0);
		player.setYSpeed(0);
		return new DuckingState;
	}

	if (input.getFieldInput(FB_M_ATK))
	{
		player.setXSpeed(0);
		player.setYSpeed(0);
		return new MeleeState;
	}

	if (input.getFieldInput(FB_SHOOT))
	{
		player.setXSpeed(0);
		player.setYSpeed(0);
		return new RangedState;
	}

	if (input.getFieldInput(FB_EVADE))
	{
		return new EvasionState;
	}

	if (input.getFieldInput(FB_UP))
	{
		return new HitStunState;
	}

	if (player.lateralCollision(map, player.collideBlock(map, RUN_SPEED, RUN_SPEED, 0, 0), player.collideBlock(map, 0, 0, 1, 1)))
	{
		return new FallingState;
	}

	return NULL;
}

void InitRunState::update(ALLEGRO_BITMAP* tileSheet, MapHandler& map, Player& player)
{
	if (player.getOrientation())
	{
		al_draw_bitmap_region(tileSheet, 0, 32, PLAYER_SIZE, PLAYER_SIZE,
			player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
	}
	else
	{
		al_draw_bitmap_region(tileSheet, 0, 64, PLAYER_SIZE, PLAYER_SIZE,
			player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
	}
}

PlayerState* RunningState::action(InputHandler input, MapHandler& map, Player& player)
{
	aFrames++;

	if (aFrames >= 36)
	{
		aFrames = 0;
	}

	if (!input.getFieldInput(FB_RIGHT) && !input.getFieldInput(FB_LEFT))
	{
		return new IdleState;
	}

	if (input.getFieldInput(FB_JUMP))
	{
		return new InitJumpState;
	}

	if (input.getFieldInput(FB_DOWN))
	{
		player.setXSpeed(0);
		player.setYSpeed(0);
		return new DuckingState;
	}

	if (input.getFieldInput(FB_M_ATK))
	{
		player.setXSpeed(0);
		player.setYSpeed(0);
		return new MeleeState;
	}

	if (input.getFieldInput(FB_SHOOT))
	{
		player.setXSpeed(0);
		player.setYSpeed(0);
		return new RangedState;
	}

	if (input.getFieldInput(FB_EVADE))
	{
		return new EvasionState;
	}

	if (input.getFieldInput(FB_UP))
	{
		return new HitStunState;
	}

	if (player.lateralCollision(map, player.collideBlock(map, RUN_SPEED, RUN_SPEED, 0, 0), player.collideBlock(map, 0, 0, 1, 1)))
	{
		return new FallingState;
	}

	return NULL;
}

void RunningState::update(ALLEGRO_BITMAP* tileSheet, MapHandler& map, Player& player)
{
	if (player.getOrientation())
	{
		al_draw_bitmap_region(tileSheet, ((1 + aFrames) / 6) * PLAYER_SIZE, 32, PLAYER_SIZE, PLAYER_SIZE,
			player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
	}
	else
	{
		al_draw_bitmap_region(tileSheet, ((1 + aFrames) / 6) * PLAYER_SIZE, 64, PLAYER_SIZE, PLAYER_SIZE,
			player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
	}
}