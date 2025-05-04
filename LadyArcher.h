#pragma once
#include "PlayerCaracter.h"

class LadyArcher : public PlayerCharacter
{
public:
	LadyArcher() = delete;
	LadyArcher(string name, float healthPoint, float energy, EnergyType eType = EnergyType::Stamina) :
		PlayerCharacter(name, healthPoint, energy, eType)
	{

	}
};
