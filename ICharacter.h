#pragma once
#include <iostream>
#include <functional>
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

class ICharacter
{


public:

	virtual int GetId()const = 0;

	virtual string GetName() const = 0;

	virtual void GetHit(float damage) = 0;

	virtual void GetHeal(float healValue) = 0;

	virtual void GainEnergy(float eValue) = 0;

	virtual float GetEnergy()const = 0;

	virtual void SpendEnergy(float eValue) = 0;

	virtual EnergyType GetEnergyType() const = 0;

	virtual CharacterAttributes& GetAttributes() = 0;

	virtual float GetHealthPoints() const = 0;

	virtual bool& IsDead() = 0;

	virtual void Death() = 0;
	
	virtual void GainExperience(int expPoints) = 0;
};

