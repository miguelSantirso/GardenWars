#include "Sprite.h"

Sprite::Sprite(CIw2DImage* image) : graphic(image), angle(0), size(1), position(CIwVec2(0,0))
{
	offset.x = -(graphic->GetWidth() * 0.5);
	offset.y = -(graphic->GetHeight() * 0.5);
}

void Sprite::release()
{
	if (graphic != NULL)
		graphic = NULL;
}


void Sprite::draw(CIwVec2 camPos)
{
	screenPos.x = position.x - camPos.x + 0.5 * SCREEN_WIDTH;
	screenPos.y = position.y - camPos.y + 0.5 * SCREEN_HEIGHT;

	if (screenPos.x < - 0.5 * graphic->GetWidth() || 
		screenPos.x > SCREEN_WIDTH + 0.5 * graphic->GetWidth()||
		screenPos.y < - 0.5 * graphic->GetHeight() || 
		screenPos.y > SCREEN_HEIGHT + 0.5 * graphic->GetHeight())
	{
		return; // The sprite is not visible in the screen
	}

	transform.SetRot(angle);
	transform.SetTrans(screenPos);
	Iw2DSetTransformMatrix(transform);

	Iw2DDrawImage(graphic, offset, CIwSVec2(graphic->GetWidth() * size, graphic->GetHeight() * size));
}