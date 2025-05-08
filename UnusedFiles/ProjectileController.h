//#pragma once
//
//#include <SFML/Graphics.hpp>
//#include "Projectile.h"
//#include "ProjectileMesh.h"
//#include "Character.h"
//#include <type_traits>
//#include <concepts>
//#include <iostream>
//#include <cmath>
//
//using namespace std;
//using namespace sf;
//
//template <typename Mesh, typename Obj>
//class ProjectileController
//{
//protected:
//    vector<Mesh>* projMesh;
//    vector<Obj>* projEntity;
//    
//    virtual float GetDistanceToTarget(Vector2f point);
//
//public:
//    ProjectileController() = delete;
//
//    ProjectileController(vector<Mesh>* _mesh, vector<Obj>* _npcObj) : projMesh(_mesh), projEntity(_npcObj)
//    {
//        static_assert(std::is_base_of_v<ProjectileMesh, Mesh>, "Mesh must inherit from ProjectileMesh");
//        static_assert(std::is_base_of_v<Projectile, Obj>, "Obj must inherit from ProjectileEntity");
//    }
//
//    virtual void HandleBehavior(Vector2f targetPoint, Character& enemy, float deltaTime);
//    virtual bool IsDead() { return projMesh.IsDead(); }
//    virtual void Update(float deltaTime /* const sf::RenderWindow& window*/)
//    {
//        projMesh->Update(deltaTime);
//    };
//    virtual void Draw(sf::RenderWindow& window)
//    {
//        projMesh->Draw(window);  // делегуємо рендер у Mesh
//    }
//
//    virtual Mesh &GetMesh()
//    {
//        return projMesh;
//    }
//
//    virtual Obj &GetEntiity()
//    {
//        return projEntity;
//    }
//
//    //~ProjectileController()
//    //{
//    //    cout << "Projectile controller destroyed!" << endl;
//    //    //delete projMesh;
//    //    //delete projEntity;
//    //}
//};
//
//template<typename Mesh, typename Obj>
//float ProjectileController<Mesh, Obj>::GetDistanceToTarget(Vector2f point)
//{
//    Vector2f a = projMesh.GetPosition();
//    Vector2f b = point;
//    return std::sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
//}
//
//template<typename Mesh, typename Obj>
//void ProjectileController<Mesh, Obj>::HandleBehavior(Vector2f targetPoint, Character& enemy, float deltaTime)
//{
//    projMesh.Update(deltaTime);
//
//    bool isCharged = this->projEntity.IsCharged();
//    float dist = GetDistanceToTarget(targetPoint);
//
//    if (dist <= 40.f && !projEntity->HasHitTarget())
//    {
//        
//        auto dmg = projEntity.GetDamage();
//
//        if (isCharged)
//        {
//            dmg *= 2.f;
//        }
//
//        this->projEntity.SetDamage(dmg);
//        this->projEntity.ApplyDamage(enemy);
//        std::cout << enemy.GetName() << " get hit " << dmg << "damage!" << endl;
//        this->projMesh.EndLifeTime();
//    }
//}

#pragma once

#include <SFML/Graphics.hpp>
#include "Projectile.h"
#include "ProjectileMesh.h"
#include "Character.h"
#include <type_traits>
#include <concepts>
#include <iostream>
#include <cmath>

using namespace std;
using namespace sf;

template <typename Mesh, typename Obj>
class ProjectileController
{
protected:
    Mesh projMesh;
    Obj projEntity;

    float GetDistance(Vector2f a, Vector2f b) const
    {
        return std::sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
    }

public:
    ProjectileController() = delete;

    //ProjectileController(Mesh _mesh, Obj _entity)
    //    : projMesh(_mesh), projEntity(_entity)
    //{
    //    static_assert(std::is_base_of_v<ProjectileMesh, Mesh>, "Mesh must inherit from ProjectileMesh");
    //    static_assert(std::is_base_of_v<Projectile, Obj>, "Obj must inherit from Projectile");
    //}

    ProjectileController(Mesh&& _mesh, Obj&& _entity)
        : projMesh(std::move(_mesh)), projEntity(std::move(_entity))
    {
        static_assert(std::is_base_of_v<ProjectileMesh, Mesh>, "Mesh must inherit from ProjectileMesh");
        static_assert(std::is_base_of_v<Projectile, Obj>, "Obj must inherit from Projectile");
    }

    virtual void HandleBehavior(Vector2f targetPoint, Character& enemy, float deltaTime)
    {
        projMesh.Update(deltaTime);
        std::cout << "Arrow Pos: " << projMesh.GetPosition().x << " " << projMesh.GetPosition().y << std::endl;
        float dist = GetDistance(projMesh.GetPosition(), targetPoint);

        if (dist <= 80.f && !projEntity.HasHitTarget())
        {
            float dmg = projEntity.GetDamage();

            if (projEntity.IsCharged())
            {
                cout << "Charged: " << dmg << " * 2" << endl;
                dmg *= 2.f;
            }
                

            projEntity.SetDamage(dmg);
            projEntity.ApplyDamage(enemy);
            std::cout << enemy.GetName() << " get hit " << dmg << " damage!" << std::endl;

            projMesh.EndLifeTime();
            projEntity.SetHitTarget(true);
        }
    }

    void Update(float deltaTime)
    {
        projMesh.Update(deltaTime);
    }

    void Draw(sf::RenderWindow& window)
    {
        
        if (!IsDead())
        {
            cout << "Arrow Drawed!" << endl;
            projMesh.Draw(window);
        }
            
    }

    bool IsDead() const
    {
        return projMesh.IsDead();
    }

    Mesh& GetMesh() const { return projMesh; }
    Obj& GetEntity() { return projEntity; }

    float GetDamage() { return projEntity.GetDamage(); }
};
