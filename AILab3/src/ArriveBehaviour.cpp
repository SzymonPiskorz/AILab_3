#include "ArriveBehaviour.h"

void ArriveBehaviour::update(Ship* ship, float t_delaTime)
{
	if (ship->getPosition() != ship->getTargetPos()->getPosition())
	{

		sf::Vector2f velocity = ship->getTargetPos()->getPosition() - ship->getPosition();
		float mag = sqrt((velocity.x * velocity.x) + (velocity.y * velocity.y));
		velocity /= m_timeToTarget;

		if (velocity.x != 0 || velocity.y != 0)
		{

			if (mag < m_stopRadius)
				ship->setSpeed(ship->getMinNPCSpeed());
			else if (mag > m_slowRadius)
				ship->setSpeed(ship->getMaxSpeed());
			else
			{
				ship->setSpeed(ship->getMaxSpeed() * (mag / m_slowRadius));
			}

			velocity /= sqrt((velocity.x * velocity.x) + (velocity.y * velocity.y));
			velocity *= ship->getMaxSpeed();

			sf::Vector2f dir = velocity - ship->getVelocity();
			dir /= m_timeToTarget;

			if (sqrt((dir.x * dir.x) + (dir.y * dir.y)) < ship->getMaxSpeed())
			{
				dir /= sqrt((dir.x * dir.x) + (dir.y * dir.y));
				dir *= ship->getMaxSpeed();
			}

			//ship->setRotation(atan2f(dir.y, dir.x) * (180.0f / 3.14f));
		}
	}
}
