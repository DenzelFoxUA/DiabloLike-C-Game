﻿
#include <SFML/Graphics.hpp>
#include "BaseMesh.h"
#include "CharacterMesh.h"
#include <iostream>
#include "PathsConfig.h"
#include "LadyUnit.h"
#include "UnitBuilder.h"
#include "SkeletonUnit.h"
#include "ProjectileModels.h"
#include "Forest.h"
#include "Attributes.h"

using namespace std;
using namespace ArrowsPaths;

int main()
{
    const int windowHeight = 1080;
    const int windowWidth = 1920;

    RenderWindow window(VideoMode(windowWidth, windowHeight), "Diablo-like Games");
    ProjectileModels::LoadTextures();

    //global container for all projectiles
    ProjectilesContainer projContainer;

    //Creating main character
    string nameMainChar = "Eva";
    auto arrowSimple = std::make_unique<Arrow>(ProjectileType::ArrowMagic, 152, 80.f, false);

    UnitBuilder<LadyUnit, LadyArcher> playerUnitBuilder;

    auto playerUnit = playerUnitBuilder
        .SetTexturesPrimary(JSONTextureLoader::
            LoadTextureMeta(JSON_TEXTURES_PATH + LADYARCHER_JSON_TEXTURES_FILE))
        .SetTexturesSecondary(JSONTextureLoader::
            LoadTextureMeta(JSON_TEXTURES_PATH + LADYSWORD_JSON_TEXTURES_FILE))
        .SetSpawnPoint(SpawnPoint{ 1000,900 })
        .SetProjectile(ProjectileType::ArrowSimple)
        .SetEntity(LadyArcher(0, nameMainChar, 2500.f, 500.f, 500.f, PlayerStartAttributes::LADY))
        .SetCooldown(1.f)
        .SetContainer(&projContainer)
        .SetDeathAnimationTime(2.5f)
        .SetHPRegenerationRate(0.f)
        .SetStaminaRegenerationRate(15.f)
        .SetManaRegenerationRate(0.f)
        .SetSpeed(400.f)
        .SetAnimDuration(0.05f)
        .Build();

    playerUnit->SetSpeed(120.f);
    
    //levels
    string forestLevelTextures = "JSONData/textures/Levels/LevelForest.json";
    ForestLevel<LadyUnit> forest = ForestLevel<LadyUnit>(forestLevelTextures, window, 
        &*playerUnit,&projContainer, 15.f, 128.f,256.f);


    forest.Render(windowHeight,windowWidth);

    return 0;
}


