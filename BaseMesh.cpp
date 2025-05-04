
#include "BaseMesh.h"

void BaseMesh::Draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

void BaseMesh::Update(float deltaTime, const sf::RenderWindow& window) 
{
    animation.Update(deltaTime);
}

Vector2f BaseMesh::GetPosition() const {
    return this->sprite.getPosition();
}

Vector2f BaseMesh::GetCenter() const {
    sf::FloatRect bounds = this->sprite.getGlobalBounds();
    return {
        bounds.left + bounds.width / 2.f,
        bounds.top + bounds.height / 2.f
    };
}