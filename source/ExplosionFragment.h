#ifndef _ExplosionFragment_h_
#define _ExplosionFragment_h_

#include "Iw2D.h"
#include "IwGeom.h"

#include "Effect.h"
#include "Sprite.h"

// A star-shaped particle, used when tiles explode
struct ExplosionFragment : public Effect, public Sprite
{
	float speed;
    int timer;
    int colour;

    ExplosionFragment(CIw2DImage* graphic, CIwVec2 const & startPos, CIwVec2 const & startVel, int _colour);
	~ExplosionFragment() {}
    bool update(int elapsed);
	void render(const CIwVec2& camPos);
};

#endif
