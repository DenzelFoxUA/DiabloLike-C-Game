#include "Enemies.h"

std::map<int, IBaseUnit*> Enemies::enemies;

void Enemies::Add(int id, IBaseUnit* pos)
{
	enemies.emplace(id, pos);
}

void Enemies::Update()
{
	for (auto it = enemies.begin(); it != enemies.end(); )
	{
		if (it->second->IsDead())
		{
			it = enemies.erase(it); // ✅ erase повертає наступний ітератор
		}
		else
		{
			++it;
		}
	}
}
vector<IBaseUnit*> Enemies::Get()
{
	vector<IBaseUnit*> _enemies;
	for (auto& [key, enemy] : enemies)
	{
		_enemies.push_back(enemy);
	}
	return _enemies;
}