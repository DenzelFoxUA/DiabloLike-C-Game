#include "PlayerCharacterController.h"

void PlayerController::HandleInput(float deltaTime)
{
    sf::Vector2f velocity{ 0.f, 0.f };
    bool& isMoving = mesh->IsMoving();
    isMoving = false;

    if (this->entity.GetHealthPoints() <= 0)
    {
        Death(deltaTime);
    }
    else
    {
        SwitchModes();
        MovementHandler(deltaTime, isMoving);
        UpdateStateAndDirection();
        
    }
}

void PlayerController::SwitchModes()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
    {
        this->entity.SetModeTwoActive(false);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
        this->entity.SetModeTwoActive(true);
}

void PlayerController::UpdateStateAndDirection()
{
    bool& isMoving = mesh->IsMoving();
    auto& curState = mesh->CurrentState();
    auto& prevState = mesh->PreviousState();
    auto& curDir = mesh->CurrentDir();
    auto& lastDir = mesh->LastDir();

    if (curState != prevState || curDir != lastDir)
    {
        sf::Texture* newTexture =
            (curState == CharacterState::Run) ? &mesh->MoveTextures()[curDir] :
            (curState == CharacterState::Attack) ? &mesh->AttackTextures()[curDir] :
            &mesh->IdleTextures()[curDir];

        int height = mesh->TextureData(TextureCategory::Idle).frameHeight;
        int width = mesh->TextureData(TextureCategory::Idle).frameWidth;
        int columns = mesh->TextureData(TextureCategory::Idle).numberOfColumns;
        int frames = mesh->TextureData(TextureCategory::Idle).numberOfFrames;

        mesh->Animation().SetSheet(newTexture, width, height, columns, frames, curState != CharacterState::Attack);

        mesh->PreviousState() = curState;
        mesh->LastDir() = curDir;
    }

    if (!mesh->IsAttacking() && !mesh->IsDead()) {
        mesh->CurrentState() = isMoving ? CharacterState::Run : CharacterState::Idle;
    }
}

void PlayerController::Update(float deltaTime, const sf::RenderWindow& window)
{
    this->entity.LevelUp();
    this->RegenerateHP(deltaTime);
    this->RegenerateEnergy(deltaTime);
    this->RegenerateMana(deltaTime);

    if (!ForbiddenZones::GetForbiddenZones().empty())
        this->IsTressPassing(ForbiddenZones::GetForbiddenZones());

    this->mesh->Update(deltaTime, window,
        this->entity.GetHealthPoints(), this->entity.GetHPMaxLimit(),
        this->entity.GetStaminaPoints(), this->entity.GetStaminaLimit(),
        this->entity.GetManaPoints(), this->entity.GetManaLimit());
}

void PlayerController::SubscribeOnEnemy(NPCEntity& enemy)
{
    this->entity.SubscribeOnEnemy(enemy);
}

void PlayerController::UnsubscribeFromEnemy(Character& enemy)
{
    this->entity.UnsubscribeFromEnemy(enemy);
}

void PlayerController::Death(float deltaTime)
{
    auto& curState = mesh->CurrentState();
    auto& curDir = mesh->CurrentDir();

    if (curState == CharacterState::Dead)
    {
        mesh->Animation().Update(deltaTime);
        return;
    }

    std::cout << entity.GetName() << " is died!\n";

    auto& deathTextures = mesh->DeathTextures();
    auto it = deathTextures.find(curDir);

    if (it == deathTextures.end())
    {
        std::cerr << "[ERROR] No death texture for direction " << static_cast<int>(curDir) << "!\n";
        return;
    }

    sf::Texture* newTexture = &it->second;

    const auto& meta = mesh->TextureData(TextureCategory::Death);
    if (meta.frameWidth == 0 || meta.frameHeight == 0 || meta.numberOfFrames == 0)
    {
        std::cerr << "[ERROR] Invalid TextureMeta for Death animation!\n";
        return;
    }

    curState = CharacterState::Dead;

    mesh->Animation().SetSheet(
        newTexture,
        meta.frameWidth,
        meta.frameHeight,
        meta.numberOfColumns,
        meta.numberOfFrames,
        false);

    mesh->PreviousState() = curState;
    mesh->LastDir() = curDir;
    
    mesh->Animation().Update(deltaTime);
    this->entity.Death();
}

void PlayerController::MoveToPoint(Vector2f point, float deltaTime, bool& isMoving)
{
    auto direction = mesh->MoveToPoint(point - mesh->GetPosition());
    mesh->PendingDirection() = direction;

    mesh->IsAttacking() = false;
    isMoving = true;

}

void PlayerController::MovementHandler(float deltaTime, bool& isMoving)
{
    sf::FloatRect playerBounds = mesh->Sprite().getGlobalBounds();
    sf::Vector2f proposedMove(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        mesh->CurrentDir() = Direction::Up;
        proposedMove.y -= mesh->GetSpeed() * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        mesh->CurrentDir() = Direction::Down;
        proposedMove.y += mesh->GetSpeed() * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        mesh->CurrentDir() = Direction::Left;
        proposedMove.x -= mesh->GetSpeed() * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        mesh->CurrentDir() = Direction::Right;
        proposedMove.x += mesh->GetSpeed() * deltaTime;
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
        mesh->Sprite().move(finalMove);
        isMoving = true;
    }
}

void PlayerController::SetActiveMesh(CharacterMesh* activeMesh)
{
    mesh = activeMesh;
}