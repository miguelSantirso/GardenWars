#ifndef _STAR_H_
#define _STAR_H_

#include "Iw2D.h"
#include "Config.h"

class Star
{
public:
	Star(int x, int y);
	~Star();

	void release();

	void draw(int camX, int camY);

	float worldX;
	float worldY;
private:
	CIw2DImage* graphic;

	int screenX;
	int screenY;
};

#endif
