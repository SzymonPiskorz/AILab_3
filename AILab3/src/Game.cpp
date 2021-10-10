#include "Game.h"
#include <iostream>

Game::Game() :
	m_window{ sf::VideoMode{ WINDOW_WIDTH, WINDOW_HEIGHT, 32U }, "AI Lab 3" },
	m_exitGame{ false },
	m_player{ 0.0f, 5.0f, 0.5f, 1.0f, new ControllerBehaviour, sf::Vector2f(500.0f, 500.0f)},
	m_wanderNPC{ 200.0f, 5.0f, 1.0f, 2.0f, new WanderBehaviour, sf::Vector2f(250.0f, 250.0f)},
	m_seekerNPC{ 250.0f, 5.0f, 0.5f, 3.0f, new SeekBehaviour, sf::Vector2f(700.0f, 250.0f)},
	m_arriveNPC{ 250.0f, 5.0f, 0.5f, 3.0f, new ArriveBehaviour, sf::Vector2f(700.0f, 250.0f)}
{
	setupFontAndText(); // load font 
	m_seekerNPC.setTargetPos(&m_player);
	m_arriveNPC.setTargetPos(&m_player);
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
	m_wanderNPC.update(t_deltaTime.asSeconds());
	m_seekerNPC.update(t_deltaTime.asSeconds());
	m_arriveNPC.update(t_deltaTime.asSeconds());

}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);
	m_window.draw(m_player);
	m_window.draw(m_wanderNPC);
	m_window.draw(m_seekerNPC);
	m_window.draw(m_arriveNPC);
	m_window.display();
}

void Game::setupFontAndText()
{
}
