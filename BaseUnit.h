#pragma once
#include <functional>
#include <iostream>
#include "IBaseUnit.h"


class ProjectilesContainer;

template <typename EntityT>
class BaseUnit : public IBaseUnit
{
protected:

    map<int, int> enemiesSubscriptions;

    EntityT _character;
    ProjectileType _projectileEquiped;
    ProjectilesContainer* allGameProjectiles;

    virtual void GetHit(float dmg) override
    {
        this->_character.GetHit(dmg);
    };

    virtual string GetName() override
    {
       return this->_character.GetName();
    }


    
public:

    BaseUnit(const EntityT& character, ProjectileType equip, ProjectilesContainer* container)
        : _character(character), _projectileEquiped(equip), allGameProjectiles(container)
    {
    }

    virtual EntityT& GetEntity() override { return this->_character; }

    virtual bool& IsDead() override
    {
        return this->_character.IsDead();
    }

    virtual void SetDeathAnimationTime(float val) = 0;

    virtual void SetAttackDelay(float time) override {

    }
    //virtual CharacterMesh& GetMesh() = 0;
    virtual Vector2f GetPosition() = 0;
    virtual Vector2f GetCenter() = 0;
    virtual void MoveToPoint(Vector2f point, float deltaTime) = 0;
    virtual void SetAnimationDuration(float newVal) = 0;
    virtual void SetSpeed(float val) = 0;
    virtual void Draw(RenderWindow& window) = 0;
    virtual IController& GetController() = 0;

    virtual void Update(float deltaTime, const sf::RenderWindow& window) = 0;

    virtual void Shot(Texture& projTexture, Vector2f targetPos) = 0;
    virtual void ShotCharged(Texture& projTexture, Vector2f targetPos) = 0;

    virtual void MeleeAttack(Direction facing, const std::vector<IBaseUnit*>& enemies, bool isCharged) = 0;

    //virtual void Death() = 0;

    virtual ProjectileType GetTypeOfProjectile() override
    {
        return this->_projectileEquiped;
    }

    virtual void SubscribeOnEnemy(Character& enemy) = 0;
    virtual void UnsubscribeFromEnemy(Character& enemy) = 0;

    virtual void GainXP(int expPoints) = 0;
    virtual void SpendEnergy(float value) = 0;
    
    void SetEnergyRegainValue(float val) override
    {

    }

    void SetManaRegainValue(float val) override
    {
      
    }

    void SetHPRegainValue(float val) override
    {
       
    }

    virtual void GainEnergyBySource(float value) = 0;
    virtual void HealBySource(float value) = 0;
    virtual void HandleBehavior(IBaseUnit* target, float deltaTime) = 0;
    virtual void HandleInput(float deltaTime) override {};
    virtual void HandleMouseEvent(const sf::Event& event, const sf::RenderWindow& window, float dt) override {};

    virtual ~BaseUnit() override = default;

    template <typename, typename>
    friend class UnitBuilder;
};