#include "Engine.h"

unsigned long long Engine::getHighScore()
{
	std::ifstream highScoreFile("High Score.txt");
	unsigned long long highScore = 0;
	std::string line;

	if (std::getline(highScoreFile, line))
	{
		highScore = std::stoi(line);
	}

	highScoreFile.close();

	return highScore;
}

void Engine::setNewHighScore(unsigned long long& score)
{
	std::ofstream highScoreFile("High Score.txt");

	highScoreFile << score;

	highScoreFile.close();
}

// Set the game state to gameover and handle high score checking
void Engine::checkHighScore()
{
	currentGameState = GameState::GAMEOVER;

	if (score > getHighScore())
	{
		setNewHighScore(score);
	}

	highScoreText.setString("High score: " + std::to_string(getHighScore()));
	yourScoreText.setString("Your score: " + std::to_string(score));
}