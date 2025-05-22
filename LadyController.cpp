#include "LadyController.h"

Vector2f LadyController::Shot()
{
    this->mesh->IsChargingAttack() = false;
    return this->mesh->PendingDirection();
}

Vector2f LadyController::ShotCharged()
{
    this->mesh->IsChargingAttack() = true;
    return this->mesh->PendingDirection();
}

void LadyController::HandleInput(float deltaTime)
{
    PlayerController::HandleInput(deltaTime);

    if (mesh->IsChargingAttack()) {
        float& chargeTime = mesh->ChargeTime();
        chargeTime += deltaTime;
        if (chargeTime > mesh->MaxChargeTime())
            chargeTime = mesh->MaxChargeTime();
    }
}

void LadyController::HandleEvent(const sf::Event& event, const sf::RenderWindow& window)
{
    bool& isAttacking = mesh->IsAttacking();
    bool& shotAlreadyCharged = mesh->IsCharged();
    bool& chargingShot = mesh->IsChargingAttack();
    float& chargeTime = mesh->ChargeTime();
    float& attackTimer = mesh->AttackTimer();
    bool& pendingNormalShot = mesh->PendingNormalAttack();
    bool& pendingChargedShot = mesh->PendingChargedAttack();
    float& pendingChargeTime = mesh->PendingChargeTime();
    Vector2f& pendingDirection = mesh->PendingDirection();

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        if (!isAttacking) {
            isAttacking = true;
            chargingShot = true;
            chargeTime = 0.f;
            shotAlreadyCharged = false;
            attackTimer = 0.f;

            mesh->CurrentState() = CharacterState::Attack;
            auto& dir = mesh->CurrentDir();

            const auto& meta = mesh->TextureData(TextureCategory::Attack);

            mesh->Animation().SetSheet(
                &mesh->AttackTextures()[dir],
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
            sf::Vector2f direction = mousePos - mesh->GetCenter();

            if (chargeTime < 2.0f) {
                pendingNormalShot = true;
            }
            else {
                pendingChargedShot = true;
                pendingChargeTime = chargeTime;
            }

            pendingDirection = direction;
            mesh->Animation().Resume();
        }
    }
}

void LadyController::Update(float deltaTime, const sf::RenderWindow& window)
{
    PlayerController::Update(deltaTime,window);
}

void LadyController::Draw(sf::RenderWindow& window)
{
    mesh->Draw(window);
}

void LadyController::HandleBehavior(sf::Vector2f target, Character& enemy, float deltaTime)
{
}

Character& LadyController::GetEntity()
{
    return this->entity;
}
