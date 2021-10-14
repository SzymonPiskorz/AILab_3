#include "Ship.h"

Ship::Ship(float t_speed, float t_acceleration, float t_rotSpeed, float t_shipType, Behaviour* t_beh, sf::Vector2f t_pos, float t_maxSpeed) :
	m_speed(t_speed),
	m_acceleration(t_acceleration),
	m_rotSpeed(t_rotSpeed),
	m_maxSpeed(t_maxSpeed),
	m_minSpeed(0.01f),
	m_behaviour(t_beh)
{
	setTexture(t_shipType);
	setPosition(t_pos);
	setRotation(0);
	m_direction = 0;
	m_visionDistance = 200;
	m_visionAngle = 45 * 3.141f * 180;
	col1 = sf::Color(255, 0, 0, 255);
	col2 = sf::Color(255, 0, 0, 255);
}

void Ship::update(float t_deltaTime)
{
	m_shipName.setPosition(getPosition() + sf::Vector2f(20, 20));
	m_behaviour->update(this, t_deltaTime);

	m_position += m_velocity * t_deltaTime;

	m_sprite.setPosition(m_position);

	handleBoundry();
	updateRotation();
	setVisionCone();
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

	m_velocity = (m_velocity / (sqrt((m_velocity.x * m_velocity.x) + (m_velocity.y * m_velocity.y)))) * m_speed;
}

void Ship::decelerate()
{
	m_speed -= m_acceleration;

	if (m_speed < m_minSpeed)
		m_speed = m_minSpeed;

	m_velocity = (m_velocity / (sqrt((m_velocity.x * m_velocity.x) + (m_velocity.y * m_velocity.y)))) * m_speed;
}

void Ship::rotateL(float t_deltaTime)
{
	m_direction -= m_rotSpeed * t_deltaTime;
	m_velocity = sf::Vector2f(cosf(m_direction), sinf(m_direction)) * m_speed;
	updateRotation();
}

void Ship::rotateR(float t_deltaTime)
{
	m_direction += m_rotSpeed * t_deltaTime;
	m_velocity = sf::Vector2f(cosf(m_direction), sinf(m_direction)) * m_speed;
	updateRotation();
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
	return 0.01f;
}

Ship* Ship::getTargetPos() const
{
	return m_targetPos;
}


void Ship::draw(sf::RenderTarget& t_target, sf::RenderStates t_states) const
{
	t_target.draw(m_shipName, t_states);
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

void Ship::setupFontAndText(std::string t_string)
{
	if (!m_ArialBlackfont.loadFromFile("Assets\\fonts\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}

	m_shipName.setFont(m_ArialBlackfont);
	m_shipName.setString(t_string);
	m_shipName.setPosition(getPosition()+sf::Vector2f(20, 20));
	m_shipName.setCharacterSize(18U);
	m_shipName.setOutlineColor(sf::Color::White);
	m_shipName.setFillColor(sf::Color::Black);
	m_shipName.setOutlineThickness(3.0f);
}

void Ship::setVisionCone()
{
	float min = atan2f(m_velocity.y, m_velocity.x) - m_visionAngle;
	float max = atan2f(m_velocity.y, m_velocity.x) + m_visionAngle;

	sf::Vector2f minVec = sf::Vector2f(cosf(min), sinf(min));
	sf::Vector2f maxVec = sf::Vector2f(cosf(max), sinf(max));

	float minCross = (minVec.x * (getTargetPos()->getPosition() - getPosition()).y) - (minVec.y * (getTargetPos()->getPosition() - getPosition()).x);
	float maxCross = (maxVec.x * (getTargetPos()->getPosition() - getPosition()).y) - (maxVec.y * (getTargetPos()->getPosition() - getPosition()).x);
	
	sf::Vector2f distVec = getTargetPos()->getPosition() - getPosition();
	
	if (minCross > 0 && maxCross < 0)
	{
		
		if (((distVec.x * distVec.x) + (distVec.y * distVec.y)) < m_visionDistance * m_visionDistance)
		{
			col1 = sf::Color(255, 0, 0, 255);
			col2 = sf::Color(255, 0, 0, 255);
			std::cout << "in vision" << std::endl;
		}
		else
		{
			col1 = sf::Color(0, 0, 255, 255);
			col2 = sf::Color(0, 0, 255, 255);
		}
	}
}

void Ship::moveToTarget(sf::Vector2f t_target, float t_deltaTime)
{
	if (((m_velocity.x* m_velocity.x) + (m_velocity.y * m_velocity.y)) > m_maxSpeed * m_maxSpeed)
	{
		m_velocity = (m_velocity/(sqrt((m_velocity.x * m_velocity.x) + (m_velocity.y * m_velocity.y)))) * m_maxSpeed;
	}

	m_velocity += t_target * m_speed * t_deltaTime;
}

void Ship::updateRotation()
{
	m_sprite.setRotation((atan2f(m_velocity.y, m_velocity.x)) * (180.0f/ 3.14f));
}

float Ship::getHeading()
{
	return m_direction;
}
