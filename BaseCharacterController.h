#pragma once
#include "IController.h"

template <typename EntiT>
class BaseCharacterController : public IController
{
protected:

	CharacterMesh* mesh;
	EntiT& entity;

    Clock attackTimer;
    Time attackCooldown;

    bool isChasing,
        isTressPass = false;

    //default mesures
    float regainE_Timer = 1.2f;
    float regainE_Tik = 0.f;

    float regainMana_Timer = 2.f;
    float regainMana_Tik = 0.f;

    float regainHP_Timer = 2.f;
    float regainHP_Tik = 0.f;

    virtual void ChasingEnemy(Vector2f point, float deltaTime, bool& isMoving) = 0;
    virtual void UpdateStateAndDirection(Vector2f target) = 0;
    virtual void UpdateStateAndDirection() = 0;
    virtual void SwitchModes() = 0;

    virtual bool IsTressPassing(vector<FloatRect> forbiddenZones)
    {
        FloatRect meshZone = this->mesh->Sprite().getGlobalBounds();
        for (auto zone : forbiddenZones)
        {
            if (meshZone.intersects(zone))
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
public:

    BaseCharacterController(CharacterMesh* _mesh, EntiT& _npcObj)
        : mesh(_mesh), entity(_npcObj)
    {
        isChasing = false;
    }

    //mesh methods
    virtual void SetSpeed(float val) = 0;
    virtual void Draw(sf::RenderWindow& window) = 0;
    virtual void MoveToPoint(Vector2f point, float deltaTime, bool& isMoving) = 0;

    Vector2f GetCenter() override
    {
        return this->mesh->GetCenter();
    }

    Vector2f GetPosition() override
    {
        return this->mesh->GetPosition();
    }

    void FreezeOnMidFrame() override
    {
        mesh->Animation().FreezeOnMidFrame();
    }

    bool& IsAttacking() const override
    {
        return mesh->IsAttacking();
    }

    bool AnimationIsFinished() override
    {
        return this->mesh->Animation().IsFinished();
    }
    bool& PendingNormalAttack() override
    {
        return this->mesh->PendingNormalAttack();
    }
    bool& PendingChargedAttack() override
    {
        return this->mesh->PendingChargedAttack();
    }

    virtual float GetDistanceToTarget(Vector2f point) override
    {
        Vector2f a = mesh->GetPosition();
        Vector2f b = point;
        return std::sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
    }

    void ChangeDirectionOnTarget(Vector2f target) override
    {
        sf::Vector2f playerPos = mesh->GetCenter();
        sf::Vector2f delta = target - playerPos;

        float angle = std::atan2(delta.x, -delta.y) * 180.f / 3.14159265f;
        if (angle < 0.f) angle += 360.f;

        if (angle >= 337.5 || angle < 22.5)
            mesh->CurrentDir() = Direction::Up;
        else if (angle >= 22.5 && angle < 67.5)
            mesh->CurrentDir() = Direction::UpRight;
        else if (angle >= 67.5 && angle < 112.5)
            mesh->CurrentDir() = Direction::Right;
        else if (angle >= 112.5 && angle < 157.5)
            mesh->CurrentDir() = Direction::RightDown;
        else if (angle >= 157.5 && angle < 202.5)
            mesh->CurrentDir() = Direction::Down;
        else if (angle >= 202.5 && angle < 247.5)
            mesh->CurrentDir() = Direction::LeftDown;
        else if (angle >= 247.5 && angle < 292.5)
            mesh->CurrentDir() = Direction::Left;
        else if (angle >= 292.5 && angle < 337.5)
            mesh->CurrentDir() = Direction::UpLeft;

        mesh->LastDir() = mesh->CurrentDir();
    }

    virtual Direction GetCurrentDirection() override 
    { 
        return this->mesh->CurrentDir();
    }
    virtual Vector2f GetCurrentPosition() override 
    { 
        return this->mesh->GetPosition(); 
    }

    bool& IsMoving() override
    {
        return this->mesh->IsMoving();
    }

    void SetDeathAnimationTime(float val) override
    {
        if(val > 0)
            this->mesh->DeathAnimationTimeLimit() = val;
    }

    void SetAnimationDuration(float newVal)  override
    {
        this->mesh->SetAnimationDuration(newVal);
    }

    virtual void SetAttackDelay(float time)
    {
        if (time <= 0.4f)
        {
            cerr << "Time value of attack delay is to small" << endl;
            this->mesh->SetAttackDelay(1.f);
            return;
        }
        else if (time > 10.f)
        {
            cerr << "Time value of attack delay is to large" << endl;
            this->mesh->SetAttackDelay(1.f);
            return;
        }
        else
            this->mesh->SetAttackDelay(time);
            
    }

    FloatRect GetMeshBounds() override
    {
        return this->mesh->GetBounds();
    }

    Direction GetDirectionFromVector(sf::Vector2f dir) {
        if (dir.x == 0.f && dir.y < 0.f) return Direction::Up;
        if (dir.x == 0.f && dir.y > 0.f) return Direction::Down;
        if (dir.x < 0.f && dir.y == 0.f) return Direction::Left;
        if (dir.x > 0.f && dir.y == 0.f) return Direction::Right;

        if (dir.x > 0.f && dir.y < 0.f) return Direction::UpRight;
        if (dir.x > 0.f && dir.y > 0.f) return Direction::RightDown;
        if (dir.x < 0.f && dir.y < 0.f) return Direction::UpLeft;
        if (dir.x < 0.f && dir.y > 0.f) return Direction::LeftDown;

        return this->mesh->LastDir();
    }

    //entity methods


    virtual void Death(float deltaTime) = 0;

    void SpendEnergy(float value) override
    {
        if(value >= 0)
            this->entity.SpendStamina(value);
    }
    void GainEnergy(float value) override
    {
        if(value > 0)
            this->entity.GainStamina(value);
    }
    float GetEnergyLimit() override
    {
        return this->entity.GetStaminaLimit();
    }
    void SetEnergyLimit(float value) override
    {
        if (value >= 0)
        this->entity.SetStaminaLimit(value);
    }

    CharacterAttributes& GetAttributes() const {
        return this->entity.GetAttributes();
    }

    virtual float GetEnergy() override {
        return this->entity.GetStaminaPoints();
    }

    virtual Character& GetEntity() override
    {
        return this->entity;
    }

    virtual bool& IsDead()
    {
        return this->entity.IsDead();
    }

    void RegenerateEnergy(float deltaTime) override
    {
        regainE_Tik += deltaTime;

        if (this->entity.GetStaminaPoints() < this->entity.GetStaminaLimit()
            && regainE_Timer <= regainE_Tik)
        {
            cout << "Gained " << this->entity.GetStaminaRegainValue() << " energy!" << endl;
            this->GainEnergy(this->entity.GetStaminaRegainValue());
            regainE_Tik = 0.f;
        }

    }

    void RegenerateHP(float deltaTime) override
    {
        regainHP_Tik += deltaTime;

        if (this->entity.GetHealthPoints() < this->entity.GetHPMaxLimit()
            && regainHP_Timer <= regainHP_Tik)
        {
            cout << "Gained " << this->entity.GetHPRegainValue() << " health!" << endl;
            this->entity.Heal(this->entity.GetHPRegainValue());
            regainHP_Tik = 0.f;
        }

    }

    void RegenerateMana(float deltaTime) override
    {
        regainMana_Tik += deltaTime;

        if (this->entity.GetManaPoints() < this->entity.GetManaLimit()
            && regainMana_Timer <= regainMana_Tik)
        {
            cout << "Gained " << this->entity.GetManaRegainValue() << " health!" << endl;
            this->entity.Heal(this->entity.GetManaRegainValue());
            regainMana_Tik = 0.f;
        }

    }

    void SetEnergyRegainValue(float val) override
    {
        if (val >= 0)
        this->entity.SetStaminaRegainValue(val);
    }

    void SetManaRegainValue(float val) override
    {
        if (val >= 0)
            this->entity.SetManaRegainValue(val);
    }

    void SetHPRegainValue(float val) override
    {
        if (val >= 0)
        this->entity.SetHPRegainValue(val);
    }

    void HealBySource(float val) override
    {
        if (val > 0)
        this->entity.Heal(val);
    }

    //combat calcs
    float CaltulateShootSpeed(bool isCharged) override
    {
        float multiplyer = isCharged ? 2.f : 1.f;

        return this->entity.GetAttributes().strength * ProjectileSpeed::ARROW_SIMPLE * multiplyer;
    }

    float CalculateShootDamage(bool isCharged, ProjectileType type) override
    {
        float multiplyer = isCharged ? 2.f : 1.f;

        float basicDamage = type == ProjectileType::ArrowSimple ? Damage::BOW_ARROW :
            ProjectileType::ArrowMagic ? Damage::BOW_CHARGED : 0;

        return this->entity.GetAttributes().agility * basicDamage * multiplyer;
    }

    float CalculateHitRadius(bool isCharged, ProjectileType type) override
    {
        float multiplyer = isCharged ? 2.f : 1.f;

        float basicRadius = type == ProjectileType::ArrowSimple ? ProjectileHitRadius::ARROW_SIMPLE :
            ProjectileType::ArrowMagic ? ProjectileHitRadius::ARROW_CHARGED : 0;

        return this->entity.GetAttributes().agility * multiplyer + basicRadius;
    }

    float CaltculateMeleeDamage(bool isPowered) override
    {
        float dmg = this->entity.GetAttributes().strength * Damage::MELEE_ATTACK;
        return dmg;
    }

    //update
    virtual void Update(float deltaTime, const sf::RenderWindow& window)
    {
        if (PendingChargedAttack())
        {
            this->mesh->SetAttackDelay(2.f);
        }
            
        if (PendingNormalAttack())
            this->mesh->SetAttackDelay(1.f);
    }
    //event
    virtual void HandleMouseEvent(const Event& event, const RenderWindow& window, float deltaTime) = 0;
    
    //input and behavior
    virtual void HandleInput(float deltaTime) = 0;
    virtual void HandleBehavior(Vector2f target, Character& enemy, float deltaTime) = 0;
};