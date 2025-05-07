#pragma once
#include "Character.h"

using namespace std;
using namespace sf;

template <typename Mesh, typename Entity>
class BaseUnit
{
protected:

    int id;
    Entity _character;

public:

    BaseUnit(int id, const Entity& character) : id(id), _character(character)
    {
        static_assert(std::is_base_of_v<Character, Entity>, "Obj must inherit from Character");
    }

    virtual Entity& GetEntity()
    {
        return this->_character;
    }

    virtual bool& IsDead()
    {
        return this->_character.IsDead();
    }
    virtual Mesh& GetMesh() = 0;
    virtual Vector2f GetPosition() const = 0;
    virtual Vector2f GetCenter() const = 0;
    virtual Vector2f MoveToPoint(Vector2f point) = 0;
    virtual void SetAnimationDuration(float newVal) = 0;
    virtual void SetSpeed(float val) = 0;
    virtual void Draw(sf::RenderWindow& window) = 0;

    template <typename, typename, typename>
    friend class UnitBuilder;
};