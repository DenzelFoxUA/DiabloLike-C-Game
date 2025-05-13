#include "LadyController.h"

Vector2f LadyController::Shot()
{
    this->charActiveMesh->IsChargingAttack() = false;
    return this->charActiveMesh->PendingDirection();
}

Vector2f LadyController::ShotCharged()
{
    this->charActiveMesh->IsChargingAttack() = true;
    return this->charActiveMesh->PendingDirection();
}

void LadyController::HandleInput(float deltaTime)
{
    PlayerController::HandleInput(deltaTime);

    if (charActiveMesh->IsChargingAttack()) {
        float& chargeTime = charActiveMesh->ChargeTime();
        chargeTime += deltaTime;
        if (chargeTime > charActiveMesh->MaxChargeTime())
            chargeTime = charActiveMesh->MaxChargeTime();
    }
}

void LadyController::HandleEvent(const sf::Event& event, const sf::RenderWindow& window)
{
    bool& isAttacking = charActiveMesh->IsAttacking();
    bool& shotAlreadyCharged = charActiveMesh->IsCharged();
    bool& chargingShot = charActiveMesh->IsChargingAttack();
    float& chargeTime = charActiveMesh->ChargeTime();
    float& attackTimer = charActiveMesh->AttackTimer();
    bool& pendingNormalShot = charActiveMesh->PendingNormalAttack();
    bool& pendingChargedShot = charActiveMesh->PendingChargedAttack();
    float& pendingChargeTime = charActiveMesh->PendingChargeTime();
    Vector2f& pendingDirection = charActiveMesh->PendingDirection();

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        if (!isAttacking) {
            isAttacking = true;
            chargingShot = true;
            chargeTime = 0.f;
            shotAlreadyCharged = false;
            attackTimer = 0.f;

            charActiveMesh->CurrentState() = CharacterState::Attack;
            auto& dir = charActiveMesh->CurrentDir();

            const auto& meta = charActiveMesh->TextureData(TextureCategory::Attack);

            charActiveMesh->Animation().SetSheet(
                &charActiveMesh->AttackTextures()[dir],
                meta.frameWidth,
                meta.frameHeight,
                meta.numberOfColumns,
                meta.numberOfFrames,
                false);
        }
    }

    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
    {
        if (chargingShot) {
            chargingShot = false;
            shotAlreadyCharged = false;

            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            sf::Vector2f direction = mousePos - charActiveMesh->GetCenter();

            if (chargeTime < 2.0f) {
                pendingNormalShot = true;
            }
            else {
                pendingChargedShot = true;
                pendingChargeTime = chargeTime;
            }

            pendingDirection = direction;
            charActiveMesh->Animation().Resume();
        }
    }
}

void LadyController::Update(float deltaTime, const sf::RenderWindow& window)
{
    PlayerController::Update(deltaTime,window);
    //characterMesh.Update(deltaTime, window);
}

void LadyController::Draw(sf::RenderWindow& window)
{
    charActiveMesh->Draw(window);
}

void LadyController::HandleBehavior(sf::Vector2f target, Character& enemy, float deltaTime)
{
}

Character& LadyController::GetEntity()
{
    return this->characterEntity;
}
