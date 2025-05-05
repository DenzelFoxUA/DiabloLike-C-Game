#pragma once
#include "NPCEntity.h"

class Skeleton : public NPCEntity
{
public:
	Skeleton() = delete;
	Skeleton(float health, float energy, string name = "Skeleton", 
		EnergyType eType = EnergyType::Stamina, bool isFriendly = false) :
		NPCEntity(name, health, energy, eType, isFriendly)
	{

	}
};
