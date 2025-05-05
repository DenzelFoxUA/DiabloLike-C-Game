//#pragma once
//#include <SFML/Graphics.hpp>
//#include "NPCEntity.h"
//#include "NPCMesh.h"
//#include <type_traits>
//#include <concepts>
//#include <iostream>
//#include <cmath>
//
//using namespace std;
//using namespace sf;
//
//template <typename Mesh, typename Obj>
//class NPC_Controller
//{
//protected:
//    Mesh* npcMesh;
//    Obj* npcEntity;
//
//    sf::Clock attackTimer;
//    Time attackCooldown;
//
//    bool isChasing;
//    virtual void ChasingEnemy(Vector2f point, float deltaTime, bool& isMoving);
//    virtual float GetDistanceToTarget(Vector2f point);
//
//public:
//    NPC_Controller() = delete;
//
//    NPC_Controller(Mesh* _mesh, Obj* _npcObj, float cooldown) :npcMesh(_mesh), npcEntity(_npcObj)
//    {
//        static_assert(std::is_base_of_v<NPCMesh, Mesh>, "Mesh must inherit from NPCMesh");
//        static_assert(std::is_base_of_v<NPCEntity, Obj>, "Obj must inherit from NPCEntity");
//        this->isChasing = false;
//        attackCooldown = sf::seconds(cooldown);
//    }
//
//    
//    virtual void HandleBehavior(Vector2f target, float deltaTime);
//    virtual void Update(float deltaTime, const sf::RenderWindow& window) = 0;
//
//    ~NPC_Controller()
//    {
//        cout << "Player controller destroyed!" << endl;
//        delete npcMesh;
//        delete npcEntity;
//    }
//};
//template<typename Mesh, typename Obj>
//void NPC_Controller<Mesh, Obj>::ChasingEnemy(Vector2f point, float deltaTime, bool& isMoving)
//{ 
//    auto direction = npcMesh->MoveToPoint(point - this->npcMesh->GetPosition());
//    npcMesh->PendingDirection() = direction;
//    npcMesh->Sprite().move(direction * npcMesh->GetSpeed() * deltaTime);
//    isChasing = true;
//    npcMesh->IsAttacking() = false;
//    isMoving = true;
//}
//
////template<typename Mesh, typename Obj>
////void NPC_Controller<Mesh, Obj>::Attacking(Vector2f point, float deltaTime, bool& isMoving)
////{
////    auto direction = npcMesh->MoveToPoint(point - this->npcMesh->GetPosition());
////    npcMesh->PendingDirection() = direction;
////    npcMesh->Sprite().move(direction * npcMesh->GetSpeed() * deltaTime);
////    isChasing = true;
////    npcMesh->IsAttacking() = false;
////    isMoving = true;
////}
//
//template<typename Mesh, typename Obj>
//float NPC_Controller<Mesh, Obj>::GetDistanceToTarget(Vector2f point)
//{
//    Vector2f a = npcMesh->GetPosition();
//    Vector2f b = point;
//    return std::sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
//}
//
//template<typename Mesh, typename Obj>
//void NPC_Controller<Mesh, Obj>::HandleBehavior(Vector2f target, float deltaTime)
//{
//    float timeNow = deltaTime;
//
//    sf::Vector2f velocity{ 0.f, 0.f };
//    bool& isMoving = npcMesh->IsMoving();
//    Vector2f curPosition = npcMesh->GetPosition();
//
//    if (GetDistanceToTarget(target) > 500)
//    {
//        npcMesh->IsAttacking() = false;
//        isChasing = false;
//        isMoving = false;
//        npcMesh->CurrentState() = CharacterState::Idle;
//    }
//    else if (GetDistanceToTarget(target) <= 500 && GetDistanceToTarget(target) > 60)
//    { 
//        ChasingEnemy(target, deltaTime, isMoving);
//        npcMesh->CurrentState() = CharacterState::Run;
//    }
//    else if (GetDistanceToTarget(target) <= 60 && GetDistanceToTarget(target) >= 0)
//    {
//        if (attackTimer.getElapsedTime() >= attackCooldown)
//        {
//            isChasing = false;
//            isMoving = false;
//            npcMesh->IsAttacking() = true;
//            npcMesh->CurrentState() = CharacterState::Attack;
//
//            attackTimer.restart(); // ⏱ перезапуск таймера після атаки
//        }
//        else
//        {
//            // ще не час для нової атаки
//            npcMesh->IsAttacking() = false;
//            npcMesh->CurrentState() = CharacterState::Idle; // або залишити поточний стан
//        }
//    }
//
//
//    if (velocity.x != 0 && velocity.y != 0)
//        velocity /= std::sqrt(2.f);
//
//    npcMesh->Sprite().move(velocity * deltaTime);
//    
//
//    if (!npcMesh->IsAttacking()) {
//        npcMesh->CurrentState() = npcMesh->IsMoving() ? CharacterState::Run : CharacterState::Idle;
//    }
//
//    auto& curState = npcMesh->CurrentState();
//    auto& prevState = npcMesh->PreviousState();
//    auto& curDir = npcMesh->CurrentDir();
//    auto& lastDir = npcMesh->LastDir();
//
//    if (curPosition.x < target.x)
//    {
//        curDir = Direction::Right;
//    }
//    else if (curPosition.x > target.x)
//    {
//        curDir = Direction::Left;
//    }
//    else if (curPosition.x == target.x && curPosition.y > target.y)
//    {
//        curDir = Direction::Down;
//    }
//    else if (curPosition.x == target.x && curPosition.y < target.y)
//    {
//        curDir = Direction::Up;
//    }
//
//    TextureMeta curMeta = (curState == CharacterState::Attack) ? npcMesh->TextureData(TextureCategory::Attack) :
//        (curState == CharacterState::Idle) ? npcMesh->TextureData(TextureCategory::Idle) :
//        npcMesh->TextureData(TextureCategory::Move);
//
//
//    if (curState != prevState || curDir != lastDir)
//    {
//        sf::Texture* newTexture =
//            (curState == CharacterState::Run) ? &npcMesh->MoveTextures()[curDir] :
//            (curState == CharacterState::Attack) ? &npcMesh->AttackTextures()[curDir] :
//            &npcMesh->IdleTextures()[curDir];
//
//        
//        //looping animation
//        /*bool shouldLoop = (curState == CharacterState::Attack) ? ;*/
//
//        npcMesh->Animation().SetSheet(newTexture, curMeta.frameWidth, curMeta.frameHeight,
//            curMeta.numberOfColumns, curMeta.numberOfFrames, true);
//
//        npcMesh->PreviousState() = curState;
//        npcMesh->LastDir() = curDir;
//    }
//
//    npcMesh->Animation().Update(deltaTime);
//
//}

#pragma once

#include <SFML/Graphics.hpp>
#include "NPCEntity.h"
#include "NPCMesh.h"
#include <type_traits>
#include <concepts>
#include <iostream>
#include <cmath>

using namespace std;
using namespace sf;

template <typename Mesh, typename Obj>
class NPC_Controller
{
protected:
    Mesh* npcMesh;
    Obj* npcEntity;

    sf::Clock attackTimer;
    Time attackCooldown;

    bool isChasing;

    virtual void ChasingEnemy(Vector2f point, float deltaTime, bool& isMoving);
    virtual float GetDistanceToTarget(Vector2f point);

public:
    NPC_Controller() = delete;

    NPC_Controller(Mesh* _mesh, Obj* _npcObj, float cooldown) : npcMesh(_mesh), npcEntity(_npcObj)
    {
        static_assert(std::is_base_of_v<NPCMesh, Mesh>, "Mesh must inherit from NPCMesh");
        static_assert(std::is_base_of_v<NPCEntity, Obj>, "Obj must inherit from NPCEntity");
        isChasing = false;
        attackCooldown = sf::seconds(cooldown);
    }

    virtual void HandleBehavior(Vector2f target, Character& enemy, float deltaTime);
    virtual void Update(float deltaTime, const sf::RenderWindow& window) = 0;

    ~NPC_Controller()
    {
        cout << "NPC controller destroyed!" << endl;
        delete npcMesh;
        delete npcEntity;
    }
};

template<typename Mesh, typename Obj>
void NPC_Controller<Mesh, Obj>::ChasingEnemy(Vector2f point, float deltaTime, bool& isMoving)
{
    auto direction = npcMesh->MoveToPoint(point - npcMesh->GetPosition());
    npcMesh->PendingDirection() = direction;
    npcMesh->Sprite().move(direction * npcMesh->GetSpeed() * deltaTime);
    isChasing = true;
    npcMesh->IsAttacking() = false;
    isMoving = true;
}

template<typename Mesh, typename Obj>
float NPC_Controller<Mesh, Obj>::GetDistanceToTarget(Vector2f point)
{
    Vector2f a = npcMesh->GetPosition();
    Vector2f b = point;
    return std::sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

//template<typename Mesh, typename Obj>
//void NPC_Controller<Mesh, Obj>::HandleBehavior(Vector2f target, float deltaTime)
template<typename Mesh, typename Obj>
void NPC_Controller<Mesh, Obj>::HandleBehavior(Vector2f target, Character & enemy, float deltaTime)
{
    bool& isMoving = npcMesh->IsMoving();
    Vector2f curPosition = npcMesh->GetPosition();
    float distance = GetDistanceToTarget(target);

    // Якщо ворог далеко — бути Idle
    if (distance > 500 || enemy.GetHealthPoints()<=0)
    {
        npcMesh->IsAttacking() = false;
        isChasing = false;
        isMoving = false;
        npcMesh->CurrentState() = CharacterState::Idle;
    }
    // Якщо в зоні переслідування
    else if (distance > 60)
    {
        ChasingEnemy(target, deltaTime, isMoving);
        npcMesh->CurrentState() = CharacterState::Run;
    }
    // Якщо в зоні атаки
    else
    {
        isChasing = false;
        isMoving = false;

        // Якщо анімація атаки завершена — повернутися в Idle
        if (npcMesh->CurrentState() == CharacterState::Attack &&
            npcMesh->Animation().IsFinished())
        {
            npcMesh->IsAttacking() = false;
            npcMesh->CurrentState() = CharacterState::Idle;
        }
        // Якщо ще не можна атакувати — чекати
        else if (attackTimer.getElapsedTime() < attackCooldown)
        {
            npcMesh->IsAttacking() = false;
            // залишити попередній стан (Idle або те, що було)
        }
        // Атакувати
        else
        {
            npcMesh->IsAttacking() = true;
            npcMesh->CurrentState() = CharacterState::Attack;
            enemy.GetHit(100);
            cout << enemy.GetName() << " taking " << 100 << " damage!";
            cout << enemy.GetName() << " has " << enemy.GetHealthPoints() << " HP.";
            attackTimer.restart();
        }
    }

    // Зупинити рух, якщо не потрібно рухатись
    if (!isMoving)
        npcMesh->PendingDirection() = { 0.f, 0.f };

    // Оновити позицію (рух)
    npcMesh->Sprite().move(npcMesh->PendingDirection() * npcMesh->GetSpeed() * deltaTime);

    // Напрямок
    auto& curDir = npcMesh->CurrentDir();
    if (std::abs(target.x - curPosition.x) > std::abs(target.y - curPosition.y))
        curDir = (target.x > curPosition.x) ? Direction::Right : Direction::Left;
    else
        curDir = (target.y > curPosition.y) ? Direction::Down : Direction::Up;

    // Анімація
    auto& curState = npcMesh->CurrentState();
    auto& prevState = npcMesh->PreviousState();
    auto& lastDir = npcMesh->LastDir();

    if (curState != prevState || curDir != lastDir)
    {
        sf::Texture* newTexture =
            (curState == CharacterState::Run) ? &npcMesh->MoveTextures()[curDir] :
            (curState == CharacterState::Attack) ? &npcMesh->AttackTextures()[curDir] :
            &npcMesh->IdleTextures()[curDir];

        TextureCategory texCategory =
            (curState == CharacterState::Run) ? TextureCategory::Move :
            (curState == CharacterState::Attack) ? TextureCategory::Attack :
            TextureCategory::Idle;

        const auto& meta = npcMesh->TextureData(texCategory);

        bool shouldLoop = (curState != CharacterState::Attack);

        npcMesh->Animation().SetSheet(
            newTexture,
            meta.frameWidth,
            meta.frameHeight,
            meta.numberOfColumns,
            meta.numberOfFrames,
            shouldLoop
        );

        prevState = curState;
        lastDir = curDir;
    }

    npcMesh->Animation().Update(deltaTime);
}
