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

    Texture _textureStatic;
    FloatRect _bounds;

    virtual void LoadTextures(string commonPath, 
        string nameOfTexture);

public:

    StaticMesh() = default;
    StaticMesh(TextureMeta textureData, SpawnPoint spawnP)
    {

        LoadTextures(textureData.folderPath, textureData.fileName);
        int height = textureData.frameHeight;
        int width = textureData.frameWidth;
        int columns = textureData.numberOfColumns;
        int frames = textureData.numberOfFrames;

        int split = height / 2;

        bottom.setTextureRect(IntRect(0, split, width, height - split));
        top.setTextureRect(sf::IntRect(0, 0, width, split));

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
