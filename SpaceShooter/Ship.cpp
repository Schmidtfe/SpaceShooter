#include "Ship.h"
#include "Projectile.h"

Ship::Ship()
	: Entity()
{}

Ship::Ship(const char* textureSheet, SDL_Renderer* ren, int xpos, int ypos, int moveSpeed, float rateOfFire, ProjectileManager* projMan)
	: Entity(textureSheet, ren, xpos, ypos, moveSpeed)
{
  isShooting = false;
  fireRate = 2;
  fireRate = rateOfFire;
  pm = projMan;
  projectiles.clear();
  shootCooldown = std::rand()%240;
}

Ship::~Ship()
{}

void Ship::update()
{
	Entity::update();
	if (shootCooldown > 0) {
		shootCooldown--;
	}
	for (Projectile* p : projectiles)
	{
		if (p->getPosition().y < 0 - p->getSize().y / 2 || p->getPosition().y > pm->getWindowHeight() + p->getSize().y / 2)
		{
			removeProjectile(p);
			pm->removeProjectile(p);
		}
	}
}

int Ship::getShootCooldown()
{
	return shootCooldown;
}

Projectile* Ship::shootProjectile(glm::vec2 vel)
{
	if (shootCooldown <= 0)
	{
		//std::cout << "Shooting Projectile!" << std::endl;
		Projectile* p = new Projectile("assets/projectile.png", renderer, x, y, 16, vel);
		p->setSize(32);
		projectiles.push_back(p);
		shootCooldown = int(60.0f / fireRate);
		return p;
	}
	return NULL;
}

bool Ship::checkCollisionFor(Entity* toCheck) 
{
	if (glm::length(getPosition() - toCheck->getPosition()) < getSize().x / 2 + toCheck->getSize().x / 2)
	{
		return true;
	}
	return false;
}

void Ship::removeProjectile(Projectile* p)
{
	for (Uint8 i = 0; i < projectiles.size(); i++)
	{
		if (projectiles[i] == p)
			projectiles.erase(projectiles.begin() + i);
	}
}
