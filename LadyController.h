
#pragma once
#include "Arrow.h"
#include "ArrowMesh.h"
#include "PlayerCharacterController.h"
#include "LadyArcher.h"
#include "LadyArcherMesh.h"
#include "ProjectileObject.h"


class LadyController : public PlayerController
{
protected:

    void ChasingEnemy(Vector2f point, float deltaTime, bool& isMoving) override {}

public:

    LadyController(LadyArcherMesh* _meshCurrent, LadyArcher& _entity)
        : PlayerController(_meshCurrent, _entity){}

    virtual Character& GetEntity() override;
    void HandleMouseEvent(const sf::Event& event, const sf::RenderWindow& window, float deltaTime) override;
    void HandleInput(float deltaTime) override;
    Vector2f Shot();
    Vector2f ShotCharged();
   // void ChangeDirectionOnTarget(Vector2f mousePos) override;
    
    void Update(float deltaTime, const sf::RenderWindow& window) override;
    void Draw(sf::RenderWindow& window) override; //
    void HandleBehavior(sf::Vector2f target, Character& enemy, float deltaTime) override;//
    
    //void ChasingEnemy(Vector2f point, float deltaTime, bool& isMoving) override {}//

    void SetSpeed(float val) override //
    {
        this->mesh->SetSpeed(val);
    }

};



