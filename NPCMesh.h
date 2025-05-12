#pragma once

#include "CharacterMesh.h"

class NPCMesh : public CharacterMesh
{
protected:


public:
    NPCMesh(vector<TextureMeta> texturePathList, SpawnPoint spawnP)
        :CharacterMesh(texturePathList, spawnP) {
        if (!healthMeterTex.loadFromFile("textures/Characters/UIBars/NPC_health_meter.png")) {
            std::cout << "Failed to load: " << "\n";
        }

        if (!healthBarTex.loadFromFile("textures/Characters/UIBars/NPC_health_bar.png")) {
            std::cout << "Failed to load: " << "\n";
        }

        cout << "Bar texture loaded" << endl;
        healthBarSprite.setTexture(healthBarTex);
        healthBarSprite.setPosition(this->sprite.getPosition().x - 10.f, this->sprite.getPosition().y - 10.f);

        healthMeterSprite.setTexture(healthMeterTex);
        healthMeterSprite.setPosition(this->sprite.getPosition().x, this->sprite.getPosition().y);

    };


	Vector2f GetCenter() const override;
	Vector2f GetPosition() const override;

    void Update(float deltaTime, const sf::RenderWindow& window, float _hp, float hpMax,
        float stamina, float staminaMax, float mana, float manaMax) override
    {
        CharacterMesh::Update(deltaTime, window, _hp, hpMax);

        if (isDead)
        {
            cout << "This mesh is dead" << endl;
            return;
        }
        // Рухаємо бар над головою
        sf::Vector2f spritePos = sprite.getPosition();
        healthMeterSprite.setPosition(spritePos.x, spritePos.y);
        healthBarSprite.setPosition(spritePos.x - 10.f, spritePos.y - 10.f);

        // Оновлюємо обрізку — бар зменшується при втраті HP
        float hp = _hp;         // ← заміни на актуальний метод
        float maxHp = hpMax;        // ← заміни на актуальний метод

        float ratio = static_cast<float>(hp) / std::max(1.f, maxHp);
        int meter_fullWidth = healthMeterTex.getSize().x;
        int meter_height = healthMeterTex.getSize().y;
        int meter_visibleWidth = std::max(1, static_cast<int>(meter_fullWidth * ratio));

        healthMeterSprite.setTexture(healthMeterTex, true); // важливо: true = зберегти rect
        healthMeterSprite.setTextureRect(sf::IntRect(0, 0, meter_visibleWidth, meter_height));
    }

    void Draw(sf::RenderWindow& window) override
    {
        CharacterMesh::Draw(window);
        if (!isDead)
        {
            window.draw(healthBarSprite);
            window.draw(healthMeterSprite);
        }

    }
};
