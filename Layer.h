#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"

class Layer
{
protected:
	Sprite* layerSprite;
public:
	Layer() = delete;
	Layer(int index, Sprite* sprite) : layerSprite(sprite)
	{
		
	}

	void Draw(RenderWindow window)
	{
		window.draw(*layerSprite);
	}
	
};
