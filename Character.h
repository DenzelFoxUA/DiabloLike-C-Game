#pragma once
#include <iostream>
using namespace std;

enum EnergyType
{
	Mana,
	Stamina
};

struct CharacterAttributes
{
	int strength,
		agility,
		willpower,
		inteligence,
		luck;
};

class Character
{
protected:

	string name;
	float health;
	float energy;
	EnergyType energyType;
	bool isDead;

	CharacterAttributes attributes;

public:

	Character() = delete;

	Character(string name, float health, float energy, CharacterAttributes attributes, EnergyType eType)
	{
		this->name = name;
		this->health = health;
		this->energy = energy;
		this->energyType = eType;
		this->attributes = attributes;
		isDead = false;
		
	}

	virtual string GetName() const;

	virtual void GetHit(float damage);

	virtual void GetHeal(float healValue);

	virtual void GainEnergy(float eValue);

	virtual void SpendEnergy(float eValue);

	virtual EnergyType GetEnergyType() const;

	virtual CharacterAttributes& GetAttributes();

	virtual float GetHealthPoints() const;

	virtual bool& IsDead();

	~Character() = default;
};

