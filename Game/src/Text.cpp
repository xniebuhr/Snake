#include "Engine.h"

void Engine::setupText(sf::Text* textItem, const sf::Font& font, const std::string& value, int size, sf::Color color)
{
	textItem->setFont(font);
	textItem->setString(value);
	textItem->setCharacterSize(size);
	textItem->setFillColor(color);
}

// Load all the text to be used
void Engine::loadText()
{
	mainFont.loadFromFile("fonts/slant_regular.ttf");
	setupText(&titleText, mainFont, "Snake", 28, sf::Color::Blue);
	sf::FloatRect titleTextBounds = titleText.getLocalBounds();
	titleText.setPosition(sf::Vector2f(resolution.x / 2 - titleTextBounds.width / 2, -9));

	setupText(&currentLevelText, mainFont, "Level 1", 28, sf::Color::Blue);
	currentLevelText.setPosition(sf::Vector2f(15, -9));
	sf::FloatRect currentLevelTextBounds = currentLevelText.getGlobalBounds();

	setupText(&applesEatenText, mainFont, "Apples: 0", 28, sf::Color::Blue);
	applesEatenText.setPosition(sf::Vector2f(currentLevelTextBounds.left + currentLevelTextBounds.width + 20, -9));

	setupText(&scoreText, mainFont, "Score: " + std::to_string(score), 28, sf::Color::Blue);
	sf::FloatRect scoreTextBounds = scoreText.getLocalBounds();
	scoreText.setPosition(sf::Vector2f(resolution.x - scoreTextBounds.width - 15, -9));

	setupText(&gameOverText, mainFont, "GAME OVER", 72, sf::Color::Red);
	sf::FloatRect gameOverTextBounds = gameOverText.getLocalBounds();
	gameOverText.setPosition(sf::Vector2f(resolution.x / 2 - gameOverTextBounds.width / 2, 100));
	gameOverText.setOutlineColor(sf::Color::Black);
	gameOverText.setOutlineThickness(2);

	setupText(&pressEnterText, mainFont, "Press Enter to start", 38, sf::Color::Yellow);
	sf::FloatRect pressEnterTextBounds = pressEnterText.getLocalBounds();
	pressEnterText.setPosition(sf::Vector2f(resolution.x / 2 - pressEnterTextBounds.width / 2, 200));
	pressEnterText.setOutlineColor(sf::Color::Black);
	pressEnterText.setOutlineThickness(2);

	setupText(&yourScoreText, mainFont, "Your Score: " + std::to_string(score), 32, sf::Color::Cyan);
	sf::FloatRect yourScoreTextBounds = yourScoreText.getLocalBounds();
	yourScoreText.setPosition(sf::Vector2f(resolution.x / 2 - yourScoreTextBounds.width / 2, 300));
	yourScoreText.setOutlineColor(sf::Color::Black);
	yourScoreText.setOutlineThickness(2);

	setupText(&highScoreText, mainFont, "High Score: " + std::to_string(getHighScore()), 32, sf::Color::Cyan);
	sf::FloatRect highScoreTextBounds = highScoreText.getLocalBounds();
	highScoreText.setPosition(sf::Vector2f(resolution.x / 2 - highScoreTextBounds.width / 2, 350));
	highScoreText.setOutlineColor(sf::Color::Black);
	highScoreText.setOutlineThickness(2);

	setupText(&pausedText, mainFont, "Paused", 38, sf::Color::Cyan);
	sf::FloatRect pausedTextBounds = pausedText.getLocalBounds();
	pausedText.setPosition(sf::Vector2f(resolution.x / 2 - pausedTextBounds.width / 2, 200));
	pausedText.setOutlineColor(sf::Color::Black);
	pausedText.setOutlineThickness(2);
}
