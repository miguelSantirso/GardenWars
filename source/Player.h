#ifndef _Player_H_
#define _Player_H_

#include "Iw2D.h"

#include "Sprite.h"
#include "Config.h"
#include "World.h"

#define ANGULAR_VELOCITY 0.01

class Player : public Sprite
{
public:
	Player(CIw2DImage* image);

	void update(World* theWorld);

	CIwSVec2 velocity;
	float speed;
};

#endif