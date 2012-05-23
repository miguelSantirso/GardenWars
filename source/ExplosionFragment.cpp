#include "ExplosionFragment.h"
#include "Config.h"

ExplosionFragment::ExplosionFragment(CIw2DImage* graphic, CIwVec2 const & startPos, CIwVec2 const & startVel, int _colour) : Sprite(graphic)
{
	speed = 0.01;
    colour = _colour;
    timer = rand() % 20;
    position = startPos;
}

bool ExplosionFragment::update(int elapsed)
{
    timer += 1;

    // Move under gravity
	position.y -= speed;
	size += 0.12;
	angle += 600;

	speed *= 1.3;

    // The effect disappears after about 1 second
    return timer<35;
}


void ExplosionFragment::render(const CIwVec2& camPos)
{
	draw(camPos);
}