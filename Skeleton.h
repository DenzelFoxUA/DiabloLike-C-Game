#pragma once
#include "NPCEntity.h"

class Skeleton : public NPCEntity
{
public:
	Skeleton() = delete;
	Skeleton(int id, 
		string name,
		float health, 
		float stamina,
		float mana,
		CharacterAttributes attributes,
		float detectRadius,
		int gainXp,
		bool isFriendly = false) :
		NPCEntity(id, name, health, stamina,mana,detectRadius,
			gainXp,attributes, isFriendly){}
};
