#pragma once

using namespace std;

namespace StaminaRequirements
{
	const float MELEE_ATTACK = 50.f,
		ARROW_CHARGED_SHOT = 100.f,
		ARROW_SIMPLE_SHOT = 50.f;

};

namespace Damage
{
	const float MELEE_ATTACK = 10.f,
		MELEE_CHARGED = 20.f,
		BOW_ARROW = 10.f,
		BOW_CHARGED = 20.f;
}


namespace Range
{
	const float MELEE_ATTACK = 40.f;
	const float MELEE_ATTACK_CHARGED = 60.f;
}

namespace ProjectileSpeed
{
	const float ARROW_SIMPLE = 100.f;
}

namespace ProjectileHitRadius
{
	const float ARROW_SIMPLE = 40.f;
	const float ARROW_CHARGED = 60.f;
}

namespace ProjectileLifeTime
{
	const float ARROW_SIMPLE = 2.f;
	const float ARROW_CHARGED = 6.f;
}


