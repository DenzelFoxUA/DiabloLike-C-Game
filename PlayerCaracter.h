#pragma once
#include <iostream>
#include "Character.h"
using namespace std;

class PlayerCharacter : public Character
{
protected:

public:

	PlayerCharacter() = delete;

	PlayerCharacter(string name, float health, float energy, EnergyType eType) : Character(name, health, energy, eType)
	{
	}

	~PlayerCharacter() = default;
};
