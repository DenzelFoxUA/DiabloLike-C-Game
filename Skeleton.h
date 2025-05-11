#pragma once
#include "NPCEntity.h"

class Skeleton : public NPCEntity
{
public:
	Skeleton() = delete;
	Skeleton(int id, float health, float energy,float detectRadius,int gainXp, CharacterAttributes attributes,
		EnergyType eType = EnergyType::Stamina, string name = "Skeleton", bool isFriendly = false) :
		NPCEntity(id, name, health, energy,detectRadius,gainXp,attributes, eType, isFriendly)
	{

	}
};
