#ifndef _WORLD_H_
#define _WORLD_H_

#include "Iw2D.h"

#include "SimpleResourceManager.h"
#include "Config.h"

#define NUM_H_TILES ((SCREEN_WIDTH / TILE_WIDTH) + 2)
#define NUM_V_TILES ((SCREEN_HEIGHT / TILE_HEIGHT) + 2)

class World
{
public:
	enum TileType { Grass = 0, Stone, StoneTall, Dirt, Water };

	World();
	~World();
	void release();

	void draw(int cameraX, int cameraY);
	
	bool isPositionNavigable(int worldX, int worldY);

private:
	TileType* grid[WORLD_TILES_WIDTH];
	CIw2DImage* tileImages[5];

	int camX;
	int camY;

	void drawTile(int i, int j);

};

#endif
