#include "LadyArcherMesh.h"

void LadyArcherMesh::Draw(sf::RenderWindow& window)
{
    PlayerCharacterMesh::Draw(window);  
}

void LadyArcherMesh::Update(float deltaTime, const sf::RenderWindow& window, float hp, float hpMax,
    float stamina, float staminaMax, float mana, float manaMax)
{
    PlayerCharacterMesh::Update(deltaTime, window,hp,hpMax,stamina,staminaMax,mana,manaMax);

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

