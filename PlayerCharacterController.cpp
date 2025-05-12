#include "PlayerCharacterController.h"

Character& PlayerController::GetEntity()
{
    return this->characterEntity;
}

void PlayerController::HandleInput(float deltaTime)
{
    sf::Vector2f velocity{ 0.f, 0.f };
    bool& isMoving = characterMesh.IsMoving();
    isMoving = false;

    if (this->characterEntity.GetHealthPoints() <= 0)
    {
        auto& curState = characterMesh.CurrentState();

        if (curState != CharacterState::Dead)
        {
            std::cout << characterEntity.GetName() << " is died!\n";

            curState = CharacterState::Dead;
            auto& curDir = characterMesh.CurrentDir();

            Texture* newTexture = &characterMesh.DeathTextures()[curDir];

            const auto& meta = characterMesh.TextureData(TextureCategory::Death);

            characterMesh.Animation().SetSheet(
                newTexture,
                meta.frameWidth,
                meta.frameHeight,
                meta.numberOfColumns,
                meta.numberOfFrames,
                false);

            characterMesh.PreviousState() = curState;
            characterMesh.LastDir() = curDir;
        }
        characterMesh.Animation().Update(deltaTime);
    }
    else
    {
        sf::FloatRect playerBounds = characterMesh.Sprite().getGlobalBounds();
        sf::Vector2f proposedMove(0.f, 0.f);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            characterMesh.CurrentDir() = Direction::Up;
            proposedMove.y -= characterMesh.GetSpeed() * deltaTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            characterMesh.CurrentDir() = Direction::Down;
            proposedMove.y += characterMesh.GetSpeed() * deltaTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            characterMesh.CurrentDir() = Direction::Left;
            proposedMove.x -= characterMesh.GetSpeed() * deltaTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            characterMesh.CurrentDir() = Direction::Right;
            proposedMove.x += characterMesh.GetSpeed() * deltaTime;
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
            characterMesh.Sprite().move(finalMove);
            isMoving = true;
        }

        if (!characterMesh.IsAttacking() && !characterMesh.IsDead()) {
            characterMesh.CurrentState() = isMoving ? CharacterState::Run : CharacterState::Idle;
        }

        auto& curState = characterMesh.CurrentState();
        auto& prevState = characterMesh.PreviousState();
        auto& curDir = characterMesh.CurrentDir();
        auto& lastDir = characterMesh.LastDir();

        if (curState != prevState || curDir != lastDir)
        {
            sf::Texture* newTexture =
                (curState == CharacterState::Run) ? &characterMesh.MoveTextures()[curDir] :
                (curState == CharacterState::Attack) ? &characterMesh.AttackTextures()[curDir] :
                &characterMesh.IdleTextures()[curDir];

            int height = characterMesh.TextureData(TextureCategory::Idle).frameHeight;
            int width = characterMesh.TextureData(TextureCategory::Idle).frameWidth;
            int columns = characterMesh.TextureData(TextureCategory::Idle).numberOfColumns;
            int frames = characterMesh.TextureData(TextureCategory::Idle).numberOfFrames;

            characterMesh.Animation().SetSheet(newTexture, width, height, columns, frames, curState != CharacterState::Attack);

            characterMesh.PreviousState() = curState;
            characterMesh.LastDir() = curDir;
        }
    }
}

void PlayerController::MoveUp(Vector2f& velocity)
{
    velocity.y -= characterMesh.GetSpeed();
}

void PlayerController::MoveDown(Vector2f& velocity)
{
    velocity.y += characterMesh.GetSpeed();
}

void PlayerController::MoveLeft(Vector2f& velocity)
{
    velocity.x -= characterMesh.GetSpeed();
}

void PlayerController::MoveRight(Vector2f& velocity)
{
    velocity.x += characterMesh.GetSpeed();
}

bool PlayerController::IsTressPassing(vector<FloatRect> forbiddenZones)
{
    FloatRect playerZone = this->characterMesh.Sprite().getGlobalBounds();
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
    this->RegenerateEnergy(this->characterEntity.GetEnergyRegainValue(), deltaTime);

    if (!ForbiddenZones::GetForbiddenZones().empty())
        this->IsTressPassing(ForbiddenZones::GetForbiddenZones());

    characterMesh.Update(deltaTime, window);
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
    return this->characterMesh.GetCenter();
}


void PlayerController::SpendEnergy(float value)
{
    this->characterEntity.SpendEnergy(value);
}

void PlayerController::GainEnergy(float value)
{
    this->characterEntity.GainEnergy(value);
}

float PlayerController::GetEnergyLimit()
{
    return this->characterEntity.GetEnergyLimit();
}

void PlayerController::SetEnergyLimit(float value)
{
    this->characterEntity.SetEnergyLimit(value);
}

float& PlayerController::GetChargeTime() const
{
    return this->characterMesh.ChargeTime();
}

bool& PlayerController::IsChargingAttack() const
{
    return this->characterMesh.IsChargingAttack();
}
void PlayerController::FreezeOnMidFrame()
{
    this->characterMesh.Animation().FreezeOnMidFrame();
}
bool& PlayerController::IsAttacking() const
{
    return this->characterMesh.IsAttacking();
}

bool PlayerController::AnimationIsFinished()
{
    return this->characterMesh.Animation().IsFinished();
}

bool& PlayerController::PendingNormalAttack()
{
    return this->characterMesh.PendingNormalAttack();
}

bool& PlayerController::PendingChargedAttack()
{
    return this->characterMesh.PendingChargedAttack();
}