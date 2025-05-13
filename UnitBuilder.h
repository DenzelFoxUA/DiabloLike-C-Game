#pragma once
#include "Character.h"
#include "CharacterMesh.h"
#include <optional> //can be empty, reset()!
#include "BaseUnit.h"
#include <memory>
#include <vector>
#include "ProjectileManager.h"

template <typename UnitT, typename EntityT>
class UnitBuilder
{
private:
    vector<TextureMeta> _texturesRanged;
    vector<TextureMeta> _texturesMelee;
    SpawnPoint _spawnPoint;
    optional<EntityT> _entity;
    ProjectileType _projectile;
    float _cooldown;
    ProjectilesContainer* _container = nullptr;

public:

    UnitBuilder& SetTexturesRanged(vector<TextureMeta> textures)
    {
        this->_texturesRanged = move(textures);
        return *this;
    }

    UnitBuilder& SetTexturesMelee(vector<TextureMeta> textures)
    {
        this->_texturesMelee = move(textures);
        return *this;
    }

    UnitBuilder& SetSpawnPoint(const SpawnPoint& sp)
    {
        this->_spawnPoint = sp;
        return *this;
    }

    UnitBuilder& SetEntity(const EntityT& entity)
    {
        this->_entity = move(entity);
        return *this;
    }

    UnitBuilder& SetArrow(ProjectileType type)
    {
        this->_projectile = type;
        return *this;
    }

    UnitBuilder& SetCooldown(float cd)
    {
        this->_cooldown = cd;
        return *this;
    }
    UnitBuilder& SetContainer(ProjectilesContainer* container)
    {
        this->_container = container;
        return *this;
    }

    unique_ptr<UnitT> Build()
    {
        static_assert(std::is_base_of_v<BaseUnit<EntityT>, UnitT>,
            "UnitType must inherit from BaseUnit!");
        if (!_entity.has_value()) {
            throw std::logic_error("Entity was not set in UnitBuilder before Build()");
        }
        return make_unique<UnitT>( 
            _texturesRanged,
            _texturesMelee,
            _spawnPoint,
            *_entity,
            _projectile,
            _cooldown, 
            _container);
    }

    void Reset()
    {
        //this->_arrow.reset();
        //this->_projectileTexture.reset();
        this->_entity.reset();
        //this->_container.reset();
    }
};
