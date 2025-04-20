#include "GameOverScreen.h"
#include <iostream>

GameOverScreen::GameOverScreen(float width, float height, int score)
    : WelcomeScreen(width, height), selectedOptionIndex(0)
{
    if (!this->backgroundTexture.loadFromFile("Textures/death.png")) {
        std::cout << "ERROR::GAMEOVER SCREEN::Could not load background texture" << std::endl;
    }
    this->background.setTexture(this->backgroundTexture);
    this->background.setScale(
        width / this->backgroundTexture.getSize().x, 
        height / this->backgroundTexture.getSize().y);

    // Set up game over title
    title.setFont(font);
    title.setString("Game Over");
    title.setCharacterSize(60);
    title.setFillColor(sf::Color::Red);
    title.setPosition(width / 2 - title.getGlobalBounds().width / 2, height / 4);

    // Set up score text
    scoreText.setFont(font);
    scoreText.setString("Score: " + std::to_string(score));
    scoreText.setCharacterSize(40);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(width / 2 - scoreText.getGlobalBounds().width / 2, height / 2.5);

    // Set up options
    std::string optionStrings[] = {"Restart", "Exit"};
    for (int i = 0; i < 2; ++i) {
        options[i].setFont(font);
        options[i].setString(optionStrings[i]);
        options[i].setCharacterSize(40);
        options[i].setFillColor(i == selectedOptionIndex ? sf::Color::Yellow : sf::Color::White);
        options[i].setPosition(width / 2 - options[i].getGlobalBounds().width / 2, height / 1.8 + i * 50);
    }
}

void GameOverScreen::draw(sf::RenderWindow& window) {
    window.draw(background);
    window.draw(title);
    window.draw(scoreText);
    for (int i = 0; i < 2; ++i) {
        window.draw(options[i]);
    }
}

void GameOverScreen::moveUp() {
    if (selectedOptionIndex > 0) {
        options[selectedOptionIndex].setFillColor(sf::Color::White);
        --selectedOptionIndex;
        options[selectedOptionIndex].setFillColor(sf::Color::Yellow);
    }
}

void GameOverScreen::moveDown() {
    if (selectedOptionIndex < 1) {
        options[selectedOptionIndex].setFillColor(sf::Color::White);
        ++selectedOptionIndex;
        options[selectedOptionIndex].setFillColor(sf::Color::Yellow);
    }
}

int GameOverScreen::getSelectedOption() const {
    return selectedOptionIndex;
}
