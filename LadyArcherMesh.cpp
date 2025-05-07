#include "LadyArcherMesh.h"

void LadyArcherMesh::Draw(sf::RenderWindow& window)
{
    PlayerCharacterMesh::Draw(window);  
}

void LadyArcherMesh::Update(float deltaTime, const sf::RenderWindow& window)
{
    PlayerCharacterMesh::Update(deltaTime, window);

    if (isAttacking) {
        attackTimer += deltaTime;

        if (attackTimer >= attackDelay) {
            isAttacking = false;
            currentState = CharacterState::Idle;

            int height = texturesData[TextureCategory::Idle].frameHeight;
            int width = texturesData[TextureCategory::Idle].frameWidth;
            int columns = texturesData[TextureCategory::Idle].numberOfColumns;
            int frames = texturesData[TextureCategory::Idle].numberOfFrames;

            animation.SetSheet(&idleTextures[currentDir], width, height, columns, frames, true);
        }
    }
}

Texture& LadyArcherMesh::ArrowTex()
{
    return this->arrowTexture;
}
