
#pragma once
#include "Arrow.h"
#include "ArrowMesh.h"
#include "PlayerCharacterController.h"
#include "LadyArcher.h"
#include "LadyArcherMesh.h"
#include "ArrowController.h"

enum ArrowType {
    Simple
};

class LadyArcherController : public PlayerController<LadyArcherMesh, LadyArcher>
{
protected:
    std::vector<ArrowController> arrowControllers;
    Arrow equipedArrow;
public:

    LadyArcherController(LadyArcherMesh& _mesh, LadyArcher& _entity, Arrow arrow)
        : PlayerController(_mesh, _entity), equipedArrow(arrow)
    {
     
    }

    void HandleEvent(const sf::Event& event, const sf::RenderWindow& window) override;
    void HandleInput(float deltaTime) override;
    void Shoot(sf::Texture& arrowTexture, sf::Vector2f direction);
    void ShootCharged(sf::Texture& texture, sf::Vector2f direction, float charge);
    void Update(float deltaTime, const sf::RenderWindow& window, CharacterMesh& targetMesh, Character& target) override;
    void Draw(sf::RenderWindow& window) override;

    void SetSpeed(float val) override
    {
        this->characterMesh.SetSpeed(val);
    }
};



