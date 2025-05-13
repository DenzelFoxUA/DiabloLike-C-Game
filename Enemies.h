#pragma once
#include "BaseUnit.h"


static class Enemies
{

public:
	static map<int, IBaseUnit*> enemies;

	static void Add(int id, IBaseUnit* pos);
	static void Update();
	static vector<IBaseUnit*> Get();
};