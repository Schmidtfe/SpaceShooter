#include "EnemyManager.h"
#include <vector>

//std::vector<Entity*> enemies;

EnemyManager::EnemyManager(SDL_Renderer *ren, Game* game)
{
	cooldown = 60 * 3;
	wave = 1;
	enemyNum = 1;
	prevEnemyNum = 0;
	renderer = ren;
	thisGame = game;
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
				if (enemies[i]->getPosition().y < 48)
				{
					enemies[i]->setDirY(1);
				}
				else {
					enemies[i]->setDirY(0);
				}
				if (enemies[i]->getPosition().x <= 33 && enemies[i]->getDirX() < 0)
				{
					enemies[i]->setDirX(1);
				}
				if (enemies[i]->getPosition().x >= (800-33) && enemies[i]->getDirX() > 0)
				{
					enemies[i]->setDirX(-1);
				}
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
	//
	int randomX = 32 + (std::rand() % (800 - 32 - 32 + 1));
	Entity* enemy = new Entity("assets/enemy.png", renderer, randomX, -33, 2);
	int randomDir = (std::rand() % 1) * 2 - 1;
	enemy->setDirX(randomDir);
	enemies[index] = enemy;
	
}

void EnemyManager::removeEnemy(Entity* toRemove)
{
	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i] == toRemove)
		{
			enemies.erase(enemies.begin() + i);
			thisGame->points += 5;
			//std::cout << "Deleting at: " << i << std::endl;
		}
	}
	std::cout << "Remaining Enemies: " << enemies.size() << std::endl;
	if (enemies.size() == 0)
	{
		enemiesDefeated = true;
		cooldown = 60 * 3;
	}
}

void EnemyManager::createEnemies()
{
	std::cout << "Wave " << wave << std::endl;
	int tmp = (wave+1)/2;
	enemies.resize(tmp);
	wave++;

	int currEnemyNum = enemies.size();
	
	for (int i = 0; i < currEnemyNum; i++)
	{
		addEnemy(i);
		//std::cout << enemies[i]->num << std::endl;
	}
	//std::cout << enemies.size() << std::endl;
}