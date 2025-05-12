#include "Character.h"

void Character::GetHit(float damage)
{
	this->health -= damage;
}

void Character::Heal(float healValue)
{
	this->health += healValue;
}

void Character::GainStamina(float eValue)
{
	this->stamina += eValue;
}

void Character::SpendStamina(float eValue)
{
	this->stamina -= eValue;
}

void Character::GainMana(float eValue)
{
	this->mana += eValue;
}

void Character::SpendMana(float eValue)
{
	this->mana -= eValue;
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

float Character::GetManaPoints()
{
	return this->mana;
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

void Character::SetStaminaLimit(float value)
{
	this->staminaMax = value;
}

float Character::GetStaminaLimit()
{
	return this->staminaMax;
}

void Character::SetHPMaxLimit(float value)
{
	this->healthMax = value;
}

float Character::GetHPMaxLimit()
{
	return this->healthMax;
}

float Character::GetManaLimit()
{
	return this->manaMax;
}
void Character::SetManaLimit(float value)
{
	this->manaMax = value;
}

int Character::GetId()
{
	return id;
}

float Character::GetStaminaPoints()
{
	return this->stamina;
}