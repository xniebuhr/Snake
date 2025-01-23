#include "Engine.h"

void Engine::update()
{
	// Check if it's time for the next frame
	if (timeSinceLastMove.asSeconds() >= sf::seconds(1.f / float(speed)).asSeconds())
	{
		// Reset the time
		timeSinceLastMove = sf::Time::Zero;

		// Handle direction change
		if (!directionQueue.empty())
		{
			switch (snakeDirection)
			{
			case Direction::UP:
				if (directionQueue.front() != Direction::DOWN)
					snakeDirection = directionQueue.front();
				break;
			case Direction::DOWN:
				if (directionQueue.front() != Direction::UP)
					snakeDirection = directionQueue.front();
				break;
			case Direction::LEFT:
				if (directionQueue.front() != Direction::RIGHT)
					snakeDirection = directionQueue.front();
				break;
			case Direction::RIGHT:
				if (directionQueue.front() != Direction::LEFT)
					snakeDirection = directionQueue.front();
				break;
			}
			directionQueue.pop_front();
		}

		// Get the next position of the head to check collisions
		sf::Vector2f nextPosition = snake[0].getPosition();
		switch (snakeDirection)
		{
		case Direction::UP:
			nextPosition.y -= 20;
			break;
		case Direction::DOWN:
			nextPosition.y += 20;
			break;
		case Direction::LEFT:
			nextPosition.x -= 20;
			break;
		case Direction::RIGHT:
			nextPosition.x += 20;
			break;
		}

		// Wrap the snake around if it goes outside the screen
		if (nextPosition.x < 0)
			nextPosition.x = resolution.x - 20;
		else if (nextPosition.x >= resolution.x)
			nextPosition.x = 0;

		if (nextPosition.y < 0)
			nextPosition.y = resolution.y - 20;
		else if (nextPosition.y >= resolution.y)
			nextPosition.y = 0;

		// Check for collision with itself
		for (int i = 1; i < snake.size(); i++)
		{
			if (snake[i].getShape().getGlobalBounds().contains(nextPosition))
			{
				currentGameState = GameState::GAMEOVER;
				checkHighScore();
				return;
			}
		}

		// Check for collision with walls
		for (auto& w : wallSections)
		{
			if (w.getShape().getGlobalBounds().contains(nextPosition))
			{
				currentGameState = GameState::GAMEOVER;
				checkHighScore();
				return;
			}
		}

		// Save the position of the head
		sf::Vector2f lastSectionPosition = snake[0].getPosition();

		// Update snake's head position
		snake[0].setPosition(nextPosition);

		sf::Vector2f thisSectionPosition;
		// Update the position of each body section of the snake
		for (int i = 1; i < snake.size(); i++)
		{
			thisSectionPosition = snake[i].getPosition();
			snake[i].setPosition(lastSectionPosition);
			lastSectionPosition = thisSectionPosition;
		}

		// Update the position to be drawn correctly
		for (auto& s : snake)
		{
			s.update();
		}

		// Check if snake eats the apple
		if (snake[0].getShape().getGlobalBounds().intersects(apple.getSprite().getGlobalBounds()))
		{
			applesEatenThisLevel += 1;
			applesEatenTotal += 1;
			applesEatenText.setString("Apples: " + std::to_string(applesEatenTotal));

			addSnakeSection();
			moveApple();
			speed += .25;
			score *= 1.05;
		}

		// Increment score based on the apples eaten in the current level, with a multiplier for higher levels
		score += (applesEatenThisLevel + 1) * currentLevel;

		// Update the score text and move it to fit
		scoreText.setString("Score: " + std::to_string(score));
		sf::FloatRect scoreTextBounds = scoreText.getLocalBounds();
		scoreText.setPosition(sf::Vector2f(resolution.x - scoreTextBounds.width - 15, -9));

		// Check if it's time to move to the next level
		if (applesEatenThisLevel >= 20 && currentLevel < maxLevels)
		{
			beginNextLevel();
		}
	}
}