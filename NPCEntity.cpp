#include "NPCEntity.h"

bool NPCEntity::IsFriendly() const
{
	return this->isFriendly;
}

void NPCEntity::SetFriendly()
{
	this->isFriendly = true;
}