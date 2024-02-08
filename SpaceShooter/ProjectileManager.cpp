#include "ProjectileManager.h"

ProjectileManager::ProjectileManager()
{
	projectiles.clear();
}

ProjectileManager::~ProjectileManager()
{}

void ProjectileManager::update()
{
	for (Projectile* p : projectiles)
	{
		p->update();
	}
}

void ProjectileManager::render()
{
	for (Projectile* p : projectiles)
	{
		p->render();
	}
}

void ProjectileManager::addProjectile(Projectile* p)
{
	projectiles.push_back(p);
}