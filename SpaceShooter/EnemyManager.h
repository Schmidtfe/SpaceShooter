#pragma once
#include "Entity.h"
#include <vector>
#include "Game.h"

class EnemyManager
{
public:
	std::vector<Entity*> enemies;
	EnemyManager(SDL_Renderer* ren, Game* game);
	~EnemyManager();

	void update();
	void render();
	void addEnemy(int index);
	void removeEnemy(Entity* toRemove);
	void createEnemies();
	int wave;
	Game* thisGame;

private:
	int cooldown;
	int enemyNum;
	int prevEnemyNum;
	bool enemiesDefeated = true;

	SDL_Renderer* renderer;
};

