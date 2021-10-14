#include "WanderBehaviour.h"

void WanderBehaviour::update(Ship* ship, float t_delaTime)
{
	if (timer.getElapsedTime().asSeconds() > m_restartTime)
	{
		timer.restart();

		pickTarget(ship);
	}

	if(target.x != NULL && target.y != NULL)
		ship->moveToTarget(target, t_delaTime);
}

void WanderBehaviour::pickTarget(Ship* ship)
{
	m_restartTime = 2;

	sf::Vector2f targetOffset = ship->getPosition() + ((ship->getVelocity() / 
		(sqrt((ship->getVelocity().x * ship->getVelocity().x) + (ship->getVelocity().y * ship->getVelocity().y)))) * m_targetCentre);

	float randRad = (rand() % 360) * (180.0f / 3.14f);
	target = sf::Vector2f(cosf(randRad), sinf(randRad)) * m_targetRadius + targetOffset;

	target -= ship->getPosition();
	target /= sqrt((target.x * target.x) + (target.y * target.y));
}
