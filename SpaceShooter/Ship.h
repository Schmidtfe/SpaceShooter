#pragma once
#include "Entity.h"
#include "ProjectileManager.h"
#include "Projectile.h"

class Ship: public Entity
{
public:
	Ship();
	Ship(const char* textureSheet, SDL_Renderer* ren, int xpos, int ypos, int moveSpeed, float rateOfFire);
	~Ship();

	void update() override;

	void shootProjectile(ProjectileManager* pm, glm::vec2 vel);
	std::vector<Projectile*> projectiles;
	int getShootCooldown();

protected:
	int shootCooldown = 0;
	float fireRate = 2;
};

