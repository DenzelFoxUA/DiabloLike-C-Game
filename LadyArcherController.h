
#pragma once
#include "Arrow.h"
#include "ArrowMesh.h"
#include "PlayerCharacterController.h"
#include "LadyArcher.h"
#include "LadyArcherMesh.h"
//#include "ArrowController.h"
#include "ProjectileObject.h"


class LadyArcherController : public PlayerController
{
protected:
    //vector<ArrowController> arrowControllers;
    /*vector<unique_ptr<ArrowController>> arrowControllers;
    Arrow equipedArrow;*/

    void ChasingEnemy(Vector2f point, float deltaTime, bool& isMoving) {}
    float GetDistanceToTarget(Vector2f point) { return this->GetDistanceToTarget(point); }

public:

    LadyArcherController(LadyArcherMesh& _mesh, LadyArcher& _entity)
        : PlayerController(_mesh, _entity)//, equipedArrow(arrow)
    {
     
    }
    virtual Character& GetEntity() override;
    void HandleEvent(const sf::Event& event, const sf::RenderWindow& window) override;
    void HandleInput(float deltaTime) override;
    Vector2f Shot();
    Vector2f ShotCharged();
    //void ShootCharged(sf::Texture& texture, sf::Vector2f direction, float charge);
    void Update(float deltaTime, const sf::RenderWindow& window/*, CharacterMesh& targetMesh, Character& target*/) override;
    void Draw(sf::RenderWindow& window) override;
    void HandleBehavior(sf::Vector2f target, Character& enemy, float deltaTime) override;
    //void UpdateArrows(float deltaTime, const sf::RenderWindow& window, vector<IController*> targets);

    void SetSpeed(float val) override
    {
        this->characterMesh.SetSpeed(val);
    }

};



