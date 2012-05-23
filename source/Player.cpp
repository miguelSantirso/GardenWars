#include "Player.h"
#include "s3eAccelerometer.h"

Player::Player(CIw2DImage* image) : Sprite(image)
{
	speed = 0.004;
	velocity.x = 0;
	velocity.y = 0;

	s3eAccelerometerStart();
}


void Player::update()
{
	velocity.x = s3eAccelerometerGetX();
	velocity.y = (-600 - s3eAccelerometerGetY());

	float throttle = ABS(velocity.GetLength() / 100.0);
	if (throttle > 1)
		throttle = 1;

	if (velocity.GetLength() > 0)
		velocity.Normalise();

	position.x += throttle * speed * velocity.x;
	position.y += throttle * speed * velocity.y;

	angle = IwGeomAtan2(velocity.y, velocity.x);

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

