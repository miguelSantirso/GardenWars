#ifndef _BALLBOT_H_
#define _BALLBOT_H_

#include "Iw2D.h"

#include "Config.h"

#define ANGULAR_VELOCITY 0.01

class BallBot
{
public:
	BallBot();
	~BallBot();

	void release();

	void update();
	void draw();

	float worldX;
	float worldY;

	CIwSVec2 velocity;
	float speed;
private:
	CIw2DImage* graphic;
};

#endif