#pragma once
#include "NPC_Controller.h"
#include "SkeletonMesh.h"
#include "Skeleton.h"


class SkeletonController : public NPC_Controller
{
protected:

public:
	SkeletonController(SkeletonMesh& _mesh, Skeleton& _entity, float cooldown)
		: NPC_Controller(_mesh, _entity, cooldown)
	{

	}

	void HandleBehavior(Vector2f target, Character& enemy, float deltaTime) override;
	void Update(float deltaTime, const sf::RenderWindow& window) override;
	void Draw(sf::RenderWindow& window) override;

    Character& GetEntity() override;
    void SetSpeed(float val) override;

    void HandleInput(float deltaTime) override;

    void HandleEvent(const sf::Event& event, const sf::RenderWindow& window) override;

};
