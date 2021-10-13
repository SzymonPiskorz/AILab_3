#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>
#include "Global.h"
#include "Ship.h"

#include "ControllerBehaviour.h"
#include "WanderBehaviour.h"
#include "SeekBehaviour.h"
#include "ArriveBehaviour.h"
#include "PursueBehaviour.h"

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();

	void setupFontAndText();

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_message; // text used for message on screen
	bool m_exitGame; // control exiting game

	Ship m_player;
	Ship m_wanderNPC;
	Ship m_seekerNPC;
	Ship m_arriveSlowNPC;
	Ship m_arriveFastNPC;
	Ship m_pursueNPC;

	std::vector<Ship> ships;

	int m_shipEnabled = 0;
};

#endif // !GAME_HPP

