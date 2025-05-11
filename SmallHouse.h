#pragma once
#include "StaticMesh.h"

class SmallHouse : public StaticMesh
{
protected:
	
public:

	SmallHouse() = delete;
	SmallHouse(TextureMeta texture, SpawnPoint spawnP)
		: StaticMesh(texture, spawnP) {

		this->_bounds.top = this->GetCenter(Bottom).y-60;
		this->_bounds.left = this->GetPosition().x + 60;
		this->_bounds.width = texture.frameWidth - 180;
		this->_bounds.height = texture.frameHeight/13;
	} 

	FloatRect GetMapBounds() const override
	{
		return this->_bounds;
	}

	void Update(float deltaTime, const RenderWindow& window) override
	{

	}
};
