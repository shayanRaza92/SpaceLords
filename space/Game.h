#pragma once

#include <map>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "WelcomeScreen.h"  // Include the WelcomeScreen header
#include "Villain.h"
#include "GameOverScreen.h"
#include "PowerUps.h"

class Game
{
private:
    // Window
    sf::RenderWindow* window;

    // Resources
    std::map<std::string, sf::Texture*> textures;
    std::vector<Bullet*> bullets;

    // GUI
    sf::Font font;
    sf::Text pointText;

    sf::Text gameOverText;

    // World
    sf::Texture worldBackgroundTex;
    sf::Sprite worldBackground;

    // Systems
    unsigned points;

    // Player
    Player* player;

    // Villain

    Villain* villain;  // Old single villain pointer, keep it for a fallback or testing
    std::vector<Villain*> villains;  // Vector of villains
    float villainSpawnTimer;
    float villainSpawnTimerMax;




    // Player GUI
    sf::RectangleShape playerHpBar;
    sf::RectangleShape playerHpBarBack;

    // Enemies
    float spawnTimer;
    float spawnTimerMax;
    std::vector<Enemy*> enemies;

    //Power Ups
    std::vector<PowerUp*> powerUps;
    float powerUpSpawnTimer;
    float powerUpSpawnTimerMax;

    // Welcome Screen
    WelcomeScreen* welcomeScreen;
    bool isWelcomeScreenActive;  // Flag to track whether the welcome screen is active

    //gameover Screen

    GameOverScreen* gameOverScreen;
    bool isGameOver;  // Pointer to the GameOverScreen

    // Private functions
    void initWindow();
    void initTextures();
    void initGUI();
    void initWorld();
    void initSystems();
    void initPlayer();
    void initEnemies();
    void initWelcomeScreen();
    void initGameOverScreen();
    void initPowerUp();

public:
    Game();
    virtual ~Game();

    // Functions
    void run();

    void updatePollEvents();
    void updateInput();
    void updateGUI();
    void updateWorld();
    void updateCollision();
    void updateBullets();
    void updateEnemies();
    void updateVillain();
    void updateCombat();
    void updatePowerUps();
    void update();

    void renderGUI();
    void renderWorld();
    void render();
};
