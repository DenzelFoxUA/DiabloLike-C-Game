
#include <SFML/Graphics.hpp>
#include "BaseMesh.h"
#include "CharacterMesh.h"
#include "LadyArcherMesh.h"
#include "LadyArcher.h"
#include "LadyArcherController.h"
#include "Skeleton.h"
#include "SkeletonMesh.h"
#include "SkeletonController.h"
#include <iostream>
#include "PathsConfig.h"
#include "LadyArcherUnit.h"
#include "UnitBuilder.h"
#include "SkeletonUnit.h"
#include "NPC_Controller.h"
#include "SmallHouse.h"
#include "ForbiddenZonesConfig.h"
#include "Tree.h"

using namespace std;
using namespace ArrowsPaths;
int main()
{
    const int windowHeight = 1080;
    const int windowWidth = 1920;
    const int tileHeight = 128,
              tileWidth = 256;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Diablo_Like Game");

    string grassTexturePath = "textures/World/Grass/tileable-1-grey.png";
    sf::Texture grassTile;
    if (!grassTile.loadFromFile(grassTexturePath)) {
        std::cout << "Error loading grass texture!\n";
    }

    sf::Sprite grassSprite;
    grassSprite.setTexture(grassTile);

    Texture arrowTexture;
    Texture powerArrowTexture;
    if (!arrowTexture.loadFromFile(ARROW_TEXTURES_SIMPLE_FOLDER + ARROW_TEXTURES_SIMPLE_FILE))
    {
        std::cout << "Error loading arrow texture!\n";
    }

    if (!powerArrowTexture.loadFromFile(ARROW_TEXTURES_EFFECTS_FOLDER + ARROW_TEXTURES_FIRE_FILE))
    {
        std::cout << "Error loading arrow texture!\n";
    }

    //loaded static textures for multiple use
    map<int, Texture> trees = JSONTextureLoader
        ::LoadStaticTextures(JSON_TEXTURES_PATH + TREES_JSON_TEXTURES_FILE);
    map<int, Texture> houses = JSONTextureLoader
        ::LoadStaticTextures(JSON_TEXTURES_PATH + HOUSES_TEXTURES_JSON_FILE);

    SmallHouse house3 = SmallHouse(houses[3], SpawnPoint{100,600});

    Tree tree = Tree(trees[1], SpawnPoint{1500,320});
    Tree tree2 = Tree(trees[1], SpawnPoint{ 600,180 });
    Tree tree3 = Tree(trees[2], SpawnPoint{ 1000,480 });
    Tree tree4 = Tree(trees[2], SpawnPoint{ 200,180 });

    //creating boundries
    ForbiddenZones::GetForbiddenZones().push_back(house3.GetMapBounds());
    ForbiddenZones::GetForbiddenZones().push_back(tree.GetMapBounds());
    ForbiddenZones::GetForbiddenZones().push_back(tree2.GetMapBounds());
    ForbiddenZones::GetForbiddenZones().push_back(tree3.GetMapBounds());
    ForbiddenZones::GetForbiddenZones().push_back(tree4.GetMapBounds());

    ProjectilesContainer projContainer;

    string nameMainChar = "Eva";
    auto arrowSimple = std::make_unique<Arrow>(ProjectileType::ArrowMagic, 152, 80.f, false);

    UnitBuilder<LadyArcherUnit,LadyArcher> ladyArcherBuilder;

    vector<unique_ptr<IBaseUnit>> skeletons;

    CharacterAttributes mainCharAttributes = {
        5, //str
        7, //agil
        5, //intell
        5, //willpower
        5 // luck
    };

    CharacterAttributes skeletonsAttribute = {
        5, //str
        4, //agil
        1, //intell
        1, //willpower
        2 // luck
    };

    auto archerEva = ladyArcherBuilder
        .SetTextures(JSONTextureLoader::
            LoadTextureMeta(JSON_TEXTURES_PATH + LADYARCHER_JSON_TEXTURES_FILE))
        .SetSpawnPoint(SpawnPoint{ 1000,400 })
        .SetArrow(ProjectileType::ArrowSimple)
        .SetEntity(LadyArcher(0,nameMainChar, 1600.f, 500.f, 200.f,mainCharAttributes))
        .SetCooldown(0.f)
        .SetContainer(&projContainer)
        .Build();

    for (int i = 1, x = 100, y = 100; i <= 3; i++)
    {
        UnitBuilder<SkeletonUnit, Skeleton> skeletonBuilder;
        auto skeleton1 = skeletonBuilder
            .SetTextures(JSONTextureLoader::
                LoadTextureMeta(JSON_TEXTURES_PATH + SKELETON_BASIC_JSON_TEXTURES_FILE))
            .SetSpawnPoint(SpawnPoint{ x, y })
            .SetArrow(ProjectileType::None)
            .SetEntity(Skeleton(i,600.f, 200.f,700.f,100.f, 100, skeletonsAttribute))
            .SetCooldown(2.f)
            .Build();
        skeleton1->SetAnimationDuration(0.3f);
        skeleton1->SetSpeed(180.f);

        skeletons.emplace_back(move(skeleton1));

        if (i % 2 == 0)
            x += x;
        else
            y += y;

        skeletonBuilder.Reset();
    }

    sf::Clock clock;

    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();
        std::vector<IBaseUnit*> enemyPointers;
        for (auto& enemy : skeletons)
            enemyPointers.push_back(enemy.get());


        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            archerEva->HandleEvent(event, window);
        }
        archerEva->HandleInput(dt);
        archerEva->Update(dt, window,arrowTexture,powerArrowTexture);

        for (auto& skeleton : enemyPointers)
        {
            archerEva->SubscribeOnEnemy(skeleton->GetEntity());
        }


        for (auto& skeleton : skeletons)
        {
            if (skeleton->IsDead()) continue;

            skeleton->GetController().HandleBehavior(archerEva->GetPosition(), archerEva->GetEntity(), dt);
            skeleton->GetController().Update(dt, window);
        }

        projContainer.Update(dt,enemyPointers);


        window.clear();


        float offsetX = -1 * tileHeight;
        float offsetY = -1 * tileWidth;
        

        for (int y = 0; y <= windowHeight + tileHeight; y += tileHeight) {
            for (int x = 0; x <= windowWidth + tileHeight; x += tileWidth) {
                grassSprite.setPosition(x + offsetX, y + offsetY);
                window.draw(grassSprite);
            }
        }

        house3.DrawBottom(window);

        for (auto& skeleton : skeletons)
        {
            skeleton->Draw(window);
        }
        
        archerEva->Draw(window);
        projContainer.DrawAll(window);
        
        house3.DrawTop(window);

        tree.DrawTop(window);
        tree.DrawBottom(window);
        tree2.DrawTop(window);
        tree2.DrawBottom(window);
        tree3.DrawTop(window);
        tree3.DrawBottom(window);
        tree4.DrawTop(window);
        tree4.DrawBottom(window);
        
        window.display();
    }

    return 0;
}
