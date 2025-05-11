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
	float energyMax = 500;

	CharacterAttributes attributes;

	std::unordered_map<int, std::function<void(int)>> deathListeners;
	int nextListenerId = 0;

public:

	Character() = delete;

	Character(int id, string name, float health, float energy, CharacterAttributes attributes, EnergyType eType)
	{
		this->id = id;
		this->name = name;
		this->health = health;
		this->energy = energy;
		this->energyType = eType;
		this->attributes = attributes;
		isDead = false;
		
	}

	virtual int GetId()const override
	{
		return id;
	}

	virtual float GetEnergy() const override
	{
		return this->energy;
	}

	virtual string GetName() const override;

	virtual void GetHit(float damage) override;

	virtual void GetHeal(float healValue) override;

	virtual void GainEnergy(float eValue) override;

	virtual void SpendEnergy(float eValue) override;

	virtual EnergyType GetEnergyType() const override;

	virtual CharacterAttributes& GetAttributes() override;

	virtual float GetHealthPoints() const override;

	virtual bool& IsDead() override;

	virtual void Death()  override
	{
		if (isDead) return;
		isDead = true;

		std::cout << "Enemy died!\n";
		for (auto& [_, listener] : deathListeners)
		{
			listener(100); // Наприклад, 100 досвіду
		}
	}
	
	int SubscribeOnDeath(std::function<void(int expGained)> caller)
	{
		int id = nextListenerId++;
		deathListeners[id] = caller;
		return id;
	}

	void UnsubscribeOnDeath(int listenerId)
	{
		deathListeners.erase(listenerId);
	}


	virtual void GainExperience(int expPoints) = 0;

	~Character() = default;
};

