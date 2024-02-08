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
	void setShipTexture(const char* fileName);
	void createLivesDisplay();
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
	bool isPlayer = false;
	void showLivesFor(int time);

private:
	float x;
	float y;
	int speed = 4;
	int lives = 1;
	glm::vec2 direction;
	bool invincible = false;
	int invinCooldown = 0;
	void blinkAnimation();
	void setLiveDisplayPos();
	int liveDisTimer = 60*3;

	SDL_Texture* texture;
	SDL_Rect texRect, sizeRect;
	SDL_Renderer* renderer;

	std::vector<SDL_Texture*> livesDisplay;
	std::vector<SDL_Rect> livDisTexRect;
	std::vector<SDL_Rect> livDisSizeRect;
};

