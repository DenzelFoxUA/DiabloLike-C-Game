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
	float energy;
	EnergyType energyType;
	bool isDead;

	float energyMax; 
	float healthMax;

	CharacterAttributes attributes;

	float energyRegainValue = 20;
	float healthRegainValue = 0;

	std::unordered_map<int, std::function<void(int)>> deathListeners;
	int nextListenerId = 0;

public:

	Character() = delete;

	Character(int id, 
		string name, 
		float health, 
		float energy, 
		CharacterAttributes attributes, 
		EnergyType eType)
	{
		this->id = id;
		this->name = name;
		this->health = health;
		this->energy = energy;
		this->energyMax = energy;
		this->healthMax = health;
		this->energyType = eType;
		this->attributes = attributes;
		isDead = false;
		
	}

	//values
	string GetName() override;
	int GetId() override;
	float GetEnergy() override;
	EnergyType GetEnergyType() const override;
	CharacterAttributes& GetAttributes() override;
	float GetHealthPoints() override;
	void SetEnergyLimit(float value) override;
	float GetEnergyLimit() override;
	void SetHPMaxLimit(float value) override;
	float GetHPMaxLimit() override;

	float GetEnergyRegainValue() override
	{
		return this->energyRegainValue;
	}
	float GetHPRegainValue() override
	{
		return this->healthRegainValue;
	}
	void SetEnergyRegainValue(float val) override
	{
		this->energyRegainValue = val;
	}

	void SetHPRegainValue(float val) override
	{
		this->healthRegainValue = val;
	}

	//actions
	void GetHit(float damage) override;
	void Heal(float healValue) override;
	void GainEnergy(float eValue) override;
	void SpendEnergy(float eValue) override;
	virtual void Death() override;
	virtual void GainExperience(int expPoints) = 0;

	//bool
	bool& IsDead() override;
	
	//events funcs
	int SubscribeOnDeath(std::function<void(int expGained)> caller);
	void UnsubscribeOnDeath(int listenerId);

	~Character() = default;
};

