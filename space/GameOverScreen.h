#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H

#include "WelcomeScreen.h"
#include <SFML/Graphics.hpp>

class GameOverScreen : public WelcomeScreen {
public:
    GameOverScreen(float width, float height, int score);
    void draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    int getSelectedOption() const;

private:
    int selectedOptionIndex;
    sf::Text title;
    sf::Text scoreText;
    sf::Text options[2]; // For Restart and Exit options
    sf::Texture backgroundTexture;
    sf::Sprite background;
    sf::Font font; // Ensure a font is loaded during initialization
};

#endif // GAMEOVERSCREEN_H
