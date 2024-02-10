#include "ProjectileManager.h"

ProjectileManager::ProjectileManager(int screenWidth, int screenHeight)
{
	windowWidth = screenWidth;
	windowHeight = screenHeight;
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

void ProjectileManager::removeProjectile(Projectile* p)
{
	for (int i = 0; i < projectiles.size(); i++)
	{
		if (projectiles[i] == p)
		{
			projectiles.erase(projectiles.begin() + i);
		}
	}
}

int ProjectileManager::getWindowHeight()
{
	return windowHeight;
}