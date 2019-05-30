#include "rangedstate.h"
#include "idlestate.h"

PlayerState* RangedState::action(InputHandler input, MapHandler& map, Player& player)
{
	aFrames++;

	if (player.getRangedType() == ONE_HAND_PROJECTILE)
	{
		if (aFrames >= 16)
		{
			aFrames = 0;
			return new IdleState;
		}
	}
	else if (player.getRangedType() == ONE_HAND_PISTOL)
	{
		if (aFrames >= 16)
		{
			aFrames = 0;
			return new IdleState;
		}
	}
	else if (player.getRangedType() == ONE_HAND_MAGNUM)
	{
		if (aFrames >= 24)
		{
			aFrames = 0;
			return new IdleState;
		}
	}
	else if (player.getRangedType() == TWO_HAND_12_GAUGE)
	{
		if (aFrames >= 48)
		{
			aFrames = 0;
			return new IdleState;
		}
	}
	else if (player.getRangedType() == TWO_HAND_COMBAT_SHOTGUN)
	{
		if (aFrames >= 32)
		{
			aFrames = 0;
			return new IdleState;
		}
	}

	if (input.getFieldInput(FB_UP))
	{
		return new HitStunState;
	}

	return NULL;
}

void RangedState::update(ALLEGRO_BITMAP* tileSheet, MapHandler& map, Player& player)
{
	if (player.getOrientation())
	{
		if (player.getRangedType() == ONE_HAND_PROJECTILE)
		{
			if (aFrames < 4 && aFrames >= 0)
			{
				al_draw_bitmap_region(tileSheet, 0 * PLAYER_SIZE, (7 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
					player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
			}
			else if (aFrames < 8 && aFrames >= 4)
			{
				al_draw_bitmap_region(tileSheet, 1 * PLAYER_SIZE, (7 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
					player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
			}
			else if (aFrames < 16 && aFrames >= 8)
			{
				al_draw_bitmap_region(tileSheet, 2 * PLAYER_SIZE, (7 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
					player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
			}
		}
		else if (player.getRangedType() == ONE_HAND_PISTOL)
		{
			al_draw_bitmap_region(tileSheet, (aFrames / 4) * PLAYER_SIZE, (9 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (player.getRangedType() == ONE_HAND_MAGNUM)
		{
			al_draw_bitmap_region(tileSheet, (4 + (aFrames / 6)) * PLAYER_SIZE, (9 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (player.getRangedType() == TWO_HAND_12_GAUGE)
		{
			al_draw_bitmap_region(tileSheet, (aFrames / 6) * PLAYER_SIZE, (11 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (player.getRangedType() == TWO_HAND_COMBAT_SHOTGUN)
		{
			al_draw_bitmap_region(tileSheet, (aFrames / 4) * PLAYER_SIZE, (12 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
	}
	else
	{
		if (player.getRangedType() == ONE_HAND_PROJECTILE)
		{
			if (aFrames < 4 && aFrames >= 0)
			{
				al_draw_bitmap_region(tileSheet, 0 * PLAYER_SIZE, (8 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
					player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
			}
			else if (aFrames < 8 && aFrames >= 4)
			{
				al_draw_bitmap_region(tileSheet, 1 * PLAYER_SIZE, (8 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
					player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
			}
			else if (aFrames < 16 && aFrames >= 8)
			{
				al_draw_bitmap_region(tileSheet, 2 * PLAYER_SIZE, (8 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
					player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
			}
		}
		else if (player.getRangedType() == ONE_HAND_PISTOL)
		{
			al_draw_bitmap_region(tileSheet, (aFrames / 4) * PLAYER_SIZE, (10 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (player.getRangedType() == ONE_HAND_MAGNUM)
		{
			al_draw_bitmap_region(tileSheet, (4 + (aFrames / 6)) * PLAYER_SIZE, (10 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (player.getRangedType() == TWO_HAND_12_GAUGE)
		{
			al_draw_bitmap_region(tileSheet, (aFrames / 6) * PLAYER_SIZE, (13 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (player.getRangedType() == TWO_HAND_COMBAT_SHOTGUN)
		{
			al_draw_bitmap_region(tileSheet, (aFrames / 4) * PLAYER_SIZE, (14 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
	}
}

PlayerState* MidairRangedState::action(InputHandler input, MapHandler& map, Player& player)
{
	aFrames++;

	if (player.getRangedType() == ONE_HAND_PROJECTILE)
	{
		if (aFrames >= 16)
		{
			aFrames = 0;
			return new FallingState;
		}
	}
	else if (player.getRangedType() == ONE_HAND_PISTOL)
	{
		if (aFrames >= 16)
		{
			aFrames = 0;
			return new FallingState;
		}
	}
	else if (player.getRangedType() == ONE_HAND_MAGNUM)
	{
		if (aFrames >= 24)
		{
			aFrames = 0;
			return new FallingState;
		}
	}

	if (input.getFieldInput(FB_UP))
	{
		player.setXSpeed(0);
		player.setYSpeed(0);
		return new AirHitStunState;
	}

	return NULL;
}

void MidairRangedState::update(ALLEGRO_BITMAP* tileSheet, MapHandler& map, Player& player)
{
	if (player.getOrientation())
	{
		if (player.getRangedType() == ONE_HAND_PROJECTILE)
		{
			if (aFrames < 4 && aFrames >= 0)
			{
				al_draw_bitmap_region(tileSheet, 0 * PLAYER_SIZE, (15 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
					player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
			}
			else if (aFrames < 8 && aFrames >= 4)
			{
				al_draw_bitmap_region(tileSheet, 1 * PLAYER_SIZE, (15 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
					player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
			}
			else if (aFrames < 16 && aFrames >= 8)
			{
				al_draw_bitmap_region(tileSheet, 2 * PLAYER_SIZE, (15 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
					player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
			}
		}
		else if (player.getRangedType() == ONE_HAND_PISTOL)
		{
			al_draw_bitmap_region(tileSheet, (aFrames / 4) * PLAYER_SIZE, (16 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (player.getRangedType() == ONE_HAND_MAGNUM)
		{
			al_draw_bitmap_region(tileSheet, (4 + (aFrames / 6)) * PLAYER_SIZE, (16 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
	}
	else
	{
		if (player.getRangedType() == ONE_HAND_PROJECTILE)
		{
			if (aFrames < 4 && aFrames >= 0)
			{
				al_draw_bitmap_region(tileSheet, 4 * PLAYER_SIZE, (15 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
					player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
			}
			else if (aFrames < 8 && aFrames >= 4)
			{
				al_draw_bitmap_region(tileSheet, 5 * PLAYER_SIZE, (15 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
					player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
			}
			else if (aFrames < 16 && aFrames >= 8)
			{
				al_draw_bitmap_region(tileSheet, 6 * PLAYER_SIZE, (15 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
					player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
			}
		}
		else if (player.getRangedType() == ONE_HAND_PISTOL)
		{
			al_draw_bitmap_region(tileSheet, (aFrames / 4) * PLAYER_SIZE, (17 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (player.getRangedType() == ONE_HAND_MAGNUM)
		{
			al_draw_bitmap_region(tileSheet, (4 + (aFrames / 6)) * PLAYER_SIZE, (17 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
	}
}

PlayerState* DuckingRangedState::action(InputHandler input, MapHandler& map, Player& player)
{
	aFrames++;

	if (player.getRangedType() == ONE_HAND_PROJECTILE)
	{
		if (aFrames >= 16)
		{
			aFrames = 0;
			return new DuckingState;
		}
	}
	else if (player.getRangedType() == ONE_HAND_PISTOL)
	{
		if (aFrames >= 16)
		{
			aFrames = 0;
			return new DuckingState;
		}
	}
	else if (player.getRangedType() == ONE_HAND_MAGNUM)
	{
		if (aFrames >= 24)
		{
			aFrames = 0;
			return new DuckingState;
		}
	}

	if (input.getFieldInput(FB_UP))
	{
		return new HitStunState;
	}

	return NULL;
}

void DuckingRangedState::update(ALLEGRO_BITMAP* tileSheet, MapHandler& map, Player& player)
{
	if (player.getOrientation())
	{
		if (player.getRangedType() == ONE_HAND_PROJECTILE)
		{
			if (aFrames < 4 && aFrames >= 0)
			{
				al_draw_bitmap_region(tileSheet, 0 * PLAYER_SIZE, (18 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
					player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
			}
			else if (aFrames < 8 && aFrames >= 4)
			{
				al_draw_bitmap_region(tileSheet, 1 * PLAYER_SIZE, (18 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
					player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
			}
			else if (aFrames < 16 && aFrames >= 8)
			{
				al_draw_bitmap_region(tileSheet, 2 * PLAYER_SIZE, (18 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
					player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
			}
		}
		else if (player.getRangedType() == ONE_HAND_PISTOL)
		{
			al_draw_bitmap_region(tileSheet, (aFrames / 4) * PLAYER_SIZE, (20 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (player.getRangedType() == ONE_HAND_MAGNUM)
		{
			al_draw_bitmap_region(tileSheet, (4 + (aFrames / 6)) * PLAYER_SIZE, (20 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
	}
	else
	{
		if (player.getRangedType() == ONE_HAND_PROJECTILE)
		{
			if (aFrames < 4 && aFrames >= 0)
			{
				al_draw_bitmap_region(tileSheet, 4 * PLAYER_SIZE, (18 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
					player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
			}
			else if (aFrames < 8 && aFrames >= 4)
			{
				al_draw_bitmap_region(tileSheet, 5 * PLAYER_SIZE, (18 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
					player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
			}
			else if (aFrames < 16 && aFrames >= 8)
			{
				al_draw_bitmap_region(tileSheet, 6 * PLAYER_SIZE, (18 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
					player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
			}
		}
		else if (player.getRangedType() == ONE_HAND_PISTOL)
		{
			al_draw_bitmap_region(tileSheet, (aFrames / 4) * PLAYER_SIZE, (21 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (player.getRangedType() == ONE_HAND_MAGNUM)
		{
			al_draw_bitmap_region(tileSheet, (4 + (aFrames / 6)) * PLAYER_SIZE, (21 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
	}
}