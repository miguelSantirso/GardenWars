#ifndef _SIMPLE_RESOURCE_MANAGER_H_
#define _SIMPLE_RESOURCE_MANAGER_H_

#include "Iw2D.h"

#define NUM_RESOURCES 5
#define RESOURCE_CHARACTER 0
#define RESOURCE_DIRT 1
#define RESOURCE_GRASS 2
#define RESOURCE_STONE 3
#define RESOURCE_STAR 4

class SimpleResourceManager
{
public:
	SimpleResourceManager();
	~SimpleResourceManager();

	void release();

	CIw2DImage* getImage(int imageId);
private:
	CIw2DImage* images[NUM_RESOURCES];
};

#endif