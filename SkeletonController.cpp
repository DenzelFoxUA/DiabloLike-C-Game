#include "SkeletonController.h"
#include <iostream>

void SkeletonController::HandleBehavior(Vector2f target, Character& enemy, float deltaTime)
{
    NPC_Controller::HandleBehavior(target,enemy,deltaTime);
}


void SkeletonController::Update(float deltaTime, const sf::RenderWindow& window)
{
    this->npcMesh.Update(deltaTime, window, 
        this->npcEntity.GetHealthPoints(), this->npcEntity.GetHPMaxLimit());
}

void SkeletonController::Draw(sf::RenderWindow& window)
{
    npcMesh.Draw(window);
}

Character& SkeletonController::GetEntity()
{
    return this->npcEntity;
}

void SkeletonController::SetSpeed(float val)
{
    this->npcMesh.SetSpeed(val);
}

void SkeletonController::HandleInput(float deltaTime)
{
    
}

void SkeletonController::HandleEvent(const sf::Event& event, const sf::RenderWindow& window)
{
    
}

