#pragma once
#include <iostream>
#include <functional>
#include "ICharacter.h"
using namespace std;

class Character:public ICharacter
{
protected:

	int id;
	string name;
	float health;
	float stamina;
	float mana;
	bool isDead;

	float staminaMax;
	float healthMax;
	float manaMax;

	CharacterAttributes attributes;

	float staminaRegainValue = 20;
	float manaRegainValue = 5;
	float healthRegainValue = 0;

	std::unordered_map<int, std::function<void(int)>> deathListeners;
	int nextListenerId = 0;

public:

	Character() = delete;

	Character(int id, 
		string name, 
		float health, 
		float stamina,
		float mana,
		CharacterAttributes attributes)
	{
		this->id = id;
		this->name = name;
		this->health = health;
		this->stamina = stamina;
		this->staminaMax = stamina;
		this->healthMax = health;
		this->mana = mana; 
		this->manaMax = mana;
		this->attributes = attributes;
		isDead = false;
		
	}

	//values
	string GetName() override;
	int GetId() override;
	float GetStaminaPoints() override;

	float GetStaminaLimit() override;
	void SetStaminaLimit(float value) override;
	float GetManaLimit() override;
	void SetManaLimit(float value) override;

	CharacterAttributes& GetAttributes() override;

	void GainMana(float eValue) override;

	void SpendMana(float eValue) override;

	float GetHealthPoints() override;
	float GetManaPoints() override;
	void SetHPMaxLimit(float value) override;
	float GetHPMaxLimit() override;

	float GetStaminaRegainValue() override
	{
		return this->staminaRegainValue;
	}
	float GetHPRegainValue() override
	{
		return this->healthRegainValue;
	}
	float GetManaRegainValue() override
	{
		return this->staminaRegainValue;
	}

	void SetStaminaRegainValue(float val) override
	{
		this->staminaRegainValue = val;
	}

	void SetManaRegainValue(float val) override
	{
		this->manaRegainValue = val;
	}

	void SetHPRegainValue(float val) override
	{
		this->healthRegainValue = val;
	}

	//actions
	void GetHit(float damage) override;
	void Heal(float healValue) override;
	void GainStamina(float eValue) override;
	void SpendStamina(float eValue) override;
	virtual void Death() override;
	virtual void GainExperience(int expPoints) = 0;

	//bool
	bool& IsDead() override;
	
	//events funcs
	int SubscribeOnDeath(std::function<void(int expGained)> caller);
	void UnsubscribeOnDeath(int listenerId);

	~Character() = default;
};

