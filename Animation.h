
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Animation {
private:
    sf::Sprite& sprite;
    sf::Texture* texture = nullptr;

    int frameWidth = 0;
    int frameHeight = 0;
    int columns = 0;
    int totalFrames = 0;
    int currentFrame = 0;
    float frameTimer = 0.f;
    float frameDuration = 0.1f;

    bool isFinished = false,
        mustBeLooped = true,
        isPaused = false;

public:

    Animation() = delete;
    Animation(sf::Sprite& spriteRef, float framesDuration = 0.05f);

    void SetSheet(sf::Texture* tex, int frameW, int frameH, int cols, int frames, bool mustBeLooped = true);
    void Update(float deltaTime);
    void Reset();
    bool IsFinished() const;
    bool IsPaused() const {
        return isPaused;
    }
    void SetFrameDuration(float newValue);
    void FreezeOnMidFrame();
    void Resume();
};
