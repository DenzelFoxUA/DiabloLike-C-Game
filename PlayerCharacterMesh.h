#pragma once
#include "CharacterMesh.h"
#include "JSONTextureLoader.h"
#include "PathsConfig.h"

class PlayerCharacterMesh : public CharacterMesh
{
    sf::Sprite staminaMeterSprite;
    Texture staminaMeterTex;

    sf::Sprite manaMeterSprite;
    Texture manaMeterTex;

public:

    PlayerCharacterMesh(vector<TextureMeta> texturePathList, SpawnPoint spawnP) :CharacterMesh(texturePathList, spawnP)
    {
        map<UI_Parts, Texture> textures = 
           move(JSONTextureLoader::LoadPlayerUITextures(JSON_TEXTURES_PATH + PLAYER_UI_TEX_FILE));

        for (auto& [key,tex] : textures)
        {
            cout << key << endl;
            if (key == UI_Parts::PlayerHealthBar)
            {
                this->healthBarTex = move(tex);
            }
            else if (key == UI_Parts::PlayerHealthMeter)
            {
                this->healthMeterTex = move(tex);
            }
            else if (key == UI_Parts::PlayerManaMeter)
            {
                this->manaMeterTex = move(tex);
            }
            else if (key == UI_Parts::PlayerStaminaMeter)
            {
                this->staminaMeterTex = move(tex);
            }
        }

        staminaMeterSprite.setTexture(staminaMeterTex);
        staminaMeterSprite.setPosition(105, 80);

        manaMeterSprite.setTexture(manaMeterTex);
        manaMeterSprite.setPosition(105, 100);

        healthMeterSprite.setTexture(healthMeterTex);
        healthMeterSprite.setPosition(85, 30);

        healthBarSprite.setTexture(healthBarTex);
        healthBarSprite.setPosition(20, 20);
    };

    Vector2f GetCenter() const override;
    Vector2f GetPosition() const override;

    virtual void Update(float deltaTime, const sf::RenderWindow& window, 
        float _hp, float hpMax, 
        float _stamina, float staminaMax,
        float _mana, float manaMax) override
    {
        CharacterMesh::Update(deltaTime, window, _hp, hpMax);

        UpdateBar(healthMeterSprite, healthMeterTex, hpMax, _hp);
        UpdateBar(staminaMeterSprite, staminaMeterTex, staminaMax, _stamina);
        UpdateBar(manaMeterSprite, manaMeterTex, manaMax, _mana);
    }

    void Draw(sf::RenderWindow& window) override {

        CharacterMesh::Draw(window);
        window.draw(manaMeterSprite);
        window.draw(staminaMeterSprite);
        window.draw(healthMeterSprite);
        window.draw(healthBarSprite);

    }

    void UpdateBar(sf::Sprite& source, Texture& texture, float maxVal, float val)
    {
        float _val = val;
        float _maxVal = maxVal;

        float ratio = static_cast<float>(_val) / std::max(1.f, _maxVal);
        int meter_fullWidth = texture.getSize().x;
        int meter_height = texture.getSize().y;
        int meter_visibleWidth = std::max(1, static_cast<int>(meter_fullWidth * ratio));

        source.setTexture(texture, true);
        source.setTextureRect(sf::IntRect(0, 0, meter_visibleWidth, meter_height));
    }
};