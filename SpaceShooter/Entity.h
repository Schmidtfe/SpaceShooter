#pragma once
#include "Game.h"
#include <glm.hpp>

class Entity
{
public:
	Entity();
	Entity(const char* textureSheet, SDL_Renderer* ren, int xpos, int ypos, int index);
	~Entity();

	void update();
	void render();
	SDL_Texture* loadTexture(const char* fileName);
	void addDirection(int x, int y);
	int getDirX();
	int getDirY();
	void setDirX(int x);
	void setDirY(int y);
	int num;

private:
	float x;
	float y;
	int speed = 4;
	int lives = 3;
	glm::vec2 direction;

	SDL_Texture* texture;
	SDL_Rect texRect, sizeRect;
	SDL_Renderer* renderer;
};

