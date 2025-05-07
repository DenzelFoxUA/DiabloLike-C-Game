#pragma once
#include "Character.h"
#include "CharacterMesh.h"
#include <optional> //can be empty, reset()!
#include "BaseUnit.h"
#include <memory>
#include <vector>

template <typename UnitT, typename MeshT, typename EntityT>
class UnitBuilder
{
private:
    int _id = 0;
    vector<TextureMeta> _textures;
    SpawnPoint _spawnPoint;
    optional<EntityT> _entity;
    optional<Texture> _projectileTexture;
    optional<Arrow> _arrow;
    float _cooldown;

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

    UnitBuilder& SetProjectileTexture(const sf::Texture& texture)
    {
        this->_projectileTexture = texture;
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

    UnitBuilder& SetArrow(const Arrow& arrow)
    {
        this->_arrow = arrow;
        return *this;
    }

    UnitBuilder& SetCooldown(float cd)
    {
        this->_cooldown = cd;
        return *this;
    }

    unique_ptr<UnitT> Build()
    {
        static_assert(std::is_base_of_v<BaseUnit<MeshT, EntityT>, UnitT>,
            "UnitType must inherit from BaseUnit<MeshType, EntityType>");

        return make_unique<UnitT>(_id, _textures, _spawnPoint,*_entity,* _projectileTexture,*_arrow, _cooldown);
    }
};
