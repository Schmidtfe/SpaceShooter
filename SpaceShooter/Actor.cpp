#include "Actor.h"

Actor::Actor()
	: Ship()
{}

Actor::Actor(const char* textureSheet, SDL_Renderer* ren, int xpos, int ypos, int moveSpeed, int rateOfFire, ProjectileManager* projMan)
	: Ship(textureSheet, ren, xpos, ypos, moveSpeed, rateOfFire, projMan)
{}

Actor::~Actor()
{}


void Actor::update() 
{
	Ship::update();
	setLiveDisplayPos();
	if (direction != glm::vec2(0.0f, 0.0f))
	{
		glm::vec2 velocity = glm::normalize(Ship::direction);
	}
}

void Actor::render()
{
	if (invincible)
		blinkAnimation();
	Ship::render();
	if (liveDisTimer > 0)
	{
		for (int i = 0; i < lives; i++)
		{
			SDL_RenderCopy(Ship::renderer, livesDisplay[i], &livDisTexRect[i], &livDisSizeRect[i]);
		}
		liveDisTimer--;
	}
}

void Actor::createLivesDisplay()
{
	for (int i = 0; i < lives; i++)
	{
		SDL_Texture* lifeTex = loadTexture("assets/heart.png");
		livesDisplay.push_back(lifeTex);

		SDL_Rect tRect;
		tRect.w = 512;
		tRect.h = 512;
		tRect.x = 0;
		tRect.y = 0;
		livDisTexRect.push_back(tRect);

		SDL_Rect sRect;
		sRect.w = 16;
		sRect.h = 16;
		livDisSizeRect.push_back(sRect);
	}
}

int Actor::takeDamage()
{
	lives--;
	return lives;
}

void Actor::showLivesFor(int time)
{
	liveDisTimer = time;
}

bool Actor::isInvincible()
{
	return invincible;
}

void Actor::setInvincible(int time)
{
	invincible = true;
	invinCooldown = time;
}


void Actor::setLiveDisplayPos()
{
	for (int i = 0; i < lives; i++)
	{
		livDisSizeRect[i].x = x - livDisSizeRect[i].w / 2 + (i - float(lives - 1) / 2) * livDisSizeRect[i].w;
		livDisSizeRect[i].y = y + (sizeRect.h / 2 * -1 - livDisSizeRect[i].h);

	}
}

void Actor::blinkAnimation()
{
	invinCooldown--;
	//std::cout << "Invincibility..." << std::endl;
	if (invinCooldown / 10 % 2 == 1)
	{
		SDL_SetTextureAlphaMod(texture, 0);
	}
	else {
		SDL_SetTextureAlphaMod(texture, 255);
	}
	if (invinCooldown <= 0)
		invincible = false;
}