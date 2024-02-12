#pragma once
#include "Game.h"
#include <glm.hpp>
#include <vector>

class Entity
{
public:
	Entity();
	Entity(const char* textureSheet, SDL_Renderer* ren, int xpos, int ypos, int moveSpeed);
	~Entity();

	virtual void update();
	virtual void render();
	SDL_Texture* loadTexture(const char* fileName);
	void setTexture(const char* fileName);
	void addDirection(int x, int y);
	int getDirX();
	int getDirY();
	void setDirX(int x);
	void setDirY(int y);
	glm::vec2 getPosition();
	glm::vec2 getSize();
	void setPosition(glm::vec2 pos);
	int num;

protected:
	float x;
	float y;
	int speed;
	int lives;
	glm::vec2 direction;
	glm::vec2 position;

	SDL_Texture* texture;
	SDL_Rect texRect, sizeRect;
	SDL_Renderer* renderer;

	std::vector<SDL_Texture*> livesDisplay;
	std::vector<SDL_Rect> livDisTexRect;
	std::vector<SDL_Rect> livDisSizeRect;
};

