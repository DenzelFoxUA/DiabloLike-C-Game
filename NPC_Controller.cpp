#include "NPC_Controller.h"


void NPC_Controller::ChasingEnemy(Vector2f point, float deltaTime, bool& isMoving)
{
    auto direction = npcMesh.MoveToPoint(point - npcMesh.GetPosition());
    npcMesh.PendingDirection() = direction;

    isChasing = true;
    npcMesh.IsAttacking() = false;
    isMoving = true;
}

float NPC_Controller::GetDistanceToTarget(Vector2f point)
{
    Vector2f a = npcMesh.GetPosition();
    Vector2f b = point;
    return std::sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

void NPC_Controller::HandleBehavior(Vector2f target, Character& enemy, float deltaTime)
{
    bool& isMoving = npcMesh.IsMoving();
    Vector2f curPosition = npcMesh.GetPosition();
    float distance = GetDistanceToTarget(target);
    bool inAttackRange = distance <= 60;
    bool targetAlive = enemy.GetHealthPoints() > 0;

    if (this->npcEntity.GetHealthPoints() <= 0)
    {
        this->npcMesh.DeathAnimation_Timer() += deltaTime;

        if (npcMesh.DeathAnimation_Timer() >= npcMesh.DeathAnimationTimeLimit())
            this->npcEntity.Death();

        auto& curState = npcMesh.CurrentState();

        if (curState != CharacterState::Dead)
        {
            std::cout << npcEntity.GetName() << " is died!\n";

            curState = CharacterState::Dead;
            auto& curDir = npcMesh.CurrentDir();

            sf::Texture* newTexture = &npcMesh.DeathTextures()[curDir];

            const auto& meta = npcMesh.TextureData(TextureCategory::Death);

            npcMesh.Animation().SetSheet(
                newTexture,
                meta.frameWidth,
                meta.frameHeight,
                meta.numberOfColumns,
                meta.numberOfFrames,
                false);

            npcMesh.PreviousState() = curState;
            npcMesh.LastDir() = curDir;
        }
        else if (npcMesh.Animation().IsFinished())
        {
            npcMesh.Animation().Reset();
            auto& curDir = npcMesh.CurrentDir();
            sf::Texture* newTexture = &npcMesh.DeathTextures()[curDir];
            const auto& meta = npcMesh.TextureData(TextureCategory::Death);

            npcMesh.Animation().SetSheet(
                newTexture,
                meta.frameWidth,
                meta.frameHeight,
                meta.numberOfColumns,
                meta.numberOfFrames,
                false);
        }

        npcMesh.Animation().Update(deltaTime);
        return;
    }

    if (inAttackRange && targetAlive)
    {
        isChasing = false;
        isMoving = false;
        npcMesh.PendingDirection() = { 0.f, 0.f };

        if (npcMesh.CurrentState() == CharacterState::Attack &&
            npcMesh.Animation().IsFinished())
        {
            npcMesh.IsAttacking() = false;
            npcMesh.CurrentState() = CharacterState::Idle;
        }
        else if (attackTimer.getElapsedTime() < attackCooldown)
        {
            npcMesh.IsAttacking() = false;
        }
        else
        {
            npcMesh.IsAttacking() = true;
            npcMesh.CurrentState() = CharacterState::Attack;
            enemy.GetHit(100);
            std::cout << enemy.GetName() << " taking " << 100 << " damage!\n";
            std::cout << enemy.GetName() << " has " << enemy.GetHealthPoints() << " HP.\n";
            attackTimer.restart();
        }
    }
    else if (distance > 500 || !targetAlive)
    {
        npcMesh.IsAttacking() = false;
        isChasing = false;
        isMoving = false;
        npcMesh.CurrentState() = CharacterState::Idle;
        npcMesh.PendingDirection() = { 0.f, 0.f };
    }
    else
    {
        ChasingEnemy(target, deltaTime, isMoving);
        npcMesh.CurrentState() = CharacterState::Run;

        sf::Vector2f moveVector = npcMesh.PendingDirection() * npcMesh.GetSpeed() * deltaTime;
        sf::FloatRect bounds = npcMesh.Sprite().getGlobalBounds();
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
            npcMesh.CurrentState() = CharacterState::Idle;
            npcMesh.PendingDirection() = { 0.f, 0.f };
        }

        npcMesh.Sprite().move(finalMove);
    }

    auto& curDir = npcMesh.CurrentDir();
    if (std::abs(target.x - curPosition.x) > std::abs(target.y - curPosition.y))
        curDir = (target.x > curPosition.x) ? Direction::Right : Direction::Left;
    else
        curDir = (target.y > curPosition.y) ? Direction::Down : Direction::Up;

    auto& curState = npcMesh.CurrentState();
    auto& prevState = npcMesh.PreviousState();
    auto& lastDir = npcMesh.LastDir();

    if (curState != prevState || curDir != lastDir)
    {
        sf::Texture* newTexture =
            (curState == CharacterState::Run) ? &npcMesh.MoveTextures()[curDir] :
            (curState == CharacterState::Attack) ? &npcMesh.AttackTextures()[curDir] :
            &npcMesh.IdleTextures()[curDir];

        TextureCategory texCategory =
            (curState == CharacterState::Run) ? TextureCategory::Move :
            (curState == CharacterState::Attack) ? TextureCategory::Attack :
            TextureCategory::Idle;

        const auto& meta = npcMesh.TextureData(texCategory);
        bool shouldLoop = (curState != CharacterState::Attack);

        npcMesh.Animation().SetSheet(
            newTexture,
            meta.frameWidth,
            meta.frameHeight,
            meta.numberOfColumns,
            meta.numberOfFrames,
            shouldLoop);

        prevState = curState;
        lastDir = curDir;
    }

    npcMesh.Animation().Update(deltaTime);
}


