#ifndef _Effects_h_
#define _Effects_h_

#include "Iw2D.h"

// Note: the position of effects is stored as a fixed point position in the playing area.
// So IW_GEOM_ONE is the size of a tile.
// This allows the positions to remain consistant when the screen is rotated

/**
 * Base class for graphical effects
 */
struct Effect
{
    virtual bool update(int elapsed) = 0;
	virtual void render(const CIwVec2& camPos) = 0;
    virtual ~Effect() {}
};

#endif
