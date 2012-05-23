#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "Iw2D.h"
#include "Config.h"

class Sprite
{
public:
	CIwVec2 position;

	Sprite(CIw2DImage* image);
	~Sprite() { release(); }

	void release();

	void draw(CIwVec2 camPos);

protected:
	CIw2DImage* graphic;

	float angle;

	// Auxiliary
	CIwSVec2 offset;
	CIwSVec2 screenPos;
	CIwMat2D transform;
};

#endif