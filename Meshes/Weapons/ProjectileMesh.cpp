#include "ProjectileMesh.h"
#include <cmath>
#include <iostream>

void ProjectileMesh::Update(float deltaTime)
{
    
    sprite.move(velocity * deltaTime);
    lifeTime -= deltaTime;
    //std::cout << "Updating arrow. Remaining time: " << lifeTime << "s\n";
}

void ProjectileMesh::Draw(sf::RenderWindow& window)
{
    window.draw(this->sprite);
}

bool ProjectileMesh::IsOffScreen(sf::RenderWindow& window) const
{
    sf::Vector2f pos = sprite.getPosition();
    return pos.x < 0 || pos.x > window.getSize().x || pos.y < 0 || pos.y > window.getSize().y;
}

sf::FloatRect ProjectileMesh::GetBounds() const
{
    return sprite.getGlobalBounds();
}

const sf::Texture* ProjectileMesh::GetTexturePtr() const {
    return sprite.getTexture();
}

sf::Vector2f ProjectileMesh::GetPosition() const {
    return sprite.getPosition();
}

bool ProjectileMesh::IsDead() const {
    return lifeTime <= 0.f;
}

void ProjectileMesh::MarkToDestroy() {
    
    this->lifeTime = 0.f;
}

void ProjectileMesh::SetSpeed(float newSpeed) {
    speed = newSpeed;

    UpdateVelocity();
}

ProjectileMesh::ProjectileMesh(const ProjectileMesh& other)
{
    sprite = other.sprite;
    direction = other.direction;
    velocity = other.velocity;
    speed = other.speed;
    lifeTime = other.lifeTime;
}

ProjectileMesh& ProjectileMesh::operator=(const ProjectileMesh& other)
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

void ProjectileMesh::UpdateVelocity()
{
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0.f)
        velocity = (direction / length) * speed;
    else
        velocity = { 0.f, 0.f };
}

void ProjectileMesh::EndLifeTime() {

    lifeTime = 0.f;

}

