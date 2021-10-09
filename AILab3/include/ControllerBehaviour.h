#pragma once

#include "Behaviour.h"

class ControllerBehaviour : public Behaviour
{
	void update(Ship* ship, float t_delaTime);
};

