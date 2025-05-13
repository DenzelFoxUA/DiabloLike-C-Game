#pragma once
#include "LadyArcher.h"
#include "LadyArcherMesh.h"
#include "LadySwordMesh.h"
#include "LadyController.h"
#include "BaseUnit.h"
#include <optional>
#include "ProjectileManager.h"
#include "Enemies.h"

using namespace std;

class LadyUnit :public BaseUnit<LadyArcher>
{
protected:

	LadyArcherMesh _meshRanged;
	LadySwordMesh _meshMelee;

	optional<LadyController> _controller;

	float staminaReqForShoot = 50;
	float staminaReqForChargedShot = 230;
	float staminaReqForMeleeAttack = 70;

	float CaltulateShootSpeed(bool isCharged);

	float CalculateShootDamage(bool isCharged);

	float CalculateHitRadius(bool isCharged);

	float CaltculateMeleeDamage(bool isPowered, float swordDamage = 20)
	{
		float dmg = this->_character.GetAttributes().strength * swordDamage;
	}

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
		cout << "Current energy: " << this->_controller->GetEnergy();
		if (_character.GetStaminaPoints() >= staminaReqForShoot)
		{
			cout << "Energy spent: " << staminaReqForShoot << endl; //normal attack value
			this->_controller->SpendEnergy(staminaReqForShoot);
			Vector2f direction = this->_controller->Shot();

			bool isCharged = false;
			Vector2f center = this->_controller->GetCenter();

			float speed = CaltulateShootSpeed(isCharged);
			float damage = CalculateShootDamage(isCharged);
			float hitRadius = CalculateHitRadius(isCharged);

			std::unique_ptr<IProjectileObject> projectilePtr =
				std::make_unique<ProjectileObject<ArrowMesh, Arrow>>(
					std::move(ArrowMesh(texture, center, direction, speed, 1.5f)),
					std::move(Arrow(_projectileEquiped, damage, hitRadius, isCharged))
				);
			this->allGameProjectiles->AddProjectile(std::move(projectilePtr));
		}
		else
		{
			cout << "Not enouqh energy!!!" << endl;
		}

	}

	void ShotCharged(Texture& texture) override
	{
		cout << "Current energy: " << this->_controller->GetEnergy();
		if (this->_controller->GetEnergy() >= staminaReqForChargedShot)
		{
			cout << "Energy spent: " << staminaReqForChargedShot << endl; //power value
			this->_controller->SpendEnergy(staminaReqForChargedShot);

			Vector2f direction = this->_controller->Shot();

			bool isCharged = true;
			Vector2f center = this->_meshRanged.GetCenter();

			float speed = CaltulateShootSpeed(isCharged);
			float damage = CalculateShootDamage(isCharged);
			float hitRadius = CalculateHitRadius(isCharged);

			std::unique_ptr<IProjectileObject> projectilePtr =
				std::make_unique<ProjectileObject<ArrowMesh, Arrow>>(
					std::move(ArrowMesh(texture, center, direction, speed, 2.f)),
					std::move(Arrow(_projectileEquiped, damage, hitRadius, isCharged))
				);

			this->allGameProjectiles->AddProjectile(std::move(projectilePtr));
		}
		else
		{
			cout << "Not enouqh energy!!!" << endl;
		}

	}

	virtual void MeleeAttack(Direction facing, const std::vector<IBaseUnit*>& enemies) override
	{
		if (this->_controller->GetEnergy() >= staminaReqForMeleeAttack)
		{
			this->_controller->SpendEnergy(staminaReqForMeleeAttack);
			cout << "Entering melee attack method" << endl;
			sf::Vector2f playerPos = this->_meshMelee.GetPosition();
			sf::Vector2f facingVec = DirectionToVector(facing);

			cout << "Player pos: " << playerPos.x << " - " << playerPos.y << endl;
			cout << "Direction " << facingVec.x << facingVec.y << endl;

			float attackRadius = 80.f;
			float dotThreshold = 0.3f;

			cout << attackRadius << " - RADIUS" << endl;


			for (IBaseUnit* enemy : enemies) {
				sf::Vector2f toEnemy = enemy->GetPosition() - playerPos;

				cout << "Distance to enemy = " << toEnemy.x << "/" << toEnemy.y << endl;
				float distance = this->_controller->GetDistanceToTarget(enemy->GetPosition());
				std::cout << "Distance to enemy: " << distance << "\n";

				if (distance > attackRadius) continue;

				sf::Vector2f dirToEnemy = toEnemy / distance;
				float dot = dirToEnemy.x * facingVec.x + dirToEnemy.y * facingVec.y;
				std::cout << "Dot product = " << dot << "\n";
				if (dot > dotThreshold) {

					enemy->GetEntity().GetHit(170);
					std::cout << "Hit enemy in front!\n";
				}
			}
		}
		else
		{
			cout << "Not enogh stamina!" << endl;
		}
		
	}

	void Update(float deltaTime, const sf::RenderWindow& window, Texture&projTexture, Texture& projChargedTexture)
	{
		auto currDirection = this->_controller->GetCurrentDirection();
		auto currentPosition = this->_controller->GetCurrentPosition();
		if (!this->_character.IsModeTwoActive())
		{
			this->_controller->SetActiveMesh(&_meshRanged);
			this->_meshRanged.SetPosition(currentPosition);
			this->_meshRanged.CurrentDir() = currDirection;
			this->_controller->Update(deltaTime, window);
			RangedMethod(deltaTime, window, projTexture, projChargedTexture);
		}	
		else
		{
			this->_controller->SetActiveMesh(&_meshMelee);
			this->_meshMelee.SetPosition(currentPosition);
			this->_meshMelee.CurrentDir() = currDirection;
			this->_controller->SetActiveMesh(&_meshMelee);
			this->_controller->Update(deltaTime, window);
			MeleeMethod(deltaTime, window);
		}
			
		
	}

	void RangedMethod(float deltaTime, const sf::RenderWindow& window, Texture& projTexture, Texture& projChargedTexture)
	{
		
		//this->_controller->Update(deltaTime, window);
		float& chargeTime = this->_controller->GetChargeTime();
		bool& chargingShot = this->_controller->IsChargingAttack();

		if (chargingShot) {

			chargeTime += deltaTime;
			if (chargeTime >= 2.0f) {
				this->_controller->FreezeOnMidFrame();
			}
		}

		if (this->_controller->IsAttacking() && this->_controller->AnimationIsFinished()) {
			if (this->_controller->PendingNormalAttack()) {
				Shot(projTexture);
				this->_controller->PendingNormalAttack() = false;
				cout << "Normal----------------------------->" << endl;

			}
			else if (this->_controller->PendingChargedAttack()) {
				ShotCharged(projChargedTexture);
				this->_controller->PendingChargedAttack() = false;
				cout << "CHARGED CHARGED!!!----------------------------->" << endl;
			}

			this->_meshRanged.IsAttacking() = false;
			this->_meshRanged.CurrentState() = CharacterState::Idle;
			this->_meshRanged.Animation().Resume();
		}
	}

	void MeleeMethod(float deltaTime, const sf::RenderWindow& window)
	{
		cout << "Entering melee mode" << endl;
		if (this->_controller->IsAttacking() && this->_controller->AnimationIsFinished()) {
			cout << "Passed firs if" << endl;
			cout << "Pending Normal Attack " << this->_controller->PendingNormalAttack() << endl;
			if (this->_controller->PendingNormalAttack()) {
				vector<IBaseUnit*> enemies = Enemies::Get();
				MeleeAttack(this->_controller->GetCurrentDirection(), enemies);
				this->_controller->PendingNormalAttack() = false;
				cout << "Normal----------------------------->" << endl;

			}
			this->_meshRanged.IsAttacking() = false;
			this->_meshRanged.CurrentState() = CharacterState::Idle;
			this->_meshRanged.Animation().Resume();
		}
	}

	void Draw(sf::RenderWindow& window) override
	{
		this->_controller->Draw(window);
	}

	LadyArcherMesh& GetMesh() override
	{
		return this->_meshRanged;
	}

	Vector2f GetPosition() override
	{
		return this->_controller->GetCurrentPosition();
	}
	Vector2f GetCenter() const  override
	{
		return this->_meshRanged.GetCenter();
	}
	Vector2f MoveToPoint(Vector2f point)  override
	{
		return this->_meshRanged.MoveToPoint(point);
	}
	void SetAnimationDuration(float newVal)  override
	{
		this->_meshRanged.SetAnimationDuration(newVal);
	}

	void SetSpeed(float val) override
	{
		this->_meshRanged.SetSpeed(val);
	}

	void SubscribeOnEnemy(Character& enemy) override
	{
		int id = enemy.GetId();
		if (enemiesSubscriptions.contains(id)) return;

		int listenerId = enemy.SubscribeOnDeath([this](int exp) {
			this->GainXP(exp);
			});

		enemiesSubscriptions[id] = listenerId;
	}

	void UnsubscribeFromEnemy(Character& enemy) override
	{
		int id = enemy.GetId();
		auto it = enemiesSubscriptions.find(id);
		if (it == enemiesSubscriptions.end()) return;

		enemy.UnsubscribeOnDeath(it->second);
		enemiesSubscriptions.erase(it);
	}

	void GainXP(int expPoints) override
	{
		this->_controller->GetEntity().GainExperience(expPoints);
	}

	virtual void SpendEnergy(float value)
	{
		this->_controller->SpendEnergy(value);
	}

	virtual void GainEnergyBySource(float value)
	{
		this->_controller->GainEnergy(value);
	}

	virtual void HealBySource(float value)
	{
		this->_controller->HealBySource(value);
	}
	void HandleBehavior(IBaseUnit* target, float deltaTime) override {}
	template <typename,typename>
	friend class UnitBuilder;
};