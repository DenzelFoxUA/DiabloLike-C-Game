#pragma once
#include "CharacterMesh.h"

class PlayerCharacterMesh : public CharacterMesh
{


public:
	PlayerCharacterMesh(vector<TextureMeta> texturePathList) :CharacterMesh(texturePathList) {

	};

	Vector2f GetCenter() const override;
	Vector2f GetPosition() const override;
};