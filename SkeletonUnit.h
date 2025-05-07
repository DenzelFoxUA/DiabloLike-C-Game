#pragma once
#include "Skeleton.h"
#include "SkeletonMesh.h"
#include "SkeletonController.h"
#include "BaseUnit.h"
#include <optional>

using namespace std;

class SkeletonUnit :public BaseUnit<SkeletonMesh, Skeleton>
{
protected:

	SkeletonMesh _mesh;
	optional<SkeletonController> _controller;

public:

	SkeletonUnit(int id, const vector<TextureMeta>& textures, SpawnPoint sp,
		const Skeleton& entity, Texture projectile, Arrow arrow, float cooldown) : BaseUnit(id, entity), _mesh(textures, sp)
	{
		_controller.emplace(_mesh, _character, cooldown);
	}

	void HandleBehavior(Vector2f target, Character& enemy, float deltaTime)
	{
		this->_controller->HandleBehavior(target, enemy, deltaTime);
	}

	void Update(float deltaTime, const sf::RenderWindow& window, CharacterMesh& targetMesh, Character& target)
	{
		this->_controller->Update(deltaTime, window,targetMesh,target);
	}
	void Draw(sf::RenderWindow& window)
	{
		this->_controller->Draw(window);
	}

	/*virtual LadyArcher& GetEntity()
	{
		return this->_character;
	}*/

	SkeletonMesh& GetMesh() override
	{
		return this->_mesh;
	}

	//virtual bool& IsDead() override
	//{
	//	return this->_mesh.IsDead();
	//}

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

	template <typename, typename, typename>
	friend class UnitBuilder;
};
