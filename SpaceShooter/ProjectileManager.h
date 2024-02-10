#pragma once
#include "Projectile.h"
#include <vector>

class ProjectileManager
{
public:
	ProjectileManager(int screenWidth, int screenHeight);
	~ProjectileManager();

	std::vector<Projectile*> projectiles;
	void update();
	void render();
	void addProjectile(Projectile* p);
	void removeProjectile(Projectile* p);
	int getWindowHeight();

protected:
	int windowHeight;
	int windowWidth;
};

