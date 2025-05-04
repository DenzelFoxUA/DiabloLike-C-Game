#include "PlayerCharacterMesh.h"

Vector2f PlayerCharacterMesh::GetCenter() const {
    sf::FloatRect bounds = this->sprite.getGlobalBounds();
    return {
        bounds.left + bounds.width / 2.f,
        bounds.top + bounds.height / 2.f
    };
}

Vector2f PlayerCharacterMesh::GetPosition() const {
    return this->sprite.getPosition();
}