#pragma once
#include "PlayerCharacterController.h"
#include "LadyArcher.h"
#include "LadyArcherMesh.h"

class LadyArcherController : public PlayerController<LadyArcherMesh,LadyArcher>
{
protected:

public:
	LadyArcherController(LadyArcherMesh *_mesh, LadyArcher *_entity) : PlayerController(_mesh, _entity)
	{

	}

    void HandleEvent(const sf::Event& event, const sf::RenderWindow& window) override;
    void HandleInput(float deltaTime) override;
	void Shoot(sf::Texture& arrowTexture, sf::Vector2f direction);
	void ShootCharged(sf::Texture& texture, sf::Vector2f direction, float charge);
    void Update(float deltaTime, const sf::RenderWindow& window) override;
};
