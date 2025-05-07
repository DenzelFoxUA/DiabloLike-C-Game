#pragma once
#include "LadyArcher.h"
#include "LadyArcherMesh.h"
#include "LadyArcherController.h"
#include "BaseUnit.h"
#include <optional>

using namespace std;

class LadyArcherUnit :public BaseUnit<LadyArcherMesh,LadyArcher>
{
protected:

	LadyArcherMesh _mesh;

	optional<LadyArcherController> _controller;

public:

	LadyArcherUnit(int id, const vector<TextureMeta>& textures, SpawnPoint sp,
		const LadyArcher& entity, Texture projectile, Arrow arrow, float cooldown = 0.f): BaseUnit(id,entity), _mesh(textures,sp,projectile)
	{ 
		_controller.emplace(_mesh, _character,arrow);	
	}

	void HandleInput(float deltaTime)
	{
		this->_controller->HandleInput(deltaTime);
	}

	void HandleEvent(const sf::Event& event, const sf::RenderWindow& window)
	{
		this->_controller->HandleEvent(event, window);
	}

	void Shoot(sf::Texture& texture, sf::Vector2f direction)
	{
		this->_controller->Shoot(texture,direction);
	}

	void ShootCharged(sf::Texture& texture, sf::Vector2f direction, float charge)
	{
		this->_controller->ShootCharged(texture, direction, charge);
	}

	void Update(float deltaTime, const sf::RenderWindow& window, CharacterMesh& targetMesh, Character& target)
	{
		this->_controller->Update(deltaTime, window, targetMesh, target);
	}
	void Draw(sf::RenderWindow& window)
	{
		this->_controller->Draw(window);
	}

	/*virtual LadyArcher& GetEntity()
	{
		return this->_character;
	}*/

	LadyArcherMesh& GetMesh() override
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
		this->_mesh.SetSpeed(val);
	}

	template <typename, typename, typename>
	friend class UnitBuilder;
};