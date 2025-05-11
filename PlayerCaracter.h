#pragma once
#include <iostream>
#include "Character.h"
#include "NPCEntity.h"
#include <map>
using namespace std;

class PlayerCharacter : public Character
{
protected:

	int level;
	int experience;
	int levelingStep = 290;

	map<int, int> enemiesSubscriptions;

public:

	PlayerCharacter() = delete;

	PlayerCharacter(int id, string name, float health, float energy, CharacterAttributes attributes, EnergyType eType)
		: Character(id,name, health, energy, attributes, eType), level(1),experience(0)
	{

	}

	virtual void LevelUp();

	virtual void GainExperience(int points) override;

	void SubscribeOnEnemy(Character& enemy);

	void UnsubscribeFromEnemy(Character& enemy);

	~PlayerCharacter() = default;
};
