#include "SeekBehaviour.h"

void SeekBehaviour::update(Ship* ship, float t_delaTime)
{
	//	velocity *= maxSpeed;

	//	movement = velocity;

	sf::Vector2f dist = ship->getTargetPos()->getPosition() - ship->getPosition();

	if (dist.x != 0 || dist.y != 0)
	{
		dist = dist / (sqrt((dist.x * dist.x) + (dist.y * dist.y)));
		ship->setRotation(atan2f(dist.y, dist.x) * (180 / 3.14f));
	}


}