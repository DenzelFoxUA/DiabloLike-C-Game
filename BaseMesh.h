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
    Melee,
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

inline sf::Vector2f DirectionToVector(Direction dir) {
    switch (dir) {
    case Direction::Up: return { 0.f, -1.f };
    case Direction::Down: return { 0.f, 1.f };
    case Direction::Left: return { -1.f, 0.f };
    case Direction::Right: return { 1.f, 0.f };
    }
    return { 0.f, 0.f };
}

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
    virtual void SetPosition(Vector2f pos);
    virtual Vector2f GetCenter() const;
    virtual void Update(float deltaTime, const sf::RenderWindow& window, float hp = 0, float hpMax = 0, 
        float stamina = 0, float staminaMax = 0, float mana = 0, float manaMax = 0);
    virtual Vector2f MoveToPoint(Vector2f point);
    virtual void SetAnimationDuration(float newVal);
};