#pragma once

#include "CharacterMesh.h"

class NPCMesh : public CharacterMesh
{
public:
	NPCMesh(vector<TextureMeta> texturePathList, SpawnPoint spawnP) 
		:CharacterMesh(texturePathList, spawnP) {

	};
	Vector2f GetCenter() const override;
	Vector2f GetPosition() const override;
};
