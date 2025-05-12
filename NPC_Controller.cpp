#include "NPC_Controller.h"

Character& NPC_Controller::GetEntity()
{
    return this->npcEntity;
}

bool NPC_Controller::IsTressPassing(const vector<FloatRect>& forbiddenZones)
{
    FloatRect npcZone = this->npcMesh.Sprite().getGlobalBounds();
    for (const auto& zone : forbiddenZones)
    {
        if (npcZone.intersects(zone))
        {
            std::cout << "Tresspassing zone: " << zone.left << ", " << zone.top << ", "
                << zone.width << "x" << zone.height << std::endl;
            this->isTressPass = true;
            return true;
        }
    }

    this->isTressPass = false;
    return false;
}

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
            this->Death();

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

bool& NPC_Controller::IsDead()
{
    return this->npcEntity.IsDead();
}

Vector2f NPC_Controller::GetCenter()
{
    return this->npcMesh.GetCenter();
}

void NPC_Controller::Death()
{
    cout << "Object died in controller NPC" << endl;
    this->npcEntity.Death();
    this->npcMesh.IsDead() = true;
    cout << "Is npc mesh dead: " << npcMesh.IsDead() << endl;
}

void NPC_Controller::SpendEnergy(float value)
{
    this->npcEntity.SpendStamina(value);
}

void NPC_Controller::GainEnergy(float value)
{
    this->npcEntity.GainStamina(value);
}

float NPC_Controller::GetEnergyLimit()
{
    return this->npcEntity.GetStaminaLimit();
}

void NPC_Controller::SetEnergyLimit(float value)
{
    this->npcEntity.SetStaminaLimit(value);
}

float& NPC_Controller::GetChargeTime() const
{
    return this->npcMesh.ChargeTime();
}

bool& NPC_Controller::IsChargingAttack() const
{
    return this->npcMesh.IsChargingAttack();
}

void NPC_Controller::FreezeOnMidFrame()
{
    this->npcMesh.Animation().FreezeOnMidFrame();
}

bool& NPC_Controller::IsAttacking() const
{
    return this->npcMesh.IsAttacking();
}

bool NPC_Controller::AnimationIsFinished()
{
    return this->npcMesh.Animation().IsFinished();
}

bool& NPC_Controller::PendingNormalAttack()
{
    return this->npcMesh.PendingNormalAttack();
}

bool& NPC_Controller::PendingChargedAttack()
{
    return this->npcMesh.PendingChargedAttack();
}

void NPC_Controller::Update(float deltaTime, const sf::RenderWindow& window)
{
    RegenerateEnergy(this->npcEntity.GetStaminaRegainValue(), deltaTime);
    RegenerateHP(this->npcEntity.GetHPRegainValue(), deltaTime);

    this->npcMesh.Update(deltaTime, window,
        this->npcEntity.GetHealthPoints(), this->npcEntity.GetHPMaxLimit());
    //
    /*UpdateHealthBar(this->npcMesh.GetHealthSprite(), this->npcMesh.GetHealthTexture(),
        this->npcEntity.GetHealthPoints(), this->npcEntity.GetHPMaxLimit());*/
}

void NPC_Controller::UpdateHealthBar(sf::Sprite& barSprite, 
    const sf::Texture& barTexture, int currentHp, int maxHp)
{
    // Безпечне ділення
    float healthRatio = static_cast<float>(currentHp) / std::max(1, maxHp);

    // Розміри текстури
    int fullWidth = barTexture.getSize().x;
    int height = barTexture.getSize().y;

    // Гарантія що хоч 1 піксель буде намальовано
    int visibleWidth = std::max(1, static_cast<int>(fullWidth * healthRatio));
    Vector2f charPos = { this->npcMesh.GetPosition().x,this->npcMesh.GetPosition().y };
    // Встановлюємо текстуру (важливо: перед setTextureRect)
    barSprite.setTexture(barTexture,true);
    barSprite.setTextureRect(sf::IntRect(charPos.x, charPos.y, visibleWidth, height));
}