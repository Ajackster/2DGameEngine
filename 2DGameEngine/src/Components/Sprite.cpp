#include "Sprite.h"

SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
Sprite::Sprite(std::string id) {
    isAnimated = false;
    isFixed = false;
    SetTexture(id);
}

Sprite::Sprite(std::string id, int numFrames, int animationSpeed, bool hasDirections, bool isFixed) {
    isAnimated = true;
    this->numFrames = numFrames;
    this->animationSpeed = animationSpeed;
    this->isFixed = isFixed;

    if (hasDirections) {
        Animation downAnimation = Animation(0, numFrames, animationSpeed);
        Animation rightAnimation = Animation(1, numFrames, animationSpeed);
        Animation leftAnimation = Animation(2, numFrames, animationSpeed);
        Animation upAnimation = Animation(3, numFrames, animationSpeed);

        animations.emplace("DownAnimation", downAnimation);
        animations.emplace("RightAnimation", rightAnimation);
        animations.emplace("LeftAnimation", leftAnimation);
        animations.emplace("UpAnimation", upAnimation);

        this->animationIndex = 0;
        this->currentAnimationName = "DownAnimation";
    }
    else {
        Animation singleAnimation = Animation(0, numFrames, animationSpeed);
        animations.emplace("SingleAnimation", singleAnimation);
        this->animationIndex = 0;
        this->currentAnimationName = "SingleAnimation";
    }

    Play(this->currentAnimationName);
    SetTexture(id);
}

bool Sprite::IsPlayingAnimation(std::string animationName) const {
    return currentAnimationName == animationName;
}

void Sprite::Play(std::string animationName) {
    numFrames = animations[animationName].numFrames;
    animationIndex = animations[animationName].index;
    animationSpeed = animations[animationName].animationSpeed;
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
    if (isAnimated) {
        sourceRectangle.x = sourceRectangle.w * static_cast<int>((SDL_GetTicks() / animationSpeed) % numFrames);
    }
    sourceRectangle.y = animationIndex * transform->height;

    if (isFixed) {
        destinationRectangle.x = static_cast<int>(transform->GetPosition().x);
        destinationRectangle.y = static_cast<int>(transform->GetPosition().y);
    }
    else {
        destinationRectangle.x = static_cast<int>(transform->GetPosition().x) - Game::camera.x;
        destinationRectangle.y = static_cast<int>(transform->GetPosition().y) - Game::camera.y;
    }

    destinationRectangle.w = transform->width * transform->scale;
    destinationRectangle.h = transform->height * transform->scale;
}

void Sprite::Render() {
    TextureManager::Draw(texture, sourceRectangle, destinationRectangle, spriteFlip);
}
