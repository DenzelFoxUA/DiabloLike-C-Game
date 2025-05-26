
#pragma once
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Level.h"

using namespace std;
using namespace sf;
using namespace sf::Glsl;

template <typename UnitT>
class ForestLevel : public Level<UnitT>
{

protected:

    const string levelName = "Forest Level";
    map<string, Texture> levelTextures;

    void DrawGround(RenderWindow& window, Sprite* sprite, float tileWidth, float tileHeight,
        float offsetX = 0.f, float offsetY = 0.f) override
    {
        for (int y = 0; y <= window.getSize().y + tileHeight * 2.f; y += tileHeight) {
            for (int x = 0; x <= window.getSize().x + tileHeight * 2.f; x += tileWidth) {
                sprite->setPosition(x + offsetX, y + offsetY);
                window.draw(*sprite);
            }
        }
    }

public:
    ForestLevel(string levelTexturesPath, RenderWindow& window,
        UnitT* mainCharacter, ProjectilesContainer* projContainer,
        float spawnTime, float tileH, float tileW)
        : Level<LadyUnit>(window, mainCharacter, projContainer,spawnTime, tileH, tileW)
    {
        levelTextures = JSONTextureLoader::LoadLevelTextures(levelTexturesPath);

    }

    void Render(int windowHeight, int windowWidth) override
    {
        //створенн€ земл≥
        sf::Texture* grassTile = &this->levelTextures["DarkGrass"];
        sf::Sprite grassSprite;
        grassSprite.setTexture(*grassTile);

        //додаванн€ статичних моделей
        SmallHouse house3 = SmallHouse(levelTextures["SmallHouse3"], SpawnPoint{ 100,600 });

        vector<Tree> trees = {
            Tree(levelTextures["Tree1"], SpawnPoint{1500,320}),
            Tree(levelTextures["Tree1"], SpawnPoint{600,180}),
            Tree(levelTextures["Tree2"], SpawnPoint{1000,480}),
            Tree(levelTextures["Tree2"], SpawnPoint{200,180})
        };

        //додаванн€ зон статичних моделей де персонаж≥ ≥ монстри не можуть ходити
        ForbiddenZones::GetForbiddenZones().push_back(house3.GetMapBounds());
        for (auto& object : trees)
            ForbiddenZones::GetForbiddenZones().push_back(object.GetMapBounds());

        //генерац≥€ скелет≥в з налаштуванн€м
        for (int i = 1; i <= 10; i++) {
            Vector2f pos = this->GetRandomSpawnPosition(ForbiddenZones::GetForbiddenZones(),
                this->window.getSize().x, this->window.getSize().y);

            UnitBuilder<SkeletonUnit, Skeleton> skeletonBuilder;
            auto skeleton = skeletonBuilder
                .SetTexturesPrimary(JSONTextureLoader::LoadTextureMeta(JSON_TEXTURES_PATH + SKELETON_BASIC_JSON_TEXTURES_FILE))
                .SetSpawnPoint(SpawnPoint{ pos.x, pos.y })
                .SetProjectile(ProjectileType::None)
                .SetEntity(Skeleton(i, "Skeleton", 600.f, 200.f, 0.f, BasicEnemiesAttributes::SKELETON, 900.f, 100))
                .SetCooldown(3.f)
                .SetSpeed(110.f)
                .SetAnimDuration(0.12f)
                .SetDeathAnimationTime(3.5f)
                .SetHPRegenerationRate(0.f)
                .SetManaRegenerationRate(0.f)
                .SetStaminaRegenerationRate(20.f)
                .Build();

            this->enemies.emplace_back(move(skeleton));
            skeletonBuilder.Reset();
        }

        //додаванн€ скелет≥в до списку ворог≥в
        for (auto& enemy : this->enemies)
            Enemies::AddNPCEnemy(enemy->GetEntity().GetId(), enemy.get());

        //додаванн€ гравц€ €к противника скелет≥в
        Enemies::AddPlayerEnemy(this->mainCharacter->GetEntity().GetId(), this->mainCharacter);

        //≥тератор ворог≥в дл€ Spawn методу
        int enemiesIterator = 0;

        //шейдер прозорост≥ на статичн≥ об"Їкти, щоб було видно персонажа за домами ≥ тд
        sf::Shader shader;
        if (!shader.loadFromFile("transparent_circle.frag", sf::Shader::Fragment)) {
            std::cerr << "FAILED TO LOAD SHADER\n";
        }

        //запуск в≥кна
        sf::Clock clock;

        while (this->window.isOpen()) 
        {
            Enemies::Update();
            float dt = clock.restart().asSeconds();

            std::vector<IBaseUnit*> enemyPointers;
            for (auto& enemy : this->spawnedEnemies)
                enemyPointers.push_back(enemy.get());

            sf::Event event;
            while (this->window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    this->window.close();

                this->mainCharacter->HandleMouseEvent(event, this->window, dt);
            }

            this->mainCharacter->HandleInput(dt);
            this->mainCharacter->Update(dt, this->window);

            for (auto& enemy : enemyPointers)
                this->mainCharacter->SubscribeOnEnemy(enemy->GetEntity());

            for (auto& enemy : this->spawnedEnemies) {
                if (enemy->IsDead()) continue;
                this->mainCharacter->HandleBehavior(this->mainCharacter, dt);
                enemy->Update(dt, this->window);
            }

            this->projContainer->Update(dt, enemyPointers);

            this->window.setView(this->window.getDefaultView());
            sf::Vector2f worldPos = this->mainCharacter->GetCenter();
            sf::Vector2f screenPos = static_cast<sf::Vector2f>(
                this->window.mapCoordsToPixel(worldPos, this->window.getView())
                );
            screenPos.y = this->window.getSize().y - screenPos.y;

            this->window.clear();

            float offsetX = -1.f * this->tileHeight;
            float offsetY = -1.f * this->tileWidth;

            DrawGround(this->window, &grassSprite, this->tileWidth, 
                this->tileHeight, offsetX, offsetY);
            house3.DrawBottom(this->window);

            if (enemiesIterator == 0 ||
                (enemiesIterator < this->enemies.size() && this->spawnTik >= this->spawnTime)) {
                this->SpawnEnemy(enemiesIterator);
                this->spawnTik = 0.f;
                enemiesIterator++;
            }

            this->spawnTik += dt;

            for (auto& enemy : this->spawnedEnemies)
                enemy->Draw(this->window);

            this->mainCharacter->Draw(this->window);
            this->projContainer->DrawAll(this->window);

            shader.setUniform("texture", sf::Shader::CurrentTexture);
            shader.setUniform("playerPos", screenPos);
            shader.setUniform("radius", 90.f);

            shader.setUniform("spritePos", static_cast<Vec2>(house3.GetTopSprite().getPosition()));
            house3.DrawTop(this->window, shader);

            for (auto& mesh : trees) {
                shader.setUniform("spritePos", static_cast<Vec2>(mesh.GetTopSprite().getPosition()));
                mesh.DrawTop(this->window, shader);
                mesh.DrawBottom(this->window);
            }

            this->window.display();
        }
    }
};

