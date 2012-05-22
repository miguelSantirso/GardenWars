#include "Star.h"

Star::Star(int x, int y)
{
	graphic = Iw2DCreateImage("star.png");

	worldX = x;
	worldY = y;
}

Star::~Star()
{
	release();
}

void Star::release()
{
	delete graphic;
}


void Star::draw(int camX, int camY)
{
	screenX = worldX - camX + 0.5*SCREEN_WIDTH;
	screenY = worldY - camY + 0.5 * SCREEN_HEIGHT;

	if (screenX < -graphic->GetWidth() || screenX > SCREEN_WIDTH || screenY < -graphic->GetHeight() || screenY > SCREEN_HEIGHT)
		return;

	CIwMat2D transform;
	transform.SetRot();
	transform.SetTrans(CIwSVec2(screenX, screenY));
	// Set this transform as the active transform for Iw2D
    Iw2DSetTransformMatrix(transform);

	int offsetX = -(graphic->GetWidth() * 0.5);
	int offsetY = -(graphic->GetHeight() * 0.5);
	Iw2DDrawImage(graphic, CIwSVec2(offsetX, offsetY));
}
