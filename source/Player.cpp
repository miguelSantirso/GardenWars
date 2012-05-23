#include "Player.h"
#include "s3eAccelerometer.h"

Player::Player()
{
	graphic = Iw2DCreateImage("character.png");

	position = CIwVec2(50, 50);

	speed = 0.006;
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

	position.x += speed * velocity.x;
	position.y += speed * velocity.y;

	// Clamp world coordinates
	if (position.x < 0)
		position.x = 0;
	if (position.x > WORLD_PIXELS_WIDTH)
		position.x = WORLD_PIXELS_WIDTH;
	if (position.y < 0)
		position.y = 0;
	if (position.y > WORLD_PIXELS_HEIGHT)
		position.y = WORLD_PIXELS_HEIGHT;
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
