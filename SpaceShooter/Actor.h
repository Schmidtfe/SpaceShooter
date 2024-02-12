#pragma once
#include "Ship.h"

class Actor: public Ship
{
public:
	Actor();
	Actor(const char* textureSheet, SDL_Renderer* ren, int xpos, int ypos, int moveSpeed, int rateOfFire, ProjectileManager* projMan);
	~Actor();

	void update();
	void render();

	void createLivesDisplay();
	int takeDamage();
	bool isInvincible();
	void setInvincible(int time);
	void showLivesFor(int time);

protected:
	int lives;
	bool invincible;
	int invinCooldown;
	void blinkAnimation();
	void setLiveDisplayPos();
	int liveDisTimer;

	std::vector<SDL_Texture*> livesDisplay;
	std::vector<SDL_Rect> livDisTexRect;
	std::vector<SDL_Rect> livDisSizeRect;
};

