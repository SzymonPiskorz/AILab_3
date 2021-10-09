#include "WanderBehaviour.h"

void WanderBehaviour::update(Ship* ship, float t_delaTime)
{
	if (timer.getElapsedTime().asSeconds() > 1)
	{
		timer.restart();

		if (rand() % 2 == 0)
			ship->rotateL(t_delaTime);
		else
			ship->rotateR(t_delaTime);
	}
}
