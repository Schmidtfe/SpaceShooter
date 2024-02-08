#include "Projectile.h"

Projectile::Projectile()
	: Entity()
{}

Projectile::Projectile(const char* textureSheet, SDL_Renderer* ren, int xpos, int ypos, int moveSpeed, glm::vec2 vel)
	: Entity(textureSheet, ren, xpos, ypos, moveSpeed)
{
	Entity::direction = vel;
}

Projectile::~Projectile()
{}

void Projectile::update()
{
	Entity::update();
	//std::cout << "I exist! Coordinates: (" << Entity::x << "/" << Entity::y << ")" << std::endl;
}

void Projectile::render()
{
	Entity::render();
}

void Projectile::setSize(int size)
{
	Entity::sizeRect.w = size;
	Entity::sizeRect.h = size;
}