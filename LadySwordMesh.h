#pragma once
#include "PlayerCharacterMesh.h"
#include "Meshes/Weapons/ArrowMesh.h"
#include <SFML/Graphics.hpp>
#include "Projectile.h"
#include "Arrow.h"


class LadySwordMesh : public PlayerCharacterMesh
{
protected:


public:

    LadySwordMesh() = delete;
    LadySwordMesh(vector<TextureMeta> texturePathList, SpawnPoint spawnP)
        : PlayerCharacterMesh(texturePathList, spawnP) {
    };

    void Update(float deltaTime, const sf::RenderWindow& window, float hp, float hpMax,
        float stamina, float staminaMax, float mana, float manaMax) override;
    void Draw(sf::RenderWindow& window) override;

};