#pragma once
#include "Behaviour.h"
class PursueBehaviour : public Behaviour
{
	void update(Ship* ship, float t_delaTime);

	sf::Vector2f offset = sf::Vector2f(20.0f, 20.0f);
};

