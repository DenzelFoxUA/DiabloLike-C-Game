#include "Projectile.h"

void Projectile::SetDamage(float dmg) { damage = dmg; }
float Projectile::GetDamage() { return damage; }
void Projectile::ApplyDamage(Character & target) { target.GetHit(this->damage); }