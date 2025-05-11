#pragma once

#include <SFML/Graphics.hpp>
#include "NPCEntity.h"
#include "NPCMesh.h"
#include "Arrow.h"
#include <type_traits>
#include <concepts>
#include <iostream>
#include <cmath>

using namespace std;
using namespace sf;

class IController
{
protected:

    virtual void ChasingEnemy(Vector2f point, float deltaTime, bool& isMoving) = 0;
    virtual float GetDistanceToTarget(Vector2f point) = 0;

public:

    virtual void SetSpeed(float val) = 0;
    virtual void HandleInput(float deltaTime) = 0;
    virtual Character& GetEntity() = 0;
    virtual void HandleEvent(const sf::Event& event, const sf::RenderWindow& window) = 0;
    virtual void Update(float deltaTime, const sf::RenderWindow& window/*, CharacterMesh& targetMesh, Character& target*/) = 0;
    virtual void Draw(sf::RenderWindow& window) = 0;
    virtual void HandleBehavior(Vector2f target, Character& enemy, float deltaTime) = 0;
    virtual bool& IsDead() = 0;
    virtual Vector2f GetCenter() = 0;
    virtual void Death() = 0;
};
