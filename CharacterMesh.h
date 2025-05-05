#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include <map>
#include <vector>
#include "Meshes/Weapons/ArrowMesh.h"
#include "BaseMesh.h"
#include <iostream>

using namespace std;
using namespace sf;

enum class CharacterState 
{
    Idle,
    Run,
    Attack,
    Cast,
    Hurt,
    Dead
};

enum AttackType
{
    Ranged,
    Magic,
    Melee
};

class CharacterMesh : public BaseMesh
{
protected:

    Texture* activeTexture = nullptr;

    bool chargingAttack = false;
    float chargeTime = 0.f;
    const float maxChargeTime = 2.f;
    bool attackAlreadyCharged = false;

    bool pendingNormalAttack = false;
    bool pendingChargedAttack = false;
    float pendingChargeTime = 0.f;
    sf::Vector2f pendingDirection = { 0.f, 0.f };

    float attackTimer = 0.f;
    const float attackDelay = 0.7f;

    map<TextureCategory,TextureMeta> texturesData;
    map<Direction, sf::Texture> idleTextures;
    map<Direction, sf::Texture> movementTextures;
    map<Direction, sf::Texture> attackTextures;
    map<Direction, sf::Texture> deathTextures;

    Direction currentDir = Direction::Right;
    Direction lastDir = Direction::Right;

    CharacterState currentState = CharacterState::Idle;
    CharacterState previousState = CharacterState::Idle;

    bool isAttacking = false;
    bool isMoving = false;
    bool isDead = false;
    float moveSpeed = 250.f;
    std::vector<ArrowMesh> arrows;
    
    void LoadTextures(map<Direction, Texture>& target, string commonPath, string nameOfTexture) override;

public:
    CharacterMesh() = delete;
    CharacterMesh(vector<TextureMeta> texturePathList, SpawnPoint spawnP) : BaseMesh(texturePathList, spawnP)
    {
        for (const auto& texture : texturePathList)
        {
            texturesData.emplace(texture.category, texture);

            auto& target = (texture.category == TextureCategory::Idle) ? this->idleTextures :
                (texture.category == TextureCategory::Move) ? this->movementTextures :
                (texture.category == TextureCategory::Death) ? this->deathTextures :
                this->attackTextures;

            LoadTextures(target, texture.folderPath, texture.fileName);
        }
        
        int height = texturesData[TextureCategory::Idle].frameHeight;
        int width = texturesData[TextureCategory::Idle].frameWidth;
        int columns = texturesData[TextureCategory::Idle].numberOfColumns;
        int frames = texturesData[TextureCategory::Idle].numberOfFrames;

        sprite.setPosition(spawnP.x, spawnP.y);
        animation.SetSheet(&idleTextures[currentDir], width, height, columns, frames);
    }

    
    virtual float& GetSpeed();

    virtual Direction& CurrentDir();

    virtual Direction& LastDir();
    virtual bool& IsAttacking();
    virtual Sprite& Sprite();

    virtual CharacterState& CurrentState();
    virtual CharacterState& PreviousState();

    virtual map<Direction, sf::Texture>& IdleTextures();
    virtual map<Direction, sf::Texture>& MoveTextures();
    virtual map<Direction, sf::Texture>& AttackTextures();
    virtual map<Direction, sf::Texture>& DeathTextures();

    virtual Animation& Animation();
    virtual TextureMeta& TextureData(TextureCategory category);

    void Update(float deltaTime, const sf::RenderWindow& window) override;
    void Draw(sf::RenderWindow& window) override;

    virtual bool& IsCharged();
    virtual bool& IsMoving();
    virtual bool& IsDead()
    {
        return this->isDead;
    }
    virtual bool& IsChargingAttack();
    virtual bool& PendingNormalAttack();
    virtual bool& PendingChargedAttack();

    virtual float& ChargeTime();
    virtual float& AttackTimer();

    virtual Vector2f& PendingDirection();
    virtual float& PendingChargeTime();
    virtual const float AttackDelay();
    virtual const float MaxChargeTime();

    ~CharacterMesh()
    {
        cout << "Character mesh destroyed!" << endl;
        delete activeTexture;
    }
};
