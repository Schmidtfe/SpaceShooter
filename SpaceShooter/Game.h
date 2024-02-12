#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <glm.hpp>

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void input();
	void update();
	void render();
	void clean();

	bool running() { return isRunning; };

	void checkForCollision();
	void pauseAndReset();
	
	SDL_Texture* tex;
	int points;

private:
	int count;
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
	int windowWidth;
	int windowHeight;
	int pauseTime;

};

