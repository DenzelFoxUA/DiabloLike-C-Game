#include "NPCEntity.h"

bool NPCEntity::IsFriendly() const
{
	return this->isFriendly;
}

void NPCEntity::SetFriendly()
{
	this->isFriendly = true;
}

int NPCEntity::GetXPReward()
{
	return this->expPontsGranted;
}

float NPCEntity::GetDetectRadius()
{
	return this->detectRadius;
}