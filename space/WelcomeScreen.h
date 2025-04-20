#ifndef WELCOMESCREEN_H
#define WELCOMESCREEN_H

#include <SFML/Graphics.hpp>
#include <string>

class WelcomeScreen {
public:
    WelcomeScreen(float width, float height);
    void draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    int getSelectedOption() const;

protected:
    int selectedOptionIndex;
    sf::Font font;
    sf::Text title;
    sf::Text options[3];

    // Background texture and sprite
    sf::Texture backgroundTexture;
    sf::Sprite background;
};

#endif // WELCOMESCREEN_H
