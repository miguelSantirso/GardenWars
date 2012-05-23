#include "Simulation.h"

Simulation::Simulation() : thePlayer(NULL), theWorld(NULL), stars(NULL), starsCollected(0)
{
	camPos.x = 0.5 * WORLD_PIXELS_WIDTH;
	camPos.y = 0.5 * WORLD_PIXELS_HEIGHT;
	theWorld = new World();
}


void Simulation::release()
{
	if (theWorld != NULL)
	{
		delete theWorld;
		theWorld = NULL;
	}
	
	releasePlayer();
	releaseStars();
}


void Simulation::start()
{
	releasePlayer();
	thePlayer = new Player(g_Resources->getImage(RESOURCE_CHARACTER));

	spawnStars(50);
	starsCollected = 0;
}
void Simulation::stop()
{
	releasePlayer();
	releaseStars();
}


void Simulation::update()
{
	if (thePlayer != NULL)
	{
		thePlayer->update(theWorld);
		camPos = thePlayer->position;
	}

	checkCollisionsWithStars();
}


void Simulation::draw()
{
	theWorld->draw(camPos.x, camPos.y);

	if (thePlayer != NULL)
		thePlayer->draw(camPos);

	drawStars();

	g_EffectsManager->render(camPos);
}


int Simulation::getStarsCollected()
{
	return starsCollected;
}

void Simulation::spawnStars(int howMany)
{
	releaseStars();

	nStars = howMany;
	stars = new Star*[nStars];

	for (int i = 0; i < nStars; i++)
	{
		stars[i] = new Star(g_Resources->getImage(RESOURCE_STAR));
		stars[i]->position.x = IwRandMinMax(0, WORLD_PIXELS_WIDTH);
		stars[i]->position.y = IwRandMinMax(0, WORLD_PIXELS_HEIGHT);
	}
}
void Simulation::drawStars()
{
	if (stars == NULL)
		return;

	for (int i = 0; i < nStars; i++)
	{
		if (stars[i] != NULL)
			stars[i]->draw(camPos);
	}
}
void Simulation::releaseStars()
{
	if (stars != NULL)
	{
		for (int i = 0; i < nStars; i++)
			if (stars[i] != NULL)
			{
				delete stars[i];
				stars[i] = NULL;
			}

		delete [] stars;
		stars = NULL;
	}
}


void Simulation::releasePlayer()
{
	if (thePlayer != NULL)
	{
		delete thePlayer;
		thePlayer = NULL;
	}
}


void Simulation::checkCollisionsWithStars()
{
	if (stars == NULL || thePlayer == NULL)
		return;

	for (int i = 0; i < nStars; i++)
	{
		if (stars[i] != NULL && (thePlayer->position - stars[i]->position).GetLength() < 80)
		{
			ExplosionFragment* exp = new ExplosionFragment(g_Resources->getImage(RESOURCE_STAR), stars[i]->position, CIwVec2(0, -0.0001), 0xff223355);
			g_EffectsManager->add(exp);

			delete stars[i];
			stars[i] = NULL;

			starsCollected++;
		}
	}
}
