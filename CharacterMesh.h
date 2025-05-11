////#pragma once
////#include <SFML/Graphics.hpp>
////#include "Animation.h"
////#include <map>
////#include <vector>
////#include "Meshes/Weapons/ArrowMesh.h"
////#include "BaseMesh.h"
////#include <iostream>
////
////using namespace std;
////using namespace sf;
////
////enum class CharacterState 
////{
////    Idle,
////    Run,
////    Attack,
////    Cast,
////    Hurt,
////    Dead
////};
////
////enum AttackType
////{
////    Ranged,
////    Magic,
////    Melee
////};
////
////class CharacterMesh : public BaseMesh
////{
////protected:
////
////    Texture* activeTexture = nullptr;
////
////    bool chargingAttack = false;
////    float chargeTime = 0.f;
////    const float maxChargeTime = 2.f;
////    bool attackAlreadyCharged = false;
////
////    bool pendingNormalAttack = false;
////    bool pendingChargedAttack = false;
////    float pendingChargeTime = 0.f;
////
////    sf::Vector2f pendingDirection = { 0.f, 0.f };
////
////    float attackTimer = 0.f;
////    const float attackDelay = 1.f;
////
////    map<TextureCategory,TextureMeta> texturesData;
////
////    map<Direction, sf::Texture> idleTextures;
////    map<Direction, sf::Texture> movementTextures;
////    map<Direction, sf::Texture> attackTextures;
////    map<Direction, sf::Texture> deathTextures;
////   
////
////    Direction currentDir = Direction::Right;
////    Direction lastDir = Direction::Right;
////
////    CharacterState currentState = CharacterState::Idle;
////    CharacterState previousState = CharacterState::Idle;
////
////    bool isAttacking = false;
////    bool isMoving = false;
////    bool isDead = false;
////    float moveSpeed = 250.f;
////
////    float deathAnimatuionTime = 2.2f;
////    float deathAnimTik = 0.f;
////    
////    void LoadTextures(map<Direction, Texture>& target, string commonPath, string nameOfTexture) override;
////
////public:
////
////    CharacterMesh() = default;
////    CharacterMesh(vector<TextureMeta> texturePathList, SpawnPoint spawnP) : BaseMesh(texturePathList, spawnP)
////    {
////        for (const auto& texture : texturePathList)
////        {
////            texturesData.emplace(texture.category, texture);
////
////            auto& target = (texture.category == TextureCategory::Idle) ? this->idleTextures :
////                (texture.category == TextureCategory::Move) ? this->movementTextures :
////                (texture.category == TextureCategory::Death) ? this->deathTextures :
////                (texture.category == TextureCategory::Attack) ? this->attackTextures :
////                throw exception("Wrong textures category!");
////
////            LoadTextures(target, texture.folderPath, texture.fileName);
////        }
////        
////        int height = texturesData[TextureCategory::Idle].frameHeight;
////        int width = texturesData[TextureCategory::Idle].frameWidth;
////        int columns = texturesData[TextureCategory::Idle].numberOfColumns;
////        int frames = texturesData[TextureCategory::Idle].numberOfFrames;
////
////        sprite.setPosition(spawnP.x, spawnP.y);
////        animation.SetSheet(&idleTextures[currentDir], width, height, columns, frames);
////    }
////
////    virtual void SetSpeed(float val);
////    virtual const float& GetSpeed();
////
////    virtual Direction& CurrentDir();
////
////    virtual Direction& LastDir();
////    virtual bool& IsAttacking();
////    virtual Sprite& Sprite();
////
////    virtual CharacterState& CurrentState();
////    virtual CharacterState& PreviousState();
////
////    virtual map<Direction, sf::Texture>& IdleTextures();
////    virtual map<Direction, sf::Texture>& MoveTextures();
////    virtual map<Direction, sf::Texture>& AttackTextures();
////    virtual map<Direction, sf::Texture>& DeathTextures();
////
////    virtual Animation& Animation();
////    virtual TextureMeta& TextureData(TextureCategory category);
////
////    void Update(float deltaTime, const sf::RenderWindow& window) override;
////    void Draw(sf::RenderWindow& window) override;
////
////    virtual bool& IsCharged();
////    virtual bool& IsMoving();
////    virtual bool& IsDead();
////    virtual bool& IsChargingAttack();
////    virtual bool& PendingNormalAttack();
////    virtual bool& PendingChargedAttack();
////
////    virtual float& ChargeTime();
////    virtual float& AttackTimer();
////
////    virtual Vector2f& PendingDirection();
////    virtual float& PendingChargeTime();
////    virtual const float AttackDelay();
////    virtual const float MaxChargeTime();
////
////    virtual float& DeathAnimation_Timer()
////    {
////        return this->deathAnimTik;
////    }
////    virtual float DeathAnimationTimeLimit()
////    {
////        return this->deathAnimatuionTime;
////    }
////
////    ~CharacterMesh()
////    {
////        cout << "Character mesh destroyed!" << endl;
////        delete activeTexture;
////    }
////};
//
//#pragma once
//#include <SFML/Graphics.hpp>
//#include "Animation.h"
//#include <map>
//#include <vector>
//#include "Meshes/Weapons/ArrowMesh.h"
//#include "BaseMesh.h"
//#include <iostream>
//
//using namespace std;
//using namespace sf;
//
//enum class CharacterState
//{
//    Idle,
//    Run,
//    Attack,
//    Cast,
//    Hurt,
//    Dead
//};
//
//enum AttackType
//{
//    Ranged,
//    Magic,
//    Melee
//};
//
//class CharacterMesh : public BaseMesh
//{
//protected:
//    Texture* activeTexture = nullptr;
//
//    bool chargingAttack = false;
//    float chargeTime = 0.f;
//    const float maxChargeTime = 2.f;
//    bool attackAlreadyCharged = false;
//
//    bool pendingNormalAttack = false;
//    bool pendingChargedAttack = false;
//    float pendingChargeTime = 0.f;
//
//    sf::Vector2f pendingDirection = { 0.f, 0.f };
//
//    float attackTimer = 0.f;
//    const float attackDelay = 1.f;
//
//    map<TextureCategory, TextureMeta> texturesData;
//
//    map<Direction, sf::Texture> idleTextures;
//    map<Direction, sf::Texture> movementTextures;
//    map<Direction, sf::Texture> attackTextures;
//    map<Direction, sf::Texture> deathTextures;
//
//    Direction currentDir = Direction::Right;
//    Direction lastDir = Direction::Right;
//
//    CharacterState currentState = CharacterState::Idle;
//    CharacterState previousState = CharacterState::Idle;
//
//    bool isAttacking = false;
//    bool isMoving = false;
//    bool isDead = false;
//    float moveSpeed = 150.f;
//
//    float deathAnimatuionTime = 2.2f;
//    float deathAnimTik = 0.f;
//
//    void LoadTextures(map<Direction, Texture>& target, string commonPath, string nameOfTexture) override;
//
//public:
//    CharacterMesh() = default;
//
//    CharacterMesh(vector<TextureMeta> texturePathList, SpawnPoint spawnP) : BaseMesh(texturePathList, spawnP)
//    {
//        for (const auto& texture : texturePathList)
//        {
//            texturesData.emplace(texture.category, texture);
//
//            auto& target = (texture.category == TextureCategory::Idle) ? idleTextures :
//                (texture.category == TextureCategory::Move) ? movementTextures :
//                (texture.category == TextureCategory::Death) ? deathTextures :
//                (texture.category == TextureCategory::Attack) ? attackTextures :
//                throw runtime_error("Unsupported texture category");
//
//            LoadTextures(target, texture.folderPath, texture.fileName);
//        }
//
//        InitFromTextures(spawnP);
//    }
//
//    void InitFromTextures(SpawnPoint spawnP)
//    {
//        if (texturesData.find(TextureCategory::Idle) == texturesData.end()) {
//            throw runtime_error("Idle texture meta is required for CharacterMesh initialization");
//        }
//
//        const auto& meta = texturesData[TextureCategory::Idle];
//
//        sprite.setPosition(spawnP.x, spawnP.y);
//        animation.SetSheet(&idleTextures[currentDir], meta.frameWidth, meta.frameHeight, meta.numberOfColumns, meta.numberOfFrames);
//    }
//
//    virtual void SetSpeed(float val);
//    virtual const float& GetSpeed();
//
//    virtual Direction& CurrentDir();
//    virtual Direction& LastDir();
//    virtual bool& IsAttacking();
//    virtual Sprite& Sprite();
//
//    virtual CharacterState& CurrentState();
//    virtual CharacterState& PreviousState();
//
//    virtual map<Direction, sf::Texture>& IdleTextures();
//    virtual map<Direction, sf::Texture>& MoveTextures();
//    virtual map<Direction, sf::Texture>& AttackTextures();
//    virtual map<Direction, sf::Texture>& DeathTextures();
//
//    virtual Animation& Animation();
//    virtual TextureMeta& TextureData(TextureCategory category);
//
//    void Update(float deltaTime, const sf::RenderWindow& window) override;
//    void Draw(sf::RenderWindow& window) override;
//
//    virtual bool& IsCharged();
//    virtual bool& IsMoving();
//    virtual bool& IsDead();
//    virtual bool& IsChargingAttack();
//    virtual bool& PendingNormalAttack();
//    virtual bool& PendingChargedAttack();
//
//    virtual float& ChargeTime();
//    virtual float& AttackTimer();
//
//    virtual Vector2f& PendingDirection();
//    virtual float& PendingChargeTime();
//    virtual const float AttackDelay();
//    virtual const float MaxChargeTime();
//
//    virtual float& DeathAnimation_Timer()
//    {
//        return this->deathAnimTik;
//    }
//    virtual float DeathAnimationTimeLimit()
//    {
//        return this->deathAnimatuionTime;
//    }
//    ~CharacterMesh()
//    {
//        cout << "Character mesh destroyed!" << endl;
//        delete activeTexture; // зауваженн€: активна текстура Ч не тво€ в≥дпов≥дальн≥сть, €кщо не new
//    }
//};

//#pragma once
//#include <SFML/Graphics.hpp>
//#include "Animation.h"
//#include <map>
//#include <vector>
//#include "Meshes/Weapons/ArrowMesh.h"
//#include "BaseMesh.h"
//#include <iostream>
//
//using namespace std;
//using namespace sf;
//
//enum class CharacterState 
//{
//    Idle,
//    Run,
//    Attack,
//    Cast,
//    Hurt,
//    Dead
//};
//
//enum AttackType
//{
//    Ranged,
//    Magic,
//    Melee
//};
//
//class CharacterMesh : public BaseMesh
//{
//protected:
//
//    Texture* activeTexture = nullptr;
//
//    bool chargingAttack = false;
//    float chargeTime = 0.f;
//    const float maxChargeTime = 2.f;
//    bool attackAlreadyCharged = false;
//
//    bool pendingNormalAttack = false;
//    bool pendingChargedAttack = false;
//    float pendingChargeTime = 0.f;
//
//    sf::Vector2f pendingDirection = { 0.f, 0.f };
//
//    float attackTimer = 0.f;
//    const float attackDelay = 1.f;
//
//    map<TextureCategory,TextureMeta> texturesData;
//
//    map<Direction, sf::Texture> idleTextures;
//    map<Direction, sf::Texture> movementTextures;
//    map<Direction, sf::Texture> attackTextures;
//    map<Direction, sf::Texture> deathTextures;
//   
//
//    Direction currentDir = Direction::Right;
//    Direction lastDir = Direction::Right;
//
//    CharacterState currentState = CharacterState::Idle;
//    CharacterState previousState = CharacterState::Idle;
//
//    bool isAttacking = false;
//    bool isMoving = false;
//    bool isDead = false;
//    float moveSpeed = 250.f;
//
//    float deathAnimatuionTime = 2.2f;
//    float deathAnimTik = 0.f;
//    
//    void LoadTextures(map<Direction, Texture>& target, string commonPath, string nameOfTexture) override;
//
//public:
//
//    CharacterMesh() = default;
//    CharacterMesh(vector<TextureMeta> texturePathList, SpawnPoint spawnP) : BaseMesh(texturePathList, spawnP)
//    {
//        for (const auto& texture : texturePathList)
//        {
//            texturesData.emplace(texture.category, texture);
//
//            auto& target = (texture.category == TextureCategory::Idle) ? this->idleTextures :
//                (texture.category == TextureCategory::Move) ? this->movementTextures :
//                (texture.category == TextureCategory::Death) ? this->deathTextures :
//                (texture.category == TextureCategory::Attack) ? this->attackTextures :
//                throw exception("Wrong textures category!");
//
//            LoadTextures(target, texture.folderPath, texture.fileName);
//        }
//        
//        int height = texturesData[TextureCategory::Idle].frameHeight;
//        int width = texturesData[TextureCategory::Idle].frameWidth;
//        int columns = texturesData[TextureCategory::Idle].numberOfColumns;
//        int frames = texturesData[TextureCategory::Idle].numberOfFrames;
//
//        sprite.setPosition(spawnP.x, spawnP.y);
//        animation.SetSheet(&idleTextures[currentDir], width, height, columns, frames);
//    }
//
//    virtual void SetSpeed(float val);
//    virtual const float& GetSpeed();
//
//    virtual Direction& CurrentDir();
//
//    virtual Direction& LastDir();
//    virtual bool& IsAttacking();
//    virtual Sprite& Sprite();
//
//    virtual CharacterState& CurrentState();
//    virtual CharacterState& PreviousState();
//
//    virtual map<Direction, sf::Texture>& IdleTextures();
//    virtual map<Direction, sf::Texture>& MoveTextures();
//    virtual map<Direction, sf::Texture>& AttackTextures();
//    virtual map<Direction, sf::Texture>& DeathTextures();
//
//    virtual Animation& Animation();
//    virtual TextureMeta& TextureData(TextureCategory category);
//
//    void Update(float deltaTime, const sf::RenderWindow& window) override;
//    void Draw(sf::RenderWindow& window) override;
//
//    virtual bool& IsCharged();
//    virtual bool& IsMoving();
//    virtual bool& IsDead();
//    virtual bool& IsChargingAttack();
//    virtual bool& PendingNormalAttack();
//    virtual bool& PendingChargedAttack();
//
//    virtual float& ChargeTime();
//    virtual float& AttackTimer();
//
//    virtual Vector2f& PendingDirection();
//    virtual float& PendingChargeTime();
//    virtual const float AttackDelay();
//    virtual const float MaxChargeTime();
//
//    virtual float& DeathAnimation_Timer()
//    {
//        return this->deathAnimTik;
//    }
//    virtual float DeathAnimationTimeLimit()
//    {
//        return this->deathAnimatuionTime;
//    }
//
//    ~CharacterMesh()
//    {
//        cout << "Character mesh destroyed!" << endl;
//        delete activeTexture;
//    }
//};

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
    const float attackDelay = 1.f;

    map<TextureCategory, TextureMeta> texturesData;

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
    float moveSpeed = 150.f;

    float deathAnimatuionTime = 2.2f;
    float deathAnimTik = 0.f;

    void LoadTextures(map<Direction, Texture>& target, string commonPath, string nameOfTexture) override;

public:
    CharacterMesh() = default;

    CharacterMesh(vector<TextureMeta> texturePathList, SpawnPoint spawnP) : BaseMesh(texturePathList, spawnP)
{
    for (const auto& texture : texturePathList)
    {
        texturesData.emplace(texture.category, texture);

        auto& target = (texture.category == TextureCategory::Idle) ? idleTextures :
            (texture.category == TextureCategory::Move) ? movementTextures :
            (texture.category == TextureCategory::Death) ? deathTextures :
            (texture.category == TextureCategory::Attack) ? attackTextures :
            throw exception("Wrong textures category!");

        LoadTextures(target, texture.folderPath, texture.fileName);
    }

    const auto& idleMeta = texturesData[TextureCategory::Idle];

    sprite.setPosition(spawnP.x, spawnP.y);
    animation.SetSheet(&idleTextures[currentDir], idleMeta.frameWidth, idleMeta.frameHeight,
        idleMeta.numberOfColumns, idleMeta.numberOfFrames);
}

    //    InitFromTextures(spawnP);
    //}

    void InitFromTextures(SpawnPoint spawnP)
    {
        if (texturesData.find(TextureCategory::Idle) == texturesData.end()) {
            throw runtime_error("Idle texture meta is required for CharacterMesh initialization");
        }

        const auto& meta = texturesData[TextureCategory::Idle];

        sprite.setPosition(spawnP.x, spawnP.y);
        animation.SetSheet(&idleTextures[currentDir], meta.frameWidth, meta.frameHeight, meta.numberOfColumns, meta.numberOfFrames);
    }

    virtual void SetSpeed(float val);
    virtual const float& GetSpeed();

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
    virtual bool& IsDead();
    virtual bool& IsChargingAttack();
    virtual bool& PendingNormalAttack();
    virtual bool& PendingChargedAttack();

    virtual float& ChargeTime();
    virtual float& AttackTimer();

    virtual Vector2f& PendingDirection();
    virtual float& PendingChargeTime();
    virtual const float AttackDelay();
    virtual const float MaxChargeTime();

    virtual float& DeathAnimation_Timer()
    {
        return this->deathAnimTik;
    }
    virtual float DeathAnimationTimeLimit()
    {
        return this->deathAnimatuionTime;
    }
    ~CharacterMesh()
    {
        cout << "Character mesh destroyed!" << endl;
        delete activeTexture; // зауваженн€: активна текстура Ч не тво€ в≥дпов≥дальн≥сть, €кщо не new
    }
};