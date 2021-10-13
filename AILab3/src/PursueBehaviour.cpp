#include "PursueBehaviour.h"

void PursueBehaviour::update(Ship* ship, float t_delaTime)
{

	sf::Vector2f dist = (ship->getTargetPos()->getPosition() + (ship->getTargetPos()->getVelocity() * 50.0f)) - ship->getPosition();

	if (dist.x != 0 || dist.y != 0)
	{
		dist = dist / (sqrt((dist.x * dist.x) + (dist.y * dist.y)));
		//ship->setRotation(atan2f(dist.y, dist.x) * (180 / 3.14f));
	}


}