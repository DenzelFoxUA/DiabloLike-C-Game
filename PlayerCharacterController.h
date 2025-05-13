#pragma once
#include "PlayerCaracter.h"
#include "PlayerCharacterMesh.h"
#include "Arrow.h"
#include <type_traits>
#include <concepts>
#include <iostream>
#include "IController.h"
#include "ForbiddenZonesConfig.h"

using namespace std;



class PlayerController : public IController
{
protected:

	CharacterMesh* charActiveMesh;
	PlayerCharacter& characterEntity;

    bool isTressPass = false;

    float regainE_Timer = 1.2f;
    float regainE_Tik = 0.f;

    float regainMana_Timer = 2.f;
    float regainMana_Tik = 0.f;

    float regainHP_Timer = 2.f;
    float regainHP_Tik = 0.f;

    virtual void ChasingEnemy(Vector2f point, float deltaTime, bool& isMoving) = 0;
    //virtual float GetDistanceToTarget(Vector2f point) = 0;

    virtual void MoveUp(Vector2f& velocity);
    virtual void MoveDown(Vector2f& velocity);
    virtual void MoveLeft(Vector2f& velocity);
    virtual void MoveRight(Vector2f& velocity);

    virtual bool IsTressPassing(vector<FloatRect> forbiddenZones);

public:

	PlayerController(CharacterMesh*_meshCurrent, PlayerCharacter &_characterObj)
        :charActiveMesh(_meshCurrent), characterEntity(_characterObj)
	{

	}
    //entity methods
    virtual Character& GetEntity() override;
    virtual bool& IsDead() override;
    virtual void SubscribeOnEnemy(NPCEntity& enemy);
    virtual void UnsubscribeFromEnemy(Character& enemy);
    virtual void Death()override;
    void SpendEnergy(float value) override;
    void GainEnergy(float value) override;
    float GetEnergyLimit() override;
    void SetEnergyLimit(float value) override;

    virtual float GetEnergy() override {
        return this->characterEntity.GetStaminaPoints();
    }

    void RegenerateEnergy(float val, float deltaTime) override
    {
        regainE_Tik += deltaTime;

        if (this->characterEntity.GetStaminaPoints() < this->characterEntity.GetStaminaLimit() 
            && regainE_Timer <= regainE_Tik)
        {
            cout << "Gained " << val << " energy!" << endl;
            this->GainEnergy(val);
            regainE_Tik = 0.f;
        }

    }

    void RegenerateHP(float val, float deltaTime) override
    {
        regainHP_Tik += deltaTime;

        if (this->characterEntity.GetHealthPoints() < this->characterEntity.GetHPMaxLimit()
            && regainHP_Timer <= regainHP_Tik)
        {
            cout << "Gained " << val << " health!" << endl;
            this->characterEntity.Heal(val);
            regainHP_Tik = 0.f;
        }

    }

    void RegenerateMana(float val, float deltaTime) override
    {
        regainMana_Tik += deltaTime;

        if (this->characterEntity.GetManaPoints() < this->characterEntity.GetManaLimit()
            && regainMana_Timer <= regainMana_Tik)
        {
            cout << "Gained " << val << " health!" << endl;
            this->characterEntity.Heal(val);
            regainMana_Tik = 0.f;
        }

    }

    void SetEnergyRegainValue(float val) override
    {
        this->characterEntity.SetStaminaRegainValue(val);
    }

    void SetHPRegainValue(float val) override
    {
        this->characterEntity.SetHPRegainValue(val);
    }

    void HealBySource(float val) override
    {
        this->characterEntity.Heal(val);
    }

    //mesh methods
    virtual void Draw(RenderWindow& window) = 0;
    virtual void SetSpeed(float val) = 0;
    Vector2f GetCenter() override;
    float& GetChargeTime() const override;
    bool& IsChargingAttack() const override;
    void FreezeOnMidFrame() override;
    bool& IsAttacking() const override;
    bool AnimationIsFinished() override;
    bool& PendingNormalAttack() override;
    bool& PendingChargedAttack() override;

    void SetActiveMesh(CharacterMesh* activeMesh)
    {
        charActiveMesh = activeMesh;
    }

    virtual float GetDistanceToTarget(Vector2f point) override
    {
        Vector2f a = charActiveMesh->GetPosition();
        Vector2f b = point;
        return std::sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
    };

    Direction GetCurrentDirection() override
    {
        return this->charActiveMesh->CurrentDir();
    }
    Vector2f GetCurrentPosition() override 
    { 
        return  this->charActiveMesh->GetPosition();
    }


    //input and behavior
    virtual void HandleInput(float deltaTime) override;
    virtual void HandleBehavior(Vector2f target, Character& enemy, float deltaTime) = 0;

    //event/update
	virtual void HandleEvent(const Event& event, const RenderWindow& window) = 0;
    virtual void Update(float deltaTime, const RenderWindow& window) override;


    ~PlayerController()
    {
        cout << "Player controller destroyed!" << endl;
    }
};

