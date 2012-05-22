#include "Player.h"
#include "s3eAccelerometer.h"

Player::Player(): worldX(0), worldY(0)
{
	graphic = Iw2DCreateImage("character.png");

	speed = 0.03;
	velocity.x = 0;
	velocity.y = 0;

	s3eAccelerometerStart();
}


Player::~Player()
{
	release();
}


void Player::release()
{
	delete graphic;

	s3eAccelerometerStop();
}


void Player::update()
{
	velocity.x = s3eAccelerometerGetX();
	velocity.y = (-600 - s3eAccelerometerGetY());
	if (velocity.GetLength() > 0)
		velocity.Normalise();

	worldX += speed * velocity.x;
	worldY += speed * velocity.y;

	// Clamp world coordinates
	if (worldX < 0)
		worldX = 0;
	if (worldX > WORLD_PIXELS_WIDTH)
		worldX = WORLD_PIXELS_WIDTH;
	if (worldY < 0)
		worldY = 0;
	if (worldY > WORLD_PIXELS_HEIGHT)
		worldY = WORLD_PIXELS_HEIGHT;
}


void Player::draw()
{
	CIwMat2D transform;
	transform.SetRot(IwGeomAtan2(velocity.y, velocity.x));
	transform.SetTrans(CIwSVec2(0.5*SCREEN_WIDTH, 0.5*SCREEN_HEIGHT));
	// Set this transform as the active transform for Iw2D
    Iw2DSetTransformMatrix(transform);

	int offsetX = -(graphic->GetWidth() * 0.5);
	int offsetY = -(graphic->GetHeight() * 0.5);
	Iw2DDrawImage(graphic, CIwSVec2(offsetX, offsetY));
}
