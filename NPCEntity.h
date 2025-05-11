#pragma once

#include <iostream>
#include <functional>
#include "Character.h"
using namespace std;

class NPCEntity : public Character
{
protected:

	bool isFriendly;
	float detectRadius;
	int expPontsGranted;

public:

	NPCEntity() = delete;

	NPCEntity(int id, string name, 
		float health, 
		float energy, 
		float detectRadius,
		int expReward,
		CharacterAttributes attributes, 
		EnergyType eType,
		bool isFriendly)
		: Character(id,name, health, energy, attributes, eType)
	{
		this->isFriendly = isFriendly;
		this->detectRadius = detectRadius;
		this->expPontsGranted = expReward;
	}

	bool IsFriendly() const;

	void SetFriendly();
	
	int GetXPReward();

	virtual void GainExperience(int expPoints) override{}

	virtual float GetDetectRadius();

	~NPCEntity() = default;
};

