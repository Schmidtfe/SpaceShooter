#include "Entity.h"


Entity::Entity()
{}

Entity::Entity(const char* textureSheet, SDL_Renderer* ren, int xpos, int ypos, int index)
{
	renderer = ren;
	texture = loadTexture(textureSheet);
	x = xpos;
	y = ypos;
	direction = glm::vec2(0.0f, 0.0f);
	num = index;
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


	texRect.h = 512;
	texRect.w = 512;
	texRect.x = 0;
	texRect.y = 0;

	sizeRect.w = 64;
	sizeRect.h = 64;
	sizeRect.x = x - sizeRect.w/2;
	sizeRect.y = y - sizeRect.h/2;
}

void Entity::render()
{
	SDL_RenderCopy(renderer, texture, &texRect, &sizeRect);
}

SDL_Texture* Entity::loadTexture(const char* fileName)
{
	SDL_Surface* tmpSurface = IMG_Load(fileName);
	SDL_Texture* result = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	return result;
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