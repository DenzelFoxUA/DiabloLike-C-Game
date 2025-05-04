#pragma once
#include <SFML/Graphics.hpp>

class ArrowMesh {
private:
    sf::Sprite sprite;
    sf::Vector2f velocity;
    sf::Vector2f direction;
    float speed = 250.f;
    float lifeTime = 6.f;

public:
    ArrowMesh(sf::Texture& texture, sf::Vector2f startPos, sf::Vector2f direction);

    ArrowMesh(const ArrowMesh& other);
    ArrowMesh& operator=(const ArrowMesh& other);

    void Update(float deltaTime);
    void Draw(sf::RenderWindow& window);
    bool IsOffScreen(sf::RenderWindow& window) const;
    sf::FloatRect GetBounds() const;
    const sf::Texture* GetTexturePtr() const;
    sf::Vector2f GetPosition() const;
    bool IsDead() const;
    void SetSpeed(float newSpeed);
    void UpdateVelocity();
};
