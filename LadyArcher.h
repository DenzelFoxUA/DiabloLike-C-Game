#pragma once
#include "PlayerCaracter.h"

class LadyArcher : public PlayerCharacter
{
public:
	LadyArcher() = delete;
	LadyArcher(int id, 
		string name, 
		float healthPoint, 
		float stamina,
		float mana,
		CharacterAttributes attributes) :
		PlayerCharacter(id, name, healthPoint, stamina, mana, attributes)
	{

	}
};
