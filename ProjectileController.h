#pragma once

#include <SFML/Graphics.hpp>
#include "Projectile.h"
#include "ProjectileMesh.h"
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
    Mesh* projMesh;
    Obj* projEntity;

   
    virtual float GetDistanceToTarget(Vector2f point);

public:
    ProjectileController() = delete;

    ProjectileController(Mesh* _mesh, Obj* _npcObj, float cooldown) : npcMesh(_mesh), npcEntity(_npcObj)
    {
        static_assert(std::is_base_of_v<ProjectileMesh, Mesh>, "Mesh must inherit from NPCMesh");
        static_assert(std::is_base_of_v<Projectile, Obj>, "Obj must inherit from NPCEntity");
        isChasing = false;
        attackCooldown = sf::seconds(cooldown);
    }

    virtual void HandleBehavior(Vector2f target, Character& enemy, float deltaTime);
    virtual void Update(float deltaTime, const sf::RenderWindow& window) = 0;

    ~NPC_Controller()
    {
        cout << "NPC controller destroyed!" << endl;
        delete npcMesh;
        delete npcEntity;
    }
};
