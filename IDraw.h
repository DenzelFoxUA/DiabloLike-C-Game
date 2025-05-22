#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"

class IDraw
{
public:
	virtual void Draw(sf::RenderWindow& window) = 0;
	virtual void DrawTop(RenderWindow& window) = 0;
	virtual void DrawBottom(RenderWindow& window) = 0;
	virtual void Update(float deltaTime, const RenderWindow& window) = 0;
	virtual void Update(float deltaTime, const sf::RenderWindow& window, float hp = 0, float hpMax = 0,
		float stamina = 0, float staminaMax = 0, float mana = 0, float manaMax = 0) = 0;
};
