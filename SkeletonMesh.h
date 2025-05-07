#pragma once
#include "NPCMesh.h"

class SkeletonMesh : public NPCMesh
{
public:
	SkeletonMesh(vector<TextureMeta> texturePathList, SpawnPoint spawnP)
		: NPCMesh(texturePathList, spawnP) {

	};

};