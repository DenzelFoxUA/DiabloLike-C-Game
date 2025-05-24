#include "SkeletonController.h"
#include <iostream>

void SkeletonController::HandleBehavior(Vector2f target, Character& enemy, float deltaTime)
{
    NPC_Controller::HandleBehavior(target,enemy,deltaTime);
}


void SkeletonController::Update(float deltaTime, const sf::RenderWindow& window)
{
    NPC_Controller::Update(deltaTime, window);
}

void SkeletonController::Draw(sf::RenderWindow& window)
{
    mesh->Draw(window);
}

Character& SkeletonController::GetEntity()
{
    return this->entity;
}

void SkeletonController::SetSpeed(float val)
{
    mesh->SetSpeed(val);
}

void SkeletonController::HandleInput(float deltaTime){}

void SkeletonController::HandleMouseEvent(const sf::Event& event, const sf::RenderWindow& window, float dt){}

