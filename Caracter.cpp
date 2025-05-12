#include "Character.h"

void Character::GetHit(float damage)
{
	this->health -= damage;
}

void Character::Heal(float healValue)
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

string Character::GetName()
{
	return name;
}

CharacterAttributes &Character::GetAttributes()
{
	return this->attributes;
}

float Character::GetHealthPoints()
{
	return this->health;
}

bool& Character::IsDead()
{
	return this->isDead;
}

void Character::Death()
{
	if (isDead) return;
	isDead = true;

	std::cout << "Enemy died!\n";
	for (auto& [_, listener] : deathListeners)
	{
		listener(100); // Наприклад, 100 досвіду
	}
}

int Character::SubscribeOnDeath(std::function<void(int expGained)> caller)
{
	int id = nextListenerId++;
	deathListeners[id] = caller;
	return id;
}

void Character::UnsubscribeOnDeath(int listenerId)
{
	deathListeners.erase(listenerId);
}

void Character::SetEnergyLimit(float value)
{
	this->energyMax = value;
}

float Character::GetEnergyLimit()
{
	return this->energyMax;
}

void Character::SetHPMaxLimit(float value)
{
	this->healthMax = value;
}

float Character::GetHPMaxLimit()
{
	return this->healthMax;
}

int Character::GetId()
{
	return id;
}

float Character::GetEnergy()
{
	return this->energy;
}