#include "PlayerCharacterController.h"

Character& PlayerController::GetEntity()
{
    return this->characterEntity;
}

void PlayerController::HandleInput(float deltaTime)
{
    sf::Vector2f velocity{ 0.f, 0.f };
    bool& isMoving = charActiveMesh->IsMoving();
    isMoving = false;

    if (this->characterEntity.GetHealthPoints() <= 0)
    {
        auto& curState = charActiveMesh->CurrentState();

        if (curState != CharacterState::Dead)
        {
            std::cout << characterEntity.GetName() << " is died!\n";

            curState = CharacterState::Dead;
            auto& curDir = charActiveMesh->CurrentDir();

            Texture* newTexture = &charActiveMesh->DeathTextures()[curDir];

            const auto& meta = charActiveMesh->TextureData(TextureCategory::Death);

            charActiveMesh->Animation().SetSheet(
                newTexture,
                meta.frameWidth,
                meta.frameHeight,
                meta.numberOfColumns,
                meta.numberOfFrames,
                false);

            charActiveMesh->PreviousState() = curState;
            charActiveMesh->LastDir() = curDir;
        }
        charActiveMesh->Animation().Update(deltaTime);
    }
    else
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
        {
            this->characterEntity.SetModeTwoActive(false);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
            this->characterEntity.SetModeTwoActive(true);

        sf::FloatRect playerBounds = charActiveMesh->Sprite().getGlobalBounds();
        sf::Vector2f proposedMove(0.f, 0.f);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            charActiveMesh->CurrentDir() = Direction::Up;
            proposedMove.y -= charActiveMesh->GetSpeed() * deltaTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            charActiveMesh->CurrentDir() = Direction::Down;
            proposedMove.y += charActiveMesh->GetSpeed() * deltaTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            charActiveMesh->CurrentDir() = Direction::Left;
            proposedMove.x -= charActiveMesh->GetSpeed() * deltaTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            charActiveMesh->CurrentDir() = Direction::Right;
            proposedMove.x += charActiveMesh->GetSpeed() * deltaTime;
        }

        // нормалізація діагонального руху
        if (proposedMove.x != 0 && proposedMove.y != 0)
            proposedMove /= std::sqrt(2.f);

        sf::Vector2f finalMove(0.f, 0.f);

        // Перевірка по осі X
        sf::FloatRect movedX = playerBounds;
        movedX.left += proposedMove.x;
        bool blockedX = false;
        for (const auto& zone : ForbiddenZones::GetForbiddenZones()) {
            if (movedX.intersects(zone)) {
                blockedX = true;
                break;
            }
        }
        if (!blockedX) finalMove.x = proposedMove.x;

        // Перевірка по осі Y
        sf::FloatRect movedY = playerBounds;
        movedY.top += proposedMove.y;
        bool blockedY = false;
        for (const auto& zone : ForbiddenZones::GetForbiddenZones()) {
            if (movedY.intersects(zone)) {
                blockedY = true;
                break;
            }
        }
        if (!blockedY) finalMove.y = proposedMove.y;

        if (finalMove != sf::Vector2f(0.f, 0.f)) {
            charActiveMesh->Sprite().move(finalMove);
            isMoving = true;
        }

        if (!charActiveMesh->IsAttacking() && !charActiveMesh->IsDead()) {
            charActiveMesh->CurrentState() = isMoving ? CharacterState::Run : CharacterState::Idle;
        }

        auto& curState = charActiveMesh->CurrentState();
        auto& prevState = charActiveMesh->PreviousState();
        auto& curDir = charActiveMesh->CurrentDir();
        auto& lastDir = charActiveMesh->LastDir();

        if (curState != prevState || curDir != lastDir)
        {
            sf::Texture* newTexture =
                (curState == CharacterState::Run) ? &charActiveMesh->MoveTextures()[curDir] :
                (curState == CharacterState::Attack) ? &charActiveMesh->AttackTextures()[curDir] :
                &charActiveMesh->IdleTextures()[curDir];

            int height = charActiveMesh->TextureData(TextureCategory::Idle).frameHeight;
            int width = charActiveMesh->TextureData(TextureCategory::Idle).frameWidth;
            int columns = charActiveMesh->TextureData(TextureCategory::Idle).numberOfColumns;
            int frames = charActiveMesh->TextureData(TextureCategory::Idle).numberOfFrames;

            charActiveMesh->Animation().SetSheet(newTexture, width, height, columns, frames, curState != CharacterState::Attack);

            charActiveMesh->PreviousState() = curState;
            charActiveMesh->LastDir() = curDir;
        }
    }
}

void PlayerController::MoveUp(Vector2f& velocity)
{
    velocity.y -= charActiveMesh->GetSpeed();
}

void PlayerController::MoveDown(Vector2f& velocity)
{
    velocity.y += charActiveMesh->GetSpeed();
}

void PlayerController::MoveLeft(Vector2f& velocity)
{
    velocity.x -= charActiveMesh->GetSpeed();
}

void PlayerController::MoveRight(Vector2f& velocity)
{
    velocity.x += charActiveMesh->GetSpeed();
}

bool PlayerController::IsTressPassing(vector<FloatRect> forbiddenZones)
{
    FloatRect playerZone = this->charActiveMesh->Sprite().getGlobalBounds();
    for (auto zone : forbiddenZones)
    {
        if (playerZone.intersects(zone))
        {
            cout << "Tresspassing zone:" << zone.height << "X" << zone.width << endl;
            this->isTressPass = true;
        }
        else
        {
            this->isTressPass = false;
        }
    }

    return isTressPass;
}

void PlayerController::Update(float deltaTime, const sf::RenderWindow& window)
{
    this->characterEntity.LevelUp();
    this->RegenerateHP(this->characterEntity.GetHPRegainValue(),deltaTime);
    this->RegenerateEnergy(this->characterEntity.GetStaminaRegainValue(), deltaTime);
    RegenerateMana(this->characterEntity.GetManaRegainValue(), deltaTime);

    if (!ForbiddenZones::GetForbiddenZones().empty())
        this->IsTressPassing(ForbiddenZones::GetForbiddenZones());

    this->charActiveMesh->Update(deltaTime, window,
        this->characterEntity.GetHealthPoints(), this->characterEntity.GetHPMaxLimit(),
        this->characterEntity.GetStaminaPoints(), this->characterEntity.GetStaminaLimit(),
        this->characterEntity.GetManaPoints(), this->characterEntity.GetManaLimit());
}

bool& PlayerController::IsDead()
{
    return this->characterEntity.IsDead();
}

void PlayerController::SubscribeOnEnemy(NPCEntity& enemy)
{
    //cout << "Subscribed in controller on " << enemy.GetName() << endl;
    this->characterEntity.SubscribeOnEnemy(enemy);
}

void PlayerController::UnsubscribeFromEnemy(Character& enemy)
{
    this->characterEntity.UnsubscribeFromEnemy(enemy);
}

void PlayerController::Death()
{
    this->characterEntity.Death();
}

Vector2f PlayerController::GetCenter()
{
    return this->charActiveMesh->GetCenter();
}


void PlayerController::SpendEnergy(float value)
{
    this->characterEntity.SpendStamina(value);
}

void PlayerController::GainEnergy(float value)
{
    this->characterEntity.GainStamina(value);
}

float PlayerController::GetEnergyLimit()
{
    return this->characterEntity.GetStaminaLimit();
}

void PlayerController::SetEnergyLimit(float value)
{
    this->characterEntity.SetStaminaLimit(value);
}

float& PlayerController::GetChargeTime() const
{
    return this->charActiveMesh->ChargeTime();
}

bool& PlayerController::IsChargingAttack() const
{
    return this->charActiveMesh->IsChargingAttack();
}
void PlayerController::FreezeOnMidFrame()
{
    charActiveMesh->Animation().FreezeOnMidFrame();
}
bool& PlayerController::IsAttacking() const
{
    return this->charActiveMesh->IsAttacking();
}

bool PlayerController::AnimationIsFinished()
{
    return this->charActiveMesh->Animation().IsFinished();
}

bool& PlayerController::PendingNormalAttack()
{
    return this->charActiveMesh->PendingNormalAttack();
}

bool& PlayerController::PendingChargedAttack()
{
    return this->charActiveMesh->PendingChargedAttack();
}