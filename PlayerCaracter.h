#pragma once
#include <iostream>
#include "Character.h"
using namespace std;

class PlayerCharacter : public Character
{
protected:

	int level;
	int experience;

public:

	PlayerCharacter() = delete;

	PlayerCharacter(string name, float health, float energy, CharacterAttributes attributes, EnergyType eType)
		: Character(name, health, energy, attributes, eType), level(1),experience(1)
	{

	}

	virtual void LevelUp();

	virtual void GainExperience(unsigned int points);

	~PlayerCharacter() = default;
};
