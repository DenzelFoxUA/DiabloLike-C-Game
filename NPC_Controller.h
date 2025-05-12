#pragma once

#include <SFML/Graphics.hpp>
#include "NPCEntity.h"
#include "NPCMesh.h"
#include "Arrow.h"
#include <type_traits>
#include <concepts>
#include <iostream>
#include <cmath>
#include "IController.h"
#include "Character.h"
#include "CharacterMesh.h"
#include "ForbiddenZonesConfig.h"
using namespace std;
using namespace sf;


class NPC_Controller: public IController
{
protected:

    CharacterMesh& npcMesh;
    NPCEntity& npcEntity;

    float regainE_Timer = 2.f;
    float regainE_Tik = 0.f;

    float regainHP_Timer = 2.f;
    float regainHP_Tik = 0.f;

    Clock attackTimer;
    Time attackCooldown;

    bool isChasing,
        isTressPass = false;

    virtual void ChasingEnemy(Vector2f point, float deltaTime, bool& isMoving) override;
    virtual float GetDistanceToTarget(Vector2f point) override;

    virtual bool IsTressPassing(const vector<FloatRect>& forbiddenZones);

public:

    NPC_Controller() = delete;

    NPC_Controller(CharacterMesh& _mesh, NPCEntity& _npcObj, float cooldown) : npcMesh(_mesh), npcEntity(_npcObj)
    {
        isChasing = false;
        attackCooldown = sf::seconds(cooldown);
    }

    //entity methods
    virtual Character& GetEntity() override;
    virtual bool& IsDead() override;
    virtual void Death()override;
    void SpendEnergy(float value) override;
    void GainEnergy(float value) override;
    float GetEnergyLimit() override;
    void SetEnergyLimit(float value) override;

    float GetEnergy() override {
        return this->npcEntity.GetEnergy();
    }

    void RegenerateEnergy(float val, float deltaTime) override
    {
        regainE_Tik += deltaTime;

        if (this->npcEntity.GetEnergy() < this->npcEntity.GetEnergyLimit() 
            && regainE_Timer <= regainE_Tik)
        {
            cout << "Gained " << val << " energy!" << endl;
            this->GainEnergy(val);
            regainE_Tik = 0.f;
        }

    }

    void RegenerateHP(float val, float deltaTime) override
    {
        regainHP_Tik += deltaTime;

        if (this->npcEntity.GetHealthPoints() < this->npcEntity.GetHPMaxLimit()
            && regainHP_Timer <= regainHP_Tik)
        {
            cout << "Gained " << val << " health!" << endl;
            this->npcEntity.Heal(val);
            regainE_Tik = 0.f;
        }

    }

    void SetEnergyRegainValue(float val) override
    {
        this->npcEntity.SetEnergyRegainValue(val);
    }

    void SetHPRegainValue(float val) override
    {
        this->npcEntity.SetHPRegainValue(val);
    }

    void HealBySource(float val) override
    {
        this->npcEntity.Heal(val);
    }

    //mesh methods
    virtual void SetSpeed(float val) = 0;
    virtual void Draw(sf::RenderWindow& window) = 0;
    Vector2f GetCenter() override;
    float& GetChargeTime() const override;
    bool& IsChargingAttack() const override;
    void FreezeOnMidFrame() override;
    bool& IsAttacking() const override;
    bool AnimationIsFinished() override;
    bool& PendingNormalAttack() override;
    bool& PendingChargedAttack() override;

    //input and behavior
    virtual void HandleBehavior(Vector2f target, Character& enemy, float deltaTime) override;
    virtual void HandleInput(float deltaTime) = 0;

    //events and update
    virtual void Update(float deltaTime, const sf::RenderWindow& window) override;
    virtual void HandleEvent(const sf::Event& event, const sf::RenderWindow& window) = 0;

    ~NPC_Controller()
    {
        cout << "NPC controller destroyed!" << endl;
    }
};