
#include <SFML/Graphics.hpp>
#include "BaseMesh.h"
#include "CharacterMesh.h"
#include "LadyArcherMesh.h"
#include "LadyArcher.h"
#include "LadyArcherController.h"
#include <iostream>

using namespace std;

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

    sf::Sprite grassSprite;
    grassSprite.setTexture(grassTile);

    sf::Texture arrowTexture;
    if (!arrowTexture.loadFromFile("textures/Weapons/arrow.png"))
    {
        std::cout << "Error loading arrow texture!\n";
        return -1;
    }

    std::vector<ArrowMesh> arrows;

    TextureMeta ladyArcherIdle;
    ladyArcherIdle.category = TextureCategory::Idle;
    ladyArcherIdle.fileName = "Idle_Bow_Body";
    ladyArcherIdle.folderPath = "textures/Characters/ArcherLady/Idle_Bow/";
    ladyArcherIdle.frameHeight = 180;
    ladyArcherIdle.frameWidth = 180;
    ladyArcherIdle.numberOfColumns = 4;
    ladyArcherIdle.numberOfFrames = 16;

    TextureMeta ladyArcherAttack;
    ladyArcherAttack.category = TextureCategory::Attack;
    ladyArcherAttack.fileName = "Attack_Bow_Body";
    ladyArcherAttack.folderPath = "textures/Characters/ArcherLady/Attack_Bow/";
    ladyArcherAttack.frameHeight = 180;
    ladyArcherAttack.frameWidth = 180;
    ladyArcherAttack.numberOfColumns = 6;
    ladyArcherAttack.numberOfFrames = 24;

    TextureMeta ladyArcherMove;
    ladyArcherMove.category = TextureCategory::Move;
    ladyArcherMove.fileName = "Run_Bow_Body";
    ladyArcherMove.folderPath = "textures/Characters/ArcherLady/Run_Bow/";
    ladyArcherMove.frameHeight = 180;
    ladyArcherMove.frameWidth = 180;
    ladyArcherMove.numberOfColumns = 5;
    ladyArcherMove.numberOfFrames = 20;

    vector<TextureMeta> ladyArcherTextures = { ladyArcherIdle,ladyArcherAttack,ladyArcherMove };
    string name = "Eva";
    LadyArcherMesh * heroModel = new LadyArcherMesh(ladyArcherTextures, arrows, arrowTexture);
    LadyArcher * hero = new LadyArcher(name,1600.f,1000.f);
    LadyArcherController* heroControl = new LadyArcherController(heroModel, hero);
    

    sf::Clock clock;

    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            heroControl->HandleEvent(event, window);
        }

        heroControl->HandleInput(dt);
        heroModel->Update(dt,window);

        window.clear();

        for (int y = 0; y < windowHeight; y += tileHeight) {
            for (int x = 0; x < windowWidth; x += tileWidth) {
                grassSprite.setPosition(x, y);
                window.draw(grassSprite);
            }
        }

        heroModel->Draw(window);

        auto& arrowList = heroModel->Arrows();
        for (auto it = arrowList.begin(); it != arrowList.end(); )
        {
            it->Update(dt);
            if (it->IsDead()) {
                it = arrowList.erase(it);
            }
            else {
                ++it;
            }
        }

        window.display();
    }

    return 0;
}
