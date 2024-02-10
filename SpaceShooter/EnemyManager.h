#pragma once
#include "Ship.h"
#include <vector>
#include "Game.h"
#include "ProjectileManager.h"

class EnemyManager
{
public:
	std::vector<Ship*> enemies;
	EnemyManager(SDL_Renderer* ren, Game* game, ProjectileManager* projMan);
	~EnemyManager();

	void update();
	void render();
	void addEnemy(int index);
	void removeEnemy(Entity* toRemove);
	void createEnemies();
	int wave;
	Game* thisGame;
	ProjectileManager* pm;

private:
	int cooldown;
	int enemyNum;
	int prevEnemyNum;
	bool enemiesDefeated = true;

	SDL_Renderer* renderer;
};

