#ifndef _SIMULATION_H_
#define _SIMULATION_H_

#include "Config.h"
#include "SimpleResourceManager.h"
#include "World.h"
#include "Player.h"

class Simulation
{
public:
	Simulation();
	~Simulation() { release(); }
	void release();

	void update();
	void draw();

private:
	World theWorld;
	Player thePlayer;
};

#endif