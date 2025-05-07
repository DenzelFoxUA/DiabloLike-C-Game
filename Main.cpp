
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


using namespace std;
using namespace ArcherLadyCharacterPaths;
using namespace Arrows;
using namespace SkeletonCharacterPaths;

//LadyArcherMesh BuildLadyArcherMesh(SpawnPoint);
//SkeletonMesh BuildSkeletonMesh(SpawnPoint, float, float);
//
//template <typename CharMesh>
//CharMesh BuildCharacterMesh(const vector<TextureMeta>&, Texture, SpawnPoint);

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
    if (!arrowTexture.loadFromFile(ARROW_TEXTURES_SIMPLE_PATH + ARROW_TEXTURES_SIMPLE_FILE))
    {
        std::cout << "Error loading arrow texture!\n";
    }

    sf::Sprite grassSprite;
    grassSprite.setTexture(grassTile);

    string name = "Eva";
    Arrow arrowSimple = Arrow(52, false);

    /*LadyArcherMesh heroModel = (BuildLadyArcherMesh(SpawnPoint{ 1000,400 }));
    LadyArcher hero = LadyArcher(name,1600.f,1000.f);
    LadyArcherController heroControl = LadyArcherController(heroModel, hero, arrowSimple);*/

   /* LadyArcherUnit archerEva = LadyArcherUnit(1, LadyArcherMeta(), arrowTexture, SpawnPoint{ 1000,400 }, 
        LadyArcher(name, 1600.f, 1000.f),arrowSimple);*/

    UnitBuilder<LadyArcherUnit, LadyArcherMesh, LadyArcher> ladyArcherBuilder;
    UnitBuilder<SkeletonUnit, SkeletonMesh, Skeleton> skeletonBuilder;

    auto archerEva = ladyArcherBuilder.SetId(1)
        .SetTextures(LadyArcherMeta())
        .SetProjectileTexture(arrowTexture)
        .SetSpawnPoint(SpawnPoint{ 1000,400 })
        .SetArrow(arrowSimple)
        .SetEntity(LadyArcher(name, 1600.f, 1000.f))
        .SetCooldown(0.f)
        .Build();

    auto skeleton1 = skeletonBuilder.SetId(1)
        .SetTextures(SkeletonTexturesMeta())
        .SetSpawnPoint(SpawnPoint{ 300,100 })
        .SetProjectileTexture(arrowTexture)
        .SetArrow(arrowSimple)
        .SetEntity(Skeleton(600.f, 500.f))
        .SetCooldown(2.f)
        .Build();

    skeleton1->SetAnimationDuration(0.4f);
    skeleton1->SetSpeed(80.f);
    
    //SkeletonMesh skeleton1Mesh = BuildSkeletonMesh(SpawnPoint{ 300,100 },80.f,0.4f);
    //Skeleton * skeleton1 = new Skeleton(600.f,500.f);
    //SkeletonController* skeleton1Conrol = new SkeletonController(&skeleton1Mesh, skeleton1, 1.f);

    sf::Clock clock;

    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            
            //heroControl.HandleEvent(event, window);

            archerEva->HandleEvent(event, window);
        }

        
        //heroControl.HandleInput(dt);
        archerEva->HandleInput(dt);
        //heroControl.Update(dt, window, skeleton1Mesh, *skeleton1);
        archerEva->Update(dt, window, skeleton1->GetMesh(), skeleton1->GetEntity());

        skeleton1->HandleBehavior(archerEva->GetPosition(), archerEva->GetEntity(), dt);
        skeleton1->Update(dt, window, archerEva->GetMesh(), archerEva->GetEntity());

        window.clear();

        for (int y = 0; y < windowHeight; y += tileHeight) {
            for (int x = 0; x < windowWidth; x += tileWidth) {
                grassSprite.setPosition(x, y);
                window.draw(grassSprite);
            }
        }

        skeleton1->Draw(window);

        //heroControl.Draw(window);

        archerEva->Draw(window);

        window.display();
    }

    return 0;
}

//unique_ptr<LadyArcherUnit> BuildLadyArcher(int id, 
//    string name, const vector<TextureMeta>& textures, Texture projectile, SpawnPoint sp, Arrow arrow)
//{
//    UnitBuilder<LadyArcherUnit, LadyArcherMesh, LadyArcher> builder;
//
//    return builder.SetId(id)
//        .SetTextures(textures)
//        .SetProjectileTexture(projectile)
//        .SetSpawnPoint(SpawnPoint{ 1000,400 })
//        .SetArrow(arrow)
//        .SetEntity(LadyArcher(name, 1600.f, 1000.f))
//        .Build();
//}


//SkeletonMesh BuildSkeletonMesh(SpawnPoint sp, float speed, float animationSpeed)
//{
//    vector<TextureMeta> skeletonTextures = SkeletonTexturesMeta();
//    auto skeletonMesh = BuildCharacterMesh<SkeletonMesh>(skeletonTextures, Texture(), sp);
//    skeletonMesh.SetSpeed(speed);
//    skeletonMesh.SetAnimationDuration(animationSpeed);
//    return skeletonMesh;
//}
//
//template <typename CharMesh>
//CharMesh BuildCharacterMesh(const vector<TextureMeta>& listOfTextures, Texture projectile, SpawnPoint sp)
//{ 
//    return CharMesh(listOfTextures, sp ,projectile);
//}
