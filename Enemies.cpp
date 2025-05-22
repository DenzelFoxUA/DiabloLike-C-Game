#include "Enemies.h"

std::map<int, IBaseUnit*> Enemies::enemiesNPC;
std::map<int, IBaseUnit*> Enemies::enemiesPlayers;

void Enemies::AddNPCEnemy(int id, IBaseUnit* pos)
{
	enemiesNPC.emplace(id, pos);
}

void Enemies::AddPlayerEnemy(int id, IBaseUnit* pos)
{
	enemiesPlayers.emplace(id, pos);
}

void Enemies::Update()
{
	for (auto it = enemiesNPC.begin(); it != enemiesNPC.end(); )
	{
		if (it->second->IsDead())
		{
			it = enemiesNPC.erase(it); // ✅ erase повертає наступний ітератор
		}
		else
		{
			++it;
		}
	}

	for (auto it = enemiesPlayers.begin(); it != enemiesPlayers.end(); )
	{
		if (it->second->IsDead())
		{
			it = enemiesPlayers.erase(it); // ✅ erase повертає наступний ітератор
		}
		else
		{
			++it;
		}
	}
}
vector<IBaseUnit*> Enemies::GetNPCEnemies()
{
	vector<IBaseUnit*> _enemies;
	for (auto& [key, enemy] : enemiesNPC)
	{
		_enemies.push_back(enemy);
	}
	return _enemies;
}

vector<IBaseUnit*> Enemies::GetPlayersEnemies()
{
	vector<IBaseUnit*> _enemies;
	for (auto& [key, enemy] : enemiesPlayers)
	{
		_enemies.push_back(enemy);
	}
	return _enemies;
}