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

	bool isModeTwoActive = false;

public:

	PlayerCharacter() = delete;

	PlayerCharacter(int id, 
		string name, 
		float health, 
		float stamina,
		float mana,
		CharacterAttributes attributes)
		: Character(id,name, health, stamina, mana, attributes), level(1),experience(0) {}

	//actions
	virtual void LevelUp();
	virtual void GainExperience(int points) override;
	virtual void SetModeTwoActive(bool isActive)
	{
		this->isModeTwoActive = isActive;
	}

	virtual bool IsModeTwoActive()
	{
		return this->isModeTwoActive;
	}


	//events funcs
	void SubscribeOnEnemy(Character& enemy);
	void UnsubscribeFromEnemy(Character& enemy);

	~PlayerCharacter() = default;
};
