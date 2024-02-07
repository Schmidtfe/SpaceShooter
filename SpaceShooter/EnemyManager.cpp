#include "EnemyManager.h"
#include <vector>

std::vector<Entity*> enemies;

EnemyManager::EnemyManager(SDL_Renderer *ren)
{
	cooldown = 60 * 3;
	wave = 1;
	enemyNum = 1;
	prevEnemyNum = 0;
	renderer = ren;
	enemies.resize(1);
	std::cout << enemies.size() << std::endl;
	
}

EnemyManager::~EnemyManager()
{}

void EnemyManager::update()
{
	if (cooldown > 0)
	{
		cooldown--;
	}
	else {
		if (enemiesDefeated)
		{
			std::cout << "Spawning Enemies..." << std::endl;
			enemiesDefeated = false;
			createEnemies();
		}
		else {
			for (int i = 0; i < enemies.size(); i++)
			{
				enemies[i]->update();
			}

		}
	}

}

void EnemyManager::render()
{
	for (int i = 0; i < enemies.size(); i++)
	{
		if(enemies[i])
			enemies[i]->render();
	}
}

void EnemyManager::addEnemy(int index)
{
	int randomX = 32 + (std::rand() % (800 - 64 + 1));
	Entity* enemy = new Entity("assets/enemy.png", renderer, randomX, 33, index);
	enemies[index] = enemy;
	//std::cout << enemies->size() << std::endl;
	
}

void EnemyManager::removeEnemy()
{

}

void EnemyManager::createEnemies()
{
	int tmp = prevEnemyNum;
	prevEnemyNum = enemies.size();
	enemies.resize(enemies.size() + tmp);

	int currEnemyNum = enemies.size();
	
	for (int i = 0; i < currEnemyNum; i++)
	{
		addEnemy(i);
		std::cout << enemies[i]->num << std::endl;
	}
	std::cout << enemies.size() << std::endl;
}