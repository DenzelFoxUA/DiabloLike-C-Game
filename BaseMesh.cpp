
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


Vector2f BaseMesh::MoveToPoint(Vector2f point) {
    float length = std::sqrt(point.x * point.x + point.y * point.y);
    if (length != 0)
        return point / length;
    else
        return sf::Vector2f(0.f, 0.f);
}

void BaseMesh::SetAnimationDuration(float newVal)
{
    this->animation.SetFrameDuration(newVal);
}