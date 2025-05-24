#pragma once
#include "Character.h"
#include "CharacterMesh.h"
#include <optional>
#include "BaseUnit.h"
#include <memory>
#include <vector>
#include "ProjectileManager.h"

template <typename UnitT, typename EntityT>
class UnitBuilder
{
private:
    vector<TextureMeta> _texturesPrime;
    vector<TextureMeta> _texturesSecondary;
    SpawnPoint _spawnPoint;
    optional<EntityT> _entity;
    ProjectileType _projectile;
    float _cooldown;
    ProjectilesContainer* _container = nullptr;

    float speed;
    float attackTime;
    float deathAnimTime;
    float healingRate;
    float staminaRegenRate;
    float manaRegenRate;
    float animationDuration;

    bool isPrimeTexturesSet = false;//
    bool isSecTexturesSet = false;//
    bool isSpawnPointSet = false;//
    bool isEntitySet = false;//
    bool isProjectileSet = false; //
    bool isCooldownSet = false; //
    bool isContainerSet = false; //
    bool isSpeedSet = false; //
    bool isAttackTimeSet = false; //
    bool isHealingRateSet = false; //
    bool isStaminaRegenSet = false; //
    bool isManaRegenSet = false; //
    bool isAnimationDurationSet = false;//
    bool isDeathAnimationTimeSet = false;//


public:

    UnitBuilder& SetTexturesPrimary(vector<TextureMeta> textures)
    {
        this->_texturesPrime = move(textures);
        isPrimeTexturesSet = true;
        return *this;
    }

    UnitBuilder& SetTexturesSecondary(vector<TextureMeta> textures)
    {
        
        this->_texturesSecondary = move(textures);
        isSecTexturesSet = true;
        return *this;
    }

    UnitBuilder& SetSpawnPoint(const SpawnPoint& sp)
    {
        this->_spawnPoint = sp;
        isSpawnPointSet = true;
        return *this;
    }

    UnitBuilder& SetEntity(const EntityT& entity)
    {
        this->_entity = move(entity);
        isEntitySet = true;
        return *this;
    }

    UnitBuilder& SetProjectile(ProjectileType type)
    {
        this->_projectile = type;
        isProjectileSet = true;
        return *this;
    }

    UnitBuilder& SetCooldown(float cd)
    {
        if (cd > 0.f)
        {
            this->_cooldown = cd;
            isCooldownSet = true;
        }

        return *this;
    }
    UnitBuilder& SetContainer(ProjectilesContainer* container)
    {
        this->_container = container;
        isContainerSet = true;
        return *this;
    }

    UnitBuilder& SetAnimDuration(float animTime)
    {
        if (animTime > 0.f)
        {
            this->animationDuration = animTime;
            isAnimationDurationSet = true;
        }

        return *this;
    }

    UnitBuilder& SetHPRegenerationRate(float val)
    {
        if (val >= 0.f)
        {
            this->healingRate = val;
            isHealingRateSet = true;
        }

        return *this;
    }

    UnitBuilder& SetStaminaRegenerationRate(float val)
    {
        if (val >= 0.f)
        {
            this->staminaRegenRate = val;
            isStaminaRegenSet = true;
        }

        return *this;
    }

    UnitBuilder& SetManaRegenerationRate(float val)
    {
        if (val >= 0.f)
        {
            this->manaRegenRate = val;
            isManaRegenSet = true;
        }

        return *this;
    }

    UnitBuilder& SetSpeed(float val)
    {
        if (val > 0.f)
        {
            this->speed = val;
            isSpeedSet = true;
        }

        return *this;
    }

    UnitBuilder& SetAttackTime(float val)
    {
        if (val > 0.f)
        {
            this->attackTime = val;
            isAttackTimeSet = true;
        }

        return *this;
    }

    UnitBuilder& SetDeathAnimationTime(float val)
    {
        if (val > 0.f)
        {
            this->deathAnimTime = val;
            isDeathAnimationTimeSet = true;
        }

        return *this;
    }

    unique_ptr<UnitT> Build()
    {
        static_assert(std::is_base_of_v<BaseUnit<EntityT>, UnitT>,
            "UnitType must inherit from BaseUnit!");
        if (!_entity.has_value()) {
            throw std::logic_error("Entity was not set in UnitBuilder before Build()");
        }
        
        if (isSpeedSet == false) {
            throw std::logic_error("Speed was not set in UnitBuilder before Build()");
        }
        /*if (isAttackTimeSet == false) {
            throw std::logic_error("AttackTime was not set in UnitBuilder before Build()");
        }*/
        if (isHealingRateSet == false) {
            throw std::logic_error("HealingRate was not set in UnitBuilder before Build()");
        }
        if (isStaminaRegenSet == false) {
            throw std::logic_error("StaminaRegenRate was not set in UnitBuilder before Build()");
        }
        if (isManaRegenSet == false) {
            throw std::logic_error("ManaRegenRate was not set in UnitBuilder before Build()");
        }
        
        if (isSpawnPointSet == false) {
            throw std::logic_error("SpawnPoint was not set in UnitBuilder before Build()");
        }

        if (isPrimeTexturesSet == false) {
            throw std::logic_error("Textures were not set in UnitBuilder before Build()");
        }

        if (isProjectileSet == false) {
            throw std::logic_error("ProjectileType was not set in UnitBuilder before Build()");
        }

        /*if (isAnimationDurationSet == false) {
            throw std::logic_error("Animation time was not set in UnitBuilder before Build()");
        }*/

        if (isDeathAnimationTimeSet == false) {
            throw std::logic_error("Death Animation time was not set in UnitBuilder before Build()");
        }

        if (isCooldownSet == false) {
            throw std::logic_error("Cooldown was not set in UnitBuilder before Build()");
        }

        //if (isContainerSet == false) {
        //    throw std::logic_error("ProjectilesContainer was not set in UnitBuilder before Build()");
        //}

        unique_ptr<UnitT> result = make_unique<UnitT>( 
            _texturesPrime,
            _texturesSecondary,
            _spawnPoint,
            *_entity,
            _projectile,
            _cooldown, 
            _container);

        result->SetAnimationDuration(this->animationDuration);
        result->SetSpeed(this->speed);
        result->SetDeathAnimationTime(this->deathAnimTime);
        //result->SetAttackDelay(this->attackTime);
        result->SetEnergyRegainValue(this->staminaRegenRate);
        result->SetHPRegainValue(this->healingRate);
        result->SetManaRegainValue(this->manaRegenRate);

        return result;
    }

    void Reset()
    {
        _texturesPrime.clear();
        _texturesSecondary.clear();
        _spawnPoint = {};
        _entity.reset();
        _projectile = ProjectileType::None;
        _cooldown = 0.f;
        _container = nullptr;

        speed = 0.f;
        attackTime = 0.f;
        deathAnimTime = 0.f;
        healingRate = 0.f;
        staminaRegenRate = 0.f;
        manaRegenRate = 0.f;
        animationDuration = 0.f;

        isPrimeTexturesSet = false;
        isSecTexturesSet = false;
        isSpawnPointSet = false;
        isEntitySet = false;
        isProjectileSet = false;
        isCooldownSet = false;
        isContainerSet = false;
        isSpeedSet = false;
        isAttackTimeSet = false;
        isHealingRateSet = false;
        isStaminaRegenSet = false;
        isManaRegenSet = false;
        isAnimationDurationSet = false;
        isDeathAnimationTimeSet = false;
    }

};
