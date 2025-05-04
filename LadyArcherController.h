#pragma once
#include "PlayerCharacterController.h"
#include "LadyArcher.h"
#include "LadyArcherMesh.h"

class LadyArcherController : public PlayerController<LadyArcherMesh,LadyArcher>
{
protected:
    //bool chargingShot = false;
    //float chargeTime = 0.f;
    //const float maxChargeTime = 2.f;
    //bool shotAlreadyCharged = false;

    //bool pendingNormalShot = false;
    //bool pendingChargedShot = false;
    //float pendingChargeTime = 0.f;
    //sf::Vector2f pendingDirection = { 0.f, 0.f };

    //float attackTimer = 0.f;
    //const float attackDelay = 0.7f;

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
