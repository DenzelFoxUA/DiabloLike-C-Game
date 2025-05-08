#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class ProjectileMesh
{
protected:

    Sprite sprite;
    Vector2f velocity;
    Vector2f direction;
    float speed;
    float lifeTime;

    void UpdateVelocity();
public:
    ProjectileMesh(sf::Texture& texture, sf::Vector2f startPos, sf::Vector2f direction, float speed, float lifeTime)
    {
        sprite.setTexture(texture);
        sprite.setPosition(startPos);
        this->direction = direction;
        this->speed = speed;
        this->lifeTime = lifeTime;

        FloatRect bounds = sprite.getLocalBounds();
        sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

        UpdateVelocity();

        float angle = std::atan2(direction.y, direction.x) * 180.f / 3.14159265f;
        sprite.setRotation(angle);
    }

    ProjectileMesh(const ProjectileMesh& other);
    virtual ProjectileMesh& operator=(const ProjectileMesh& other);

    virtual void Update(float deltaTime);
    virtual void Draw(RenderWindow& window);
    virtual bool IsOffScreen(RenderWindow& window) const;
    virtual FloatRect GetBounds() const;
    virtual const Texture* GetTexturePtr() const;
    virtual Vector2f GetPosition() const;
    virtual bool IsDead() const;
    virtual void MarkToDestroy();
    virtual void SetSpeed(float newSpeed);
    virtual void EndLifeTime();
    
};
