#include "SkeletonController.h"
#include <iostream>

void SkeletonController::HandleBehavior(Vector2f target, Character& enemy, float deltaTime)
{
    NPC_Controller<SkeletonMesh, Skeleton>::HandleBehavior(target,enemy,deltaTime);
}


void SkeletonController::Update(float deltaTime, const sf::RenderWindow& window, CharacterMesh& targetMesh, Character& target)
{

    this->npcMesh.Update(deltaTime, window);

}

void SkeletonController::Draw(sf::RenderWindow& window)
{
    npcMesh.Draw(window);
}
