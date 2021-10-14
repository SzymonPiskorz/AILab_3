#pragma once
#include "Behaviour.h"
class ArriveBehaviour : public Behaviour
{
	void update(Ship* ship, float t_delaTime);

private:
	float m_slowRadius = 250;
	float m_stopRadius = 100;
	float m_timeToTarget  = 0.5f;
};

