#include "Entity.h"

Entity::Entity(const char* textureSheet, SDL_Renderer* ren, int xpos, int ypos)
{
	renderer = ren;
	texture = loadTexture(textureSheet);
	x = xpos;
	y = ypos;
}

void Entity::update()
{
	x++;
	y++;

	texRect.h = 512;
	texRect.w = 512;
	texRect.x = 0;
	texRect.y = 0;

	sizeRect.x = x;
	sizeRect.y = y;
	sizeRect.w = 64;
	sizeRect.h = 64;
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