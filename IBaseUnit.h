#pragma once
#include <SFML/Graphics.hpp>
#include "Projectile.h"
#include "BaseMesh.h"
#include <cmath>

using namespace std;
using namespace sf;

class IController;
class Character;
class CharacterMesh;

class IBaseUnit {

protected:
    //
public:

    //mesh
    virtual Vector2f GetPosition() = 0;
    virtual Vector2f GetCenter() = 0;
    virtual void MoveToPoint(sf::Vector2f point, float deltaTime) = 0;
    virtual void SetAnimationDuration(float newVal) = 0;
    virtual void SetSpeed(float val) = 0;
    virtual void Draw(sf::RenderWindow& window) = 0;
    virtual void SetDeathAnimationTime(float val) = 0;
    virtual void SetAttackDelay(float time) = 0;
    //entity
    virtual Character& GetEntity() = 0;
    virtual bool& IsDead() = 0;
    virtual void GainXP(int expPoints) = 0;
    virtual void SpendEnergy(float value) = 0;
    virtual void GainEnergyBySource(float value) = 0;
    virtual void HealBySource(float value) = 0;
    virtual void GetHit(float dmg) = 0;
    virtual string GetName() = 0;

    virtual void SetEnergyRegainValue(float val) = 0;
    virtual void SetManaRegainValue(float val) = 0;
    virtual void SetHPRegainValue(float val) = 0;
    
    //events subscribtions
    virtual void SubscribeOnEnemy(Character& enemy) = 0;
    virtual void UnsubscribeFromEnemy(Character& enemy) = 0;

    //controller direct
    virtual IController& GetController() = 0;

    //controller combat
    virtual void Shot(Texture& texture, Vector2f mousePos) = 0;
    virtual void ShotCharged(Texture& texture, Vector2f targetPos) = 0;
    virtual void MeleeAttack(Direction facing, const std::vector<IBaseUnit*>& enemies, bool isCharged) = 0;
    virtual ProjectileType GetTypeOfProjectile() = 0;

    virtual void HandleInput(float deltaTime) = 0;
    virtual void HandleMouseEvent(const sf::Event& event, const sf::RenderWindow& window, float dt) = 0;
    virtual void HandleBehavior(IBaseUnit* target, float deltaTime) = 0;
    virtual void Update(float deltaTime, const sf::RenderWindow& window) = 0;

    virtual ~IBaseUnit() = default;
};

