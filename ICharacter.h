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

	//values
	virtual int GetId() = 0;
	virtual string GetName() = 0;
	virtual float GetEnergy() = 0;
	virtual EnergyType GetEnergyType() const = 0;
	virtual CharacterAttributes& GetAttributes() = 0;
	virtual float GetHealthPoints() = 0;
	virtual void GainExperience(int expPoints) = 0;
	virtual float GetEnergyLimit() = 0;
	virtual void SetEnergyLimit(float value) = 0;
	virtual void SetHPMaxLimit(float value) = 0;
	virtual float GetHPMaxLimit() = 0;
	virtual float GetEnergyRegainValue() = 0;
	virtual float GetHPRegainValue() = 0;
	virtual void SetEnergyRegainValue(float val) = 0;
	virtual void SetHPRegainValue(float val) = 0;

	//actions
	virtual void GetHit(float damage) = 0;
	virtual void Heal(float healValue) = 0;
	virtual void GainEnergy(float eValue) = 0;
	virtual void SpendEnergy(float eValue) = 0;
	virtual void Death() = 0;

	//status
	virtual bool& IsDead() = 0;

};

