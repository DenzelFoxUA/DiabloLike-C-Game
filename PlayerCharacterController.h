#pragma once
#include "PlayerCaracter.h"
#include "PlayerCharacterMesh.h"
#include <type_traits>
#include <concepts>
#include <iostream>

using namespace std;

template <typename Mesh, typename Obj>
class PlayerController
{
protected:
	Mesh *characterMesh;
	Obj *characterEntity;

public:
	PlayerController() = delete;

	PlayerController(Mesh *_mesh, Obj *_characterObj):characterMesh(_mesh), characterEntity(_characterObj)
	{
		static_assert(std::is_base_of_v<PlayerCharacterMesh, Mesh>, "Mesh must inherit from PlayerCharacterMesh");
		static_assert(std::is_base_of_v<PlayerCharacter, Obj>, "Obj must inherit from PlayerCharacter");
	}

    virtual void HandleInput(float deltaTime);
    virtual Obj * GetEntity()
    {
        return this->characterEntity;
    }
	virtual void HandleEvent(const sf::Event& event, const sf::RenderWindow& window) = 0;
	virtual void Update(float deltaTime, const sf::RenderWindow& window) = 0;

    ~PlayerController()
    {
        cout << "Player controller destroyed!" << endl;
        delete characterMesh;
        delete characterEntity;
    }
};

template<typename Mesh, typename Obj>
void PlayerController<Mesh, Obj>::HandleInput(float deltaTime)
{
    sf::Vector2f velocity{ 0.f, 0.f };
    bool& isMoving = characterMesh->IsMoving();
    isMoving = false;

    //if (this->characterEntity->GetHealthPoints() <= 0)
    //{
    //    cout << characterEntity->GetName() << " is died!" << endl;

    //    auto& curState = characterMesh->CurrentState();

    //    curState = CharacterState::Dead;

    //    auto& curDir = characterMesh->CurrentDir();

    //    sf::Texture* newTexture = &characterMesh->DeathTextures()[curDir];

    //    int height = characterMesh->TextureData(TextureCategory::Death).frameHeight;
    //    int width = characterMesh->TextureData(TextureCategory::Death).frameWidth;
    //    int columns = characterMesh->TextureData(TextureCategory::Death).numberOfColumns;
    //    int frames = characterMesh->TextureData(TextureCategory::Death).numberOfFrames;

    //    characterMesh->Animation().SetSheet(newTexture, width, height, columns, frames, false);

    //    characterMesh->PreviousState() = curState;
    //    characterMesh->LastDir() = curDir;
    //    characterMesh->Animation().Update(deltaTime);
    //    return;
    //}

    if (this->characterEntity->GetHealthPoints() <= 0)
    {
        auto& curState = characterMesh->CurrentState();

        if (curState != CharacterState::Dead)
        {
            cout << characterEntity->GetName() << " is died!" << endl;

            curState = CharacterState::Dead;
            auto& curDir = characterMesh->CurrentDir();

            sf::Texture* newTexture = &characterMesh->DeathTextures()[curDir];

            const auto& meta = characterMesh->TextureData(TextureCategory::Death);

            characterMesh->Animation().SetSheet(
                newTexture,
                meta.frameWidth,
                meta.frameHeight,
                meta.numberOfColumns,
                meta.numberOfFrames,
                false);

            characterMesh->PreviousState() = curState;
            characterMesh->LastDir() = curDir;
        }
        characterMesh->Animation().Update(deltaTime);

    }
    else
    {

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            velocity.y -= characterMesh->GetSpeed();
            characterMesh->CurrentDir() = Direction::Up;
            isMoving = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            velocity.y += characterMesh->GetSpeed();
            characterMesh->CurrentDir() = Direction::Down;
            isMoving = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            velocity.x -= characterMesh->GetSpeed();
            characterMesh->CurrentDir() = Direction::Left;
            isMoving = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            velocity.x += characterMesh->GetSpeed();
            characterMesh->CurrentDir() = Direction::Right;
            isMoving = true;
        }

        if (velocity.x != 0 && velocity.y != 0)
            velocity /= std::sqrt(2.f);

        characterMesh->Sprite().move(velocity * deltaTime);

        if (!characterMesh->IsAttacking() && !characterMesh->IsDead()) {
            characterMesh->CurrentState() = isMoving ? CharacterState::Run : CharacterState::Idle;
        }

        auto& curState = characterMesh->CurrentState();
        auto& prevState = characterMesh->PreviousState();
        auto& curDir = characterMesh->CurrentDir();
        auto& lastDir = characterMesh->LastDir();

        if (curState != prevState || curDir != lastDir)
        {
            sf::Texture* newTexture =
                (curState == CharacterState::Run) ? &characterMesh->MoveTextures()[curDir] :
                (curState == CharacterState::Attack) ? &characterMesh->AttackTextures()[curDir] :
                &characterMesh->IdleTextures()[curDir];

            int height = characterMesh->TextureData(TextureCategory::Idle).frameHeight;
            int width = characterMesh->TextureData(TextureCategory::Idle).frameWidth;
            int columns = characterMesh->TextureData(TextureCategory::Idle).numberOfColumns;
            int frames = characterMesh->TextureData(TextureCategory::Idle).numberOfFrames;

            characterMesh->Animation().SetSheet(newTexture, width, height, columns, frames, curState != CharacterState::Attack);

            characterMesh->PreviousState() = curState;
            characterMesh->LastDir() = curDir;
        }
    }

}

