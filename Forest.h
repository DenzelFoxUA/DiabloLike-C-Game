#pragma once
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Level.h"

using namespace std;
template <typename UnitT>
class ForestLevel : public Level<UnitT>
{
protected:

    const string levelName = "Forest Level";
    map<string, Texture> levelTextures;

    void DrawGround(RenderWindow& window, Sprite* sprite, float tileWidth, float tileHeight,
        float offsetX = 0.f, float offsetY = 0.f) override
    {
        for (int y = 0; y <= window.getSize().y + tileHeight*2; y += tileHeight) {
            for (int x = 0; x <= window.getSize().x + tileHeight*2; x += tileWidth) {
                sprite->setPosition(x + offsetX, y + offsetY);
                window.draw(*sprite);
            }
        }
    }

public:
    ForestLevel(string levelTexturesPath, RenderWindow& window,
        UnitT* mainCharacter, ProjectilesContainer* projContainer) 
        : Level<LadyUnit>(window,mainCharacter,projContainer)
    {
        levelTextures = JSONTextureLoader::LoadLevelTextures(levelTexturesPath);
    }

    void Render(int windowHeight, int windowWidth) override
    {
        const int tileHeight = 128,
            tileWidth = 256;

        sf::Texture* grassTile = &this->levelTextures["DarkGrass"];

        sf::Sprite grassSprite;
        grassSprite.setTexture(*grassTile);

        //creating static meshes -------------------------------------------------------------
        SmallHouse house3 = SmallHouse(levelTextures["SmallHouse3"], SpawnPoint{ 100,600 });

        vector<Tree> trees = {
            Tree(levelTextures["Tree1"], SpawnPoint{1500,320}),
            Tree(levelTextures["Tree1"], SpawnPoint{ 600,180 }),
            Tree(levelTextures["Tree2"], SpawnPoint{ 1000,480 }),
            Tree(levelTextures["Tree2"], SpawnPoint{ 200,180 })
        };
        // -----------------------------------------------------------------------------------

        //creating boundries for static objects to prevent chars walk through it
        ForbiddenZones::GetForbiddenZones().push_back(house3.GetMapBounds());
        for (auto& object : trees)
        {
            ForbiddenZones::GetForbiddenZones().push_back(object.GetMapBounds());
        }
        //--------------------------------------------------------------------------------------

        for (int i = 1; i <= 10; i++)
        {
            Vector2f pos = this->GetRandomSpawnPosition(ForbiddenZones::GetForbiddenZones(),
                this->window.getSize().x, this->window.getSize().y);

            UnitBuilder<SkeletonUnit, Skeleton> skeletonBuilder;
            auto skeleton = skeletonBuilder
                .SetTexturesPrimary(JSONTextureLoader::
                    LoadTextureMeta(JSON_TEXTURES_PATH + SKELETON_BASIC_JSON_TEXTURES_FILE))
                .SetSpawnPoint(SpawnPoint{ pos.x, pos.y })
                .SetProjectile(ProjectileType::None)
                .SetEntity(Skeleton(i,"Skeleton", 600.f, 200.f, 0.f, BasicEnemiesAttributes::SKELETON, 900.f, 100))
                .SetCooldown(3.f)
                .SetSpeed(110.f)
                .SetAnimDuration(1.f)
                .SetDeathAnimationTime(3.5f)
                .SetHPRegenerationRate(0.f)
                .SetManaRegenerationRate(0.f)
                .SetStaminaRegenerationRate(20.f)
                .SetAnimDuration(0.4f)
                .Build();

            this->enemies.emplace_back(move(skeleton));

            skeletonBuilder.Reset();
        }
        //--------------------------------------------------------------------------------------
        //adding skeletons to player global enemy list
        for (auto& enemy : this->enemies)
        {
            Enemies::AddNPCEnemy(enemy->GetEntity().GetId(), enemy.get());
        }
        //--------------------------------------------------------------------------------------
        //adding player to global lis of npc enemies
        Enemies::AddPlayerEnemy(this->mainCharacter->GetEntity().GetId(), this->mainCharacter);
        //--------------------------------------------------------------------------------------

        int enemiesIterator = 0;

        //rendering start
        sf::Clock clock;

        while (this->window.isOpen())
        {
            Enemies::Update();
            float dt = clock.restart().asSeconds();

            std::vector<IBaseUnit*> enemyPointers;
            for (auto& enemy : this->spawnedEnemies)
                enemyPointers.push_back(enemy.get());

            sf::Event event;
            while (this->window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    this->window.close();

                this->mainCharacter->HandleMouseEvent(event, this->window, dt);
            }

            this->mainCharacter->HandleInput(dt);
            this->mainCharacter->Update(dt, this->window);

            for (auto& enemy : enemyPointers)
            {
                this->mainCharacter->SubscribeOnEnemy(enemy->GetEntity());
            }

            for (auto& enemy : this->spawnedEnemies)
            {
                if (enemy->IsDead()) continue;

                this->mainCharacter->HandleBehavior(this->mainCharacter, dt);
                enemy->Update(dt, this->window);
            }

            this->projContainer->Update(dt, enemyPointers);
             
            this->window.clear();

            float offsetX = -1 * tileHeight;
            float offsetY = -1 * tileWidth;

            DrawGround(this->window, &grassSprite, tileWidth, tileHeight, offsetX, offsetY);

            house3.DrawBottom(this->window);




            if (enemiesIterator == 0 ||
                (enemiesIterator < this->enemies.size() && this->spawnTik >= this->spawnTime))
            {
                this->SpawnEnemy(enemiesIterator);
                this->spawnTik = 0.f;

                enemiesIterator++;
            }
            
            this->spawnTik += dt;

            for (auto& enemy : this->spawnedEnemies)
            {
                enemy->Draw(this->window);
            }

            this->mainCharacter->Draw(this->window);
            this->projContainer->DrawAll(this->window);

            house3.DrawTop(this->window);

            for (auto& mesh : trees)
            {
                mesh.DrawTop(this->window);
                mesh.DrawBottom(this->window);
            }

            this->window.display();
        }
    }
    

};
