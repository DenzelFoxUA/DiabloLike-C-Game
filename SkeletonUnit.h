#pragma once
#include "Skeleton.h"
#include "SkeletonMesh.h"
#include "SkeletonController.h"
#include "BaseUnit.h"
#include <optional>

using namespace std;

class SkeletonUnit :public BaseUnit<Skeleton>
{
protected:

	SkeletonMesh _mesh;
	optional<SkeletonController> _controller;

public:

	SkeletonUnit( 
		const vector<TextureMeta>& textures,
		const vector<TextureMeta>& texturesAdditonal,
		SpawnPoint sp,
		const Skeleton& entity, 
		ProjectileType projectile,
		float cooldown,
		ProjectilesContainer* container) 
		: BaseUnit(entity,projectile,container), _mesh(textures, sp)
	{
		_controller.emplace(&_mesh, static_cast<Skeleton&>(_character), cooldown);
	}

	//mesh methods
	void SetDeathAnimationTime(float val) override;
	void Draw(sf::RenderWindow& window);
	Vector2f GetPosition()  override;
	Vector2f GetCenter() override;
	void MoveToPoint(Vector2f point, float deltaTime)  override;
	void SetAnimationDuration(float newVal)  override;
	void SetSpeed(float val) override;

	virtual void SetAttackDelay(float time) override {
		this->_controller->SetAttackDelay(time);
	}

	//update input handle events
	void Update(float deltaTime, const sf::RenderWindow& window) override;
	void HandleBehavior(IBaseUnit* target, float deltaTime) override;

	//direct controller
	IController& GetController() override;

	//combat
	void MeleeAttack(Direction facing, const std::vector<IBaseUnit*>& enemies) override;

	//stats
	void SpendEnergy(float value) override;
	void GainEnergyBySource(float value) override;
	void HealBySource(float value) override;

	void SetEnergyRegainValue(float val) override
	{
		this->_controller->SetEnergyRegainValue(val);
	}

	void SetManaRegainValue(float val) override
	{
		this->_controller->SetManaRegainValue(val);
	}

	void SetHPRegainValue(float val) override
	{
		this->_controller->SetHPRegainValue(val);
	}

	//unused
	void Shot(Texture& projTexture)override {}
	void ShotCharged(Texture& projtexture) override {}

	void SubscribeOnEnemy(Character& enemy) override {}
	void UnsubscribeFromEnemy(Character& enemy) override {}
	void GainXP(int expPoints) override {}
	void HandleInput(float deltaTime) override {};
	void HandleMouseEvent(const sf::Event& event, const sf::RenderWindow& window,float dt) override {};

	template <typename, typename>
	friend class UnitBuilder;
};
