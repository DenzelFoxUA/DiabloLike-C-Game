#include "LadyArcherMesh.h"
#include <iostream>

void LadyArcherMesh::Shoot(sf::Texture& arrowTexture, sf::Vector2f direction)
{
    sf::Vector2f center = GetCenter();

    if (direction.x == 0.f && direction.y == 0.f) {
        direction.x = 1.f;
        std::cout << "WARNING: direction was zero! Defaulted to (1,0)\n";
    }
    ArrowMesh arrow(arrowTexture, GetCenter(), direction,250.f,6.f);
    
    arrows.push_back(arrow);
    std::cout << "Shooting arrow from (" << center.x << ", " << center.y << ") in direction: ("
        << direction.x << ", " << direction.y << ")\n";

}

void LadyArcherMesh::ShootCharged(sf::Texture& texture, sf::Vector2f direction, float charge)
{
    sf::Vector2f center = GetCenter();

    if (direction.x == 0.f && direction.y == 0.f) {
        direction.x = 1.f;
        std::cout << "WARNING: charged direction was zero! Defaulted to (1,0)\n";
    }

    float normalizedCharge = std::clamp(charge / maxChargeTime, 0.1f, 1.0f);
    ArrowMesh arrow(texture, center, direction,250.f, 6.f);
    float finalSpeed = 400.f + 600.f * normalizedCharge;
    arrow.SetSpeed(finalSpeed);
    arrows.push_back(arrow);

    std::cout << "Charged shot from (" << center.x << ", " << center.y << ") dir: ("
        << direction.x << ", " << direction.y << ") speed: " << finalSpeed << "\n";
}


void LadyArcherMesh::Update(float deltaTime, const sf::RenderWindow& window)
{
   PlayerCharacterMesh::Update(deltaTime, window);

    if (isAttacking) {
        attackTimer += deltaTime;

        if (attackTimer >= attackDelay) {
            if (pendingNormalAttack) {
                std::cout << "NORMAL SHOT FIRED\n";
                Shoot(arrowTexture, pendingDirection);
                pendingNormalAttack = false;
            }
            else if (pendingChargedAttack) {
                std::cout << "CHARGED SHOT FIRED\n";
                ShootCharged(arrowTexture, pendingDirection, pendingChargeTime);
                pendingChargedAttack = false;
            }

            isAttacking = false;
            currentState = CharacterState::Idle;

            int height = texturesData[TextureCategory::Idle].frameHeight;
            int width = texturesData[TextureCategory::Idle].frameWidth;
            int columns = texturesData[TextureCategory::Idle].numberOfColumns;
            int frames = texturesData[TextureCategory::Idle].numberOfFrames;
            
            animation.SetSheet(&idleTextures[currentDir], width, height, columns, frames, true);
        }
    }

    for (auto it = arrows.begin(); it != arrows.end(); )
    {
        std::cout << "UPDATING ARROW\n";
        it->Update(deltaTime);

        if (it->IsDead()) {
            std::cout << "ARROW REMOVED\n";
            it = arrows.erase(it);
        }
        else {
            ++it;
        }
    }
}

void LadyArcherMesh::Draw(sf::RenderWindow& window)
{
    PlayerCharacterMesh::Draw(window);  

    for (ArrowMesh& arrow : arrows)
    {
        std::cout << "DRAWING ARROW AT: " << arrow.GetPosition().x << ", " << arrow.GetPosition().y << "\n";
        arrow.Draw(window);
    }
        
}

vector<ArrowMesh>& LadyArcherMesh::Arrows()
{
    return this->arrows;
}

Texture& LadyArcherMesh::ArrowTex()
{
    return this->arrowTexture;
}

//bool& LadyArcherMesh::IsCharged()
//{
//    return this->shotAlreadyCharged;
//}
//
//bool& LadyArcherMesh::IsChargingAttack()
//{
//    return this->chargingShot;
//}
//
//float& LadyArcherMesh::ChargeTime()
//{
//    return this->chargeTime;
//}
//
//float& LadyArcherMesh::AttackTimer()
//{
//    return this->attackTimer;
//}
//
//bool& LadyArcherMesh::PendingNormalAttack()
//{
//    return this->pendingNormalShot;
//}
//bool& LadyArcherMesh::PendingChargedAttack()
//{
//    return this->pendingChargedShot;
//}
//
//Vector2f& LadyArcherMesh::PendingDirection()
//{
//    return this->pendingDirection;
//}
//
//float& LadyArcherMesh::PendingChargeTime()
//{
//    return this->pendingChargeTime;
//}
//
//const float LadyArcherMesh::AttackDelay()
//{
//    return this->attackDelay;
//}
//
//const float LadyArcherMesh::MaxChargeTime()
//{
//    return this->maxChargeTime;
//}
