#include "LadyController.h"

Vector2f LadyController::Shot()
{
    this->mesh->IsChargingAttack() = false;
    return this->mesh->PendingDirection();
}

Vector2f LadyController::ShotCharged()
{
    this->mesh->Animation().SetFrameDuration(0.5f);
    this->mesh->IsChargingAttack() = true;
    return this->mesh->PendingDirection();
}

void LadyController::HandleInput(float deltaTime)
{
    PlayerController::HandleInput(deltaTime);
}

void LadyController::HandleMouseEvent(const sf::Event& event, const sf::RenderWindow& window, float deltaTime)
{
    bool& isAttacking = mesh->IsAttacking();
    bool& chargingShot = mesh->IsChargingAttack();
    float& attackTimer = mesh->AttackTimer();
    bool& pendingNormalShot = mesh->PendingNormalAttack();
    bool& pendingChargedShot = mesh->PendingChargedAttack();
    Vector2f& pendingDirection = mesh->PendingDirection();

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        if (!isAttacking&& this->entity.GetStaminaPoints()>=StaminaRequirements::ARROW_SIMPLE_SHOT) {
            isAttacking = true;
            chargingShot = true;
            attackTimer = 0.f;

            sf::Vector2f playerPos = mesh->GetCenter();
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            sf::Vector2f delta = mousePos - playerPos;

            mesh->CurrentState() = CharacterState::Attack;

            if (std::abs(delta.x) > std::abs(delta.y)) {
                if (delta.x > 0)
                    mesh->CurrentDir() = Direction::Right;
                else
                    mesh->CurrentDir() = Direction::Left;
            }
            else {
                if (delta.y > 0)
                    mesh->CurrentDir() = Direction::Down;
                else
                    mesh->CurrentDir() = Direction::Up;
            }

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
        else
        {
            cout << "Not enough stamina!" << endl;
        }
    }

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
    {
        if (!isAttacking && this->entity.GetStaminaPoints() >= StaminaRequirements::ARROW_CHARGED_SHOT) {
            isAttacking = true;
            chargingShot = true;
            pendingChargedShot = true;
            attackTimer = 0.f;

            sf::Vector2f playerPos = mesh->GetCenter();
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            sf::Vector2f delta = mousePos - playerPos;

            mesh->CurrentState() = CharacterState::Attack;

            if (std::abs(delta.x) > std::abs(delta.y)) {
                if (delta.x > 0)
                    mesh->CurrentDir() = Direction::Right;
                else
                    mesh->CurrentDir() = Direction::Left;
            }
            else {
                if (delta.y > 0)
                    mesh->CurrentDir() = Direction::Down;
                else
                    mesh->CurrentDir() = Direction::Up;
            }

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
        else
        {
            cout << "Not enough stamina!" << endl;
        }
    }

    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        sf::Vector2f direction = mousePos - mesh->GetCenter();
        pendingNormalShot = true;
        pendingChargedShot = false;
        pendingDirection = direction;
    }

    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right)
    {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        sf::Vector2f direction = mousePos - mesh->GetCenter();
        pendingNormalShot = false;
        pendingChargedShot = true;
        pendingDirection = direction;
    }
}

void LadyController::Update(float deltaTime, const sf::RenderWindow & window)
{  
    BaseCharacterController::Update(deltaTime,window);
    PlayerController::Update(deltaTime, window);
}

void LadyController::Draw(sf::RenderWindow& window)
{
    mesh->Draw(window);
}

void LadyController::HandleBehavior(sf::Vector2f target, Character& enemy, float deltaTime){}

Character& LadyController::GetEntity()
{
    return this->entity;
}
