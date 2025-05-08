#include "Character.h"

void Character::GetHit(float damage)
{
	this->health -= damage;
}

void Character::GetHeal(float healValue)
{
	this->health += healValue;
}

void Character::GainEnergy(float eValue)
{
	this->energy += eValue;
}

void Character::SpendEnergy(float eValue)
{
	this->energy -= eValue;
}

EnergyType Character::GetEnergyType() const
{
	return energyType;
}

string Character::GetName() const
{
	return name;
}

CharacterAttributes &Character::GetAttributes()
{
	return this->attributes;
}