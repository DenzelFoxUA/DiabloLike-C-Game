#pragma once

#include <SFML/Graphics.hpp>
#include "NPCEntity.h"
#include "NPCMesh.h"
#include "Arrow.h"
#include <type_traits>
#include <concepts>
#include <iostream>
#include <cmath>
#include "BaseCharacterController.h"
#include "Character.h"
#include "CharacterMesh.h"
#include "ForbiddenZonesConfig.h"
using namespace std;
using namespace sf;


class NPC_Controller: public BaseCharacterController<NPCEntity>
{
protected:

    Clock attackTimer;
    Time attackCooldown;

    void ChasingEnemy(Vector2f point, float deltaTime, bool& isMoving) override;

    void UpdateStateAndDirection(Vector2f target) override;
    void UpdateStateAndDirection() override {};
    virtual void IdleBehavior();

public:

    NPC_Controller() = delete;

    NPC_Controller(CharacterMesh* _mesh, NPCEntity& _npcObj, float cooldown) 
        : BaseCharacterController<NPCEntity>(_mesh,_npcObj)
    {
        isChasing = false;
        attackCooldown = sf::seconds(cooldown);
    }

    //entity methods
    virtual void Death(float deltaTime) override;
    virtual void Draw(sf::RenderWindow& window) override {};

    //mesh methods
    virtual void MoveToPoint(Vector2f point, float deltaTime, bool& isMoving) override;
    void SetSpeed(float val) override;
    void UpdateHealthBar(sf::Sprite& barSprite, const Texture& barTexture,
        int currentHp, int maxHp);
    

    //input and behavior
    virtual void HandleBehavior(Vector2f target, Character& enemy, float deltaTime) override;
    virtual void HandleInput(float deltaTime) = 0;
    virtual void SwitchModes() override {};

    //events and update
    virtual void Update(float deltaTime, const sf::RenderWindow& window) override;
    virtual void HandleEvent(const sf::Event& event, const sf::RenderWindow& window) = 0;

    ~NPC_Controller()
    {
        cout << "NPC controller destroyed!" << endl;
    }
};