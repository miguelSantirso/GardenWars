#ifndef _ExplosionFragment_h_
#define _ExplosionFragment_h_

#include "Effect.h"

#include "IwGeom.h"

// A star-shaped particle, used when tiles explode
struct ExplosionFragment : public Effect
{
    CIwVec2 pos;
    CIwVec2 vel;
    int timer;
    int colour;

    ExplosionFragment(CIwVec2 const & startPos, CIwVec2 const & startVel, int _colour);
    bool update(int elapsed);
    void render();
};

#endif
