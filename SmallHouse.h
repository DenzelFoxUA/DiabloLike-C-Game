#pragma once
#include "StaticMesh.h"

class SmallHouse : public StaticMesh
{
protected:
	
public:

	SmallHouse() = delete;
	SmallHouse(Texture& texture, SpawnPoint spawnP)
		: StaticMesh(texture, spawnP) {

		if (texture.getSize().x == 0 || texture.getSize().y == 0) {
			std::cerr << "Warning: SmallHouse received empty texture!" << std::endl;
		}

		this->_bounds.top = this->GetCenter(Bottom).y-60;
		this->_bounds.left = this->GetPosition().x + 60;
		this->_bounds.width = texture.getSize().x - 180;
		this->_bounds.height = texture.getSize().y /13;
	} 

	FloatRect GetMapBounds() const override
	{
		return this->_bounds;
	}

	void Update(float deltaTime, const RenderWindow& window) override
	{

	}
};
