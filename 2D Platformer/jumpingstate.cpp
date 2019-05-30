#include "jumpingstate.h"
#include "idlestate.h"

PlayerState* InitJumpState::action(InputHandler input, MapHandler& map, Player& player)
{
	if (input.getFieldInput(FB_JUMP))
	{
		player.incMomentum();

		if (player.getMomentum() == JUMP_SPEED)
		{
			player.setYSpeed(0);
			return new JumpingState;
		}
	}
	else
	{
		player.setYSpeed(0);
		return new JumpingState;
	}

	if (input.getFieldInput(FB_UP))
	{
		player.setXSpeed(0);
		player.setYSpeed(0);
		return new HitStunState;
	}

	return NULL;
}

void InitJumpState::update(ALLEGRO_BITMAP* tileSheet, MapHandler& map, Player& player)
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

PlayerState* InitDblJumpState::action(InputHandler input, MapHandler& map, Player& player)
{
	aFrames++;

	if (aFrames >= 9)
	{
		aFrames = 0;
		player.setMomentum(JUMP_SPEED);
		player.setYSpeed(0);
		player.setDblJump(true);
		return new JumpingState;
	}

	if (input.getFieldInput(FB_RIGHT))
	{
		if (player.getOrientation())
		{
			player.airLateralCollision(map, player.collideBlock(map, RUN_SPEED, RUN_SPEED, 0, 0));
		}
		else
		{
			player.setOrientation(true);
			player.airLateralCollision(map, player.collideBlock(map, RUN_SPEED, RUN_SPEED, 0, 0));
		}
	}

	if (input.getFieldInput(FB_LEFT))
	{
		if (player.getOrientation())
		{
			player.setOrientation(false);
			player.airLateralCollision(map, player.collideBlock(map, RUN_SPEED, RUN_SPEED, 0, 0));
		}
		else
		{
			player.airLateralCollision(map, player.collideBlock(map, RUN_SPEED, RUN_SPEED, 0, 0));
		}
	}

	if (!input.getFieldInput(FB_LEFT) && !input.getFieldInput(FB_RIGHT))
	{
		player.setXSpeed(0);
	}

	if (input.getFieldInput(FB_UP))
	{
		player.setXSpeed(0);
		player.setYSpeed(0);
		return new AirHitStunState;
	}

	if (input.getFieldInput(FB_M_ATK))
	{
		player.setXSpeed(0);
		player.setYSpeed(0);
		return new MidairMeleeState;
	}

	if (input.getFieldInput(FB_SHOOT))
	{
		player.setXSpeed(0);
		player.setYSpeed(0);
		return new MidairRangedState;
	}

	return NULL;
}

void InitDblJumpState::update(ALLEGRO_BITMAP* tileSheet, MapHandler& map, Player& player)
{
	if (player.getOrientation())
	{
		al_draw_bitmap_region(tileSheet, (1 + (aFrames / 3)) * PLAYER_SIZE, 3 * PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE,
			player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
	}
	else
	{
		al_draw_bitmap_region(tileSheet, (5 + (aFrames / 3)) * PLAYER_SIZE, 3 * PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE,
			player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
	}
}

PlayerState* JumpingState::action(InputHandler input, MapHandler& map, Player& player)
{
	player.airVerticalCollision(map, player.collideBlock(map, 0, 0, -32, -3));

	if (player.getYSpeed() >= 0.0)
	{
		return new FallingState;
	}

	if (input.getFieldInput(FB_RIGHT))
	{
		if (player.getOrientation())
		{
			player.airLateralCollision(map, player.collideBlock(map, RUN_SPEED, RUN_SPEED, 0, 0));
		}
		else
		{
			player.setOrientation(true);
			player.airLateralCollision(map, player.collideBlock(map, RUN_SPEED, RUN_SPEED, 0, 0));
		}
	}

	if (input.getFieldInput(FB_LEFT))
	{
		if (player.getOrientation())
		{
			player.setOrientation(false);
			player.airLateralCollision(map, player.collideBlock(map, RUN_SPEED, RUN_SPEED, 0, 0));
		}
		else
		{
			player.airLateralCollision(map, player.collideBlock(map, RUN_SPEED, RUN_SPEED, 0, 0));
		}
	}

	if (!input.getFieldInput(FB_LEFT) && !input.getFieldInput(FB_RIGHT))
	{
		player.setXSpeed(0);
	}

	if (input.getFieldInput(FB_M_ATK))
	{
		player.setXSpeed(0);
		player.setYSpeed(0);
		return new MidairMeleeState;
	}

	if (input.getFieldInput(FB_SHOOT))
	{
		player.setXSpeed(0);
		player.setYSpeed(0);
		return new MidairRangedState;
	}

	if (input.getFieldInput(FB_UP))
	{
		player.setXSpeed(0);
		player.setYSpeed(0);
		return new AirHitStunState;
	}

	return NULL;
}

void JumpingState::update(ALLEGRO_BITMAP* tileSheet, MapHandler& map, Player& player)
{
	if (player.getOrientation())
	{
		al_draw_bitmap_region(tileSheet, 0, 3 * PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE,
			player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
	}
	else
	{
		al_draw_bitmap_region(tileSheet, 4 * PLAYER_SIZE, 3 * PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE,
			player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
	}
}

PlayerState* FallingState::action(InputHandler input, MapHandler& map, Player& player)
{
	if (player.fallingCollision(map, player.collideBlock(map, 0, 0, 3, 32)))
	{
		player.setDblJump(false);
		return new IdleState;
	}

	if (input.getFieldInput(FB_RIGHT))
	{
		if (player.getOrientation())
		{
			player.airLateralCollision(map, player.collideBlock(map, RUN_SPEED, RUN_SPEED, 0, 0));
		}
		else
		{
			player.setOrientation(true);
			player.airLateralCollision(map, player.collideBlock(map, RUN_SPEED, RUN_SPEED, 0, 0));
		}
	}

	if (input.getFieldInput(FB_LEFT))
	{
		if (player.getOrientation())
		{
			player.setOrientation(false);
			player.airLateralCollision(map, player.collideBlock(map, RUN_SPEED, RUN_SPEED, 0, 0));
		}
		else
		{
			player.airLateralCollision(map, player.collideBlock(map, RUN_SPEED, RUN_SPEED, 0, 0));
		}
	}

	if (!input.getFieldInput(FB_LEFT) && !input.getFieldInput(FB_RIGHT))
	{
		player.setXSpeed(0);
	}

	if (input.getFieldInput(FB_JUMP) && !player.getDblJump())
	{
		return new InitDblJumpState;
	}

	if (input.getFieldInput(FB_M_ATK))
	{
		player.setXSpeed(0);
		player.setYSpeed(0);
		return new MidairMeleeState;
	}

	if (input.getFieldInput(FB_SHOOT))
	{
		player.setXSpeed(0);
		player.setYSpeed(0);
		return new MidairRangedState;
	}

	if (input.getFieldInput(FB_UP))
	{
		player.setXSpeed(0);
		player.setYSpeed(0);
		return new AirHitStunState;
	}

	return NULL;
}

void FallingState::update(ALLEGRO_BITMAP* tileSheet, MapHandler& map, Player& player)
{
	if (player.getOrientation())
	{
		al_draw_bitmap_region(tileSheet, 0, 3 * PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE,
			player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
	}
	else
	{
		al_draw_bitmap_region(tileSheet, 4 * PLAYER_SIZE, 3 * PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE,
			player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
	}
}