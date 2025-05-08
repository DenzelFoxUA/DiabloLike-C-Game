#pragma once
#include "Character.h"

enum ProjectileType
{
	None,
	ArrowSimple,
	ArrowMagic,
	ThrowableMagic,
	Knive,
	Bullet
};

class IProjectile
{
public:
	virtual void SetDamage(float dmg) = 0;
	virtual float GetDamage() = 0;
	virtual void ApplyDamage(Character& target) = 0;
	virtual bool& IsCharged() = 0;

	virtual float GetHitRadius() = 0;

	virtual void SetHitTarget(bool val) = 0;
	virtual bool HasHitTarget() const = 0;
	virtual ProjectileType GetType() = 0;
};

class Projectile:public IProjectile
{
protected:

	float damage;
	bool isCharged;
	bool hitTarget = false;
	float hitRadius;
	ProjectileType type;

public:

	Projectile() = delete;
	Projectile(ProjectileType type, float damage, float hitRadius, bool isCharged, bool isHit = false)
		: damage(damage),hitRadius(hitRadius), isCharged(isCharged),type(type), hitTarget(isHit) { }

	virtual void SetDamage(float dmg);
	virtual float GetDamage();
	virtual void ApplyDamage(Character&target);
	virtual bool& IsCharged();

	virtual float GetHitRadius() { return hitRadius; }

	virtual void SetHitTarget(bool val) { hitTarget = val; }
	virtual bool HasHitTarget() const { return hitTarget; }

	virtual ProjectileType GetType();

};
