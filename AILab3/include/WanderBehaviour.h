#pragma once
#include "Behaviour.h"

class WanderBehaviour : public Behaviour
{
	void update(Ship* ship, float t_delaTime);

	sf::Clock timer;

	sf::Vector2f target;

	void pickTarget();
};

