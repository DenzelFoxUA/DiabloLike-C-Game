#include "Animation.h"

Animation::Animation(sf::Sprite& spriteRef, float framesDuration) : sprite(spriteRef) 
{
    this->frameDuration = framesDuration;
}

void Animation::SetSheet(sf::Texture* tex, int frameW, int frameH, int cols, int frames, bool mustBeLooped) {
    texture = tex;
    frameWidth = frameW;
    frameHeight = frameH;
    columns = cols;
    totalFrames = frames;
    currentFrame = 0;
    frameTimer = 0.f;
    sprite.setTexture(*texture);

    this->mustBeLooped = mustBeLooped;
    isFinished = false;

    sprite.setTexture(*texture);

    //remove bug of multiplying character
    sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
}

void Animation::Update(float deltaTime) {

    if (isFinished || !texture || paused) return;

    frameTimer += deltaTime;
    if (frameTimer >= frameDuration)
    {
        frameTimer = 0.f;
        currentFrame++;

        if (currentFrame >= totalFrames)
        {
            if (mustBeLooped)
                currentFrame = 0;
            else {
                currentFrame = totalFrames - 1;
                isFinished = true;
            }
        }

        int frameX = (currentFrame % columns) * frameWidth;
        int frameY = (currentFrame / columns) * frameHeight;
        sprite.setTextureRect(sf::IntRect(frameX, frameY, frameWidth, frameHeight));
    }
}

void Animation::Reset() {
    currentFrame = 0;
    frameTimer = 0.f;
    isFinished = false;
}

bool Animation::IsFinished() const
{
    return isFinished;
}
