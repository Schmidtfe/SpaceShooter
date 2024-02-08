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

	void update();
	void render();
	SDL_Texture* loadTexture(const char* fileName);
	void addDirection(int x, int y);
	int getDirX();
	int getDirY();
	void setDirX(int x);
	void setDirY(int y);
	glm::vec2 position;
	glm::vec2 getPosition();
	void setPosition(glm::vec2 pos);
	int num;
	int takeDamage();
	bool isInvincible();
	void setInvincible(int time);

private:
	float x;
	float y;
	int speed = 4;
	int lives = 3;
	glm::vec2 direction;
	bool invincible = false;
	int invinCooldown = 0;
	void blinkAnimation();

	SDL_Texture* texture;
	SDL_Rect texRect, sizeRect;
	SDL_Renderer* renderer;
};

