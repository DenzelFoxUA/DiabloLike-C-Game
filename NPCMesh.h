#pragma once

#include "CharacterMesh.h"

class NPCMesh : public CharacterMesh
{
public:
	NPCMesh(vector<TextureMeta> texturePathList) :CharacterMesh(texturePathList) {

	};
	Vector2f GetCenter() const override;
	Vector2f GetPosition() const override;
};
