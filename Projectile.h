#pragma once

class Projectile
{
protected:

	float damage;

public:

	Projectile() = delete;
	Projectile(float damage): damage(damage){}

	virtual void SetDamage(float dmg);
	virtual float ApplyDamage();
};
