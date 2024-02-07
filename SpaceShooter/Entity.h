#pragma once
#include "Game.h"
class Entity
{
public:
	Entity(const char* textureSheet, SDL_Renderer* ren, int xpos, int ypos);
	~Entity();

	void update();
	void render();
	SDL_Texture* loadTexture(const char* fileName);

private:
	int x;
	int y;

	SDL_Texture* texture;
	SDL_Rect texRect, sizeRect;
	SDL_Renderer* renderer;
};

