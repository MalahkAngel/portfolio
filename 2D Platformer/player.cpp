#include "player.h"
#include "idlestate.h"
#include "jumpingstate.h"

Player::Player(float xPos, float yPos)
{
	// sprite position
	pos.first = xPos;
	pos.second = yPos;

	// rectangular hitbox
	hitbox.left = pos.first + 8;
	hitbox.right = pos.first + 24;
	hitbox.bottom = pos.second;
	hitbox.top = pos.second - 32;

	// rhombic hitbox
	hitbox.center.first = pos.first + 16;
	hitbox.center.second = pos.second - 16;

	// player speed modifiers
	xSpeed = 0;
	ySpeed = 0;
	momentum = 0;

	// state modifiers
	orientation = true;
	dblJump = false;
	nextMap = false;
	meleeType = ONE_HAND_DAGGER;
	rangedType = ONE_HAND_PISTOL;

	// misc effect parameters
	iFrames = 0;
	bNum = 0;
	bFrames = 0;
	dNum = 0;
	dFrames = 0;
	blood.resize(0);
	dust.resize(0);

	// initalize sprite sheet
	tileSheet = al_load_bitmap("assets/sprites/playerField-mp.png");
	assert(tileSheet);
	al_convert_mask_to_alpha(tileSheet, al_map_rgb(255, 0, 255));

	// initialize state machine
	currentState = new IdleState;
}

void Player::initBlood()
{
	bNum = rand() % 200 + 200;

	for (int i = 0; i < bNum; i++)
	{
		Particle_Player newParticle;

		if (orientation)
		{
			newParticle.pos.first = (pos.first + 16) + rand() % 16 + (-12);
			newParticle.pos.second = (pos.second - 16) + rand() % 11 + (-5);
			newParticle.vel.first = rand() % 4 + 1;
		}
		else
		{
			newParticle.pos.first = (pos.first + 16) + rand() % 16 + (-12);
			newParticle.pos.second = (pos.second - 16) + rand() % 11 + (-5);
			newParticle.vel.first = -(rand() % 4 + 1);
		}

		newParticle.vel.second = rand() % 3 + (-2);
		newParticle.orientation = orientation;
		newParticle.active = true;
		blood.push_back(newParticle);
	}
}

void Player::drawBlood(MapHandler& map)
{
	int size = int(blood.size()) * 16;
	float xOffset = map.getCamX();
	float yOffset = map.getCamY();
	ALLEGRO_VERTEX* vertex = new ALLEGRO_VERTEX[size];

	for (std::vector<Particle_Player>::iterator i = blood.begin(); i != blood.end(); i++)
	{
		if (i->active)
		{
			i->pos.first += i->vel.first;
			i->pos.second += i->vel.second;

			if (i->orientation)
			{
				i->vel.first -= 0.3;
				if (i->vel.first <= 0.0) i->vel.first = 0.0;
			}
			else
			{
				i->vel.first += 0.3;
				if (i->vel.first >= 0.0) i->vel.first = 0.0;
			}

			i->vel.first += 0.3;
			vertex[i - blood.begin()] = { i->pos.first - xOffset, i->pos.second - yOffset,
				0, 0, 0, al_map_rgb(255, 0, 0) };
			vertex[i - blood.begin() + 1] = { i->pos.first - xOffset, i->pos.second + 1 - yOffset,
				0, 0, 0, al_map_rgb(255 / 2, 0, 0) };
			vertex[i - blood.begin() + 2] = { i->pos.first - xOffset, i->pos.second + 2 - yOffset,
				0, 0, 0, al_map_rgb(255, 0, 0) };
			vertex[i - blood.begin() + 3] = { i->pos.first - xOffset, i->pos.second + 3 - yOffset,
				0, 0, 0, al_map_rgb(255 / 2, 0, 0) };
			vertex[i - blood.begin() + 4] = { i->pos.first + 1 - xOffset, i->pos.second - yOffset,
				0, 0, 0, al_map_rgb(255, 0, 0) };
			vertex[i - blood.begin() + 5] = { i->pos.first + 1 - xOffset, i->pos.second + 1 - yOffset,
				0, 0, 0, al_map_rgb(255 / 2, 0, 0) };
			vertex[i - blood.begin() + 6] = { i->pos.first + 1 - xOffset, i->pos.second + 2 - yOffset,
				0, 0, 0, al_map_rgb(255, 0, 0) };
			vertex[i - blood.begin() + 7] = { i->pos.first + 1 - xOffset, i->pos.second + 3 - yOffset,
				0, 0, 0, al_map_rgb(255 / 2, 0, 0) };
			vertex[i - blood.begin() + 8] = { i->pos.first + 2 - xOffset, i->pos.second - yOffset,
				0, 0, 0, al_map_rgb(255, 0, 0) };
			vertex[i - blood.begin() + 9] = { i->pos.first + 2 - xOffset, i->pos.second + 1 - yOffset,
				0, 0, 0, al_map_rgb(255 / 2, 0, 0) };
			vertex[i - blood.begin() + 10] = { i->pos.first + 2 - xOffset, i->pos.second + 2 - yOffset,
				0, 0, 0, al_map_rgb(255, 0, 0) };
			vertex[i - blood.begin() + 11] = { i->pos.first + 2 - xOffset, i->pos.second + 3 - yOffset,
				0, 0, 0, al_map_rgb(255 / 2, 0, 0) };
			vertex[i - blood.begin() + 12] = { i->pos.first + 3 - xOffset, i->pos.second - yOffset,
				0, 0, 0, al_map_rgb(255, 0, 0) };
			vertex[i - blood.begin() + 13] = { i->pos.first + 3 - xOffset, i->pos.second + 1 - yOffset,
				0, 0, 0, al_map_rgb(255 / 2, 0, 0) };
			vertex[i - blood.begin() + 14] = { i->pos.first + 3 - xOffset, i->pos.second + 2 - yOffset,
				0, 0, 0, al_map_rgb(255, 0, 0) };
			vertex[i - blood.begin() + 15] = { i->pos.first + 3 - xOffset, i->pos.second + 3 - yOffset,
				0, 0, 0, al_map_rgb(255 / 2, 0, 0) };

			if (bFrames % 3 == 0 && bFrames != 24)
			{
				if (i - blood.begin() != 0 && (rand() % 10) % (i - blood.begin()) == 0)
				{
					i->active = false;
				}
			}
		}
	}

	al_draw_prim(vertex, NULL, 0, 0, size + 1, ALLEGRO_PRIM_POINT_LIST);
	delete[] vertex;
	bFrames++;

	if (bFrames >= 24)
	{
		bFrames = 0;
		blood.resize(0);
	}
}

void Player::action(InputHandler input, MapHandler& map)
{
	PlayerState* newState = currentState->action(input, map, *this);

	if (newState != NULL)
	{
		delete currentState;
		currentState = newState;
	}
}

void Player::update(MapHandler& map)
{
	currentState->update(tileSheet, map, *this);
	pos.first += xSpeed;
	pos.second += ySpeed;
	hitbox.left = pos.first + 8;
	hitbox.right = pos.first + 24;
	hitbox.bottom = pos.second;
	hitbox.top = pos.second - 32;
	hitbox.center.first = hitbox.left + 8;
	hitbox.center.second = hitbox.top + 16;
	drawBlood(map);
}

int Player::projectDown(MapHandler& map, float scalar)
{
	int numBlocks = map.getMap().blocks.size();

	if (!orientation)
	{
		for (int i = 0; i < numBlocks; i++)
		{
			if (hitbox.center.first < map.getMap().blocks[i].right &&
				hitbox.center.first > map.getMap().blocks[i].left &&
				hitbox.bottom + scalar > map.getMap().blocks[i].top &&
				hitbox.top + scalar < map.getMap().blocks[i].bottom)
			{
				return i;
			}
		}
	}

	return -1;
}

int Player::collideBlock(MapHandler& map, float x1, float x2, float y1, float y2)
{
	int numBlocks = map.getMap().blocks.size();

	if (orientation)
	{
		for (int i = 0; i < numBlocks; i++)
		{
			if (hitbox.left + x1 < map.getMap().blocks[i].right &&
				hitbox.right + x2 > map.getMap().blocks[i].left &&
				hitbox.bottom + y1 > map.getMap().blocks[i].top &&
				hitbox.top + y2 < map.getMap().blocks[i].bottom)
			{
				return i;
			}
		}
	}
	else
	{
		for (int i = numBlocks - 1; i >= 0; i--)
		{
			if (hitbox.left - x1 < map.getMap().blocks[i].right &&
				hitbox.right - x2 > map.getMap().blocks[i].left &&
				hitbox.bottom + y1 > map.getMap().blocks[i].top &&
				hitbox.top + y2 < map.getMap().blocks[i].bottom)
			{
				return i;
			}
		}
	}

	return -1;
}

int Player::reverseBlock(MapHandler& map, float x1, float x2, float y1, float y2)
{
	int numBlocks = map.getMap().blocks.size();

	if (!orientation)
	{
		for (int i = 0; i < numBlocks; i++)
		{
			if (hitbox.left + x1 < map.getMap().blocks[i].right &&
				hitbox.right + x2 > map.getMap().blocks[i].left &&
				hitbox.bottom + y1 > map.getMap().blocks[i].top &&
				hitbox.top + y2 < map.getMap().blocks[i].bottom)
			{
				return i;
			}
		}
	}
	else
	{
		for (int i = numBlocks - 1; i >= 0; i--)
		{
			if (hitbox.left - x1 < map.getMap().blocks[i].right &&
				hitbox.right - x2 > map.getMap().blocks[i].left &&
				hitbox.bottom + y1 > map.getMap().blocks[i].top &&
				hitbox.top + y2 < map.getMap().blocks[i].bottom)
			{
				return i;
			}
		}
	}

	return -1;
}

bool Player::lateralCollision(MapHandler& map, int xBlock, int yBlock)
{
	if (orientation)
	{
		if (xBlock == -1)
		{
			xSpeed = 2.0;

			if (yBlock != -1)
			{
				if (map.getBlock(yBlock).type >= 5 && map.getBlock(yBlock).type <= 11)
				{
					float cPos = float(hitbox.center.first - map.getBlock(yBlock).left) / TILE_SIZE;
					float yPos = (1 - cPos) * map.getBlock(yBlock).slopeLeft + cPos * map.getBlock(yBlock).slopeRight;
					pos.second = (map.getBlock(yBlock).bottom - 2) - yPos;
				}
				else
				{
					ySpeed = 0.0;
				}
			}
			else if (yBlock == -1)
			{
				return true;
			}
		}
		else if (map.getBlock(xBlock).type >= 1 && map.getBlock(xBlock).type <= 4)
		{
			if (map.getBlock(xBlock).type != 2)
			{
				xSpeed = 0.0;
				ySpeed = 0.0;
			}
			else
			{
				xSpeed = 2.0;
				ySpeed = 0.0;
			}
		}
		else if (map.getBlock(xBlock).type >= 5 && map.getBlock(xBlock).type <= 11)
		{
			xSpeed = 2.0;
			float cPos = float(hitbox.center.first - map.getBlock(xBlock).left) / TILE_SIZE;
			float yPos = (1 - cPos) * map.getBlock(xBlock).slopeLeft + cPos * map.getBlock(xBlock).slopeRight;
			pos.second = (map.getBlock(xBlock).bottom - 2) - yPos;
		}
		else if (map.getBlock(xBlock).type >= 12 && map.getBlock(xBlock).type <= 18)
		{
			xSpeed = 2.0;
			float cPos = float(map.getBlock(xBlock).left - hitbox.center.first) / TILE_SIZE;
			float yPos = cPos * map.getBlock(xBlock).slopeLeft + (1 - cPos) * map.getBlock(xBlock).slopeRight;
			pos.second = (map.getBlock(xBlock).bottom) - yPos;
		}
	}
	else
	{
		if (xBlock == -1)
		{
			xSpeed = -2.0;

			if (yBlock != -1)
			{
				if (map.getBlock(yBlock).type >= 12 && map.getBlock(yBlock).type <= 18)
				{
					float cPos = float(map.getBlock(yBlock).right - hitbox.center.first) / TILE_SIZE;
					float yPos = cPos * map.getBlock(yBlock).slopeLeft + (1 - cPos) * map.getBlock(yBlock).slopeRight;
					pos.second = (map.getBlock(yBlock).bottom) - yPos;
				}
				else
				{
					ySpeed = 0.0;
				}
			}
			else
			{
				return true;
			}
		}
		else if (map.getBlock(xBlock).type >= 1 && map.getBlock(xBlock).type <= 4)
		{
			if (map.getBlock(xBlock).type != 2)
			{
				xSpeed = 0.0;
				ySpeed = 0.0;
			}
			else
			{
				xSpeed = -2.0;
				ySpeed = 0.0;
			}
		}
		else if (map.getBlock(xBlock).type >= 5 && map.getBlock(xBlock).type <= 11)
		{
			xSpeed = -2.0;
			float cPos = float(hitbox.center.first - map.getBlock(xBlock).right) / TILE_SIZE;
			float yPos = (1 - cPos) * map.getBlock(xBlock).slopeLeft + cPos * map.getBlock(xBlock).slopeRight;
			pos.second = (map.getBlock(xBlock).bottom + 2) - yPos;
		}
		else if (map.getBlock(xBlock).type >= 12 && map.getBlock(xBlock).type <= 18)
		{
			xSpeed = -2.0;
			float cPos = float(map.getBlock(xBlock).right - hitbox.center.first) / TILE_SIZE;
			float yPos = cPos * map.getBlock(xBlock).slopeLeft + (1 - cPos) * map.getBlock(xBlock).slopeRight;
			pos.second = (map.getBlock(xBlock).bottom) - yPos;
		}
	}

	return false;
}

void Player::airLateralCollision(MapHandler& map, int xBlock)
{
	if (orientation)
	{
		if (xBlock == -1)
		{
			xSpeed = 2.0;
		}
		else if (map.getBlock(xBlock).type == 2)
		{
			xSpeed = 2.0;
		}
		else
		{
			xSpeed = 0.0;
		}
	}
	else
	{
		if (xBlock == -1)
		{
			xSpeed = -2.0;
		}
		else if (map.getBlock(xBlock).type == 2)
		{
			xSpeed = -2.0;
		}
		else
		{
			xSpeed = 0.0;
			
		}
	}
}

void Player::airVerticalCollision(MapHandler& map, int yBlock)
{
	if (momentum > 0)
	{
		if (yBlock == -1)
		{
			ySpeed -= momentum;
			momentum = 0;

			if (ySpeed <= -JUMP_SPEED)
			{
				ySpeed = -JUMP_SPEED;
			}
		}
		else
		{
			if (map.getBlock(yBlock).type == 2)
			{
				ySpeed -= momentum;
				momentum = 0;

				if (ySpeed <= -JUMP_SPEED)
				{
					ySpeed = -JUMP_SPEED;
				}
			}
			else
			{
				ySpeed = 0;
				momentum = 0;
			}
		}
	}
	else
	{
		if (yBlock == -1)
		{
			ySpeed += GRAVITY;
		}
		else
		{
			if (map.getBlock(yBlock).type == 2)
			{
				ySpeed += GRAVITY;
			}
			else
			{
				ySpeed = 0.0;
				pos.second = map.getBlock(yBlock).bottom + 32;
			}
		}
	}
}

bool Player::fallingCollision(MapHandler& map, int yBlock)
{
	if (yBlock == -1)
	{
		ySpeed += GRAVITY;

		if (ySpeed >= JUMP_SPEED)
		{
			ySpeed = JUMP_SPEED;
		}
	}
	else
	{
		if (map.getBlock(yBlock).type >= 1 && map.getBlock(yBlock).type <= 4)
		{
			xSpeed = 0.0;
			ySpeed = 0.0;
			pos.second = map.getBlock(yBlock).top;
			return true;
		}
		else if (map.getBlock(yBlock).type >= 5 && map.getBlock(yBlock).type <= 11)
		{
			xSpeed = 0.0;
			ySpeed = 0.0;
			float cPos = (hitbox.left - map.getBlock(yBlock).left) / 16;
			float yPos = (1 - cPos) * map.getBlock(yBlock).slopeLeft + cPos * map.getBlock(yBlock).slopeRight;
			pos.second = map.getBlock(yBlock).bottom - yPos;

			return true;
		}
		else if (map.getBlock(yBlock).type >= 12 && map.getBlock(yBlock).type <= 18)
		{
			xSpeed = 0.0;
			ySpeed = 0.0;
			float cPos = (map.getBlock(yBlock).right - hitbox.right) / 16;
			float yPos = cPos * map.getBlock(yBlock).slopeLeft + (1 - cPos) * map.getBlock(yBlock).slopeRight;
			pos.second = map.getBlock(yBlock).bottom - yPos;

			return true;
		}
	}

	return false;
}

void Player::standingCollision(MapHandler& map, int yBlock)
{
	if (map.getBlock(yBlock).type <= 4)
	{
		pos.second = map.getBlock(yBlock).top;
		hitbox.bottom = pos.second;
		hitbox.top = pos.second - 32.0;
	}
}

void Player::destroyPointers()
{
	al_destroy_bitmap(tileSheet);
	delete currentState;
}