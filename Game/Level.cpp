#include "Engine.h"

// Check to see if level files exist, add them to the levels vector and increment max levels if they do
void Engine::checkLevelFiles()
{
	std::ifstream levelsManifest("levels/levels.txt");
	std::ifstream testFile;

	for (std::string manifestLine; getline(levelsManifest, manifestLine);)
	{
		testFile.open("levels/" + manifestLine);
		if (testFile.is_open())
		{
			levels.emplace_back("levels/" + manifestLine);
			testFile.close();
			maxLevels++;
		}
	}
}

// Opens the level file and adds a wall wherever an 'x' is seen
void Engine::loadLevel(int& levelNumber)
{
	std::string levelFile = levels[levelNumber - 1];
	std::ifstream level(levelFile);
	std::string line;

	if (level.is_open())
	{
		for (int column = 0; column < 30; column++)
		{
			getline(level, line);
			for (int row = 0; row < 40; row++)
			{
				if (line[row] == 'x')
				{
					wallSections.emplace_back(Wall(sf::Vector2f(row * 20, column * 20), sf::Vector2f(20, 20)));
				}
			}
		}
	}
	level.close();
}

void Engine::beginNextLevel()
{
	// Increment the level
	currentLevel++;

	// Clear the walls and direction input
	wallSections.clear();
	directionQueue.clear();

	// Reset the speed, starting faster each level to make it more difficult
	speed = 4 + (1.5 * currentLevel);

	// Reset the remaining logic and text
	applesEatenThisLevel = 0;
	timeSinceLastMove = sf::Time::Zero;
	currentLevelText.setString("Level " + std::to_string(currentLevel));

	// Reset the board
	loadLevel(currentLevel);
	newSnake();
	apple.setPosition(sf::Vector2f(400, 300));
	snakeDirection = Direction::RIGHT;
}