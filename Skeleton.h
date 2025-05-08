#pragma once
#include "NPCEntity.h"

class Skeleton : public NPCEntity
{
public:
	Skeleton() = delete;
	Skeleton(float health, float energy, CharacterAttributes attributes,
		EnergyType eType = EnergyType::Stamina, string name = "Skeleton", bool isFriendly = false) :
		NPCEntity(name, health, energy,attributes, eType, isFriendly)
	{

	}
};
