#include "Ship.h"
#include "Projectile.h"

Ship::Ship()
	: Entity()
{}

Ship::Ship(const char* textureSheet, SDL_Renderer* ren, int xpos, int ypos, int moveSpeed, float rateOfFire)
	: Entity(textureSheet, ren, xpos, ypos, moveSpeed)
{
	fireRate = rateOfFire;
	projectiles.clear();
}

Ship::~Ship()
{}

void Ship::update()
{
	Entity::update();
	if (shootCooldown > 0) {
		shootCooldown--;
	}
}

int Ship::getShootCooldown()
{
	return shootCooldown;
}

void Ship::shootProjectile(ProjectileManager* pm, glm::vec2 vel)
{
	if (shootCooldown <= 0)
	{
		//std::cout << "Shooting Projectile!" << std::endl;
		Projectile* p = new Projectile("assets/projectile.png", renderer, x, y, 16, vel);
		p->setSize(32);
		pm->addProjectile(p);
		projectiles.push_back(p);
		shootCooldown = int(60.0f / fireRate);
	}
}