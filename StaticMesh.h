#pragma once
#include "BaseMesh.h"
#include <iostream>

using namespace std;

enum GetCenterOptions
{
    Actual,
    Top,
    Bottom
};

class StaticMesh
{
protected:

    Sprite top,
        bottom;

    Texture *_textureStatic;
    FloatRect _bounds;

public:

    StaticMesh() = default;
    StaticMesh(Texture& texture, SpawnPoint spawnP)
    {

        this->_textureStatic = &texture;
        int split = texture.getSize().y / 2;

        bottom.setTexture(*_textureStatic);
        top.setTexture(*_textureStatic);

        bottom.setTextureRect(IntRect(0, split, texture.getSize().x, texture.getSize().y - split));
        top.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, split));

        top.setPosition(spawnP.x, spawnP.y);
        bottom.setPosition(spawnP.x, spawnP.y + split);
        this->_bounds = bottom.getGlobalBounds();
    }

    virtual Sprite& SpriteTop();
    virtual Sprite& SpriteBottom();

    virtual FloatRect GetMapBounds() const = 0;

    virtual void Update(float deltaTime, const RenderWindow& window) = 0;
    virtual void DrawTop(RenderWindow& window);
    virtual void DrawBottom(RenderWindow& window);

    virtual Vector2f GetPosition() const;

    virtual Vector2f GetCenter(GetCenterOptions option) const;

    ~StaticMesh() = default;
};
