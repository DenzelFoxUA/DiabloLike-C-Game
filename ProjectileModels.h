#pragma once
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "PathsConfig.h"

using namespace ArrowsPaths;
using namespace sf;

static class ProjectileModels
{
protected:
    static Texture arrowTexture;
    static Texture powerArrowTexture;

public:

    static void LoadTextures();

    static Texture* GetSimpleArrowTex();

    static Texture* GetPowerArrowTex();
    
};
