#include "PlayerCaracter.h"

void PlayerCharacter::LevelUp()
{
	if (this->experience >= levelingStep)
	{
		this->level++;
		cout << name << " Level UP++" << "Current LVL: " << level << endl;
		levelingStep *= 2;
		experience = 0;

		this->attributes.agility++;
		this->attributes.strength++;
		this->attributes.luck++;
		this->attributes.inteligence++;
		this->healthMax += 500;
		this->health = healthMax;
		this->staminaMax += 100;
		this->stamina = staminaMax;
		this->manaMax += 100;
		this->mana = manaMax;
	}
}

void PlayerCharacter::GainExperience(int points)
{
	this->experience += points;
	cout << this->name << "++EXP " << points << " Exp points - " << this->experience << endl;
	
}

void PlayerCharacter::SubscribeOnEnemy(Character& enemy)
{
	int id = enemy.GetId();

	if (enemiesSubscriptions.contains(id))
	{
		std::cout << "Already subscribed to enemy " << id << std::endl;
		return;
	}

	int listenerId = enemy.SubscribeOnDeath([this](int exp) {
		this->GainExperience(exp);
		});

	enemiesSubscriptions[id] = listenerId;
}

void PlayerCharacter::UnsubscribeFromEnemy(Character& enemy)
{
	int id = enemy.GetId();

	auto it = enemiesSubscriptions.find(id);
	if (it == enemiesSubscriptions.end())
		return;

	int listenerId = it->second;
	enemy.UnsubscribeOnDeath(listenerId);
	enemiesSubscriptions.erase(it);
}

