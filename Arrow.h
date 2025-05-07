#pragma once
#include "Projectile.h"


class Arrow :public Projectile
{
public:
	Arrow() = delete;
	Arrow(float damage, bool isCharged) :Projectile(damage,isCharged) {}

};
