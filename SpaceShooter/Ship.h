#pragma once
#include "Entity.h"
#include "ProjectileManager.h"

class Ship: public Entity
{
public:
	Ship();
	Ship(const char* textureSheet, SDL_Renderer* ren, int xpos, int ypos, int moveSpeed, float rateOfFire, ProjectileManager* projMan);
	~Ship();

	void update();

	ProjectileManager* pm;
	Projectile* shootProjectile(glm::vec2 vel);
	std::vector<Projectile*> projectiles;
	int getShootCooldown();
	bool checkCollisionFor(Entity* toCheck);
	bool isShooting;
	void removeProjectile(Projectile* p);

protected:
	int shootCooldown;
	float fireRate;
};

