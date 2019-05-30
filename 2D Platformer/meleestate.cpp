#include "meleestate.h"
#include "idlestate.h"

PlayerState* MeleeState::action(InputHandler input, MapHandler& map, Player& player)
{
	aFrames++;

	if (player.getMeleeType() == ONE_HAND_DAGGER)
	{
		if (aFrames >= 16)
		{
			aFrames = 0;
			return new IdleState;
		}
	}
	else if (player.getMeleeType() == ONE_HAND_SWORD)
	{
		if (aFrames >= 24)
		{
			aFrames = 0;
			return new IdleState;
		}
	}
	else if (player.getMeleeType() == ONE_HAND_AXE)
	{
		if (aFrames >= 32)
		{
			aFrames = 0;
			return new IdleState;
		}
	}
	else if (player.getMeleeType() == ONE_HAND_BLUNT)
	{
		if (aFrames >= 24)
		{
			aFrames = 0;
			return new IdleState;
		}
	}
	else if (player.getMeleeType() == TWO_HAND_SWORD)
	{
		if (aFrames >= 32)
		{
			aFrames = 0;
			return new IdleState;
		}
	}
	else if (player.getMeleeType() == TWO_HAND_AXE)
	{
		if (aFrames >= 36)
		{
			aFrames = 0;
			return new IdleState;
		}
	}
	else if (player.getMeleeType() == TWO_HAND_BLUNT)
	{
		if (aFrames >= 32)
		{
			aFrames = 0;
			return new IdleState;
		}
	}
	else if (player.getMeleeType() == TWO_HAND_KATANA)
	{
		if (aFrames >= 24)
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

void MeleeState::update(ALLEGRO_BITMAP* tileSheet, MapHandler& map, Player& player)
{
	if (player.getOrientation())
	{
		if (player.getMeleeType() == ONE_HAND_DAGGER)
		{
			al_draw_bitmap_region(tileSheet, (aFrames / 4) * PLAYER_SIZE, (7 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (player.getMeleeType() == ONE_HAND_SWORD)
		{
			al_draw_bitmap_region(tileSheet, (aFrames / 6) * PLAYER_SIZE, (7 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (player.getMeleeType() == ONE_HAND_AXE)
		{
			al_draw_bitmap_region(tileSheet, (aFrames / 8) * PLAYER_SIZE, (7 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (player.getMeleeType() == ONE_HAND_BLUNT)
		{
			al_draw_bitmap_region(tileSheet, (aFrames / 6) * PLAYER_SIZE, (7 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (player.getMeleeType() == TWO_HAND_SWORD)
		{
			al_draw_bitmap_region(tileSheet, (4 + (aFrames / 8)) * PLAYER_SIZE, (7 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (player.getMeleeType() == TWO_HAND_AXE)
		{
			al_draw_bitmap_region(tileSheet, (4 + (aFrames / 9)) * PLAYER_SIZE, (7 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (player.getMeleeType() == TWO_HAND_BLUNT)
		{
			al_draw_bitmap_region(tileSheet, (4 + (aFrames / 8)) * PLAYER_SIZE, (7 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (player.getMeleeType() == TWO_HAND_KATANA)
		{
			al_draw_bitmap_region(tileSheet, (4 + (aFrames / 6)) * PLAYER_SIZE, (7 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
	}
	else
	{
		if (player.getMeleeType() == ONE_HAND_DAGGER)
		{
			al_draw_bitmap_region(tileSheet, (aFrames / 4) * PLAYER_SIZE, (8 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (player.getMeleeType() == ONE_HAND_SWORD)
		{
			al_draw_bitmap_region(tileSheet, (aFrames / 6) * PLAYER_SIZE, (8 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (player.getMeleeType() == ONE_HAND_AXE)
		{
			al_draw_bitmap_region(tileSheet, (aFrames / 8) * PLAYER_SIZE, (8 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (player.getMeleeType() == ONE_HAND_BLUNT)
		{
			al_draw_bitmap_region(tileSheet, (aFrames / 6) * PLAYER_SIZE, (8 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (player.getMeleeType() == TWO_HAND_SWORD)
		{
			al_draw_bitmap_region(tileSheet, (4 + (aFrames) / 8) * PLAYER_SIZE, (8 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (player.getMeleeType() == TWO_HAND_AXE)
		{
			al_draw_bitmap_region(tileSheet, (4 + (aFrames / 9)) * PLAYER_SIZE, (8 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (player.getMeleeType() == TWO_HAND_BLUNT)
		{
			al_draw_bitmap_region(tileSheet, (4 + (aFrames / 8)) * PLAYER_SIZE, (8 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (player.getMeleeType() == TWO_HAND_KATANA)
		{
			al_draw_bitmap_region(tileSheet, (4 + (aFrames / 6)) * PLAYER_SIZE, (8 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
	}
}

PlayerState* MidairMeleeState::action(InputHandler input, MapHandler& map, Player& player)
{
	aFrames++;

	if (player.getMeleeType() == ONE_HAND_DAGGER)
	{
		if (aFrames >= 16)
		{
			aFrames = 0;
			return new FallingState;
		}
	}
	else if (player.getMeleeType() == ONE_HAND_SWORD)
	{
		if (aFrames >= 24)
		{
			aFrames = 0;
			return new FallingState;
		}
	}
	else if (player.getMeleeType() == ONE_HAND_AXE)
	{
		if (aFrames >= 32)
		{
			aFrames = 0;
			return new FallingState;
		}
	}
	else if (player.getMeleeType() == ONE_HAND_BLUNT)
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

void MidairMeleeState::update(ALLEGRO_BITMAP* tileSheet, MapHandler& map, Player& player)
{
	if (player.getOrientation())
	{
		if (player.getMeleeType() == ONE_HAND_DAGGER)
		{
			al_draw_bitmap_region(tileSheet, (aFrames / 4) * PLAYER_SIZE, (15 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (player.getMeleeType() == ONE_HAND_SWORD)
		{
			al_draw_bitmap_region(tileSheet, (aFrames / 6) * PLAYER_SIZE, (15 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (player.getMeleeType() == ONE_HAND_AXE)
		{
			al_draw_bitmap_region(tileSheet, (aFrames / 8) * PLAYER_SIZE, (15 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (player.getMeleeType() == ONE_HAND_BLUNT)
		{
			al_draw_bitmap_region(tileSheet, (aFrames / 6) * PLAYER_SIZE, (15 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
	}
	else
	{
		if (player.getMeleeType() == ONE_HAND_DAGGER)
		{
			al_draw_bitmap_region(tileSheet, (4 + (aFrames / 4)) * PLAYER_SIZE, (15 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (player.getMeleeType() == ONE_HAND_SWORD)
		{
			al_draw_bitmap_region(tileSheet, (4 + (aFrames / 6)) * PLAYER_SIZE, (15 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (player.getMeleeType() == ONE_HAND_AXE)
		{
			al_draw_bitmap_region(tileSheet, (4 + (aFrames / 8)) * PLAYER_SIZE, (15 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (player.getMeleeType() == ONE_HAND_BLUNT)
		{
			al_draw_bitmap_region(tileSheet, (4 + (aFrames / 6)) * PLAYER_SIZE, (15 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
	}
}

PlayerState* DuckingMeleeState::action(InputHandler input, MapHandler& map, Player& player)
{
	aFrames++;

	if (player.getMeleeType() == ONE_HAND_DAGGER)
	{
		if (aFrames >= 16)
		{
			aFrames = 0;
			return new DuckingState;
		}
	}
	else if (player.getMeleeType() == ONE_HAND_SWORD)
	{
		if (aFrames >= 24)
		{
			aFrames = 0;
			return new DuckingState;
		}
	}
	else if (player.getMeleeType() == ONE_HAND_AXE)
	{
		if (aFrames >= 32)
		{
			aFrames = 0;
			return new DuckingState;
		}
	}
	else if (player.getMeleeType() == ONE_HAND_BLUNT)
	{
		if (aFrames >= 24)
		{
			aFrames = 0;
			return new DuckingState;
		}
	}
	else if (player.getMeleeType() == TWO_HAND_SWORD)
	{
		if (aFrames >= 32)
		{
			aFrames = 0;
			return new DuckingState;
		}
	}
	else if (player.getMeleeType() == TWO_HAND_AXE)
	{
		if (aFrames >= 36)
		{
			aFrames = 0;
			return new DuckingState;
		}
	}
	else if (player.getMeleeType() == TWO_HAND_BLUNT)
	{
		if (aFrames >= 32)
		{
			aFrames = 0;
			return new DuckingState;
		}
	}
	else if (player.getMeleeType() == TWO_HAND_KATANA)
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

void DuckingMeleeState::update(ALLEGRO_BITMAP* tileSheet, MapHandler& map, Player& player)
{
	if (player.getOrientation())
	{
		if (player.getMeleeType() == ONE_HAND_DAGGER)
		{
			al_draw_bitmap_region(tileSheet, (aFrames / 4) * PLAYER_SIZE, (18 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (player.getMeleeType() == ONE_HAND_SWORD)
		{
			al_draw_bitmap_region(tileSheet, (aFrames / 6) * PLAYER_SIZE, (18 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (player.getMeleeType() == ONE_HAND_AXE)
		{
			al_draw_bitmap_region(tileSheet, (aFrames / 8) * PLAYER_SIZE, (18 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (player.getMeleeType() == ONE_HAND_BLUNT)
		{
			al_draw_bitmap_region(tileSheet, (aFrames / 6) * PLAYER_SIZE, (18 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (player.getMeleeType() == TWO_HAND_SWORD)
		{
			al_draw_bitmap_region(tileSheet, (aFrames / 8) * PLAYER_SIZE, (19 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (player.getMeleeType() == TWO_HAND_AXE)
		{
			al_draw_bitmap_region(tileSheet, (aFrames / 9) * PLAYER_SIZE, (19 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (player.getMeleeType() == TWO_HAND_BLUNT)
		{
			al_draw_bitmap_region(tileSheet, (aFrames / 8) * PLAYER_SIZE, (19 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (player.getMeleeType() == TWO_HAND_KATANA)
		{
			al_draw_bitmap_region(tileSheet, (aFrames / 6) * PLAYER_SIZE, (19 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
	}
	else
	{
		if (player.getMeleeType() == ONE_HAND_DAGGER)
		{
			al_draw_bitmap_region(tileSheet, (4 + (aFrames / 4)) * PLAYER_SIZE, (18 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (player.getMeleeType() == ONE_HAND_SWORD)
		{
			al_draw_bitmap_region(tileSheet, (4 + (aFrames / 6)) * PLAYER_SIZE, (18 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (player.getMeleeType() == ONE_HAND_AXE)
		{
			al_draw_bitmap_region(tileSheet, (4 + (aFrames / 8)) * PLAYER_SIZE, (18 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (player.getMeleeType() == ONE_HAND_BLUNT)
		{
			al_draw_bitmap_region(tileSheet, (4 + (aFrames / 6)) * PLAYER_SIZE, (18 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (player.getMeleeType() == TWO_HAND_SWORD)
		{
			al_draw_bitmap_region(tileSheet, (4 + (aFrames) / 8) * PLAYER_SIZE, (19 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (player.getMeleeType() == TWO_HAND_AXE)
		{
			al_draw_bitmap_region(tileSheet, (4 + (aFrames) / 9) * PLAYER_SIZE, (19 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (player.getMeleeType() == TWO_HAND_BLUNT)
		{
			al_draw_bitmap_region(tileSheet, (4 + (aFrames) / 8) * PLAYER_SIZE, (19 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
		else if (player.getMeleeType() == TWO_HAND_KATANA)
		{
			al_draw_bitmap_region(tileSheet, (4 + (aFrames) / 6) * PLAYER_SIZE, (19 * PLAYER_SIZE), PLAYER_SIZE, PLAYER_SIZE,
				player.getPosition().first - map.getCamX(), (player.getPosition().second - 32) - map.getCamY(), 0);
		}
	}
}