
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

    Clock attackTimer;
    Time attackCooldown;

    bool isChasing,
        isTressPass = false;

    virtual void ChasingEnemy(Vector2f point, float deltaTime, bool& isMoving) override;
    virtual float GetDistanceToTarget(Vector2f point) override;

    virtual bool IsTressPassing(const vector<FloatRect>& forbiddenZones)
    {
        FloatRect npcZone = this->npcMesh.Sprite().getGlobalBounds();
        for (const auto& zone : forbiddenZones)
        {
            if (npcZone.intersects(zone))
            {
                std::cout << "Tresspassing zone: " << zone.left << ", " << zone.top << ", "
                    << zone.width << "x" << zone.height << std::endl;
                this->isTressPass = true;
                return true; 
            }
        }

        this->isTressPass = false;
        return false;
    }


public:

    NPC_Controller() = delete;

    NPC_Controller(CharacterMesh& _mesh, NPCEntity& _npcObj, float cooldown) : npcMesh(_mesh), npcEntity(_npcObj)
    {
        isChasing = false;
        attackCooldown = sf::seconds(cooldown);
    }

    virtual void SetSpeed(float val) = 0;
    virtual bool& IsDead() override
    { 
        return this->npcEntity.IsDead(); 
    }
    virtual void HandleBehavior(Vector2f target, Character& enemy, float deltaTime) override;
    virtual void Update(float deltaTime, const sf::RenderWindow& window) = 0;
    virtual void Draw(sf::RenderWindow& window) = 0;
    virtual Vector2f GetCenter() override
    {
        return this->npcMesh.GetCenter();
    }

    virtual void HandleEvent(const sf::Event& event, const sf::RenderWindow& window) = 0;
    virtual void HandleInput(float deltaTime) = 0;

    virtual void Death()override
    {
        cout << "Object died in controller NPC" << endl;
        this->npcEntity.Death();
    }

    ~NPC_Controller()
    {
        cout << "NPC controller destroyed!" << endl;
    }


    std::function<void(int expGained)> OnDeath;
};


