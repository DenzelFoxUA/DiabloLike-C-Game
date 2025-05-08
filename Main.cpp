
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
#include "TexturesMetaConfig.h"
#include "LadyArcherUnit.h"
#include "UnitBuilder.h"
#include "SkeletonUnit.h"
#include "NPC_Controller.h"



using namespace std;
using namespace ArcherLadyCharacterPaths;
using namespace Arrows;
using namespace SkeletonCharacterPaths;


int main()
{
    const int windowHeight = 1080;
    const int windowWidth = 1920;
    const int tileHeight = 32,
              tileWidth = 32;

    string grassTexturePath = "textures/World/Grass/Pasto[1].png";

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Diablo_Like Game");

    sf::Texture grassTile;
    if (!grassTile.loadFromFile(grassTexturePath)) {
        std::cout << "Не вдалося завантажити фон!\n";
    }

    Texture arrowTexture;
    Texture powerArrowTexture;
    if (!arrowTexture.loadFromFile(ARROW_TEXTURES_SIMPLE_PATH + ARROW_TEXTURES_SIMPLE_FILE))
    {
        std::cout << "Error loading arrow texture!\n";
    }

    if (!powerArrowTexture.loadFromFile(ARROW_TEXTURES_EFFECTS_PATH + ARROW_TEXTURES_FIRE_FILE))
    {
        std::cout << "Error loading arrow texture!\n";
    }

    //"C:\Users\denze\source\repos\DiabloLikeGame\x64\Debug\textures\Weapons\fire_arrow.png"

    sf::Sprite grassSprite;
    grassSprite.setTexture(grassTile);

    ProjectilesContainer projContainer;

    string nameMainChar = "Eva";
    //Arrow arrowSimple = Arrow(ProjectileType::ArrowMagic,152,80.f, false);
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

    auto archerEva = ladyArcherBuilder.SetId(0)
        .SetTextures(LadyArcherMeta())
        .SetSpawnPoint(SpawnPoint{ 1000,400 })
        .SetArrow(ProjectileType::ArrowSimple)
        .SetEntity(LadyArcher(nameMainChar, 1600.f, 1000.f, mainCharAttributes))
        .SetCooldown(0.f)
        .SetContainer(&projContainer)
        .Build();

    /*skeletons.emplace_back(
        ladyArcherBuilder.SetId(-1)
        .SetTextures(LadyArcherMeta())
        .SetProjectileTexture(arrowTexture)
        .SetSpawnPoint(SpawnPoint{ 1000,400 })
        .SetArrow(arrowSimple)
        .SetEntity(LadyArcher(nameMainChar, 1600.f, 1000.f))
        .SetCooldown(0.f)
        .Build()
    );*/

    for (int i = 1, x = 100, y = 100; i <= 3; i++)
    {
        UnitBuilder<SkeletonUnit, Skeleton> skeletonBuilder;
        auto skeleton1 = skeletonBuilder.SetId(i)
            .SetTextures(SkeletonTexturesMeta())
            .SetSpawnPoint(SpawnPoint{ x, y })
            .SetArrow(ProjectileType::None)
            .SetEntity(Skeleton(400.f, 200.f, skeletonsAttribute))
            .SetCooldown(2.f)
            .Build();
        skeleton1->SetAnimationDuration(0.4f);
        skeleton1->SetSpeed(80.f);

        skeletons.emplace_back(move(skeleton1));

        if (i % 2 == 0)
            x += x;
        else
            y += y;


        skeletonBuilder.Reset();
    }

    //vector<IController*> _enemiesRefs;
    //for (auto& enemie : skeletons)
    //{
    //    _enemiesRefs.emplace_back(&enemie->GetController());
    //}



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
        /*archerEva->UpdateArrows(dt, window, _enemiesRefs);*/

        for (auto& skeleton : skeletons)
        {
            if (skeleton->IsDead()) continue;


            skeleton->GetController().HandleBehavior(archerEva->GetPosition(), archerEva->GetEntity(), dt);
            skeleton->GetController().Update(dt, window);
        }

        projContainer.Update(dt,enemyPointers);


        window.clear();

        for (int y = 0; y < windowHeight; y += tileHeight) {
            for (int x = 0; x < windowWidth; x += tileWidth) {
                grassSprite.setPosition(x, y);
                window.draw(grassSprite);
            }
        }

        for (auto& skeleton : skeletons)
        {
            skeleton->Draw(window);
        } 

        archerEva->Draw(window);
        projContainer.DrawAll(window);
        window.display();
    }

    return 0;
}
