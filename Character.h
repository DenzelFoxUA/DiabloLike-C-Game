#pragma once
#include <iostream>
using namespace std;

enum EnergyType
{
	Mana,
	Stamina
};

class Character
{
protected:

	string name;
	float health;
	float energy;
	EnergyType energyType;
	bool isDead;

public:

	Character() = delete;

	Character(string name, float health, float energy, EnergyType eType)
	{
		this->name = name;
		this->health = health;
		this->energy = energy;
		this->energyType = eType;
		isDead = false;
	}

	virtual string GetName() const;

	virtual void GetHit(float damage);

	virtual void GetHeal(float healValue);

	virtual void GainEnergy(float eValue);

	virtual void SpendEnergy(float eValue);

	virtual EnergyType GetEnergyType() const;

	virtual float GetHealthPoints() const 
	{
		return this->health;
	}

	virtual bool& IsDead()
	{
		return this->isDead;
	}

	~Character() = default;
};

