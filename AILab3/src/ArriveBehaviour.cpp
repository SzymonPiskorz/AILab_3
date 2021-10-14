#include "ArriveBehaviour.h"

void ArriveBehaviour::update(Ship* ship, float t_delaTime)
{
	if (ship->getPosition() != ship->getTargetPos()->getPosition())
	{
		sf::Vector2f dist = ship->getTargetPos()->getPosition() - ship->getPosition();
		float mag = sqrt((dist.x * dist.x) + (dist.y * dist.y));

		if (mag < m_stopRadius)
			ship->setSpeed(ship->getMinNPCSpeed());
		else if (mag > m_slowRadius)
			ship->setSpeed(ship->getMaxSpeed());
		else
		{
			ship->setSpeed(ship->getMaxSpeed() * (mag / m_slowRadius));
		}

		sf::Vector2f unitVec = dist / mag;

		if (mag < m_stopRadius)
		{
			ship->moveToTarget(unitVec / 100.0f, t_delaTime);
		}
		else
			ship->moveToTarget(unitVec, t_delaTime);
	}
}
