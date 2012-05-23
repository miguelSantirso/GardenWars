#ifndef _STAR_H_
#define _STAR_H_

#include "Iw2D.h"

#include "Config.h"
#include "SimpleResourceManager.h"
#include "Sprite.h"

class Star : public Sprite
{
public:
	Star(CIw2DImage* graphic):Sprite(graphic) {}
};

#endif
