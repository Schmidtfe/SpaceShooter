#include "Game.h"
#include "Actor.h"
#include "EnemyManager.h"
#include "Projectile.h"
#include "ProjectileManager.h"

Actor* player;
EnemyManager* em;
ProjectileManager* pm;

Game::Game()
{
  points = 0;
  count = 0;
  pauseTime = 0;
}
Game::~Game()
{}

Ship* toDestroyEnemy;
Projectile* toDestroyProjectile;

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	windowWidth = width;
	windowHeight = height;
	if (fullscreen)	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystem Initialised!..." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			std::cout << "Window created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);
			std::cout << "Renderer created!" << std::endl;
		}

		isRunning = true;

	}
	else {
		isRunning = false;
	}


	pm = new ProjectileManager(windowWidth, windowHeight);
	em = new EnemyManager(renderer, this, pm);

	player = new Actor("assets/spaceship.png", renderer, windowWidth / 2, windowHeight * 7 / 8, 4, 2, pm);
	player->createLivesDisplay();
	player->showLivesFor(60 * 3);

}

void Game::input()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	//const Uint8* keyState = SDL_GetKeyboardState(NULL);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;

	case SDL_KEYDOWN:
		if (player)
		{
			//std::cout << event.key.keysym.sym << std::endl;
			switch (event.key.keysym.sym)
			{
			case SDLK_w:
				if (player->getDirY() >= 0)
					player->addDirection(0, -1);
				break;
			case SDLK_a:
				if (player->getDirX() >= 0)
					player->addDirection(-1, 0);
				break;
			case SDLK_s:
				if (player->getDirY() <= 0)
					player->addDirection(0, 1);
				break;
			case SDLK_d:
				if (player->getDirX() <= 0)
					player->addDirection(1, 0);
				break;
			case SDLK_SPACE:
				if (player->getShootCooldown() <= 0)
					pm->addProjectile(player->shootProjectile(glm::vec2(0, -1)));
				break;
			default:
				break;
			}
		}
		break;

	case SDL_KEYUP:
		if (player)
		{
			if (event.key.keysym.sym == SDLK_w)
			{
				if (player->getDirY() < 0)
					player->setDirY(0);
			}
			if (event.key.keysym.sym == SDLK_a)
			{
				if (player->getDirX() < 0)
					player->setDirX(0);
			}
			if (event.key.keysym.sym == SDLK_s)
			{
				if (player->getDirY() > 0)
					player->setDirY(0);
			}
			if (event.key.keysym.sym == SDLK_d)
			{
				if (player->getDirX() > 0)
					player->setDirX(0);
			}
		}
		break;

	default:
		break;
	}

}

void Game::update()
{
	count++;
	if (player)
	{
		if (pauseTime <= 0)
		{
			player->update();
			em->update();
			pm->update();

			if (em->enemies.size() > 0)
				if (em->enemies[0] && player)
				{
					checkForCollision();
				}
		}
		else {
			pauseAndReset();
		}
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);
	//add stuff to render here
	em->render();
	if (player)
		player->render();
	pm->render();

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;
}

void Game::checkForCollision()
{
	if (em->enemies[0])
	{
	  for (Ship* enemy : em->enemies)
		{
			//check collision between Player and enemies
			if (!player->isInvincible() && player->checkCollisionFor(enemy))
			{
				//Pause the game for a brief moment, then kill enemy and damage player
				int remainingLives = player->takeDamage();
				std::cout << remainingLives << std::endl;
				enemy->setTexture("assets/shatter.png");
				toDestroyEnemy = enemy;
				player->setTexture("assets/shatter.png");
				if (remainingLives == 0)
				{
					std::cout << "Game Over!" << std::endl;
					std::cout << "Points: " << points << std::endl;
					player = NULL;
				}
				else {
					pauseTime = 60 * 1;
				}
			}

			//check collision between Player's projectiles and enemies
			for (Projectile* playerP : player->projectiles)
			{
			  //std::cout << "Player Projectiles on field: " << player->projectiles.size() << std::endl;
				//kill enemy and destroy projectile
				if (enemy->checkCollisionFor(playerP))
				{
					std::cout << "Enemy hit!" << std::endl;
					em->removeEnemy(enemy);
					pm->removeProjectile(playerP);
					player->removeProjectile(playerP);
				}
			}

			//check collision between Player and enemies' projectiles
			for (Projectile* enemyP : enemy->projectiles)
			{
				if (player->checkCollisionFor(enemyP))
				{
					int remainingLives = player->takeDamage();
					std::cout << remainingLives << std::endl;
					toDestroyProjectile = enemyP;
					enemy->removeProjectile(enemyP);
					player->setTexture("assets/shatter.png");
					if (remainingLives == 0)
					{
						std::cout << "Game Over!" << std::endl;
						std::cout << "Points: " << points << std::endl;
						isRunning = false;
					}
					else {
						pauseTime = 60 * 1;
					}
				}
			}
		}
	}
}

void Game::pauseAndReset()
{
	if (pauseTime > 1) {
		pauseTime--;
	}
	else {
		pauseTime--;
		player->setPosition(glm::vec2(windowWidth / 2, windowHeight * 7 / 8));
		player->setTexture("assets/spaceship.png");
		player->showLivesFor(60 * 3);
		player->setInvincible(60 * 3);
		if (toDestroyEnemy)
			em->removeEnemy(toDestroyEnemy);
		if (toDestroyProjectile)
			pm->removeProjectile(toDestroyProjectile);
	}
}
