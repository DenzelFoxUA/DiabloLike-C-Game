#pragma once
#include "NPC_Controller.h"
#include "SkeletonMesh.h"
#include "Skeleton.h"


class SkeletonController : public NPC_Controller<SkeletonMesh, Skeleton>
{
protected:

public:
	SkeletonController(SkeletonMesh& _mesh, Skeleton& _entity, float cooldown)
		: NPC_Controller(_mesh, _entity, cooldown)
	{

	}

	void HandleBehavior(Vector2f target, Character& enemy, float deltaTime) override;
	void Update(float deltaTime, const sf::RenderWindow& window, CharacterMesh& targetMesh, Character& target) override;
	void Draw(sf::RenderWindow& window) override;

	void SetSpeed(float val) override
	{
		this->npcMesh.SetSpeed(val);
	}
};
