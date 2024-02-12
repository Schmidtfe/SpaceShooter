#pragma once
#include <vector>
#include "Entity.h"

class Projectile: public Entity
{
public:
	Projectile();
	Projectile(const char* textureSheet, SDL_Renderer* ren, int xpos, int ypos, int moveSpeed, glm::vec2 vel);
	~Projectile();

	void update();
	void render();
	glm::vec2 velocity;
	void setSize(int size);

};

