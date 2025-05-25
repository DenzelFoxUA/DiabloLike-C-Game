#pragma once
#include "LadyArcher.h"
#include "LadyArcherMesh.h"
#include "LadySwordMesh.h"
#include "LadyController.h"
#include "BaseUnit.h"
#include <optional>
#include "ProjectileManager.h"
#include "Enemies.h"
#include "ProjectileModels.h"

using namespace std;

class LadyUnit :public BaseUnit<LadyArcher>
{
protected:

	LadyArcherMesh _meshRanged;
	LadySwordMesh _meshMelee;

	optional<LadyController> _controller;

public:

	LadyUnit( 
		const vector<TextureMeta>& texturesRanged,
		const vector<TextureMeta>& texturesMelee,
		SpawnPoint sp,
		const LadyArcher& entity, 
		ProjectileType projectile,
		float cooldown, 
		ProjectilesContainer*container)
		: BaseUnit(entity,projectile,container), _meshRanged(texturesRanged,sp),
		_meshMelee(texturesMelee,sp)
	{ 
		_controller.emplace(&_meshRanged, this->_character);
	}

	void HandleInput(float deltaTime) override;
	void HandleMouseEvent(const sf::Event& event, const sf::RenderWindow& window, float dt) override;

	void Shot(Texture& texture, Vector2f targetPos) override;

	void ShotCharged(Texture& texture, Vector2f targetPos) override;

	void MeleeAttack(Direction facing, const std::vector<IBaseUnit*>& enemies, bool isCharged) override;
	

	/*void Update(float deltaTime, const sf::RenderWindow& window,
		Texture& projTexture, Texture& projChargedTexture);*/

	void RangedMethod(float deltaTime, const sf::RenderWindow& window,
		Texture& projTexture, Texture& projChargedTexture);

	void MeleeMethod(float deltaTime, const sf::RenderWindow& window);

	void Draw(sf::RenderWindow& window) override;

	void SetDeathAnimationTime(float val) override;

	virtual void SetAttackDelay(float time) override {
		this->_controller->SetAttackDelay(time);
	}

	Vector2f GetPosition() override;
	Vector2f GetCenter()  override;

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

	void MoveToPoint(Vector2f point, float deltaTime)  override;

	void SetAnimationDuration(float newVal)  override;

	void SetSpeed(float val) override;

	void SubscribeOnEnemy(Character& enemy) override;

	void UnsubscribeFromEnemy(Character& enemy) override;

	void GainXP(int expPoints) override;

	void SpendEnergy(float value);

	void GainEnergyBySource(float value);

	void HealBySource(float value);

	IController& GetController() override;

	//empty unused methods
	void HandleBehavior(IBaseUnit* target, float deltaTime) override {}
	void Update(float deltaTime, const sf::RenderWindow& window) override;

	template <typename,typename>
	friend class UnitBuilder;
};