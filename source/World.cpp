#include "World.h"

World::World(SimpleResourceManager* resources)
{
	for (int i = 0; i < WORLD_TILES_WIDTH; i++)
	{
		grid[i] = new TileType[WORLD_TILES_HEIGHT];
		for (int j = 0; j < WORLD_TILES_HEIGHT; j++)
		{
			if (i == 0 || i == WORLD_TILES_WIDTH -1 || j == 0 || j == WORLD_TILES_HEIGHT - 1)
				grid[i][j] = World::Stone;
			else if (IwRand() % 100 > 20)
				grid[i][j] = World::Grass;
			else 
				grid[i][j] = World::StoneTall;

		}
			
	}
	tileImages[World::Grass] = resources->getImage(RESOURCE_GRASS);
	tileImages[World::Stone] = resources->getImage(RESOURCE_STONE);
	tileImages[World::StoneTall] = resources->getImage(RESOURCE_STONE_TALL);
	tileImages[World::Dirt] = resources->getImage(RESOURCE_DIRT);
}

World::~World()
{
	release();
}

void World::release()
{
	for (int i = 0; i < WORLD_TILES_WIDTH; i++)
	{
		if (grid[i] != NULL)
		{
			delete grid[i];
			grid[i] = NULL;
		}
	}
}


void World::draw(int cameraX, int cameraY)
{
	camX = cameraX;
	camY = cameraY;

	int tileX, tileY;
	tileX = (cameraX / float(WORLD_PIXELS_WIDTH)) * WORLD_TILES_WIDTH;
	tileY = (cameraY / float(WORLD_PIXELS_HEIGHT)) * WORLD_TILES_HEIGHT;

	int minTileX = tileX - 0.5*NUM_H_TILES;
	int minTileY = tileY - 0.5*NUM_V_TILES;

	if (minTileX < 0)
		minTileX = 0;
	if (minTileX >= WORLD_TILES_WIDTH)
		minTileX = WORLD_TILES_WIDTH - 1;
	if (minTileY < 0)
		minTileY = 0;
	if (minTileY >= WORLD_TILES_HEIGHT)
		minTileY = WORLD_TILES_HEIGHT - 1;

	for (int i = minTileX; i < WORLD_TILES_WIDTH && i - minTileX <= NUM_H_TILES; i++)
		for (int j = minTileY; j < WORLD_TILES_HEIGHT && j - minTileY <= NUM_V_TILES; j++)
			drawTile(i, j);
}


void World::drawTile(int i, int j)
{
	int posX = i * TILE_WIDTH - camX + 0.5*SCREEN_WIDTH;
	int posY = j * TILE_HEIGHT - camY + 0.5*SCREEN_HEIGHT;

	CIwMat2D transform;
	transform.SetRot();
	transform.SetTrans(CIwSVec2(posX, posY));
	// Set this transform as the active transform for Iw2D
    Iw2DSetTransformMatrix(transform);

	int offsetX = -(tileImages[grid[i][j]]->GetWidth() / 2);
	int offsetY = -50;
	Iw2DDrawImage(tileImages[grid[i][j]], CIwSVec2(offsetX, offsetY));
}
