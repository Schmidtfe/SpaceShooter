#pragma once
#include "Ship.h"

class Actor: public Ship
{
public:
	Actor();
	Actor(const char* textureSheet, SDL_Renderer* ren, int xpos, int ypos, int moveSpeed, int rateOfFire);
	~Actor();

	void update() override;
	void render() override;

	void createLivesDisplay();
	int takeDamage();
	bool isInvincible();
	void setInvincible(int time);
	void showLivesFor(int time);

protected:
	int lives = 1;
	bool invincible = false;
	int invinCooldown = 0;
	void blinkAnimation();
	void setLiveDisplayPos();
	int liveDisTimer = 60 * 3;

	std::vector<SDL_Texture*> livesDisplay;
	std::vector<SDL_Rect> livDisTexRect;
	std::vector<SDL_Rect> livDisSizeRect;
};

