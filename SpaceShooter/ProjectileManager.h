#pragma once
#include "Projectile.h"
#include <vector>

class ProjectileManager
{
public:
	ProjectileManager();
	~ProjectileManager();

	std::vector<Projectile*> projectiles;
	void update();
	void render();
	void addProjectile(Projectile* p);
	void removeProjectile(Projectile* p);
	void checkForCollisions(Entity* player, std::vector<Entity*> enemies);
};

