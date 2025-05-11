#include "LadyArcherController.h"

Vector2f LadyArcherController::Shot()
{
    this->characterMesh.IsChargingAttack() = false;
    return this->characterMesh.PendingDirection();
}

Vector2f LadyArcherController::ShotCharged()
{
    this->characterMesh.IsChargingAttack() = true;
    return this->characterMesh.PendingDirection();
}

void LadyArcherController::HandleInput(float deltaTime)
{
    PlayerController::HandleInput(deltaTime);

    if (characterMesh.IsChargingAttack()) {
        float& chargeTime = characterMesh.ChargeTime();
        chargeTime += deltaTime;
        if (chargeTime > characterMesh.MaxChargeTime())
            chargeTime = characterMesh.MaxChargeTime();
    }
}

void LadyArcherController::HandleEvent(const sf::Event& event, const sf::RenderWindow& window)
{
    bool& isAttacking = characterMesh.IsAttacking();
    bool& shotAlreadyCharged = characterMesh.IsCharged();
    bool& chargingShot = characterMesh.IsChargingAttack();
    float& chargeTime = characterMesh.ChargeTime();
    float& attackTimer = characterMesh.AttackTimer();
    bool& pendingNormalShot = characterMesh.PendingNormalAttack();
    bool& pendingChargedShot = characterMesh.PendingChargedAttack();
    float& pendingChargeTime = characterMesh.PendingChargeTime();
    Vector2f& pendingDirection = characterMesh.PendingDirection();

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        if (!isAttacking) {
            isAttacking = true;
            chargingShot = true;
            chargeTime = 0.f;
            shotAlreadyCharged = false;
            attackTimer = 0.f;

            characterMesh.CurrentState() = CharacterState::Attack;
            auto& dir = characterMesh.CurrentDir();

            const auto& meta = characterMesh.TextureData(TextureCategory::Attack);

            characterMesh.Animation().SetSheet(
                &characterMesh.AttackTextures()[dir],
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
            sf::Vector2f direction = mousePos - characterMesh.GetCenter();

            if (chargeTime < 2.0f) {
                pendingNormalShot = true;
            }
            else {
                pendingChargedShot = true;
                pendingChargeTime = chargeTime;
            }

            pendingDirection = direction;
            characterMesh.Animation().Resume();
        }
    }
}

void LadyArcherController::Update(float deltaTime, const sf::RenderWindow& window)
{
    PlayerController::Update(deltaTime,window);
    //characterMesh.Update(deltaTime, window);
}

void LadyArcherController::Draw(sf::RenderWindow& window)
{
    characterMesh.Draw(window);
}

void LadyArcherController::HandleBehavior(sf::Vector2f target, Character& enemy, float deltaTime)
{
}

Character& LadyArcherController::GetEntity()
{
    return this->characterEntity;
}
