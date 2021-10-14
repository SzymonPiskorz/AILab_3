#include "PursueBehaviour.h"

void PursueBehaviour::update(Ship* ship, float t_delaTime)
{

	float speed = sqrt((ship->getVelocity().x* ship->getVelocity().x) + (ship->getVelocity().y * ship->getVelocity().y));


	if (ship->getPosition() != ship->getTargetPos()->getPosition())
	{
		
		if (speed == 0)
			speed = 1;

		sf::Vector2f unitVec = ship->getTargetPos()->getVelocity() / sqrt((ship->getTargetPos()->getVelocity().x * ship->getTargetPos()->getVelocity().x) +
																		(ship->getTargetPos()->getVelocity().y * ship->getTargetPos()->getVelocity().y));
		sf::Vector2f dist = ship->getTargetPos()->getPosition() - ship->getPosition();
		float mag = sqrt((dist.x * dist.x) + (dist.y * dist.y));

		sf::Vector2f pointAhead = ship->getTargetPos()->getPosition() + (unitVec * mag) / speed + offset;

		sf::Vector2f targetPoint = pointAhead - ship->getPosition();
		sf::Vector2f targetUnitVec = targetPoint / sqrt((targetPoint.x * targetPoint.x) + (targetPoint.x * targetPoint.x));

		ship->moveToTarget(targetUnitVec, t_delaTime);
	}


}