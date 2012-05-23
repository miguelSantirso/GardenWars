#ifndef _SIMULATION_H_
#define _SIMULATION_H_

#include "Iw2D.h"

#include "Config.h"

#include "SimpleResourceManager.h"

#include "EffectManager.h"
#include "ExplosionFragment.h"

#include "World.h"
#include "Player.h"
#include "Star.h"


class Simulation
{
public:
	Simulation();
	~Simulation() { release(); }
	void release();

	void start();
	void stop();

	void update();
	void draw();

	int getStarsCollected();

private:
	World* theWorld;
	Player* thePlayer;

	int starsCollected;
	int nStars;
	Star** stars;

	CIwVec2 camPos;

	void spawnStars(int howMany);
	void drawStars();
	void releaseStars();

	void releasePlayer();

	void checkCollisionsWithStars();
};

#endif
