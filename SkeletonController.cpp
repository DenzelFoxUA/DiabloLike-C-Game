#include "SkeletonController.h"
#include <iostream>

void SkeletonController::HandleBehavior(Vector2f target, Character& enemy, float deltaTime)
{
    NPC_Controller<SkeletonMesh, Skeleton>::HandleBehavior(target,enemy,deltaTime);
    //float& chargeTime = characterMesh->ChargeTime();
    //bool& chargingShot = characterMesh->IsChargingAttack();
    //if (chargingShot) {
    //    chargeTime += deltaTime;
    //    if (chargeTime > characterMesh->MaxChargeTime())
    //        chargeTime = characterMesh->MaxChargeTime();
    //}
}


void SkeletonController::Update(float deltaTime, const sf::RenderWindow& window)
{

    this->npcMesh->Update(deltaTime, window);

}
