#include "Game.h"

// Private functions

void Game::initWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Swaglords of Space - Game 3", sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(144);
    this->window->setVerticalSyncEnabled(false);
}

void Game::initTextures()
{
    this->textures["BULLET"] = new sf::Texture();
    this->textures["BULLET"]->loadFromFile("Textures/bullet.png");
}

void Game::initGUI()
{
    // Load font
    if (!this->font.loadFromFile("Textures/arial.ttf"))
        std::cout << "ERROR::GAME::Failed to load font" << "\n";

    // Init point text
    this->pointText.setPosition(700.f, 25.f);
    this->pointText.setFont(this->font);
    this->pointText.setCharacterSize(20);
    this->pointText.setFillColor(sf::Color::White);
    this->pointText.setString("test");

    this->gameOverText.setFont(this->font);
    this->gameOverText.setCharacterSize(60);
    this->gameOverText.setFillColor(sf::Color::Red);
    this->gameOverText.setString("Game Over!");
    this->gameOverText.setPosition(
        this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f, 
        this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f
    );

    // Init player GUI
    this->playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
    this->playerHpBar.setFillColor(sf::Color::Red);
    this->playerHpBar.setPosition(sf::Vector2f(20.f, 20.f));

    this->playerHpBarBack = this->playerHpBar;
    this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));
}

void Game::initWorld()
{
    if (!this->worldBackgroundTex.loadFromFile("Textures/background1.jpg"))
    {
        std::cout << "ERROR::GAME::COULD NOT LOAD BACKGROUND TEXTURE" << "\n";
    }

    this->worldBackground.setTexture(this->worldBackgroundTex);
}

void Game::initSystems()
{
    this->points = 0;
}

void Game::initPowerUp(){
    this->powerUpSpawnTimer = 0.f;
    this->powerUpSpawnTimerMax = 400.f;  // Spawn a power-up every 400 frames
}

void Game::initPlayer()
{
    this->player = new Player();
}

void Game::initEnemies()
{
    this->spawnTimerMax = 50.f;
    this->spawnTimer = this->spawnTimerMax;
}

void Game::initGameOverScreen()
{
    // Assuming that you want to pass the score and window dimensions to the game over screen
    int score = this->points;  // Assuming `points` tracks the player's score
    this->gameOverScreen = new GameOverScreen(800, 600, score);  // Initialize with window size and score
    this->isGameOver=true;
}

void Game::initWelcomeScreen()
{
    this->welcomeScreen = new WelcomeScreen(800, 600);  // Initialize the welcome screen with window dimensions
    this->isWelcomeScreenActive = true;  // Set to true to show the welcome screen at the start
}

// Constructor / Destructor
Game::Game()
{
    this->initWindow();
    this->initTextures();
    this->initGUI();
    this->initWorld();
    this->initSystems();
    this->initPlayer();
    this->initEnemies();
    this->initWelcomeScreen();  // Initialize welcome screen
    this->initGameOverScreen();
    this->initPowerUp();
     // Initialize villain-related variables
    this->villain = nullptr;
    this->villainSpawnTimerMax = 500.f;  // Example: Spawn after 500 frames
    this->villainSpawnTimer = 0.f;

}

Game::~Game()
{
    delete this->window;
    delete this->player;
    delete this->welcomeScreen;  // Clean up welcome screen
    delete this->gameOverScreen;  // Clean up game over screen

    // Delete textures
    for (auto& i : this->textures)
    {
        delete i.second;
    }

    // Delete bullets
    for (auto* i : this->bullets)
    {
        delete i;
    }

    // Delete enemies
    for (auto* i : this->enemies)
    {
        delete i;
    }

    if (this->villain)
    delete this->villain;

}

// Functions


void Game::updatePollEvents()
{
    sf::Event e;
    while (this->window->pollEvent(e))
    {
        if (e.Event::type == sf::Event::Closed)
            this->window->close();
        if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
            this->window->close();
    }
}

void Game::updateInput()
{
    if (this->isWelcomeScreenActive)
    {
        // Handle navigation on the welcome screen
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            this->welcomeScreen->moveUp();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            this->welcomeScreen->moveDown();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            int selectedOption = this->welcomeScreen->getSelectedOption();
            std::cout << "Enter Pressed, Option: " << selectedOption << std::endl;  // Debugging line
            if (selectedOption == 0)  // Start Game
            {
                this->isWelcomeScreenActive = false;  // Start the game
                std::cout << "Welcome Screen Finished, Game Started." << std::endl;  // Debugging line
            }
            else if (selectedOption == 2)  // Exit
            {
                this->window->close();  // Close the window
            }
        }
    }
    else if (this->isGameOver){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            this->gameOverScreen->moveUp();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            this->gameOverScreen->moveDown();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            int selectedOption = this->gameOverScreen->getSelectedOption();
            std::cout << "Enter Pressed, Option: " << selectedOption << std::endl;  // Debugging line
            if (selectedOption == 0)  // Start Game
            {
                this->isGameOver = false;  // Start the game
                std::cout << "Welcome Screen Finished, Game Started." << std::endl;  // Debugging line
            }
            else if (selectedOption == 2)  // Exit
            {
                this->window->close();  // Close the window
            }
        }
    }
    else
    {
        // Regular game controls when welcome screen is not active
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            this->player->move(-1.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            this->player->move(1.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            this->player->move(0.f, -1.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            this->player->move(0.f, 1.f);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->player->canAttack())
        {
            this->bullets.push_back(
                new Bullet(
                    this->textures["BULLET"], 
                    this->player->getPos().x + this->player->getBounds().width / 2.f, 
                    this->player->getPos().y, 
                    0.f, 
                    -1.f, 
                    5.f
                )
            );
        }
    }
}
void Game::updateCombat()
{
	for (int i = 0; i < this->enemies.size(); ++i)
	{
		bool enemy_deleted = false;
		for (size_t k = 0; k < this->bullets.size() && enemy_deleted == false; k++)
		{
			if (this->enemies[i]->getBounds().intersects(this->bullets[k]->getBounds()))
			{
				this->points += this->enemies[i]->getPoints();

				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin() + i);

				delete this->bullets[k];
				this->bullets.erase(this->bullets.begin() + k);

				enemy_deleted = true;
			}
		}
	}
}

void Game::updateEnemies()
{
	//Spawning
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->enemies.push_back(new Enemy(rand() % this->window->getSize().x-20.f, -100.f));
		this->spawnTimer = 0.f;
	}

	//Update
	unsigned counter = 0;
	for (auto *enemy : this->enemies)
	{
		enemy->update();

		//Bullet culling (top of screen)
		if (enemy->getBounds().top > this->window->getSize().y)
		{
			//Delete enemy
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
		}
		//Enemy player collision
		else if(enemy->getBounds().intersects(this->player->getBounds()))
		{
			this->player->loseHp(this->enemies.at(counter)->getDamage());
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
		}

		++counter;
	}
}

void Game::updatePowerUps()
{
    // Spawning power-ups
    this->powerUpSpawnTimer += 1.f;
    if (this->powerUpSpawnTimer >= this->powerUpSpawnTimerMax)
    {
        float posX = static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - 50));
        this->powerUps.push_back(new PowerUp(posX, -50.f));  // Spawn power-up at random horizontal position
        this->powerUpSpawnTimer = 0.f;
    }

    // Update each power-up
    for (size_t i = 0; i < this->powerUps.size(); ++i)
    {
        PowerUp* powerUp = this->powerUps[i];
        powerUp->update();

        // Check for collision with player
        if (powerUp->getBounds().intersects(this->player->getBounds()))
        {
            powerUp->applyEffect(this->player);  // Increase player's health

            // Delete the power-up after applying the effect
            delete powerUp;
            this->powerUps.erase(this->powerUps.begin() + i);
            --i;
        }
        // Remove power-ups that go off-screen
        else if (powerUp->getBounds().top > this->window->getSize().y)
        {
            delete powerUp;
            this->powerUps.erase(this->powerUps.begin() + i);
            --i;
        }
    }
}


void Game::updateBullets()
{
	unsigned counter = 0;
	for (auto *bullet : this->bullets)
	{
		bullet->update();

		//Bullet culling (top of screen)
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			//Delete bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
		}

		++counter;
	}
}

void Game::updateCollision()
{
	//Left world collision
	if (this->player->getBounds().left < 0.f)
	{
		this->player->setPosition(0.f, this->player->getBounds().top);
	}
	//Right world collison
	else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x)
	{
		this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
	}

	//Top world collision
	if (this->player->getBounds().top < 0.f)
	{
		this->player->setPosition(this->player->getBounds().left, 0.f);
	}
	//Bottom world collision
	else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y)
	{
		this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
	}
}

void Game::updateWorld()
{

}

void Game::updateGUI()
{
	std::stringstream ss;

	ss << "Points: " << this->points;

	this->pointText.setString(ss.str());

	//Update player GUI
	float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
	this->playerHpBar.setSize(sf::Vector2f(300.f * hpPercent, this->playerHpBar.getSize().y));
}

void Game::updateVillain()
{
    // Check if it's time to spawn a new villain
    this->villainSpawnTimer += 0.5f;

    // If spawn timer reaches the max, create a new villain
    if (this->villainSpawnTimer >= this->villainSpawnTimerMax)
    {
        this->villains.push_back(new Villain(rand() % this->window->getSize().x - 20.f, -100.f));  // Spawn villains at random positions
        this->villainSpawnTimer = 0.f;  // Reset spawn timer
    }

    // Update all villains in the vector
    for (size_t i = 0; i < this->villains.size(); ++i)
    {
        Villain* currentVillain = this->villains[i];
        currentVillain->update();  // Update each villain

        // Check if the player’s bullets hit the villain
        for (size_t j = 0; j < this->bullets.size(); )
        {
            if (currentVillain->getBounds().intersects(this->bullets[j]->getBounds()))
            {
                currentVillain->decreaseHealth(10);  // Damage villain
                delete this->bullets[j];  // Remove bullet
                this->bullets.erase(this->bullets.begin() + j);  // Remove bullet from the vector
            }
            else
            {
                ++j;  // Only increment if no collision
            }
        }

        // Villain defeated, reset for next spawn
        if (currentVillain->getHealth() <= 0)
        {
            delete this->villains[i];  // Delete villain object
            this->villains.erase(this->villains.begin() + i);  // Remove from vector
            --i;  // Adjust the index after erasure
        }

        // Handle collision between villain's bullets and the player
        for (auto* bullet : currentVillain->getBullets())
        {
            if (bullet->getBounds().intersects(this->player->getBounds()))
            {
                this->player->loseHp(1.5);  // Damage the player
            }
        }
    }
}



void Game::update()
{
    this->updateInput();
    this->player->update();  // Update player
    this->updateCollision();  // Update player collision with world bounds
    this->updateBullets();  // Update all bullets
    this->updateEnemies();  // Update enemies
    this->updateVillain();
    this->updateCombat();  // Handle combat logic (enemy collisions, etc.)
    this->updateGUI();  // Update GUI elements (points, health bars)
    this->updateWorld();  // Update world/environment (e.g., background)
    this->updatePowerUps();
}

void Game::run()
{
    while (this->window->isOpen()) {
        this->updatePollEvents();

        // Update game logic only if the game is ongoing (i.e., not on the welcome screen or game over screen)
        if ( this->player->getHp() > 0) {
            this->update();
          
        }

         this->render();  // Call the render function to draw the appropriate screen
    }
}



void Game::renderWorld()
{
    this->window->draw(this->worldBackground);
}
void Game::renderGUI()
{
	this->window->draw(this->pointText);
	this->window->draw(this->playerHpBarBack);
	this->window->draw(this->playerHpBar);
}
void Game::render()
{
    this->window->clear();  // Clear the screen

    if (this->isWelcomeScreenActive)
    {
        this->welcomeScreen->draw(*this->window);  // Draw the welcome screen
    }
    else if(this->player->getHp() > 0)
    {
        this->renderWorld();  // Render the world background
        this->player->render(*this->window);  // Render the player

        // Render bullets (player's bullets)
        for (auto* bullet : this->bullets)
        {
            bullet->render(this->window);
        }

        // Render enemies
        for (auto* enemy : this->enemies)
        {
            enemy->render(this->window);
        }

        // Render the villain if it exists
        
        for (auto* villain : this->villains)
        {
            villain->render(this->window);
        }

        for (auto* powerUp : this->powerUps)
        {
        powerUp->render(this->window);
        }
        this->renderGUI();  // Render the GUI (score, health bars, etc.)
    }

    else {
        this->gameOverScreen->draw(*this->window);
    }

    this->window->display();  // Display the rendered content
}
