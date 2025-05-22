#include "SkeletonUnit.h"
#include "Enemies.h"

//mesh methods
void SkeletonUnit::SetDeathAnimationTime(float val)
{
	this->_controller->SetDeathAnimationTime(val);
}

void SkeletonUnit::Draw(sf::RenderWindow& window)
{
	this->_controller->Draw(window);
}

Vector2f SkeletonUnit::GetPosition()
{
	return this->_controller->GetPosition(); //
}

Vector2f SkeletonUnit::GetCenter()
{
	return this->_controller->GetCenter(); //
}

void SkeletonUnit::MoveToPoint(Vector2f point, float deltaTime)
{
	this->_controller->MoveToPoint(point, deltaTime, this->_controller->IsMoving());
}

void SkeletonUnit::SetAnimationDuration(float newVal)
{
	this->_controller->SetAnimationDuration(newVal); //
}

void SkeletonUnit::SetSpeed(float val)
{
	this->_controller->SetSpeed(val);
}

//update input handle events
void SkeletonUnit::Update(float deltaTime, const sf::RenderWindow& window)
{
	this->_controller->Update(deltaTime, window);
	if (Enemies::GetPlayersEnemies().size() > 0)
		HandleBehavior(*Enemies::GetPlayersEnemies().begin(), deltaTime);
}

void SkeletonUnit::HandleBehavior(IBaseUnit* target, float deltaTime)
{
	this->_controller->HandleBehavior(target->GetPosition(), target->GetEntity(), deltaTime);
	if (this->_mesh.CurrentState() == CharacterState::Attack
		&& this->_controller->GetEnergy() >= StaminaRequirements::MELEE_ATTACK)
	{
		MeleeAttack(this->_mesh.CurrentDir(), { target });
	}
}

//direct controller
IController& SkeletonUnit::GetController()
{
	if (!_controller.has_value())
	{
		throw std::runtime_error("Controller not initialized!");
	}

	return *_controller;
}

//combat
void SkeletonUnit::MeleeAttack(Direction facing, const std::vector<IBaseUnit*>& enemies)
{
	if (this->_controller->GetEnergy() >= StaminaRequirements::MELEE_ATTACK)
	{
		this->_controller->SpendEnergy(StaminaRequirements::MELEE_ATTACK);
		sf::Vector2f playerPos = this->_mesh.GetPosition();
		sf::Vector2f facingVec = DirectionToVector(facing);

		float dotThreshold = 0.3f;
		float nominalDamage = _controller->CaltculateMeleeDamage(false);

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
			if (dot > dotThreshold) {

				enemy->GetHit(nominalDamage);
			}

			cout << enemy->GetName() << " taking " << nominalDamage << " damage!\n";
			cout << enemy->GetName()
				<< " has " << enemy->GetEntity().GetHealthPoints() << " HP.\n";
		}
	}
	else
	{
		cout << _character.GetName() << " dont have much strength to make a move" << endl;
	}
}

//stats
void SkeletonUnit::SpendEnergy(float value)
{
	this->_controller->SpendEnergy(value);
}

void SkeletonUnit::GainEnergyBySource(float value)
{
	this->_controller->GainEnergy(value);
}

void SkeletonUnit::HealBySource(float value)
{
	this->_controller->HealBySource(value);
}