#include "ExplosionFragment.h"
#include "Config.h"

ExplosionFragment::ExplosionFragment(CIwVec2 const & startPos, CIwVec2 const & startVel, int _colour)
{
/*	if (ExplosionFragment::graphic == NULL)
		ExplosionFragment::graphic = Iw2DCreateImage("star.png");*/

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
	int size = TILE_WIDTH * 2;
    size = size * (1000-timer) / 1000;

	/*int offsetX = -(ExplosionFragment::graphic->GetWidth() * 0.5);
	int offsetY = -(ExplosionFragment::graphic->GetHeight() * 0.5);
	Iw2DDrawImage(ExplosionFragment::graphic, CIwSVec2(offsetX, offsetY), CIwSVec2(size, size));*/
}
