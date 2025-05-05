#pragma once
#include "NPCMesh.h"

class SkeletonMesh : public NPCMesh
{
public:
	SkeletonMesh(vector<TextureMeta> texturePathList, SpawnPoint spawnP): NPCMesh(texturePathList, spawnP) {

	};
    //bool& IsCharged() override;
    //bool& IsChargingAttack() override;
    //bool& PendingNormalAttack() override;
    //bool& PendingChargedAttack() override;

    //float& ChargeTime() override;
    //float& AttackTimer() override;

    //Vector2f& PendingDirection() override;
    //float& PendingChargeTime() override;
    //const float AttackDelay() override;
    //const float MaxChargeTime() override;
};