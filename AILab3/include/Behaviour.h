#pragma once
#include <SFML/Graphics.hpp>

class Ship;

class Behaviour
{
public:
	virtual void update(Ship* ship, float t_delaTime) = 0;
};

#include "Ship.h"