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
		SpawnPoint sp,
		const Skeleton& entity, 
		ProjectileType projectile,
		float cooldown,
		ProjectilesContainer* container) : BaseUnit(entity,projectile,container), _mesh(textures, sp)
	{
		_controller.emplace(_mesh, static_cast<Skeleton&>(_character), cooldown);
	}

	IController& GetController() override
	{
		return this->_controller.value();
	}

	void HandleBehavior(Vector2f target, Character& enemy, float deltaTime)
	{
		this->_controller->HandleBehavior(target, enemy, deltaTime);
	}

	void Update(float deltaTime, const sf::RenderWindow& window)
	{
		this->_controller->Update(deltaTime, window);
	}
	void Draw(sf::RenderWindow& window)
	{
		this->_controller->Draw(window);
	}

	SkeletonMesh& GetMesh() override
	{
		return this->_mesh;
	}

	Vector2f GetPosition() const  override
	{
		return this->_mesh.GetPosition();
	}
	Vector2f GetCenter() const  override
	{
		return this->_mesh.GetCenter();
	}
	Vector2f MoveToPoint(Vector2f point)  override
	{
		return this->_mesh.MoveToPoint(point);
	}
	void SetAnimationDuration(float newVal)  override
	{
		this->_mesh.SetAnimationDuration(newVal);
	}

	void SetSpeed(float val) override
	{
		this->_controller->SetSpeed(val);
	}

	void Shot(Texture& projTexture)override
	{

	}
	void ShotCharged(Texture& projtexture) override
	{

	}

	void SubscribeOnEnemy(Character& enemy) override
	{

	}
	void UnsubscribeFromEnemy(Character& enemy) override
	{

	}

	void GainXP(int expPoints) override
	{

	}

	virtual void SpendEnergy(float value) override
	{
		this->_controller->SpendEnergy(value);
	}

	virtual void GainEnergyBySource(float value) override
	{
		this->_controller->GainEnergy(value);
	}
	virtual void HealBySource(float value) override
	{
		this->_controller->HealBySource(value);
	}

	template <typename, typename>
	friend class UnitBuilder;
};
