#pragma once
#include "PlayerCharacterMesh.h"
#include "Meshes/Weapons/ArrowMesh.h"
#include <SFML/Graphics.hpp>

class LadyArcherMesh : public PlayerCharacterMesh
{
protected:
    std::vector<ArrowMesh> arrows;
    Texture arrowTexture;


public:

    LadyArcherMesh() = delete;
    LadyArcherMesh(vector<TextureMeta> texturePathList,
        std::vector<ArrowMesh>& arrowsRef, Texture arrowTexture, SpawnPoint spawnP) 
        : PlayerCharacterMesh(texturePathList, spawnP), arrowTexture(arrowTexture) {
    };

    void Update(float deltaTime, const sf::RenderWindow& window) override;
    void Draw(sf::RenderWindow& window) override;

    vector<ArrowMesh>& Arrows();
    Texture& ArrowTex();

    //bool& IsCharged() override;
    //bool& IsChargingAttack() override;
    //bool& PendingNormalAttack() override;
    //bool& PendingChargedAttack() override;

    //float& ChargeTime() override;
    //float& AttackTimer() override;

    //Vector2f& PendingDirection() override;
    //float& PendingChargeTime() override;
    //const float AttackDelay() override;
    //const float MaxChargeTime() override;

    void Shoot(sf::Texture& arrowTexture, sf::Vector2f direction);
    void ShootCharged(sf::Texture& texture, sf::Vector2f direction, float charge);
};