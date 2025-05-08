#pragma once
#include "LadyArcher.h"
#include "LadyArcherMesh.h"
#include "LadyArcherController.h"
#include "BaseUnit.h"
#include <optional>
#include "ProjectileManager.h"

using namespace std;
//template <typename ProjectileT>
class LadyArcherUnit :public BaseUnit<LadyArcher>
{
protected:

	LadyArcherMesh _mesh;

	optional<LadyArcherController> _controller;

	
	/*unique_ptr<IProjectile> equipedProj;*/

public:

	LadyArcherUnit(int id, 
		const vector<TextureMeta>& textures, 
		SpawnPoint sp,
		const LadyArcher& entity, 
		ProjectileType projectile,
		float cooldown, 
		ProjectilesContainer*container): BaseUnit(id,entity,projectile,container), _mesh(textures,sp)/*, equipedProj(move(projectile))*/
	{ 
		//static_assert(std::is_base_of_v<IProjectile, ProjectileT>, "T must inherit from IProjectile");
		_controller.emplace(_mesh, this->_character);
	}

	IController& GetController() override
	{
		return _controller.value();
	}

	void HandleInput(float deltaTime)
	{
		this->_controller->HandleInput(deltaTime);
		
	}

	void HandleEvent(const sf::Event& event, const sf::RenderWindow& window)
	{
		this->_controller->HandleEvent(event, window);
	}

	void Shot(Texture& texture) override
	{
		//Vector2f direction = this->_controller->Shot();
		//Texture texture = this->_mesh.GetProjectileTexture();
		//this->equipedProj.IsCharged() = false;
		//Vector2f center = this->_mesh.GetCenter();
		//ArrowMesh arrowMesh(texture, center, direction, 250.f, 6.f);
		//ProjectileObject projObject = ProjectileObject(MeshT && _mesh, EntityT && _entity);
		//this->allGameProjectiles.AddProjectile(projObject);
		

		Vector2f direction = this->_controller->Shot();
		//Texture texture = this->_mesh.GetProjectileTexture();
		bool isCharged = false;
		Vector2f center = this->_mesh.GetCenter();

		//ArrowMesh arrowMesh(texture, center, direction, 150.f, 6.f);
		Arrow arrow = Arrow(_projectileEquiped, 100, 80, isCharged);
		std::unique_ptr<IProjectileObject> projectilePtr =
			std::make_unique<ProjectileObject<ArrowMesh, Arrow>>(
				std::move(ArrowMesh(texture, center, direction, 350.f, 6.f)),
				std::move(arrow)
			);

		this->allGameProjectiles->AddProjectile(std::move(projectilePtr));
		
	}

	void ShotCharged(Texture& texture, float charge) override
	{

		Vector2f direction = this->_controller->Shot();
		bool isCharged = true;
		Vector2f center = this->_mesh.GetCenter();
		Arrow arrow = Arrow(_projectileEquiped, 200.f, 80, isCharged);

		std::unique_ptr<IProjectileObject> projectilePtr =
			std::make_unique<ProjectileObject<ArrowMesh, Arrow>>(
				std::move(ArrowMesh(texture, center, direction, 450.f, 8.f)),
				std::move(arrow)
			);

		this->allGameProjectiles->AddProjectile(std::move(projectilePtr));
	}

	void Update(float deltaTime, const sf::RenderWindow& window, Texture&projTexture)
	{
		this->_controller->Update(deltaTime, window);
		float& chargeTime = this->_mesh.ChargeTime();

		bool& chargingShot = this->_mesh.IsChargingAttack();

		if (chargingShot) {

			chargeTime += deltaTime;
			if (chargeTime >= 2.0f) {
				this->_mesh.Animation().FreezeOnMidFrame();
			}
		}

		if (this->_mesh.IsAttacking() && this->_mesh.Animation().IsFinished()) {
			if (this->_mesh.PendingNormalAttack()) {
				Shot(projTexture);
				this->_mesh.PendingNormalAttack() = false;
			}
			else if (this->_mesh.PendingChargedAttack()) {
				ShotCharged(projTexture, 2.f);
				this->_mesh.PendingChargedAttack() = false;
			}

			this->_mesh.IsAttacking() = false;
			this->_mesh.CurrentState() = CharacterState::Idle;
			this->_mesh.Animation().Resume();
		}


	}

	//void UpdateArrows(float deltaTime, const sf::RenderWindow& window, vector<IController*> enemies)
	//{
	//	this->_controller->UpdateArrows(deltaTime, window, enemies);
	//}

	void Draw(sf::RenderWindow& window) override
	{
		this->_controller->Draw(window);
	}

	LadyArcherMesh& GetMesh() override
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
		this->_mesh.SetSpeed(val);
	}


	template <typename,typename>
	friend class UnitBuilder;
};