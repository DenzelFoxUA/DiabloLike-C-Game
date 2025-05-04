#include "LadyArcherController.h"
#include <iostream>

void LadyArcherController::Shoot(sf::Texture& arrowTexture, sf::Vector2f direction)
{
    characterMesh->Shoot(arrowTexture, direction);
}

void LadyArcherController::ShootCharged(sf::Texture& texture, sf::Vector2f direction, float charge)
{
    characterMesh->ShootCharged(texture, direction, charge);
}

void LadyArcherController::HandleInput(float deltaTime)
{
    PlayerController<LadyArcherMesh, LadyArcher>::HandleInput(deltaTime);
    float& chargeTime = characterMesh->ChargeTime();
    bool& chargingShot = characterMesh->IsChargingAttack();
    if (chargingShot) {
        chargeTime += deltaTime;
        if (chargeTime > characterMesh->MaxChargeTime())
            chargeTime = characterMesh->MaxChargeTime();
    }
}

void LadyArcherController::HandleEvent(const sf::Event& event, const sf::RenderWindow& window)
{
    bool& isAttacking = characterMesh->IsAttacking();
    bool& shotAlreadyCharged = characterMesh->IsCharged();
    bool& chargingShot = characterMesh->IsChargingAttack();
    float& chargeTime = characterMesh->ChargeTime();
    float& attackTimer = characterMesh->AttackTimer();
    bool& pendingNormalShot = characterMesh->PendingNormalAttack();
    bool& pendingChargedShot = characterMesh->PendingChargedAttack();
    float& pendingChargeTime = characterMesh->PendingChargeTime();
    Vector2f& pendingDirection = characterMesh->PendingDirection();

    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left)
    {
        if (!isAttacking && !shotAlreadyCharged) {
            isAttacking = true;
            chargingShot = true;
            chargeTime = 0.f;
            shotAlreadyCharged = true;
            attackTimer = 0.f;

            characterMesh->CurrentState() = CharacterState::Attack;
            auto& dir = characterMesh->CurrentDir();

            int height = characterMesh->TextureData(TextureCategory::Attack).frameHeight;
            int width = characterMesh->TextureData(TextureCategory::Attack).frameWidth;
            int columns = characterMesh->TextureData(TextureCategory::Attack).numberOfColumns;
            int frames = characterMesh->TextureData(TextureCategory::Attack).numberOfFrames;

            characterMesh->Animation().SetSheet(&characterMesh->AttackTextures()[dir], width, height, columns, frames, false);
        }
    }

    if (event.type == sf::Event::MouseButtonReleased &&
        event.mouseButton.button == sf::Mouse::Left)
    {
        if (chargingShot) {
            chargingShot = false;
            shotAlreadyCharged = false;

            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            sf::Vector2f direction = mousePos - characterMesh->GetCenter();

            std::cout << "Mouse direction: (" << direction.x << ", " << direction.y << ")\n";

            if (chargeTime < 0.15f) {
                pendingNormalShot = true;
            }
            else {
                pendingChargedShot = true;
                pendingChargeTime = chargeTime;
            }

            pendingDirection = direction;
        }
    }

}


void LadyArcherController::Update(float deltaTime, const sf::RenderWindow& window)
{

    this->characterMesh->Update(deltaTime, window);

}
