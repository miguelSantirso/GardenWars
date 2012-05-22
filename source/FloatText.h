#ifndef _FloatText_h_
#define _FloatText_h_

#include "Effect.h"

#include "IwGeom.h"
#include "IwString.h"

// Floating text - drifts upwards, then disappears. Used to show the player how much score they're getting.
struct FloatText : public Effect
{
    CIwVec2 pos;
    int timer;
    CIwStringL text;

    FloatText(CIwVec2 const & startPos, const char * string);
    bool update(int elapsed);
    void render();
};

#endif
