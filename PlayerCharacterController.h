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

	CharacterMesh& characterMesh;
	PlayerCharacter& characterEntity;
    bool isTressPass = false;

    virtual void ChasingEnemy(Vector2f point, float deltaTime, bool& isMoving) = 0;
    virtual float GetDistanceToTarget(Vector2f point) = 0;

    virtual void MoveUp(Vector2f& velocity);
    virtual void MoveDown(Vector2f& velocity);
    virtual void MoveLeft(Vector2f& velocity);
    virtual void MoveRight(Vector2f& velocity);

    virtual bool IsTressPassing(vector<FloatRect> forbiddenZones);

public:

	PlayerController(CharacterMesh&_mesh, PlayerCharacter &_characterObj)
        :characterMesh(_mesh), characterEntity(_characterObj)
	{

	}

    virtual void HandleInput(float deltaTime) override;
    virtual Character& GetEntity() override;
	virtual void HandleEvent(const Event& event, const RenderWindow& window) = 0;
    virtual void Update(float deltaTime, const RenderWindow& window) override;
    virtual void Draw(RenderWindow& window) = 0;
    virtual void SetSpeed(float val) = 0;
    virtual bool& IsDead() override;
    virtual void HandleBehavior(Vector2f target, Character& enemy, float deltaTime) = 0;
    virtual Vector2f GetCenter() override;

    virtual void SubscribeOnEnemy(NPCEntity& enemy);
    virtual void UnsubscribeFromEnemy(Character& enemy);
    virtual void Death()override;

    virtual void SpendEnergy(float value)
    {
        this->characterEntity.SpendEnergy(value);
    }
    virtual void GainEnergy(float value)
    {
        this->characterEntity.GainEnergy(value);
    }

    ~PlayerController()
    {
        cout << "Player controller destroyed!" << endl;
    }
};

