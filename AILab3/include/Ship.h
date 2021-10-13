#pragma once
#include "Global.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Behaviour;

class Ship : public sf::Drawable
{
public:
	
	Ship(float, float, float, float, Behaviour*, sf::Vector2f, float t_maxSpped = 400);

	virtual void update(float);

	sf::Vector2f const & getPosition() const;
	sf::Vector2f const & getVelocity();

	void accelerate();
	void decelerate();

	void rotateL(float);
	void rotateR(float);

	void setPosition(sf::Vector2f);
	void setRotation(float);

	Ship* getTargetPos() const;
	void setTargetPos(Ship*);

	void setSpeed(float);
	float getMaxSpeed();
	float getMinNPCSpeed();
	void setupFontAndText(std::string);
	void moveToTarget(sf::Vector2f, float );
	void updateRotation();

private:

	virtual void draw(sf::RenderTarget& t_target, sf::RenderStates t_states) const;

	void setVisionCone();

	void handleBoundry();
	void setTexture(int);

	sf::Texture m_texture;
	sf::Sprite m_sprite;

	sf::Vector2f m_velocity;
	float m_speed;
	float m_acceleration;
	float m_rotSpeed;
	float m_minSpeed;
	float m_maxSpeed;
	float m_direction;

	sf::Vector2f m_position;

	Behaviour* m_behaviour;

	Ship *m_targetPos;

	sf::Font m_ArialBlackfont;
	sf::Text m_shipName;

	float m_visionDistance;
	float m_visionAngle;
	sf::Color col1;
	sf::Color col2;
	sf::VertexArray m_coneOfVision;

};

#include "Behaviour.h"

