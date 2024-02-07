#include "Game.h"
#include "Entity.h"
#include "EnemyManager.h"

Entity* player;
EnemyManager* em;

Game::Game()
{}
Game::~Game()
{}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	windowWidth = width;
	windowHeight = height;
	if (fullscreen)
	{
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

	player = new Entity("assets/spaceship.png", renderer, windowWidth/2, windowHeight*7/8, -1);

	em = new EnemyManager(renderer);


}

void Game::input()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	const Uint8* keyState = SDL_GetKeyboardState(NULL);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;

	case SDL_KEYDOWN:
		//std::cout << keyState[SDLK_w] << std::endl;
		if (event.key.keysym.sym == SDLK_w)
		{
			if (player->getDirY() >= 0)
				player->addDirection(0, -1);
		}
		if (event.key.keysym.sym == SDLK_a)
		{
			if (player->getDirX() >= 0)
				player->addDirection(-1, 0);
		}
		if (event.key.keysym.sym == SDLK_s)
		{
			if (player->getDirY() <= 0)
				player->addDirection(0, 1);
		}
		if (event.key.keysym.sym == SDLK_d)
		{
			if (player->getDirX() <= 0)
				player->addDirection(1, 0);
		}
		break;

	case SDL_KEYUP:
		if (event.key.keysym.sym == SDLK_w)
		{
			if(player->getDirY() < 0)
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
		break;

	default:
		break;
	}

}

void Game::update()
{
	count++;
	player->update();
	em->update();
}

void Game::render()
{
	SDL_RenderClear(renderer);
	//add stuff to render here
	em->render();
	player->render();

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;
}