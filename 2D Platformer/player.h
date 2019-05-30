#pragma once

class PlayerState;
class IdleState;
class JumpingState;

#include "globals.h"
#include "inputhandler.h"
#include "maphandler.h"

struct HitBox
{
	float left, right, top, bottom;
	std::pair<float, float> center;
};

struct Particle_Player
{
	std::pair<float, float> pos;
	std::pair<float, float> vel;
	bool active, orientation;
};

class Player
{
	private:
		HitBox hitbox;
		std::pair<float, float> pos;
		float xSpeed, ySpeed, momentum;			// player movement variables
		bool orientation, dblJump, nextMap;		// orientation - false = left, true = right;
		int meleeType, rangedType, iFrames;		// weapon types and invulernability frames
		int bNum, bFrames, dNum, dFrames;		// particle effects
		std::vector<Particle_Player> blood;
		std::vector<Particle_Player> dust;
		ALLEGRO_BITMAP* tileSheet;				// sprite source
		PlayerState* currentState;				// main FSM instance

	public:
		Player(float xPos, float yPos);
		~Player() {}

		// state management
		void initBlood();
		void drawBlood(MapHandler& map);
		virtual void action(InputHandler input, MapHandler& map);
		virtual void update(MapHandler& map);

		// collision detection
		int projectDown(MapHandler& map, float scalar);
		int collideBlock(MapHandler& map, float x1, float x2, float y1, float y2);
		int reverseBlock(MapHandler& map, float x1, float x2, float y1, float y2);
		bool lateralCollision(MapHandler& map, int xBlock, int yBlock);
		void airLateralCollision(MapHandler& map, int xBlock);
		void airVerticalCollision(MapHandler& map, int yBlock);
		bool fallingCollision(MapHandler& map, int yBlock);
		void standingCollision(MapHandler& map, int yBlock);

		// mutators
		void setOrientation(bool direction) { orientation = direction; }
		void setXPosition(float xPos) { hitbox.left = xPos; hitbox.right = xPos + 32.0; }
		void setYPosition(float yPos) { hitbox.bottom = yPos; hitbox.top = yPos - 32.0; }
		void setXSpeed(float speed) { xSpeed = speed; }
		void setYSpeed(float speed) { ySpeed = speed; }
		void incIFrames() { iFrames++; }
		void incMomentum() { momentum++; }
		void setMomentum(float val) { momentum = val; }
		void clrIFrames() { iFrames = 0; }
		void clrMomentum() { momentum = 0; }
		void setDblJump(bool dbl) { dblJump = dbl; }

		// accessors
		bool getOrientation() { return orientation; }
		std::pair<float, float> getPosition() { return pos; }
		HitBox& getHitBox() { return hitbox; }
		float getXSpeed() { return xSpeed; }
		float getYSpeed() { return ySpeed; }
		float getMomentum() { return momentum; }
		bool getDblJump() { return dblJump; }
		int getMeleeType() { return meleeType; }
		int getRangedType() { return rangedType; }

		// garbage collection
		void destroyPointers();
};

class PlayerState
{
	public:
		virtual PlayerState* action(InputHandler input, MapHandler& map, Player& player) = 0;
		virtual void update(ALLEGRO_BITMAP* tileSheet, MapHandler& map, Player& player) = 0;
};

