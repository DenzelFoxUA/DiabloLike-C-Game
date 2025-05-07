#pragma once
#include "Character.h"

class Projectile
{
protected:

	float damage;
	bool isCharged;
	bool hitTarget = false;

public:

	Projectile() = delete;
	Projectile(float damage, bool isCharged, bool isHit = false): damage(damage), isCharged(isCharged), hitTarget(isHit){}

	virtual void SetDamage(float dmg);
	virtual float GetDamage();
	virtual void ApplyDamage(Character&target);
	virtual bool& IsCharged()
	{
		return this->isCharged;
	}

	virtual void SetHitTarget(bool val) { hitTarget = val; }
	virtual bool HasHitTarget() const { return hitTarget; }
};
