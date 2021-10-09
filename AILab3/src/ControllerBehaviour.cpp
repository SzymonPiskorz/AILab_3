#include "ControllerBehaviour.h"

void ControllerBehaviour::update(Ship* ship, float t_delaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		ship->accelerate();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		ship->decelerate();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		ship->rotateL(t_delaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		ship->rotateR(t_delaTime);
}
