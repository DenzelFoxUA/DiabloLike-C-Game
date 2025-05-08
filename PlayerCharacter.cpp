#include "PlayerCaracter.h"

void PlayerCharacter::LevelUp()
{
	this->level++;
}

void PlayerCharacter::GainExperience(unsigned int points)
{
	experience += points;
}