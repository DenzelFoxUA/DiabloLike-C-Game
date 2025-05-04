#pragma once

#include <iostream>
#include "Character.h"
using namespace std;

class NPCEntity : public Character
{
protected:

	bool isFriendly;

public:

	NPCEntity() = delete;

	NPCEntity(string name, float health, float energy, EnergyType eType, bool isFriendly) : Character(name, health, energy, eType)
	{
		this->isFriendly = isFriendly;
	}

	bool IsFriendly() const;

	void SetFriendly();

	~NPCEntity() = default;
};

