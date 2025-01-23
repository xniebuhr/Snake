#include "Engine.h"

Engine::Engine()
{
	// Create the window
	resolution = sf::Vector2f(800, 600);
	window.create(sf::VideoMode(resolution.x, resolution.y), "Snake");
	window.setFramerateLimit(60);

	// Set up the levels
	maxLevels = 0;
	checkLevelFiles();

	// Set the gamestate, pressing enter will call the startGame function
	currentGameState = GameState::STARTING;

	// Load all the text that will be displayed
	loadText();
}

void Engine::startGame()
{
	// Clear the directions and walls from old games
	directionQueue.clear();
	wallSections.clear();

	// Set logic to its starting state
	applesEatenThisLevel = 0;
	applesEatenTotal = 0;
	score = 0;
	speed = 4; // This number doesn't mean anything, I just found that it was a pretty balanced starting speed
	timeSinceLastMove = sf::Time::Zero;

	// Reset text so it doesn't say the old scores when a new game is started
	scoreText.setString("Score: 0");
	applesEatenText.setString("Apples: 0");

	// Setup the board
	apple.setPosition(sf::Vector2f(400, 300));
	currentLevel = 1;
	loadLevel(currentLevel);
	newSnake();
	snakeDirection = Direction::RIGHT;
	
	// Set the game state
	currentGameState = GameState::RUNNING;
	lastGameState = currentGameState;
}

void Engine::run()
{
	sf::Clock clock;
	sf::Time deltaTime;

	// Main loop
	while (window.isOpen())
	{
		deltaTime = clock.restart();
		
		if (currentGameState == GameState::PAUSED || currentGameState == GameState::GAMEOVER || currentGameState == GameState::STARTING)
		{
			input();

			if (currentGameState == GameState::GAMEOVER || currentGameState == GameState::STARTING)
			{
				draw();
			}

			sf::sleep(sf::milliseconds(2));
			continue;
		}

		timeSinceLastMove += deltaTime;
		
		input();
		update();
		draw();
	}
}

void Engine::newSnake()
{
	snake.clear();
	snake.emplace_back(sf::Vector2f(180, 300));
	snake.emplace_back(sf::Vector2f(160, 300));
	snake.emplace_back(sf::Vector2f(140, 300));
}

void Engine::addSnakeSection()
{
	sf::Vector2f newSectionPosition = snake[snake.size() - 1].getPosition();
	snake.emplace_back(newSectionPosition);
}

void Engine::addDirection(int newDirection)
{
	// Limit queue size to 4 so the user can put multiple inputs but not overflow the queue
	if (directionQueue.empty() || (directionQueue.back() != newDirection && directionQueue.size() <= 4))
	{
		directionQueue.emplace_back(newDirection);
	}
}

// Randomize the apple location until it isn't inside of a wall or the snake
void Engine::moveApple()
{
	sf::Vector2f appleResolution = sf::Vector2f(resolution.x / 20 - 2, resolution.y / 20 - 2);
	sf::Vector2f newAppleLocation;
	bool badLocation = false;
	srand(time(nullptr));

	do
	{
		badLocation = false;
		
		newAppleLocation.x = (float)(1 + rand() / ((RAND_MAX + 1u) / (int)appleResolution.x)) * 20;
		newAppleLocation.y = (float)(1 + rand() / ((RAND_MAX + 1u) / (int)appleResolution.y)) * 20;

		// Check if it is inside of the snake
		for (auto& s : snake)
		{
			if (s.getShape().getGlobalBounds().intersects(sf::Rect<float>(newAppleLocation.x, newAppleLocation.y, 20, 20)))
			{
				badLocation = true;
				break;
			}
		}

		//Check if it is inside of a wall
		for (auto& w : wallSections)
		{
			if (w.getShape().getGlobalBounds().intersects(sf::Rect<float>(newAppleLocation.x, newAppleLocation.y, 20, 20)))
			{
				badLocation = true;
				break;
			}
		}

	} while (badLocation);

	apple.setPosition(newAppleLocation);
}

void Engine::togglePause()
{
	if (currentGameState == GameState::RUNNING)
	{
		lastGameState = currentGameState;
		currentGameState = GameState::PAUSED;
	}
	else if (currentGameState == GameState::PAUSED)
	{
		currentGameState = lastGameState;
	}
}