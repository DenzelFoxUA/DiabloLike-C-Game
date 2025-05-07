#pragma once
#include <SFML/Graphics.hpp>
#include "ProjectileMesh.h"

class ArrowMesh : public ProjectileMesh
{
protected:

public:
    ArrowMesh(Texture& texture, Vector2f startPos, Vector2f direction, float speed, float lifetime) :
        ProjectileMesh(texture, startPos, direction, speed, lifetime){}

    ArrowMesh(const ArrowMesh& other) :ProjectileMesh(other) 
    {
        this->sprite = other.sprite;
        this->direction = other.direction;
        this->velocity = other.velocity;
        this->speed = other.speed;
        this->lifeTime = other.lifeTime;
    };
    ArrowMesh& operator=(const ArrowMesh& other)
    {
        if (this != &other)
        {
            this->sprite = other.sprite;
            this->direction = other.direction;
            this->velocity = other.velocity;
            speed = other.speed;
            lifeTime = other.lifeTime;
        }
        return *this;
    }
};
