#ifndef _Player_H_
#define _Player_H_

#include "Iw2D.h"

#include "Config.h"

#define ANGULAR_VELOCITY 0.01

class Player
{
public:
	Player();
	~Player();

	void release();

	void update();
	void draw();

	CIwVec2 position;

	CIwSVec2 velocity;
	float speed;
private:
	CIw2DImage* graphic;
};

#endif