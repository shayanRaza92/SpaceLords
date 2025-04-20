#include "WelcomeScreen.h"
#include <iostream>

WelcomeScreen::WelcomeScreen(float width, float height) : selectedOptionIndex(0)
{
    // Load background texture
    if (!this->backgroundTexture.loadFromFile("Textures/background.jpg")) {  // Update the path as needed
        std::cout << "ERROR::WELCOME SCREEN::Could not load background texture" << std::endl;
    }
    this->background.setTexture(this->backgroundTexture);
    this->background.setScale(width / this->backgroundTexture.getSize().x, height / this->backgroundTexture.getSize().y);  // Scale background to fit window

    // Load font
    if (!font.loadFromFile("Textures/arial.ttf")) {
        std::cout << "ERROR::WELCOME SCREEN::Failed to load font" << std::endl;
    }

    // Title text
    title.setFont(font);
    title.setString("Space Chicken");
    title.setCharacterSize(60);
    title.setFillColor(sf::Color::Yellow);
    title.setPosition(width / 2 - title.getGlobalBounds().width / 2, height / 4);

    // Menu options
    std::string menuText[] = {"Start Game", "   ", "Exit"};
    for (int i = 0; i < 3; i++) {
        options[i].setFont(font);
        options[i].setString(menuText[i]);
        options[i].setCharacterSize(40);
        options[i].setPosition(width / 2 - options[i].getGlobalBounds().width / 2, height / 2 + i * 60);

        if (i == selectedOptionIndex) {
            options[i].setFillColor(sf::Color::Red);
        } else {
            options[i].setFillColor(sf::Color::White);
        }
    }
}

void WelcomeScreen::draw(sf::RenderWindow& window) {
    window.draw(this->background);  // Draw the background first
    window.draw(this->title);
    for (const auto& option : options) {
        window.draw(option);
    }
}

void WelcomeScreen::moveUp() {
    if (selectedOptionIndex - 1 >= 0) {
        options[selectedOptionIndex].setFillColor(sf::Color::White);
        selectedOptionIndex--;
        options[selectedOptionIndex].setFillColor(sf::Color::Red);
    }
}

void WelcomeScreen::moveDown() {
    if (selectedOptionIndex + 1 < 3) {
        options[selectedOptionIndex].setFillColor(sf::Color::White);
        selectedOptionIndex++;
        options[selectedOptionIndex].setFillColor(sf::Color::Red);
    }
}

int WelcomeScreen::getSelectedOption() const {
    return selectedOptionIndex;
}
