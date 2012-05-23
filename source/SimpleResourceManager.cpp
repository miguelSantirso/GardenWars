#include "SimpleResourceManager.h"

SimpleResourceManager::SimpleResourceManager()
{
	images[RESOURCE_CHARACTER] = Iw2DCreateImage("character.png");
	images[RESOURCE_DIRT] = Iw2DCreateImage("dirt.png");
	images[RESOURCE_GRASS] = Iw2DCreateImage("grass.png");
	images[RESOURCE_STONE] = Iw2DCreateImage("stone.png");
	images[RESOURCE_STONE_TALL] = Iw2DCreateImage("stone_tall.png");
	images[RESOURCE_STAR] = Iw2DCreateImage("star.png");
	images[RESOURCE_WATER] = Iw2DCreateImage("water.png");
}

SimpleResourceManager::~SimpleResourceManager()
{
	release();
}


void SimpleResourceManager::release()
{
	for (int i = 0; i < NUM_RESOURCES; i++)
		if (images[i] != NULL)
		{
			delete images[i];
			images[i] = NULL;
		}
}


CIw2DImage* SimpleResourceManager::getImage(int imageId)
{
	return images[imageId];
}
