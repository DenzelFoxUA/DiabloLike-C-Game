#pragma once
#include "ProjectileModels.h"

Texture ProjectileModels::arrowTexture;
Texture ProjectileModels::powerArrowTexture;

    void ProjectileModels::LoadTextures()
    {
        if (!arrowTexture.loadFromFile(ARROW_TEXTURES_SIMPLE_FOLDER + ARROW_TEXTURES_SIMPLE_FILE))
        {
            std::cout << "Error loading arrow texture!\n";
        }

        if (!powerArrowTexture.loadFromFile(ARROW_TEXTURES_EFFECTS_FOLDER + ARROW_TEXTURES_FIRE_FILE))
        {
            std::cout << "Error loading arrow texture!\n";
        }
    }

    Texture* ProjectileModels::GetSimpleArrowTex()
    {
        if (arrowTexture.getSize().x != 0 && arrowTexture.getSize().y != 0)
            return &arrowTexture;
        else
            throw exception("Texture of simple arrow wasnt loaded!");
    }

    Texture* ProjectileModels::GetPowerArrowTex()
    {
        if (powerArrowTexture.getSize().x != 0 && powerArrowTexture.getSize().y != 0)
            return &powerArrowTexture;
        else
            throw exception("Texture of power arrow wasnt loaded!");
    }

