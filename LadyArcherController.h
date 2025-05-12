
#pragma once
#include "Arrow.h"
#include "ArrowMesh.h"
#include "PlayerCharacterController.h"
#include "LadyArcher.h"
#include "LadyArcherMesh.h"
#include "ProjectileObject.h"


class LadyArcherController : public PlayerController
{
protected:

    void ChasingEnemy(Vector2f point, float deltaTime, bool& isMoving) {}
    float GetDistanceToTarget(Vector2f point) { return this->GetDistanceToTarget(point); }

public:

    LadyArcherController(LadyArcherMesh& _mesh, LadyArcher& _entity)
        : PlayerController(_mesh, _entity)
    {
     
    }
    virtual Character& GetEntity() override;
    void HandleEvent(const sf::Event& event, const sf::RenderWindow& window) override;
    void HandleInput(float deltaTime) override;
    Vector2f Shot();
    Vector2f ShotCharged();
    
    void Update(float deltaTime, const sf::RenderWindow& window) override;
    void Draw(sf::RenderWindow& window) override;
    void HandleBehavior(sf::Vector2f target, Character& enemy, float deltaTime) override;
    

    void SetSpeed(float val) override
    {
        this->characterMesh.SetSpeed(val);
    }

};



