#pragma once
#include "PlayerCharacterMesh.h"
#include "Meshes/Weapons/ArrowMesh.h"
#include <SFML/Graphics.hpp>
#include "Projectile.h"
#include "Arrow.h"
#include "ProjectileController.h"
#include "ArrowController.h"

class LadyArcherMesh : public PlayerCharacterMesh
{
protected:


public:

    LadyArcherMesh() = delete;
    LadyArcherMesh(vector<TextureMeta> texturePathList, SpawnPoint spawnP)
        : PlayerCharacterMesh(texturePathList, spawnP) {
    };

    void Update(float deltaTime, const sf::RenderWindow& window) override;
    void Draw(sf::RenderWindow& window) override;
    
};