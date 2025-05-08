#pragma once
#include "LadyArcher.h"
#include "LadyArcherMesh.h"
#include "LadyArcherController.h"
#include "BaseUnit.h"
#include <optional>
#include "ProjectileManager.h"

using namespace std;

class LadyArcherUnit :public BaseUnit<LadyArcher>
{
protected:

	LadyArcherMesh _mesh;

	optional<LadyArcherController> _controller;

	float CaltulateSpeed(bool isCharged)
	{
		int multiplyer = isCharged ? 2 : 1;

		return this->_character.GetAttributes().strength * 100 * multiplyer;
	}

	float CalculateDamage(bool isCharged)
	{
		int multiplyer = isCharged ? 2 : 1;

		float basicDamage = this->_projectileEquiped == ProjectileType::ArrowSimple ? 20 :
			ProjectileType::ArrowMagic ? 40 : 0;

		return this->_character.GetAttributes().agility * basicDamage * multiplyer;
	}

	float CalculateHitRadius(bool isCharged)
	{
		int multiplyer = isCharged ? 2 : 1;

		float basicRadius = this->_projectileEquiped == ProjectileType::ArrowSimple ? 40 :
			ProjectileType::ArrowMagic ? 60 : 0;

		return this->_character.GetAttributes().agility * multiplyer + basicRadius;
	}

public:

	LadyArcherUnit(int id, 
		const vector<TextureMeta>& textures, 
		SpawnPoint sp,
		const LadyArcher& entity, 
		ProjectileType projectile,
		float cooldown, 
		ProjectilesContainer*container): BaseUnit(id,entity,projectile,container), _mesh(textures,sp)
	{ 
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

		Vector2f direction = this->_controller->Shot();

		bool isCharged = false;
		Vector2f center = this->_mesh.GetCenter();

		float speed = CaltulateSpeed(isCharged);
		float damage = CalculateDamage(isCharged);
		float hitRadius = CalculateHitRadius(isCharged);

		std::unique_ptr<IProjectileObject> projectilePtr =
			std::make_unique<ProjectileObject<ArrowMesh, Arrow>>(
				std::move(ArrowMesh(texture, center, direction, speed, 6.f)),
				std::move(Arrow(_projectileEquiped, damage, hitRadius, isCharged))
			);

		this->allGameProjectiles->AddProjectile(std::move(projectilePtr));
	}

	void ShotCharged(Texture& texture) override
	{

		Vector2f direction = this->_controller->Shot();

		bool isCharged = true;
		Vector2f center = this->_mesh.GetCenter();

		float speed = CaltulateSpeed(isCharged);
		float damage = CalculateDamage(isCharged);
		float hitRadius = CalculateHitRadius(isCharged);

		std::unique_ptr<IProjectileObject> projectilePtr =
			std::make_unique<ProjectileObject<ArrowMesh, Arrow>>(
				std::move(ArrowMesh(texture, center, direction, speed, 6.f)),
				std::move(Arrow(_projectileEquiped, damage, hitRadius, isCharged))
			);

		this->allGameProjectiles->AddProjectile(std::move(projectilePtr));
	}

	void Update(float deltaTime, const sf::RenderWindow& window, Texture&projTexture, Texture& projChargedTexture)
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
				cout << "Normal----------------------------->" << endl;
			}
			else if (this->_mesh.PendingChargedAttack()) {
				ShotCharged(projChargedTexture);
				this->_mesh.PendingChargedAttack() = false;
				cout << "CHARGED CHARGED!!!----------------------------->" << endl;
			}

			this->_mesh.IsAttacking() = false;
			this->_mesh.CurrentState() = CharacterState::Idle;
			this->_mesh.Animation().Resume();
		}
	}

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