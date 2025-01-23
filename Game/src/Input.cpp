#include "Engine.h"

void Engine::input()
{
	sf::Event event{};

	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}

		if (event.type == sf::Event::KeyPressed)
		{
			// Toggle pause with escape
			if (event.key.code == sf::Keyboard::Escape)
			{
				togglePause();
			}

			// Start the game
			if (currentGameState == GameState::GAMEOVER || currentGameState == GameState::STARTING)
			{
				if (event.key.code == sf::Keyboard::Enter)
				{
					startGame();
				}
			}

			// Get direction input
			if (event.key.code == sf::Keyboard::Up)
			{
				addDirection(Direction::UP);
			}
			else if (event.key.code == sf::Keyboard::Down)
			{
				addDirection(Direction::DOWN);
			}
			else if (event.key.code == sf::Keyboard::Left)
			{
				addDirection(Direction::LEFT);
			}
			else if (event.key.code == sf::Keyboard::Right)
			{
				addDirection(Direction::RIGHT);
			}
		}
	}
}
