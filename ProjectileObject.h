#pragma once

#include <SFML/Graphics.hpp>
#include "Projectile.h"
#include "ProjectileMesh.h"
#include "Character.h"
#include <type_traits>
#include <concepts>
#include <iostream>
#include <cmath>

class IProjectileObject 
{
public:
    virtual ~IProjectileObject() = default;
    virtual void Update(float deltaTime) = 0;
    virtual void Draw(sf::RenderWindow& window) = 0;

    virtual bool IsDead() const = 0;
    virtual float GetDamage() = 0;
    virtual sf::Vector2f GetPosition() = 0;
    virtual float GetHitRadius() = 0;
    virtual void ApplyDamageTo(Character& target) = 0;
    virtual ProjectileType GetType() = 0;
    virtual void MarkToDestroy() = 0;

};

template <typename MeshT, typename EntityT>
class ProjectileObject : public IProjectileObject
{
protected:
    
    MeshT projMesh;
    EntityT projEntity;

    inline float GetDistance(Vector2f a, Vector2f b) const
    {
        return std::sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
    }

public:
    ProjectileObject() = delete;

    ProjectileObject(MeshT&& _mesh, EntityT&& _entity)
        :projMesh(std::move(_mesh)), projEntity(std::move(_entity))
    {
        static_assert(std::is_base_of_v<ProjectileMesh, MeshT>, "Mesh must inherit from ProjectileMesh");
        static_assert(std::is_base_of_v<Projectile, EntityT>, "Obj must inherit from Projectile");
    }

    void Update(float deltaTime) override
    {
        projMesh.Update(deltaTime);
    }

    void Draw(sf::RenderWindow& window) override
    {

        if (!IsDead())
        {
            //cout << "Arrow Drawed!" << endl;
            projMesh.Draw(window);
        }

    }

    bool IsDead() const override
    {
        return projMesh.IsDead();
    }

    MeshT& GetMesh() const { return projMesh; }
    EntityT& GetEntity() { return projEntity; }

    float GetDamage() override { return projEntity.GetDamage(); }

    void ApplyDamageTo(Character& target) override
    {
        //target.GetHit(this->GetDamage());
        target.GetHit(this->GetDamage());
    }

    Vector2f GetPosition() override
    {
        return this->projMesh.GetPosition();
    }

    float GetHitRadius() override
    {
        return this->projEntity.GetHitRadius();
    }

    ProjectileType GetType() override
    {
        return this->projEntity.GetType();
    }

    virtual void MarkToDestroy() override
    {
        this->projMesh.MarkToDestroy();
    }
};

