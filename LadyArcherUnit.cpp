#include "LadyArcherUnit.h"

float LadyArcherUnit::CaltulateSpeed(bool isCharged)
{
	int multiplyer = isCharged ? 2 : 1;

	return this->_character.GetAttributes().strength * 100 * multiplyer;
}

float LadyArcherUnit::CalculateDamage(bool isCharged)
{
	int multiplyer = isCharged ? 2 : 1;

	float basicDamage = this->_projectileEquiped == ProjectileType::ArrowSimple ? 20 :
		ProjectileType::ArrowMagic ? 40 : 0;

	return this->_character.GetAttributes().agility * basicDamage * multiplyer;
}

float LadyArcherUnit::CalculateHitRadius(bool isCharged)
{
	int multiplyer = isCharged ? 2 : 1;

	float basicRadius = this->_projectileEquiped == ProjectileType::ArrowSimple ? 40 :
		ProjectileType::ArrowMagic ? 60 : 0;

	return this->_character.GetAttributes().agility * multiplyer + basicRadius;
}

