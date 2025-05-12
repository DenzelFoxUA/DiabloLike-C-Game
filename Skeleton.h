#pragma once
#include "NPCEntity.h"

class Skeleton : public NPCEntity
{
public:
	Skeleton() = delete;
	Skeleton(int id, 
		float health, 
		float stamina,
		float mana,
		float detectRadius,
		int gainXp, 
		CharacterAttributes attributes,
		string name = "Skeleton", 
		bool isFriendly = false) :
		NPCEntity(id, name, health, stamina,mana,detectRadius,
			gainXp,attributes, isFriendly){}
};
