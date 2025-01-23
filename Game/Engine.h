#pragma once
#include "SnakeSection.h"
#include "Apple.h"
#include "Wall.h"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <vector>
#include <deque>
#include <iostream>
#include <fstream>

class Engine
{
private:
	// Window variables
	sf::Vector2f resolution;
	sf::RenderWindow window;
	
	// Game objects
	std::vector<SnakeSection> snake;
	std::vector<Wall> wallSections;
	Apple apple;
	
	// Level variables
	int currentLevel;
	int maxLevels;
	std::vector<std::string> levels;
	
	// Direction handling
	int snakeDirection;
	std::deque<int> directionQueue;

	// Delta time handling
	double speed;
	sf::Time timeSinceLastMove;
	
	// Game states
	int currentGameState;
	int lastGameState;

	// Apple counters
	int applesEatenThisLevel;
	int applesEatenTotal;

	// Score
	unsigned long long score;

	// Font and text
	sf::Font mainFont;
	sf::Text titleText;
	sf::Text applesEatenText;
	sf::Text currentLevelText;
	sf::Text scoreText;
	sf::Text gameOverText;
	sf::Text pressEnterText;
	sf::Text highScoreText;
	sf::Text yourScoreText;
	sf::Text pausedText;

public:
	Engine();

	enum Direction { UP, RIGHT, DOWN, LEFT };
	enum GameState { STARTING, RUNNING, PAUSED, GAMEOVER };
	
	// Main loop functions
	void run();
	void input();
	void update();
	void draw();
	
	// Game start functions
	void startGame();
	void newSnake();

	// Game logic functions
	void addSnakeSection();
	void addDirection(int newDirection);
	void moveApple();
	
	// Changing gamestate function
	void togglePause();
	
	// Level functions
	void checkLevelFiles();
	void loadLevel(int& levelNumber);
	void beginNextLevel();

	// Text functions
	static void setupText(sf::Text* textItem, const sf::Font& font, const std::string& value, int size, sf::Color color);
	void loadText();
	
	// Score functions
	unsigned long long getHighScore();
	void setNewHighScore(unsigned long long& score);
	void checkHighScore();
};