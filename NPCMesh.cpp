#include "NPCMesh.h"

Vector2f NPCMesh::GetCenter() const {
    sf::FloatRect bounds = this->sprite.getGlobalBounds();
    return {
        bounds.left + bounds.width / 2.f,
        bounds.top + bounds.height / 2.f
    };
}

Vector2f NPCMesh::GetPosition() const {
    return this->sprite.getPosition();
}