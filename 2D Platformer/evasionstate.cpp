#include "evasionstate.h"
#include "idlestate.h"

PlayerState* EvasionState::action(InputHandler input, MapHandler& map, Player& player)
{
	if (aFrames == 0)
	{
		if (player.getOrientation())
		{
			player.setOrientation(false);
		}
		else
		{
			player.setOrientation(true);
		}
	}

	aFrames++;
	player.incIFrames();

	if (aFrames >= 32)
	{
		if (player.getOrientation())
		{
			player.setOrientation(false);
		}
		else
		{
			player.setOrientation(true);
		}

		aFrames = 0;
		player.clrIFrames();
		return new IdleState;
	}

	if (input.getFieldInput(FB_DOWN))
	{
		if (player.getOrientation())
		{
			player.setOrientation(false);
		}
		else
		{
			player.setOrientation(true);
		}

		player.setXSpeed(0);
		player.setYSpeed(0);
		return new DuckingState;
	}

	if (input.getFieldInput(FB_JUMP))
	{
		if (player.getOrientation())
		{
			player.setOrientation(false);
		}
		else
		{
			player.setOrientation(true);
		}

		player.setXSpeed(0);
		player.setYSpeed(0);
		return new InitJumpState;
	}

	if (player.lateralCollision(map, player.collideBlock(map, RUN_SPEED, RUN_SPEED, 0, 0), player.collideBlock(map, 0, 0, 1, 1)))
	{
		return new FallingState;
	}

	return NULL;
}

void EvasionState::update(ALLEGRO_BITMAP* tileSheet, MapHandler& map, Player& player)
{
	if (!player.getOrientation())
	{
		al_draw_bitmap_region(tileSheet, (aFrames / 4) * PLAYER_SIZE, 4 * PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE,
			player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
	}
	else
	{
		al_draw_bitmap_region(tileSheet, (aFrames / 4) * PLAYER_SIZE, 5 * PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE,
			player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
	}
}

PlayerState* HitStunState::action(InputHandler input, MapHandler& map, Player& player)
{
	if (aFrames == 0)
	{
		if (player.getOrientation())
		{
			player.setOrientation(false);
		}
		else
		{
			player.setOrientation(true);
		}
	}

	aFrames++;
	player.incIFrames();

	if (aFrames >= 20)
	{
		if (player.getOrientation())
		{
			player.setOrientation(false);
		}
		else
		{
			player.setOrientation(true);
		}

		aFrames = 0;
		player.clrIFrames();
		return new IdleState;
	}

	if (player.lateralCollision(map, player.collideBlock(map, RUN_SPEED, RUN_SPEED, 0, 0), player.collideBlock(map, 0, 0, 1, 1)))
	{
		return new FallingState;
	}

	return NULL;
}

void HitStunState::update(ALLEGRO_BITMAP* tileSheet, MapHandler& map, Player& player)
{
	if (!player.getOrientation())
	{
		if (aFrames > 0 && aFrames <= 4)
		{
			al_draw_bitmap_region(tileSheet, 0 * PLAYER_SIZE, 6 * PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (aFrames > 4 && aFrames <= 8)
		{
			al_draw_bitmap_region(tileSheet, 1 * PLAYER_SIZE, 6 * PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (aFrames > 8 && aFrames <= 10)
		{
			al_draw_bitmap_region(tileSheet, 2 * PLAYER_SIZE, 6 * PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (aFrames > 10 && aFrames <= 12)
		{
			al_draw_bitmap_region(tileSheet, 3 * PLAYER_SIZE, 6 * PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (aFrames > 12 && aFrames <= 14)
		{
			al_draw_bitmap_region(tileSheet, 2 * PLAYER_SIZE, 6 * PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (aFrames > 14 && aFrames <= 16)
		{
			al_draw_bitmap_region(tileSheet, 3 * PLAYER_SIZE, 6 * PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (aFrames > 16 && aFrames <= 18)
		{
			al_draw_bitmap_region(tileSheet, 2 * PLAYER_SIZE, 6 * PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (aFrames > 18 && aFrames <= 20)
		{
			al_draw_bitmap_region(tileSheet, 3 * PLAYER_SIZE, 6 * PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
	}
	else
	{
		if (aFrames > 0 && aFrames <= 4)
		{
			al_draw_bitmap_region(tileSheet, 4 * PLAYER_SIZE, 6 * PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (aFrames > 4 && aFrames <= 8)
		{
			al_draw_bitmap_region(tileSheet, 5 * PLAYER_SIZE, 6 * PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (aFrames > 8 && aFrames <= 10)
		{
			al_draw_bitmap_region(tileSheet, 6 * PLAYER_SIZE, 6 * PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (aFrames > 10 && aFrames <= 12)
		{
			al_draw_bitmap_region(tileSheet, 7 * PLAYER_SIZE, 6 * PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (aFrames > 12 && aFrames <= 14)
		{
			al_draw_bitmap_region(tileSheet, 6 * PLAYER_SIZE, 6 * PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (aFrames > 14 && aFrames <= 16)
		{
			al_draw_bitmap_region(tileSheet, 7 * PLAYER_SIZE, 6 * PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (aFrames > 16 && aFrames <= 18)
		{
			al_draw_bitmap_region(tileSheet, 6 * PLAYER_SIZE, 6 * PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (aFrames > 18 && aFrames <= 20)
		{
			al_draw_bitmap_region(tileSheet, 7 * PLAYER_SIZE, 6 * PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
	}
}

PlayerState* AirHitStunState::action(InputHandler input, MapHandler& map, Player& player)
{
	if (aFrames == 0)
	{
		if (player.getOrientation())
		{
			player.setOrientation(false);
		}
		else
		{
			player.setOrientation(true);
		}
	}

	aFrames++;
	player.incIFrames();

	if (aFrames >= 20)
	{
		if (player.getOrientation())
		{
			player.setOrientation(false);
		}
		else
		{
			player.setOrientation(true);
		}

		aFrames = 0;
		player.clrIFrames();
		return new FallingState;
	}

	player.airLateralCollision(map, player.collideBlock(map, RUN_SPEED, RUN_SPEED, 0, 0));

	return NULL;
}

void AirHitStunState::update(ALLEGRO_BITMAP* tileSheet, MapHandler& map, Player& player)
{
	if (!player.getOrientation())
	{
		if (aFrames > 0 && aFrames <= 4)
		{
			al_draw_bitmap_region(tileSheet, 0 * PLAYER_SIZE, 6 * PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (aFrames > 4 && aFrames <= 8)
		{
			al_draw_bitmap_region(tileSheet, 1 * PLAYER_SIZE, 6 * PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (aFrames > 8 && aFrames <= 10)
		{
			al_draw_bitmap_region(tileSheet, 2 * PLAYER_SIZE, 6 * PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (aFrames > 10 && aFrames <= 12)
		{
			al_draw_bitmap_region(tileSheet, 3 * PLAYER_SIZE, 6 * PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (aFrames > 12 && aFrames <= 14)
		{
			al_draw_bitmap_region(tileSheet, 2 * PLAYER_SIZE, 6 * PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (aFrames > 14 && aFrames <= 16)
		{
			al_draw_bitmap_region(tileSheet, 3 * PLAYER_SIZE, 6 * PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (aFrames > 16 && aFrames <= 18)
		{
			al_draw_bitmap_region(tileSheet, 2 * PLAYER_SIZE, 6 * PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (aFrames > 18 && aFrames <= 20)
		{
			al_draw_bitmap_region(tileSheet, 3 * PLAYER_SIZE, 6 * PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
	}
	else
	{
		if (aFrames > 0 && aFrames <= 4)
		{
			al_draw_bitmap_region(tileSheet, 4 * PLAYER_SIZE, 6 * PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (aFrames > 4 && aFrames <= 8)
		{
			al_draw_bitmap_region(tileSheet, 5 * PLAYER_SIZE, 6 * PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (aFrames > 8 && aFrames <= 10)
		{
			al_draw_bitmap_region(tileSheet, 6 * PLAYER_SIZE, 6 * PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (aFrames > 10 && aFrames <= 12)
		{
			al_draw_bitmap_region(tileSheet, 7 * PLAYER_SIZE, 6 * PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (aFrames > 12 && aFrames <= 14)
		{
			al_draw_bitmap_region(tileSheet, 6 * PLAYER_SIZE, 6 * PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (aFrames > 14 && aFrames <= 16)
		{
			al_draw_bitmap_region(tileSheet, 7 * PLAYER_SIZE, 6 * PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (aFrames > 16 && aFrames <= 18)
		{
			al_draw_bitmap_region(tileSheet, 6 * PLAYER_SIZE, 6 * PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (aFrames > 18 && aFrames <= 20)
		{
			al_draw_bitmap_region(tileSheet, 7 * PLAYER_SIZE, 6 * PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
	}
}