#pragma once
#include "StaticMesh.h"

class Tree :public StaticMesh
{
protected:

public:

	Tree() = delete;
	Tree(Texture& texture, SpawnPoint spawnP)
		: StaticMesh(texture, spawnP) {

		this->_bounds.top = this->GetCenter(Bottom).y-30;
		this->_bounds.left = this->GetCenter(Bottom).x;
		this->_bounds.width = 1.f;
		this->_bounds.height = 0.2f;
	}

	FloatRect GetMapBounds() const override
	{
		return this->_bounds;
	}
	void Update(float deltaTime, const RenderWindow& window) override
	{

	}
};
