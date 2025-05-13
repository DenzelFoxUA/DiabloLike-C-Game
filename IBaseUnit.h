#pragma once
#include <SFML/Graphics.hpp>
#include "Projectile.h"
#include "BaseMesh.h"
using namespace std;
using namespace sf;

class IController;
class Character;
class CharacterMesh;

class IBaseUnit {
public:

    //mesh
    virtual CharacterMesh& GetMesh() = 0;
    virtual Vector2f GetPosition() = 0;
    virtual Vector2f GetCenter() const = 0;
    virtual Vector2f MoveToPoint(sf::Vector2f point) = 0;
    virtual void SetAnimationDuration(float newVal) = 0;
    virtual void SetSpeed(float val) = 0;
    virtual void Draw(sf::RenderWindow& window) = 0;

    //entity
    virtual Character& GetEntity() = 0;
    virtual bool& IsDead() = 0;
    virtual void Death() = 0;
    virtual void SubscribeOnEnemy(Character& enemy) = 0;
    virtual void UnsubscribeFromEnemy(Character& enemy) = 0;
    virtual void GainXP(int expPoints) = 0;
    virtual void SpendEnergy(float value) = 0;
    
    virtual void GainEnergyBySource(float value) = 0;
    virtual void HealBySource(float value) = 0;
    
    
    //controller direct
    virtual IController& GetController() = 0;

    //controller
    virtual void Shot(Texture& texture) = 0;
    virtual void ShotCharged(Texture& texture) = 0;
    virtual void MeleeAttack(Direction facing, const std::vector<IBaseUnit*>& enemies) = 0;
    virtual ProjectileType GetTypeOfProjectile() = 0;
    virtual void HandleBehavior(IBaseUnit* target, float deltaTime) = 0;
    virtual ~IBaseUnit() = default;
};

