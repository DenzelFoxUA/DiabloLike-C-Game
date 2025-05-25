#pragma once
#include "PlayerCaracter.h"
#include "PlayerCharacterMesh.h"
#include "Arrow.h"
#include <type_traits>
#include <concepts>
#include <iostream>
#include "BaseCharacterController.h"
#include "ForbiddenZonesConfig.h"

using namespace std;

class PlayerController : public BaseCharacterController<PlayerCharacter>
{
protected:

    virtual void ChasingEnemy(Vector2f point, float deltaTime, bool& isMoving) {};

    virtual void UpdateStateAndDirection(Vector2f target) override {};
    virtual void UpdateStateAndDirection();
    virtual void SwitchModes();

public:

    PlayerController(CharacterMesh* _meshCurrent, PlayerCharacter& _characterObj)
        : BaseCharacterController<PlayerCharacter>(_meshCurrent, _characterObj) {

    };

    //entity methods
    virtual void SubscribeOnEnemy(NPCEntity& enemy);
    virtual void UnsubscribeFromEnemy(Character& enemy);

    //mesh methods
    virtual void Draw(RenderWindow& window) = 0;
    virtual void SetSpeed(float val) = 0;

    //input and behavior
    virtual void HandleInput(float deltaTime) override;
    void MoveToPoint(Vector2f point, float deltaTime, bool& isMoving) override;
    virtual void MovementHandler(float deltaTime, bool& isMoving);
    void SetActiveMesh(CharacterMesh* activeMesh);
    void HandleMouseEvent(const sf::Event& event, const sf::RenderWindow& window, float deltaTime) override{}
    /*void ChangeDirectionOnTarget(Vector2f target) override {}*/
    //event/update
    virtual void Update(float deltaTime, const RenderWindow& window) override;
    virtual void Death(float deltaTime)override;

    ~PlayerController()
    {
        cout << "Player controller destroyed!" << endl;
    }
};

