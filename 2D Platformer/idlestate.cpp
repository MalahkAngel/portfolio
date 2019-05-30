#include "idlestate.h"

PlayerState* IdleState::action(InputHandler input, MapHandler& map, Player& player)
{
	aFrames++;

	if (aFrames >= 40)
	{
		aFrames = 0;
	}

	if (input.getFieldInput(FB_RIGHT))
	{
		if (player.getOrientation())
		{
			return new InitRunState;
		}
		else
		{
			player.setOrientation(true);
			return new TurningState;
		}
	}
	
	if (input.getFieldInput(FB_LEFT))
	{
		if (!player.getOrientation())
		{
			return new InitRunState;
		}
		else
		{
			player.setOrientation(false);
			return new TurningState;
		}
	}

	if (input.getFieldInput(FB_DOWN))
	{
		player.setXSpeed(0);
		player.setYSpeed(0);
		return new DuckingState;
	}

	if (input.getFieldInput(FB_JUMP))
	{
		return new InitJumpState;
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

	if (input.getFieldInput(FB_MAP))
	{
		player.initBlood();
		return new HitStunState;
	}

	player.setXSpeed(0);
	player.setYSpeed(0);
	return NULL;
}

void IdleState::update(ALLEGRO_BITMAP* tileSheet, MapHandler& map, Player& player)
{
	if (player.getOrientation())
	{
		al_draw_bitmap_region(tileSheet, (aFrames / 10) * PLAYER_SIZE, 0, PLAYER_SIZE, PLAYER_SIZE,
			player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
	}
	else
	{
		al_draw_bitmap_region(tileSheet, (4 + (aFrames / 10)) * PLAYER_SIZE, 0, PLAYER_SIZE, PLAYER_SIZE,
			player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
	}
}

PlayerState* TurningState::action(InputHandler input, MapHandler& map, Player& player)
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

	if (input.getFieldInput(FB_DOWN))
	{
		player.setXSpeed(0);
		player.setYSpeed(0);
		return new DuckingState;
	}

	if (input.getFieldInput(FB_JUMP))
	{
		return new InitJumpState;
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
		player.initBlood();
		return new HitStunState;
	}

	if (player.lateralCollision(map, player.collideBlock(map, RUN_SPEED, RUN_SPEED, 0, 0), player.collideBlock(map, 0, 0, 1, 1)))
	{
		return new FallingState;
	}

	return NULL;
}

void TurningState::update(ALLEGRO_BITMAP* tileSheet, MapHandler& map, Player& player)
{
	if (player.getOrientation())
	{
		al_draw_bitmap_region(tileSheet, (7 * 32), 32, PLAYER_SIZE, PLAYER_SIZE,
			player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
	}
	else
	{
		al_draw_bitmap_region(tileSheet, (7 * 32), 64, PLAYER_SIZE, PLAYER_SIZE,
			player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
	}
}

PlayerState* DuckingState::action(InputHandler input, MapHandler& map, Player& player)
{
	if (!input.getFieldInput(FB_DOWN))
	{
		return new IdleState;
	}

	if (player.getOrientation())
	{
		if (input.getFieldInput(FB_LEFT))
		{
			player.setOrientation(false);
		}
	}
	else
	{
		if (input.getFieldInput(FB_RIGHT))
		{
			player.setOrientation(true);
		}
	}

	if (input.getFieldInput(FB_M_ATK))
	{
		return new DuckingMeleeState;
	}

	if (input.getFieldInput(FB_SHOOT))
	{
		return new DuckingRangedState;
	}

	if (input.getFieldInput(FB_EVADE))
	{
		return new EvasionState;
	}

	if (input.getFieldInput(FB_UP))
	{
		player.initBlood();
		return new HitStunState;
	}

	return NULL;
}

void DuckingState::update(ALLEGRO_BITMAP* tileSheet, MapHandler& map, Player& player)
{
	if (player.getOrientation())
	{
		al_draw_bitmap_region(tileSheet, 0, 18 * PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE,
			player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
	}
	else
	{
		al_draw_bitmap_region(tileSheet, 4 * PLAYER_SIZE, 18 * PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE,
			player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
	}
}