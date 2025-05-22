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


using namespace std;


template <typename UnitT>
class Level
{
protected:

    const string levelName = "Abstract";

    vector<unique_ptr<IBaseUnit>> enemies;
    Sprite ground;
    UnitT* mainCharacter;
    ProjectilesContainer* projContainer;
    RenderWindow& window;

    virtual void DrawGround(RenderWindow& window, Sprite* sprite, float tileWidth, float tileHeight,
        float offsetX = 0.f, float offsetY = 0.f) = 0;

    

public:
    Level() = delete;
    Level(RenderWindow& window,
        UnitT* mainCharacter, ProjectilesContainer* projContainer) : 
        window(window),
        mainCharacter(mainCharacter), 
        projContainer(projContainer)
	{
        
	}

    virtual void Render(int windowHeight, int windowWidth) = 0;

};