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
    Hurt
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

    bool chargingShot = false;
    float chargeTime = 0.f;
    const float maxChargeTime = 2.f;
    bool shotAlreadyCharged = false;

    bool pendingNormalShot = false;
    bool pendingChargedShot = false;
    float pendingChargeTime = 0.f;
    sf::Vector2f pendingDirection = { 0.f, 0.f };

    float attackTimer = 0.f;
    const float attackDelay = 0.7f;

    map<TextureCategory,TextureMeta> texturesData;
    map<Direction, sf::Texture> idleTextures;
    map<Direction, sf::Texture> movementTextures;
    map<Direction, sf::Texture> attackTextures;

    Direction currentDir = Direction::Right;
    Direction lastDir = Direction::Right;

    CharacterState currentState = CharacterState::Idle;
    CharacterState previousState = CharacterState::Idle;

    bool isAttacking = false;
    float moveSpeed = 250.f;
    std::vector<ArrowMesh> arrows;
    
    void LoadTextures(map<Direction, Texture>& target, string commonPath, string nameOfTexture) override;

public:
    CharacterMesh() = delete;
    CharacterMesh(vector<TextureMeta> texturePathList) : BaseMesh(texturePathList)
    {
        for (const auto& texture : texturePathList)
        {
            texturesData.emplace(texture.category, texture);

            auto& target = (texture.category == TextureCategory::Idle) ? this->idleTextures :
                (texture.category == TextureCategory::Move) ? this->movementTextures :
                this->attackTextures;

            LoadTextures(target, texture.folderPath, texture.fileName);
        }
        
        int height = texturesData[TextureCategory::Idle].frameHeight;
        int width = texturesData[TextureCategory::Idle].frameWidth;
        int columns = texturesData[TextureCategory::Idle].numberOfColumns;
        int frames = texturesData[TextureCategory::Idle].numberOfFrames;

        sprite.setPosition(1600, 800);
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

    virtual Animation& Animation();
    virtual TextureMeta& TextureData(TextureCategory category);

    void Update(float deltaTime, const sf::RenderWindow& window) override;
    void Draw(sf::RenderWindow& window) override;

    virtual bool& IsCharged() = 0;
    virtual bool& IsChargingAttack() = 0;
    virtual bool& PendingNormalAttack() = 0;
    virtual bool& PendingChargedAttack() = 0;

    virtual float& ChargeTime() = 0;
    virtual float& AttackTimer() = 0;

    virtual Vector2f& PendingDirection() = 0;
    virtual float& PendingChargeTime() = 0;
    virtual const float AttackDelay() = 0;
    virtual const float MaxChargeTime() = 0;

    ~CharacterMesh()
    {
        cout << "Character mesh destroyed!" << endl;
        delete activeTexture;
    }
};
