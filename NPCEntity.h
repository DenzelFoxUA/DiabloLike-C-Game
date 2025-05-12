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
		float stamina,
		float mana,
		float detectRadius,
		int expReward,
		CharacterAttributes attributes,
		bool isFriendly)
		: Character(id,name, health,stamina,mana, attributes)
	{
		this->isFriendly = isFriendly;
		this->detectRadius = detectRadius;
		this->expPontsGranted = expReward;
	}

	//status
	bool IsFriendly() const;
	void SetFriendly();
	
	//values
	int GetXPReward();
	virtual float GetDetectRadius();

	//actions
	virtual void GainExperience(int expPoints) override{}

	~NPCEntity() = default;
};

