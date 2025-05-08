#pragma once
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class IController;
class Character;
class CharacterMesh;

class IBaseUnit {
public:
    virtual Character& GetEntity() = 0;
    virtual CharacterMesh& GetMesh() = 0;
    virtual bool& IsDead() = 0;
    virtual Vector2f GetPosition() const = 0;
    virtual Vector2f GetCenter() const = 0;
    virtual Vector2f MoveToPoint(sf::Vector2f point) = 0;
    virtual void SetAnimationDuration(float newVal) = 0;
    virtual void SetSpeed(float val) = 0;
    virtual void Draw(sf::RenderWindow& window) = 0;
    virtual IController& GetController() = 0;

    virtual void Shot(Texture& texture) = 0;
    virtual void ShotCharged(Texture& texture) = 0;

    virtual ProjectileType GetTypeOfProjectile() = 0;

    virtual ~IBaseUnit() = default;
};

