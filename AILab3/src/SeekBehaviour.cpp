#include "SeekBehaviour.h"

void SeekBehaviour::update(Ship* ship, float t_delaTime)
{

	sf::Vector2f dist = ship->getTargetPos()->getPosition() - ship->getPosition();

	if (ship->getPosition() != ship->getTargetPos()->getPosition())
	{
		dist = dist / (sqrt((dist.x * dist.x) + (dist.y * dist.y)));
		ship->moveToTarget(dist, t_delaTime);
		
	}


}
