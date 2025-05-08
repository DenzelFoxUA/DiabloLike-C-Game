#pragma once
#include "PlayerCaracter.h"
#include "PlayerCharacterMesh.h"
#include "Arrow.h"
#include <type_traits>
#include <concepts>
#include <iostream>
#include "IController.h"

using namespace std;


class PlayerController : public IController
{
protected:

	CharacterMesh& characterMesh;
	Character& characterEntity;

    virtual void ChasingEnemy(Vector2f point, float deltaTime, bool& isMoving) = 0;
    virtual float GetDistanceToTarget(Vector2f point) = 0;

public:

	PlayerController(CharacterMesh&_mesh, Character &_characterObj):characterMesh(_mesh), characterEntity(_characterObj)
	{

	}

    virtual void HandleInput(float deltaTime) override;
    virtual Character& GetEntity() override
    {
        return this->characterEntity;
    }
	virtual void HandleEvent(const sf::Event& event, const sf::RenderWindow& window) = 0;
	virtual void Update(float deltaTime, const sf::RenderWindow& window/*, CharacterMesh& targetMesh, Character& target*/) = 0;
    virtual void Draw(sf::RenderWindow& window) = 0;
    virtual void SetSpeed(float val) = 0;
    virtual bool& IsDead() override 
    { 
        return this->characterEntity.IsDead(); 
    }
    virtual void HandleBehavior(Vector2f target, Character& enemy, float deltaTime) = 0;
    virtual Vector2f GetCenter() override
    {
        return this->characterMesh.GetCenter();
    }

    //virtual void HandleInput(float deltaTime) override;

    ~PlayerController()
    {
        cout << "Player controller destroyed!" << endl;
    }
};

