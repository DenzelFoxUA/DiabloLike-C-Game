#pragma once
#include "Projectile.h"


class Arrow :public Projectile
{
public:
	Arrow() = delete;
	Arrow(ProjectileType type, 
		float damage,
		float hitRadius, 
		bool isCharged) 
		:Projectile(type,damage,hitRadius,isCharged) {}

};
