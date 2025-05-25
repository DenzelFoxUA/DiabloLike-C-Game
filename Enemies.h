#pragma once
#include "BaseUnit.h"


class Enemies
{

public:
	static map<int, IBaseUnit*> enemiesNPC;
	static map<int, IBaseUnit*> enemiesPlayers;
	static void AddNPCEnemy(int id, IBaseUnit* pos);
	static void AddPlayerEnemy(int id, IBaseUnit* pos);
	static void Update();
	static vector<IBaseUnit*> GetNPCEnemies();
	static vector<IBaseUnit*> GetPlayersEnemies();
};