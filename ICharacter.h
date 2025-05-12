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
	

	virtual CharacterAttributes& GetAttributes() = 0;
	virtual float GetHealthPoints() = 0;
	virtual float GetStaminaPoints() = 0;
	virtual float GetManaPoints() = 0;
	virtual void GainExperience(int expPoints) = 0;

	virtual void SetHPMaxLimit(float value) = 0;
	virtual float GetHPMaxLimit() = 0;
	virtual float GetStaminaLimit() = 0;
	virtual void SetStaminaLimit(float value) = 0;
	virtual float GetManaLimit() = 0;
	virtual void SetManaLimit(float value) = 0;

	virtual void SetHPRegainValue(float val) = 0;
	virtual float GetHPRegainValue() = 0;
	virtual float GetStaminaRegainValue() = 0;
	virtual void SetStaminaRegainValue(float val) = 0;
	virtual void SetManaRegainValue(float val) = 0;
	virtual float GetManaRegainValue() = 0;

	//actions
	virtual void GetHit(float damage) = 0;
	virtual void Heal(float healValue) = 0;
	virtual void GainStamina(float eValue) = 0;
	virtual void SpendStamina(float eValue) = 0;
	virtual void GainMana(float eValue) = 0;
	virtual void SpendMana(float eValue) = 0;
	virtual void Death() = 0;

	//status
	virtual bool& IsDead() = 0;

};

