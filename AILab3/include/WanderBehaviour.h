#pragma once
#include "Behaviour.h"

class WanderBehaviour : public Behaviour
{
	void update(Ship* ship, float t_delaTime);

	sf::Clock timer;

	sf::Vector2f target = sf::Vector2f(NULL, NULL);


	void pickTarget(Ship* ship);

	float m_targetCentre = 100;
	float m_targetRadius = 100;
	float m_restartTime = 0;
};

