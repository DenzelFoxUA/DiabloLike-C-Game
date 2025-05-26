#include "NPC_Controller.h"

void NPC_Controller::MoveToPoint(Vector2f point, float deltaTime, bool& isMoving)
{
    //задати напрям
    auto direction = mesh->MoveToPoint(point - mesh->GetPosition());
    mesh->PendingDirection() = direction;
    
    //оновити статус
    isChasing = true;
    mesh->IsAttacking() = false;
    isMoving = true;
    mesh->CurrentState() = CharacterState::Run;

    //рух
    sf::Vector2f moveVector = mesh->PendingDirection() * mesh->GetSpeed() * deltaTime;
    sf::FloatRect bounds = mesh->Sprite().getGlobalBounds();
    sf::Vector2f finalMove(0.f, 0.f);

    sf::FloatRect movedX = bounds;
    movedX.left += moveVector.x;
    bool blockedX = false;
    for (const auto& zone : ForbiddenZones::GetForbiddenZones()) {
        if (movedX.intersects(zone)) {
            blockedX = true;
            break;
        }
    }
    if (!blockedX) finalMove.x = moveVector.x;

    sf::FloatRect movedY = bounds;
    movedY.top += moveVector.y;
    bool blockedY = false;
    for (const auto& zone : ForbiddenZones::GetForbiddenZones()) {
        if (movedY.intersects(zone)) {
            blockedY = true;
            break;
        }
    }
    if (!blockedY) finalMove.y = moveVector.y;

    if (finalMove == sf::Vector2f(0.f, 0.f)) {
        isMoving = false;
        mesh->CurrentState() = CharacterState::Idle;
        mesh->PendingDirection() = { 0.f, 0.f };
    }

    mesh->Sprite().move(finalMove);
}

void NPC_Controller::ChasingEnemy(Vector2f point, float deltaTime, bool& isMoving)
{
    auto direction = mesh->MoveToPoint(point - mesh->GetPosition());
    mesh->PendingDirection() = direction;

    isChasing = true;
    mesh->IsAttacking() = false;
    isMoving = true;
}

void NPC_Controller::HandleBehavior(Vector2f target, Character& enemy, float deltaTime)
{
    bool& isMoving = mesh->IsMoving();
    Vector2f curPosition = mesh->GetPosition();

    float distance = GetDistanceToTarget(target);
    bool inAttackRange = distance <= Range::MELEE_ATTACK;
    bool targetAlive = enemy.GetHealthPoints() > 0;

    if (this->entity.GetHealthPoints() <= 0)
    {
        this->Death(deltaTime);
        return;
    }

    if (inAttackRange && targetAlive)
    {
        isChasing = false;
        isMoving = false;
        mesh->PendingDirection() = { 0.f, 0.f };

        if (mesh->CurrentState() == CharacterState::Attack &&
            mesh->Animation().IsFinished())
        {
            mesh->IsAttacking() = false;
            mesh->CurrentState() = CharacterState::Idle;
        }
        else if (attackTimer.getElapsedTime() < attackCooldown)
        {
            mesh->IsAttacking() = false;
        }
        else
        {
            mesh->IsAttacking() = true;
            mesh->CurrentState() = CharacterState::Attack;
            attackTimer.restart();
        }
    }
    else if (distance > this->entity.GetDetectRadius() || !targetAlive)
    {
        //idle behavior
        IdleBehavior();
    }
    else
    {
        MoveToPoint(target, deltaTime, isMoving); 
    }

    if (!mesh->IsDead())
        UpdateStateAndDirection(target);

    mesh->Animation().Update(deltaTime);
}

void NPC_Controller::IdleBehavior()
{
    mesh->IsAttacking() = false;
    isChasing = false;
    mesh->IsMoving() = false;
    mesh->CurrentState() = CharacterState::Idle;
    mesh->PendingDirection() = { 0.f, 0.f };
}

void NPC_Controller::ChangeDirectionOnTarget(Vector2f target)
{
    float distance = GetDistanceToTarget(target);
    auto curPosition = mesh->GetPosition();

    if (distance < 100.f)
    {
        if (abs(target.x - curPosition.x) > abs(target.y - curPosition.y))
        mesh->CurrentDir() = (target.x > curPosition.x) ? Direction::Right : Direction::Left;
            else
        mesh->CurrentDir() = (target.y > curPosition.y) ? Direction::Down : Direction::Up;
    }
    else
    {
        sf::Vector2f delta = target - mesh->GetCenter();

        float angle = std::atan2(delta.x, -delta.y) * 180.f / 3.14159265f;
        if (angle < 0.f) angle += 360.f;

        if (angle >= 337.5f || angle < 22.5f)
            mesh->CurrentDir() = Direction::Up;
        else if (angle >= 22.5f && angle < 67.5f)
            mesh->CurrentDir() = Direction::UpRight;
        else if (angle >= 67.5f && angle < 112.5f)
            mesh->CurrentDir() = Direction::Right;
        else if (angle >= 112.5f && angle < 157.5f)
            mesh->CurrentDir() = Direction::RightDown;
        else if (angle >= 157.5f && angle < 202.5f)
            mesh->CurrentDir() = Direction::Down;
        else if (angle >= 202.5f && angle < 247.5f)
            mesh->CurrentDir() = Direction::LeftDown;
        else if (angle >= 247.5f && angle < 292.5f)
            mesh->CurrentDir() = Direction::Left;
        else if (angle >= 292.5f && angle < 337.5f)
            mesh->CurrentDir() = Direction::UpLeft;
    }
}

void NPC_Controller::UpdateStateAndDirection(Vector2f target)
{
    auto curPosition = mesh->GetPosition();
    auto& curState = mesh->CurrentState();
    auto& prevState = mesh->PreviousState();

    this->ChangeDirectionOnTarget(target);

    if (curState != prevState || mesh->CurrentDir() != mesh->LastDir())
    {
        sf::Texture* newTexture =
            (curState == CharacterState::Run) ? &mesh->MoveTextures()[mesh->CurrentDir()] :
            (curState == CharacterState::Attack) ? &mesh->AttackTextures()[mesh->CurrentDir()] :
            &mesh->IdleTextures()[mesh->CurrentDir()];

        TextureCategory texCategory =
            (curState == CharacterState::Run) ? TextureCategory::Move :
            (curState == CharacterState::Attack) ? TextureCategory::Attack :
            TextureCategory::Idle;

        const auto& meta = mesh->TextureData(texCategory);
        bool shouldLoop = (curState != CharacterState::Attack);

        mesh->Animation().SetSheet(
            newTexture,
            meta.frameWidth,
            meta.frameHeight,
            meta.numberOfColumns,
            meta.numberOfFrames,
            shouldLoop);

        prevState = curState;
        mesh->LastDir() = mesh->CurrentDir();
    }
}

void NPC_Controller::Death(float deltaTime)
{
    mesh->DeathAnimation_Timer() += deltaTime;

    if (mesh->DeathAnimation_Timer() >= mesh->DeathAnimationTimeLimit())
    {
        this->entity.Death();
        mesh->IsDead() = true;
        std::cout << "Is npc mesh dead: " << mesh->IsDead() << std::endl;
    }

    auto& curState = mesh->CurrentState();

    if (curState != CharacterState::Dead)
    {
        std::cout << entity.GetName() << " is died!\n";

        curState = CharacterState::Dead;
        auto& curDir = mesh->CurrentDir();

        sf::Texture* newTexture = &mesh->DeathTextures()[curDir];
        const auto& meta = mesh->TextureData(TextureCategory::Death);

        mesh->Animation().SetSheet(
            newTexture,
            meta.frameWidth,
            meta.frameHeight,
            meta.numberOfColumns,
            meta.numberOfFrames,
            false);

        mesh->PreviousState() = curState;
        mesh->LastDir() = curDir;
    }

    mesh->Animation().Update(deltaTime);
}


void NPC_Controller::Update(float deltaTime, const sf::RenderWindow& window)
{
    RegenerateEnergy(deltaTime);
    RegenerateHP(deltaTime);

    mesh->Update(deltaTime, window,
        this->entity.GetHealthPoints(), this->entity.GetHPMaxLimit());
}

void NPC_Controller::UpdateHealthBar(sf::Sprite& barSprite, 
    const sf::Texture& barTexture, int currentHp, int maxHp)
{
    float healthRatio = static_cast<float>(currentHp) / std::max(1, maxHp);

    int fullWidth = barTexture.getSize().x;
    int height = barTexture.getSize().y;

    
    int visibleWidth = std::max(1, static_cast<int>(fullWidth * healthRatio));
    Vector2f charPos = { mesh->GetPosition().x,mesh->GetPosition().y };

    barSprite.setTexture(barTexture,true);
    barSprite.setTextureRect(sf::IntRect(charPos.x, charPos.y, visibleWidth, height));
}

void NPC_Controller::SetSpeed(float val)
{
    this->mesh->SetSpeed(val);
};