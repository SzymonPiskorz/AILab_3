#include "Game.h"
#include <iostream>

Game::Game() :
	m_window{ sf::VideoMode{ WINDOW_WIDTH, WINDOW_HEIGHT, 32U }, "AI Lab 3" },
	m_exitGame{ false },
	m_player{ 0.01f, 5.0f, 2.0f, 1.0f, new ControllerBehaviour, sf::Vector2f(500.0f, 500.0f)},
	m_wanderNPC{ 400.0f, 5.0f, 1.0f, 2.0f, new WanderBehaviour, sf::Vector2f(250.0f, 250.0f)},
	m_seekerNPC{ 500.0f, 5.0f, 0.5f, 3.0f, new SeekBehaviour, sf::Vector2f(700.0f, 250.0f)},
	m_arriveSlowNPC{ 250.0f, 5.0f, 0.5f, 4.0f, new ArriveBehaviour, sf::Vector2f(700.0f, 250.0f), 200},
	m_arriveFastNPC{ 400.0f, 5.0f, 0.5f, 5.0f, new ArriveBehaviour, sf::Vector2f(700.0f, 250.0f), 500},
	m_pursueNPC{ 450.0f, 5.0f, 0.5f, 6.0f, new PursueBehaviour, sf::Vector2f(700.0f, 250.0f)}
{
	setupFontAndText(); // load font 
	m_seekerNPC.setTargetPos(&m_player);
	m_arriveSlowNPC.setTargetPos(&m_player);
	m_arriveFastNPC.setTargetPos(&m_player);
	m_pursueNPC.setTargetPos(&m_player);
	m_wanderNPC.setTargetPos(&m_player);
	m_player.setTargetPos(&m_player);
	

	m_player.setupFontAndText("Player");
	m_wanderNPC.setupFontAndText("Wander");
	m_seekerNPC.setupFontAndText("Seeker");
	m_arriveSlowNPC.setupFontAndText("Arrive Slow");
	m_arriveFastNPC.setupFontAndText("Arrive Fast");
	m_pursueNPC.setupFontAndText("Pursue");

	ships.push_back(m_wanderNPC);
	ships.push_back(m_seekerNPC);
	ships.push_back(m_arriveSlowNPC);
	ships.push_back(m_arriveFastNPC);
	ships.push_back(m_pursueNPC);
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if (sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		m_shipEnabled = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		m_shipEnabled = 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		m_shipEnabled = 2;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
		m_shipEnabled = 3;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
		m_shipEnabled = 4;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
		m_shipEnabled = 5;
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	m_player.update(t_deltaTime.asSeconds());
	if (m_shipEnabled == 5)
	{
		for (int i = 0; i < ships.size(); i++)
		{
			ships.at(i).update(t_deltaTime.asSeconds());
		}
	}
	else
	{
		ships.at(m_shipEnabled).update(t_deltaTime.asSeconds());
	}

}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);
	m_window.draw(m_player);
	m_window.draw(m_message);
	if (m_shipEnabled == 5)
	{
		for (int i = 0; i < ships.size(); i++)
		{
			m_window.draw(ships.at(i));
		}
	}
	else
	{
		m_window.draw(ships.at(m_shipEnabled));
	}
	

	m_window.display();
}

void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("Assets\\fonts\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}

	m_message.setFont(m_ArialBlackfont);
	m_message.setString("Press 1-5 to enable a specific alien ship, and press 6 to enable all of the alien ships \n 1. Wander \n 2. Seeker \n 3. Arrive Slow \n 4. Arrive Fast \n 5. Pursue");
	m_message.setPosition(0.0f, 0.0f);
	m_message.setCharacterSize(28U);
	m_message.setOutlineColor(sf::Color::White);
	m_message.setFillColor(sf::Color::Black);
	m_message.setOutlineThickness(3.0f);
}
