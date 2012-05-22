#include "ExplosionFragment.h"


ExplosionFragment::ExplosionFragment(CIwVec2 const & startPos, CIwVec2 const & startVel, int _colour)
{
    colour = _colour;
    timer = rand() % 200;
    pos = startPos;
    vel = startVel;

    vel.y -= 100000;
}
bool ExplosionFragment::update(int elapsed)
{
    timer += elapsed;

    // Move under gravity
    pos += vel * elapsed;

    vel.y += elapsed * 300;

    // The effect disappears after about 1 second
    return timer<1000;
}
void ExplosionFragment::render()
{
    int size = g_TileSize * 2;
    size = size * (1000-timer) / 1000;
    DrawSpriteCentered(starImage, IW_FIXED_MUL(pos.x, g_TileSize), IW_FIXED_MUL(pos.y, g_TileSize), size);
}
