#pragma once
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "PathsConfig.h"
#include "IBaseUnit.h"
#include "JsonTextureLoader.h"
#include "StaticMesh.h"
#include "BaseMesh.h"
#include "ForbiddenZonesConfig.h"
#include "ProjectileManager.h"
#include "Arrow.h"
#include "SmallHouse.h"
#include "Tree.h"
#include "SkeletonUnit.h"
#include "UnitBuilder.h"
#include "Enemies.h"
#include "LadyUnit.h"
#include "ProjectileModels.h"
#include "Attributes.h"
#include "Functions.h"


using namespace std;


template <typename UnitT>
class Level
{
protected:

    const float tileHeight;
    const float tileWidth;

    float spawnTik = 0.f;
    float spawnTime = 10.f;

    const string levelName = "Abstract";

    vector<unique_ptr<IBaseUnit>> enemies;
    vector<unique_ptr<IBaseUnit>> spawnedEnemies;

    Sprite ground;
    UnitT* mainCharacter;
    ProjectilesContainer* projContainer;
    RenderWindow& window;

    virtual void DrawGround(RenderWindow& window, Sprite* sprite, float tileWidth, float tileHeight,
        float offsetX = 0.f, float offsetY = 0.f) = 0;

    void SpawnEnemy(int index)
    {
       this->spawnedEnemies.emplace_back(move(this->enemies[index]));
    }

    Vector2f GetRandomSpawnPosition(const vector<FloatRect>& forbiddenZones,
        float windowWidth, float windowHeight)
    {
        Vector2f pos;
        bool valid = false;

        while (!valid)
        {
            pos.x = RandomGenerator::RandomFloat(50.f, windowWidth);
            pos.y = RandomGenerator::RandomFloat(50.f, windowHeight);

            valid = true;
            for (const auto& zone : forbiddenZones)
            {
                if (zone.contains(pos))
                {
                    valid = false;
                    break;
                }
            }
        }

        return pos;
    }

public:
    Level() = delete;
    Level(RenderWindow& window,
        UnitT* mainCharacter, ProjectilesContainer* projContainer, 
        float spawnTime, float tileH, float tileW) : 
        window(window),
        mainCharacter(mainCharacter), 
        projContainer(projContainer), 
        spawnTime(spawnTime),
        tileHeight(tileH),
        tileWidth(tileW)
    {}

    virtual void Render(int windowHeight, int windowWidth) = 0;

    ~Level()
    {
        ForbiddenZones::GetForbiddenZones().clear();
    }
};