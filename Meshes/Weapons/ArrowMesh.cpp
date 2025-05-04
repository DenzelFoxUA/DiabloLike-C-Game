#include "ArrowMesh.h"
#include <cmath>
#include <iostream>

ArrowMesh::ArrowMesh(sf::Texture& texture, sf::Vector2f startPos, sf::Vector2f direction)
{
    sprite.setTexture(texture);
    sprite.setPosition(startPos);
    this->direction = direction;
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

    UpdateVelocity();

    float angle = std::atan2(direction.y, direction.x) * 180.f / 3.14159265f;
    sprite.setRotation(angle);
}

void ArrowMesh::Update(float deltaTime)
{
    sprite.move(velocity * deltaTime);
    lifeTime -= deltaTime;
}

void ArrowMesh::Draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

bool ArrowMesh::IsOffScreen(sf::RenderWindow& window) const
{
    sf::Vector2f pos = sprite.getPosition();
    return pos.x < 0 || pos.x > window.getSize().x || pos.y < 0 || pos.y > window.getSize().y;
}

sf::FloatRect ArrowMesh::GetBounds() const
{
    return sprite.getGlobalBounds();
}

const sf::Texture* ArrowMesh::GetTexturePtr() const {
    return sprite.getTexture();
}

sf::Vector2f ArrowMesh::GetPosition() const {
    return sprite.getPosition();
}

bool ArrowMesh::IsDead() const {
    return lifeTime <= 0.f;
}

void ArrowMesh::SetSpeed(float newSpeed) {
    speed = newSpeed;

    UpdateVelocity();
}

ArrowMesh::ArrowMesh(const ArrowMesh& other)
{
    sprite = other.sprite;
    direction = other.direction;
    velocity = other.velocity;
    speed = other.speed;
    lifeTime = other.lifeTime;
}

ArrowMesh& ArrowMesh::operator=(const ArrowMesh& other)
{
    if (this != &other)
    {
        sprite = other.sprite;
        direction = other.direction;
        velocity = other.velocity;
        speed = other.speed;
        lifeTime = other.lifeTime;
    }
    return *this;
}

void ArrowMesh::UpdateVelocity()
{
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0.f)
        velocity = (direction / length) * speed;
    else
        velocity = { 0.f, 0.f };
}

