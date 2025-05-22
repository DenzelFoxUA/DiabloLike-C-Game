#pragma once
#include "NPC_Controller.h"
#include "SkeletonMesh.h"
#include "Skeleton.h"


class SkeletonController : public NPC_Controller
{
protected:

public:
	SkeletonController(SkeletonMesh* _mesh, Skeleton& _entity, float cooldown)
		: NPC_Controller(_mesh, _entity, cooldown){}

	//entity
	Character& GetEntity() override;
	
	//mesh
	void Draw(sf::RenderWindow& window) override;
	void SetSpeed(float val) override;

	//update/events
	void Update(float deltaTime, const sf::RenderWindow& window) override;
	void HandleEvent(const sf::Event& event, const sf::RenderWindow& window) override; //not using

	//behavior input
	void HandleBehavior(Vector2f target, Character& enemy, float deltaTime) override;
    void HandleInput(float deltaTime) override; //not using


};
