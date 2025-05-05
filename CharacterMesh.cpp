#include <SFML/Graphics.hpp>
#include "CharacterMesh.h"
#include <iostream>

void CharacterMesh::LoadTextures(map<Direction, Texture>& target, string folderPath, string fileName) {
    std::map<Direction, std::string> paths = {
        {Direction::Right, folderPath + fileName + "_" + to_string((int)Direction::Right) + ".png"},
        {Direction::Up,    folderPath + fileName + "_" + to_string((int)Direction::Up) + ".png"},
        {Direction::Left,  folderPath + fileName + "_" + to_string((int)Direction::Left) + ".png"},
        {Direction::Down,  folderPath + fileName + "_" + to_string((int)Direction::Down) + ".png"},
    };
    for (const auto& [dir, path] : paths) {
        sf::Texture tex;
        if (!tex.loadFromFile(path)) {
            std::cout << "Failed to load: " << path << "\n";
        }
        target[dir] = tex;
    }
    this->sprite.setTexture(target[currentDir]);
}

void CharacterMesh::Update(float deltaTime, const sf::RenderWindow& window)
{
    animation.Update(deltaTime);
}

void CharacterMesh::Draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

float& CharacterMesh::GetSpeed()
{
    return this->moveSpeed;
}

Direction& CharacterMesh::CurrentDir()
{
    return this->currentDir;
}

Direction& CharacterMesh::LastDir()
{
    return this->lastDir;
}

bool& CharacterMesh::IsAttacking()
{
    return this->isAttacking;
}

Sprite& CharacterMesh::Sprite()
{
    return this->sprite;
}

CharacterState& CharacterMesh::CurrentState()
{
    return this->currentState;
}

CharacterState& CharacterMesh::PreviousState()
{
    return this->previousState;
}

map<Direction, sf::Texture>& CharacterMesh::IdleTextures()
{
    return this->idleTextures;
}

map<Direction, sf::Texture>& CharacterMesh::MoveTextures()
{
    return this->movementTextures;
}

map<Direction, sf::Texture>& CharacterMesh::AttackTextures()
{
    return this->attackTextures;
}

map<Direction, sf::Texture>& CharacterMesh::DeathTextures()
{
    return this->deathTextures;
}

Animation& CharacterMesh::Animation()
{
    return this->animation;
}

TextureMeta& CharacterMesh::TextureData(TextureCategory category)
{
    return texturesData[category];
}

bool& CharacterMesh::IsCharged()
{
    return this->attackAlreadyCharged;
}

bool& CharacterMesh::IsMoving()
{
    return this->isMoving;
}

bool& CharacterMesh::IsChargingAttack()
{
    return this->chargingAttack;
}

float& CharacterMesh::ChargeTime()
{
    return this->chargeTime;
}

float& CharacterMesh::AttackTimer()
{
    return this->attackTimer;
}

bool& CharacterMesh::PendingNormalAttack()
{
    return this->pendingNormalAttack;
}
bool& CharacterMesh::PendingChargedAttack()
{
    return this->pendingChargedAttack;
}

Vector2f& CharacterMesh::PendingDirection()
{
    return this->pendingDirection;
}

float& CharacterMesh::PendingChargeTime()
{
    return this->pendingChargeTime;
}

const float CharacterMesh::AttackDelay()
{
    return this->attackDelay;
}

const float CharacterMesh::MaxChargeTime()
{
    return this->maxChargeTime;
}
