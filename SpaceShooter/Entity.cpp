#include "Entity.h"


Entity::Entity()
{}

Entity::Entity(const char* textureSheet, SDL_Renderer* ren, int xpos, int ypos, int moveSpeed)
{
	renderer = ren;
	texture = loadTexture(textureSheet);
	x = xpos;
	y = ypos;
	direction = glm::vec2(0.0f, 0.0f);
	position = glm::vec2(x, y);
	speed = moveSpeed;

	texRect.h = 512;
	texRect.w = 512;
	texRect.x = 0;
	texRect.y = 0;

	sizeRect.w = 64;
	sizeRect.h = 64;

	livesDisplay.resize(0);
	livDisTexRect.resize(0);
	livDisSizeRect.resize(0);
}

Entity::~Entity()
{}

void Entity::update()
{
	if (direction != glm::vec2(0.0f, 0.0f))
	{
		glm::vec2 velocity = glm::normalize(direction);
		x += velocity.x * speed;
		y += velocity.y * speed;
		//std::cout << "(" << velocity.x << ", " << velocity.y << ")" << std::endl;
	}

	position = glm::vec2(x, y);


	sizeRect.x = x - sizeRect.w/2;
	sizeRect.y = y - sizeRect.h/2;

	if(isPlayer)
		setLiveDisplayPos();
}

void Entity::render()
{
	if (invincible)
		blinkAnimation();
	SDL_RenderCopy(renderer, texture, &texRect, &sizeRect);
	if (isPlayer && liveDisTimer > 0)
	{
		for (int i = 0; i < lives; i++)
		{
			SDL_RenderCopy(renderer, livesDisplay[i], &livDisTexRect[i], &livDisSizeRect[i]);
		}
		liveDisTimer--;
	}
}

SDL_Texture* Entity::loadTexture(const char* fileName)
{
	SDL_Surface* tmpSurface = IMG_Load(fileName);
	SDL_Texture* result = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	return result;
}

void Entity::setShipTexture(const char* fileName)
{
	texture = loadTexture(fileName);
}

void Entity::createLivesDisplay()
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

void Entity::setLiveDisplayPos()
{
	for (int i = 0; i < lives; i++)
	{
		livDisSizeRect[i].x = x - livDisSizeRect[i].w/2 + (i - float(lives-1)/2)*livDisSizeRect[i].w;
		livDisSizeRect[i].y = y + (sizeRect.h / 2 * -1 - livDisSizeRect[i].h);
		
	}
}

void Entity::addDirection(int x, int y)
{
	direction.x += x;
	direction.y += y;
}

int Entity::getDirX()
{
	return direction.x;
}

int Entity::getDirY()
{
	return direction.y;
}

void Entity::setDirX(int x)
{
	direction.x = x;
}

void Entity::setDirY(int y)
{
	direction.y = y;
}

glm::vec2 Entity::getPosition()
{
	return position;
}

void Entity::setPosition(glm::vec2 pos)
{
	x = pos.x;
	y = pos.y;
}

int Entity::takeDamage()
{
	lives--;
	return lives;
}

void Entity::showLivesFor(int time)
{
	liveDisTimer = time;
}

void Entity::blinkAnimation()
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

bool Entity::isInvincible()
{
	return invincible;
}

void Entity::setInvincible(int time)
{
	invincible = true;
	invinCooldown = time;
}