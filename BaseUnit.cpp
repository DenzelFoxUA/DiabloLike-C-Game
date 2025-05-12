#include "BaseUnit.h"

void BaseUnit::Death()
{

}

virtual ProjectileType GetTypeOfProjectile() override
{
    return this->_projectileEquiped;
}