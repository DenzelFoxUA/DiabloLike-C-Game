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

	//virtual string GetName() const;

	//virtual void GetHit(float damage);

	//virtual void GetHeal(float healValue);

	//virtual void GainEnergy(float eValue);

	//virtual void SpendEnergy(float eValue);

	//virtual EnergyType GetEnergyType() const;

	~PlayerCharacter() = default;
};
