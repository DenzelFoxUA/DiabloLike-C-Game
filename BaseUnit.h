#pragma once
#include <functional>
#include <iostream>
#include "IBaseUnit.h"

class ProjectilesContainer;

template <typename EntityT>
class BaseUnit : public IBaseUnit
{
protected:

    std::map<int, int> enemiesSubscriptions;

    
    EntityT _character;
    ProjectileType _projectileEquiped;
    ProjectilesContainer* allGameProjectiles;

public:

    BaseUnit(const EntityT& character, ProjectileType equip, ProjectilesContainer* container)
        : _character(character), _projectileEquiped(equip), allGameProjectiles(container)
    {
    }

    virtual EntityT& GetEntity()
    {
        return this->_character;
    }

    virtual bool& IsDead() override
    {
        return this->_character.IsDead();
    }

    virtual CharacterMesh& GetMesh() = 0;
    virtual Vector2f GetPosition() const = 0;
    virtual Vector2f GetCenter() const = 0;
    virtual Vector2f MoveToPoint(Vector2f point) = 0;
    virtual void SetAnimationDuration(float newVal) = 0;
    virtual void SetSpeed(float val) = 0;
    virtual void Draw(RenderWindow& window) = 0;
    virtual IController& GetController() = 0;

    virtual void Shot(Texture& projTexture) = 0;
    virtual void ShotCharged(Texture& projTexture) = 0;

    virtual void Death() override
    {

    }

    virtual ProjectileType GetTypeOfProjectile() override
    {
        return this->_projectileEquiped;
    }

    virtual void SubscribeOnEnemy(Character& enemy) = 0;
    virtual void UnsubscribeFromEnemy(Character& enemy) = 0;

    virtual void GainXP(int expPoints) = 0;

    virtual void SpendEnergy(float value) = 0;
    virtual void GainEnergyDueTime(float val, float deltaTime) = 0;
    virtual void GainEnergyBySource(float value) = 0;

    virtual ~BaseUnit() override = default;

    template <typename, typename>
    friend class UnitBuilder;
};