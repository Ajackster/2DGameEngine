#include <iostream>
#include "Sprite.h"
#include "../Utils.h"

Sprite::Sprite(std::string id) {
    isAnimated = false;
    isFixed = false;
    SetTexture(id);
}

Sprite::Sprite(std::string id, bool isAnimated, bool isFixed) {
    this->isAnimated = isAnimated;
    this->numFrames = numFrames;
    this->animationDurationMS = animationDurationMS;
    this->isFixed = isFixed;

    SetTexture(id);
}

Sprite::~Sprite() {
    animations.erase(animations.begin(), animations.end());
}

void Sprite::AddAnimation(std::string name, unsigned int sheetRow, unsigned int sheetColStart, unsigned int numFrames, unsigned int animationDurationMS) {
    if (animations.count(name) == 1) {
        std::cerr << "Tried to add an animation that was already added to sprite" << std::endl;
        return;
    }

    Animation newAnimation = Animation(sheetRow, sheetColStart, numFrames, animationDurationMS);
    animations.emplace(name, newAnimation);
}

bool Sprite::IsPlayingAnimation(std::string animationName) const {
    return currentAnimationName == animationName;
}

void Sprite::Play(std::string animationName) {
    if (IsPlayingAnimation(animationName)) {
        return;
    }

    if (animations.count(animationName) == 0) {
        std::cerr << "Tried to play an animation that does not exist for the sprite" << std::endl;
        return;
    }

    numFrames = animations[animationName].numFrames;
    animationRow = animations[animationName].row;
    animationColStart = animations[animationName].colStart;
    animationDurationMS = animations[animationName].animationDurationMS;
    currentAnimationName = animationName;
}

void Sprite::SetTexture(std::string textureId) {
    texture = Game::assetManager->GetTexture(textureId);
}

void Sprite::Initialize() {
    transform = entity->GetComponent<Transform>();
    sourceRectangle.x = 0;
    sourceRectangle.y = 0;
    sourceRectangle.w = transform->width;
    sourceRectangle.h = transform->height;
}

void Sprite::Update(float deltaTime) {
    if (isAnimated && animationDurationMS != 0) {
        sourceRectangle.x =  sourceRectangle.w * (animationColStart + static_cast<int>((SDL_GetTicks() / animationDurationMS) % numFrames));
        sourceRectangle.y = animationRow * transform->height;
    }

    destinationRectangle.w = transform->width * transform->scale;
    destinationRectangle.h = transform->height * transform->scale;

    glm::vec2 isometricPosition = transform->GetIsometricPosition();
    if (isFixed) {
        destinationRectangle.x = static_cast<int>(isometricPosition.x);
        destinationRectangle.y = static_cast<int>(isometricPosition.y);
    }
    else {
        destinationRectangle.x = static_cast<int>(isometricPosition.x) - Game::camera.x;
        destinationRectangle.y = static_cast<int>(isometricPosition.y) - Game::camera.y;
    }
}

void Sprite::Render() {
    TextureManager::Draw(texture, sourceRectangle, destinationRectangle, SDL_FLIP_NONE);
}
