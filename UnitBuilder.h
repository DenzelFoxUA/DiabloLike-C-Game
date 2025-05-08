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
    int _id = 0;
    vector<TextureMeta> _textures;
    SpawnPoint _spawnPoint;
    optional<EntityT> _entity;
    ProjectileType _projectile;
    float _cooldown;
    ProjectilesContainer* _container = nullptr;

public:
    UnitBuilder& SetId(int id)
    {
        this->_id = id;
        return *this;
    }

    UnitBuilder& SetTextures(const std::vector<TextureMeta>& textures)
    {
        this->_textures = textures;
        return *this;
    }

    UnitBuilder& SetSpawnPoint(const SpawnPoint& sp)
    {
        this->_spawnPoint = sp;
        return *this;
    }

    UnitBuilder& SetEntity(const EntityT& entity)
    {
        this->_entity = entity;
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

        return make_unique<UnitT>(_id, 
            _textures,
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
