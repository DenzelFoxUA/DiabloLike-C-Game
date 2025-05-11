#pragma once
#include "PlayerCaracter.h"

class LadyArcher : public PlayerCharacter
{
public:
	LadyArcher() = delete;
	LadyArcher(int id, string name, float healthPoint, float energy, CharacterAttributes attributes, EnergyType eType = EnergyType::Stamina) :
		PlayerCharacter(id, name, healthPoint, energy,attributes, eType)
	{

	}
};
