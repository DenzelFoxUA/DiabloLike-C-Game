#pragma once

#include <SFML/Graphics.hpp>
#include "NPCEntity.h"
#include "NPCMesh.h"
#include "Arrow.h"
#include <type_traits>
#include <concepts>
#include <iostream>
#include <cmath>
#include "Global_Variables.h"

using namespace std;
using namespace sf;

class IController
{
protected:

    //behavior
    virtual void MoveToPoint(Vector2f point, float deltaTime, bool& isMoving) = 0;
    virtual void UpdateStateAndDirection(Vector2f target) = 0;

public:

    //entity methods
    virtual Character& GetEntity() = 0;
    virtual bool& IsDead() = 0;
    virtual void Death(float deltaTime) = 0;
    virtual void SpendEnergy(float value) = 0;
    virtual void GainEnergy(float value) = 0;
    virtual float GetEnergyLimit() = 0;
    virtual void SetEnergyLimit(float value) = 0;
    virtual void RegenerateEnergy(float deltaTime) = 0;
    virtual void RegenerateHP(float deltaTime) = 0;
    virtual void SetHPRegainValue(float val) = 0;
    virtual void SetEnergyRegainValue(float val) = 0;
    virtual void SetManaRegainValue(float val) = 0;
    virtual void HealBySource(float val) = 0;
    virtual void RegenerateMana(float deltaTime) = 0;
    virtual float GetEnergy() = 0;
    virtual CharacterAttributes& GetAttributes() const = 0;
    

    //mesh methods
    virtual void SetSpeed(float val) = 0;
    virtual void Draw(sf::RenderWindow& window) = 0;
    virtual Vector2f GetCenter() = 0;
    virtual void FreezeOnMidFrame() = 0;
    virtual bool& IsAttacking() const = 0;
    virtual bool AnimationIsFinished() = 0;
    virtual bool& PendingNormalAttack() = 0;
    virtual bool& PendingChargedAttack() = 0;
    virtual float& GetChargeTime() const = 0;
    virtual bool& IsChargingAttack() const = 0;
    virtual float GetDistanceToTarget(Vector2f point) = 0;
    virtual Direction GetCurrentDirection() = 0;
    virtual Vector2f GetCurrentPosition() = 0;
    virtual bool& IsMoving() = 0;
    virtual void SetDeathAnimationTime(float val) = 0;
    virtual void SetAnimationDuration(float newVal) = 0;
    virtual Vector2f GetPosition() = 0;

    //input and behavior
    virtual void HandleInput(float deltaTime) = 0;
    virtual void HandleBehavior(Vector2f target, Character& enemy, float deltaTime) = 0;

    //events and Update
    virtual void HandleEvent(const sf::Event& event, const sf::RenderWindow& window) = 0;
    virtual void Update(float deltaTime, const sf::RenderWindow& window) = 0;

    //combat calculators
    virtual float CaltulateShootSpeed(bool isCharged) = 0;
    virtual float CalculateShootDamage(bool isCharged, ProjectileType type) = 0;
    virtual float CalculateHitRadius(bool isCharged, ProjectileType type) = 0;
    virtual float CaltculateMeleeDamage(bool isPowered) = 0;
    
};
