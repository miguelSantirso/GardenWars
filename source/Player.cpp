#include "Player.h"
#include "s3eAccelerometer.h"

Player::Player(CIw2DImage* image) : Sprite(image)
{
	speed = 0.006;
	velocity.x = 0;
	velocity.y = 0;

	s3eAccelerometerStart();
}


void Player::update(World* theWorld)
{
	velocity.x = s3eAccelerometerGetX();
	velocity.y = (-600 - s3eAccelerometerGetY());

	float throttle = ABS(velocity.GetLength() / 100.0);
	if (throttle > 1)
		throttle = 1;

	if (velocity.GetLength() > 0)
		velocity.Normalise();

	angle = IwGeomAtan2(velocity.y, velocity.x);

	int nextPosX = position.x + throttle * speed * velocity.x;
	int nextPosY = position.y + throttle * speed * velocity.y;

	if (!theWorld->isPositionNavigable(nextPosX, nextPosY))
	{
		if (theWorld->isPositionNavigable(position.x, nextPosY))
			nextPosX = position.x;
		else if (theWorld->isPositionNavigable(nextPosX, position.y))
			nextPosY = position.y;
		else
			return;
	}

	position.x = nextPosX;
	position.y = nextPosY;
}

