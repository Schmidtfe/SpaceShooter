#pragma once
#include "Entity.h"
#include <vector>

class EnemyManager
{
public:
	EnemyManager(SDL_Renderer* ren);
	~EnemyManager();

	void update();
	void render();
	void addEnemy(int index);
	void removeEnemy();
	void createEnemies();

private:
	int cooldown;
	int wave;
	int enemyNum;
	int prevEnemyNum;
	bool enemiesDefeated = true;

	SDL_Renderer* renderer;
};

