#include "Projectile.h"

void Projectile::SetDamage(float dmg) { damage = dmg; }
float Projectile::ApplyDamage() { return this->damage; }