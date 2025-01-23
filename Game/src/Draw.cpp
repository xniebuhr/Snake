#include "Engine.h"

void Engine::draw()
{
	// Clear the screen
	window.clear(sf::Color::Black);

	// Draw the walls
	for (auto& w : wallSections)
	{
		window.draw(w.getShape());
	}

	// Draw the apple
	window.draw(apple.getSprite());

	// Draw the snake
	for (auto& s : snake) {
		window.draw(s.getShape());
	}

	// Draw text to screen
	window.draw(titleText);
	window.draw(currentLevelText);
	window.draw(applesEatenText);
	window.draw(scoreText);

	// Draw text for different game states
	if (currentGameState == GameState::GAMEOVER)
	{
		window.draw(gameOverText);
		window.draw(pressEnterText);
		window.draw(highScoreText);
		window.draw(yourScoreText);
	}

	if (currentGameState == GameState::STARTING)
	{
		window.draw(pressEnterText);
	}

	if (currentGameState == GameState::PAUSED)
	{
		window.draw(pausedText);
	}

	// Display everything
	window.display();
}
