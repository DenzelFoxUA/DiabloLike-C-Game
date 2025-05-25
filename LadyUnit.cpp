#include "LadyUnit.h"

void LadyUnit::HandleInput(float deltaTime)
{
	this->_controller->HandleInput(deltaTime);
}

void LadyUnit::HandleMouseEvent(const sf::Event& event, const sf::RenderWindow& window, float dt)
{
	this->_controller->HandleMouseEvent(event, window, dt);
}

void LadyUnit::Shot(Texture& texture, Vector2f mousePos)
{
	cout << "Current energy: " << this->_controller->GetEnergy();
	if (_character.GetStaminaPoints() >= StaminaRequirements::ARROW_SIMPLE_SHOT)
	{
		cout << "Energy spent: " << StaminaRequirements::ARROW_SIMPLE_SHOT << endl; //normal attack value
		this->_controller->SpendEnergy(StaminaRequirements::ARROW_SIMPLE_SHOT);
		Vector2f direction = this->_controller->Shot();

		bool isCharged = false;
		Vector2f centerPlayer = this->_controller->GetCenter();
		Vector2f dir = centerPlayer - mousePos;

		float characterCircleRadius = 60.f;

		float radAngle = atan2(dir.y, dir.x);

		float offsetX = cos(radAngle) * characterCircleRadius;
		float offsetY = sin(radAngle) * characterCircleRadius;

		centerPlayer.x -= offsetX;
		centerPlayer.y -= offsetY;
		float bowDamage = 150;

		float speed = this->_controller->CaltulateShootSpeed(isCharged);
		float damage = this->_controller->CalculateShootDamage(isCharged, 
			this->GetTypeOfProjectile()) + bowDamage;
		float hitRadius = this->_controller->CalculateHitRadius(isCharged, 
			this->GetTypeOfProjectile());

		std::unique_ptr<IProjectileObject> projectilePtr =
			std::make_unique<ProjectileObject<ArrowMesh, Arrow>>(
				std::move(ArrowMesh(texture, centerPlayer, direction, speed, ProjectileLifeTime::ARROW_SIMPLE)),
				std::move(Arrow(_projectileEquiped, damage, hitRadius, isCharged))
			);
		this->allGameProjectiles->AddProjectile(move(projectilePtr));
	}
	else
	{
		cout << "Not enouqh energy!!!" << endl;
	}
}

void LadyUnit::ShotCharged(Texture& texture, Vector2f mousePos)
{
	cout << "Current energy: " << this->_controller->GetEnergy();
	if (this->_controller->GetEnergy() >= StaminaRequirements::ARROW_CHARGED_SHOT)
	{
		cout << "Energy spent: " << StaminaRequirements::ARROW_CHARGED_SHOT << endl; //power value
		this->_controller->SpendEnergy(StaminaRequirements::ARROW_CHARGED_SHOT);

		Vector2f direction = this->_controller->Shot();

		bool isCharged = true;
		Vector2f centerPlayer = this->_controller->GetCenter();
		Vector2f dir = centerPlayer - mousePos;

		float characterCircleRadius = 60.f;

		float radAngle = atan2(dir.y, dir.x);

		float offsetX = cos(radAngle) * characterCircleRadius;
		float offsetY = sin(radAngle) * characterCircleRadius;

		centerPlayer.x -= offsetX;
		centerPlayer.y -= offsetY;

		float bowDamage = 150;

		float speed = this->_controller->CaltulateShootSpeed(isCharged);
		float damage = this->_controller->CalculateShootDamage(isCharged, this->GetTypeOfProjectile()) + bowDamage;
		float hitRadius = this->_controller->CalculateHitRadius(isCharged, this->GetTypeOfProjectile());

		std::unique_ptr<IProjectileObject> projectilePtr =
			std::make_unique<ProjectileObject<ArrowMesh, Arrow>>(
				std::move(ArrowMesh(texture, centerPlayer, direction, speed, ProjectileLifeTime::ARROW_CHARGED)),
				std::move(Arrow(_projectileEquiped, damage, hitRadius, isCharged))
			);

		this->allGameProjectiles->AddProjectile(std::move(projectilePtr));
		
	}
	else
	{
		cout << "Not enouqh energy!!!" << endl;
	}
}

void LadyUnit::MeleeAttack(Direction facing, const std::vector<IBaseUnit*>& enemies, bool isCharged)
{
	if (!isCharged && this->_controller->GetEnergy() >= StaminaRequirements::MELEE_ATTACK)
	{
		this->_controller->SpendEnergy(StaminaRequirements::MELEE_ATTACK);
	}
	else if (isCharged && this->_controller->GetEnergy() >= StaminaRequirements::MELEE_ATTACK_CHARGED)
	{
		this->_controller->SpendEnergy(StaminaRequirements::MELEE_ATTACK_CHARGED);
	}
	else
	{
		cout << "Not enogh stamina!" << endl;
		return;
	}

	sf::Vector2f playerPos = this->_meshMelee.GetPosition();
	sf::Vector2f facingVec = DirectionToVector(facing);
	float dotThreshold = 0.3f;

	cout << Range::MELEE_ATTACK << " - RADIUS" << endl;

	for (IBaseUnit* enemy : enemies) {
		sf::Vector2f toEnemy = enemy->GetPosition() - playerPos;

		cout << "Distance to enemy = " << toEnemy.x << "/" << toEnemy.y << endl;
		float distance = this->_controller->GetDistanceToTarget(enemy->GetPosition());
		std::cout << "Distance to enemy: " << distance << "\n";

		if (distance > Range::MELEE_ATTACK) continue;

		sf::Vector2f dirToEnemy = toEnemy / distance;
		float dot = dirToEnemy.x * facingVec.x + dirToEnemy.y * facingVec.y;
		std::cout << "Dot product = " << dot << "\n";

		float onehandedSwordDamage = 100;
		float nominalDmg = this->_controller->CaltculateMeleeDamage(isCharged) + onehandedSwordDamage;

		if (dot > dotThreshold) {

			enemy->GetHit(nominalDmg);
			std::cout << "Hit enemy in front!\n";
		}
	}
}



void LadyUnit::Update(float deltaTime, const sf::RenderWindow& window) {

	auto arrowTex = ProjectileModels::GetSimpleArrowTex();
	auto powerArrTex = ProjectileModels::GetPowerArrowTex();

	auto currDirection = this->_controller->GetCurrentDirection();
	auto currentPosition = this->_controller->GetCurrentPosition();

	if (!this->_character.IsModeTwoActive())
	{
		this->_controller->SetActiveMesh(&_meshRanged);
		this->_meshRanged.SetPosition(currentPosition);
		this->_meshRanged.CurrentDir() = currDirection;
		this->_controller->Update(deltaTime, window);
		RangedMethod(deltaTime, window, *arrowTex, *powerArrTex);
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
};

void LadyUnit::RangedMethod(float deltaTime, const sf::RenderWindow& window, 
	Texture& projTexture, Texture& projChargedTexture)
{

	if (this->_controller->IsAttacking() && this->_controller->AnimationIsFinished()) {
		if (this->_controller->PendingNormalAttack()) {
			Shot(projTexture, window.mapPixelToCoords(Mouse::getPosition()));
			this->_controller->PendingNormalAttack() = false;
			cout << "Normal----------------------------->" << endl;

		}
		else if (this->_controller->PendingChargedAttack()) {
			
			ShotCharged(projChargedTexture, window.mapPixelToCoords(Mouse::getPosition()));
			this->_controller->PendingChargedAttack() = false;
			cout << "CHARGED CHARGED!!!----------------------------->" << endl;
			
		}
		this->_meshRanged.IsAttacking() = false;
		this->_meshRanged.CurrentState() = CharacterState::Idle;
		
	
	}
}

void LadyUnit::MeleeMethod(float deltaTime, const sf::RenderWindow& window)
{
	vector<IBaseUnit*> enemies = Enemies::GetNPCEnemies();

	if (this->_controller->IsAttacking() && this->_controller->AnimationIsFinished()) {
		cout << "Pending Normal Attack " << this->_controller->PendingNormalAttack() << endl;
		if (this->_controller->PendingNormalAttack()) 
		{
			MeleeAttack(this->_controller->GetCurrentDirection(), enemies,false);
			this->_controller->PendingNormalAttack() = false;
			cout << "Normal----------------------------->" << endl;
		}
		else if (this->_controller->PendingChargedAttack())
		{
			MeleeAttack(this->_controller->GetCurrentDirection(), enemies, true);
			this->_controller->PendingChargedAttack() = false;
			cout << "CHARGED!!!----------------------------->" << endl;
		}

		this->_meshRanged.IsAttacking() = false;
		this->_meshRanged.CurrentState() = CharacterState::Idle;
		this->_meshRanged.Animation().Resume();
	}
}

void LadyUnit::Draw(sf::RenderWindow& window)
{
	this->_controller->Draw(window);
}

void LadyUnit::SetDeathAnimationTime(float val)
{
	this->_controller->SetDeathAnimationTime(val);
}


Vector2f LadyUnit::GetPosition()
{
	return this->_controller->GetCurrentPosition();
}
Vector2f LadyUnit::GetCenter()
{
	return this->_controller->GetCenter();
}

void LadyUnit::MoveToPoint(Vector2f point, float deltaTime)
{
	this->_controller->MoveToPoint(point, deltaTime, this->_controller->IsMoving());
}

void LadyUnit::SetAnimationDuration(float newVal)
{
	this->_controller->SetAnimationDuration(newVal);
}

void LadyUnit::SetSpeed(float val)
{
	this->_meshRanged.SetSpeed(val);
}

void LadyUnit::SubscribeOnEnemy(Character& enemy)
{
	int id = enemy.GetId();
	if (enemiesSubscriptions.contains(id)) return;

	int listenerId = enemy.SubscribeOnDeath([this](int exp) {
		this->GainXP(exp);
		});

	enemiesSubscriptions[id] = listenerId;
}

void LadyUnit::UnsubscribeFromEnemy(Character& enemy)
{
	int id = enemy.GetId();
	auto it = enemiesSubscriptions.find(id);
	if (it == enemiesSubscriptions.end()) return;

	enemy.UnsubscribeOnDeath(it->second);
	enemiesSubscriptions.erase(it);
}

void LadyUnit::GainXP(int expPoints)
{
	this->_controller->GetEntity().GainExperience(expPoints);
}

void LadyUnit::SpendEnergy(float value)
{
	this->_controller->SpendEnergy(value);
}

void LadyUnit::GainEnergyBySource(float value)
{
	this->_controller->GainEnergy(value);
}

void LadyUnit::HealBySource(float value)
{
	this->_controller->HealBySource(value);
}

IController& LadyUnit::GetController()
{
	if (!_controller.has_value())
	{
		throw std::runtime_error("Controller not initialized!");
	}
	return *_controller;
}