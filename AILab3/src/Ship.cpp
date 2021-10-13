#include "Ship.h"

Ship::Ship(float t_speed, float t_acceleration, float t_rotSpeed, float t_shipType, Behaviour* t_beh, sf::Vector2f t_pos, float t_maxSpeed) :
	m_speed(t_speed),
	m_acceleration(t_acceleration),
	m_rotSpeed(t_rotSpeed),
	m_maxSpeed(t_maxSpeed),
	m_minSpeed(-50),
	m_behaviour(t_beh)
{
	setTexture(t_shipType);
	setPosition(t_pos);
	setRotation(0);

}

void Ship::update(float t_deltaTime)
{
	m_behaviour->update(this, t_deltaTime);

	m_sprite.move(sf::Vector2f(m_velocity.x * m_speed * t_deltaTime, m_velocity.y * m_speed * t_deltaTime));

	handleBoundry();
}

sf::Vector2f const & Ship::getPosition() const
{
	return m_sprite.getPosition();
}

sf::Vector2f const & Ship::getVelocity()
{
	return m_velocity;
}

void Ship::accelerate()
{
	m_speed += m_acceleration;

	if (m_speed > m_maxSpeed)
		m_speed = m_maxSpeed;
}

void Ship::decelerate()
{
	m_speed -= m_acceleration;

	if (m_speed < m_minSpeed)
		m_speed = m_minSpeed;
}

void Ship::rotateL(float t_deltaTime)
{
	setRotation(m_sprite.getRotation() - m_speed * m_rotSpeed * t_deltaTime);
}

void Ship::rotateR(float t_deltaTime)
{
	setRotation(m_sprite.getRotation() + m_speed * m_rotSpeed * t_deltaTime);
}

void Ship::setPosition(sf::Vector2f t_pos)
{
	m_position = t_pos;
	m_sprite.setPosition(m_position);
}

void Ship::setRotation(float t_rot)
{
	m_velocity.x = cosf(t_rot * (3.14f / 180.0f));
	m_velocity.y = sinf(t_rot * (3.14f / 180.0f));
	m_sprite.setRotation(t_rot);
}


void Ship::setTargetPos(Ship* t_targetPos)
{
	m_targetPos = t_targetPos;
}

void Ship::setSpeed(float t_speed)
{
	m_speed = t_speed;
}

float Ship::getMaxSpeed()
{
	return m_maxSpeed;
}

float Ship::getMinNPCSpeed()
{
	return 0.0f;
}

Ship* Ship::getTargetPos() const
{
	return m_targetPos;
}


void Ship::draw(sf::RenderTarget& t_target, sf::RenderStates t_states) const
{
	t_target.draw(m_sprite, t_states);
}

void Ship::handleBoundry()
{
	if (m_sprite.getPosition().x > WINDOW_WIDTH + 11.0f)
	{
		setPosition(sf::Vector2f(-10.0f, m_sprite.getPosition().y));
	}

	if (m_sprite.getPosition().x < -11.0f)
	{
		setPosition(sf::Vector2f(WINDOW_WIDTH + 10.0f, m_sprite.getPosition().y));
	}
	if (m_sprite.getPosition().y > WINDOW_HEIGHT + 11.0f)
	{
		setPosition(sf::Vector2f(m_sprite.getPosition().x, -10.0f));
	}

	if (m_sprite.getPosition().y < -11.0f)
	{
		setPosition(sf::Vector2f(m_sprite.getPosition().x, WINDOW_HEIGHT + 10.0f));
	}
}

void Ship::setTexture(int t_shipNum)
{
	std::string fileLoc = "Assets\\images\\ship" + std::to_string(t_shipNum) + ".png";

	if (!m_texture.loadFromFile(fileLoc))
	{
		// simple error message if previous call fails
		std::cout << "problem loading ship " << t_shipNum << " texture" << std::endl;
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(40.0f, 41.0f);
}
