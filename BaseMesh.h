#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"

using namespace std;
using namespace sf;

struct SpawnPoint
{
    int x, y;
};

enum TextureCategory
{
    Idle,
    Move,
    Attack,
    Death,
    Static,
    StaticAnimated
};

struct TextureMeta
{
    TextureCategory category;
    string folderPath;
    string fileName;
    int frameWidth;
    int frameHeight;
    int numberOfFrames;
    int numberOfColumns;
};

enum class Direction { Right = 90, Up = 0, Left = 270, Down  = 180};

class BaseMesh
{
protected:
    Sprite sprite;
    Animation animation;

    virtual void LoadTextures(map<Direction, Texture>& target, string commonPath, string nameOfTexture) = 0;

public:

    BaseMesh() = delete;

    BaseMesh(vector<TextureMeta> texturePathList, SpawnPoint spawnPoint) :animation(sprite) {}

    virtual void Draw(sf::RenderWindow& window);
    virtual Vector2f GetPosition() const;
    virtual Vector2f GetCenter() const;
    virtual void Update(float deltaTime, const sf::RenderWindow& window);
    virtual Vector2f MoveToPoint(Vector2f point);
    virtual void SetAnimationDuration(float newVal);
};