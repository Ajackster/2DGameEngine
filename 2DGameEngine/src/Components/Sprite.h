#ifndef SPRITE_H
#define SPRITE_H

#include <SDL.h>
#include "../TextureManager.h"
#include "../AssetManager.h"
#include "../Animation.h";
#include "./Transform.h";

class Sprite: public Component {
    public:
        SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
        Sprite(std::string id);
        Sprite(std::string id, bool isAnimated, bool isFixed);
        ~Sprite();
        void AddAnimation(std::string name, unsigned int sheetRow, unsigned int sheetColStart, unsigned int numFrames, unsigned int animationDurationMS);
        bool IsPlayingAnimation(std::string animationName) const;
        void Play(std::string animationName);
        void SetTexture(std::string textureId);
        void Initialize() override;
        void Update(float deltaTime);
        void Render() override;

    private:
        Transform* transform;
        SDL_Texture* texture;
        SDL_Rect sourceRectangle;
        SDL_Rect destinationRectangle;
        bool isAnimated;
        int numFrames;
        int animationDurationMS;
        bool isFixed;
        std::map<std::string, Animation> animations;
        std::string currentAnimationName;
        unsigned int animationRow = 0;
        unsigned int animationColStart = 0;
};

#endif /* SPRITE_H */

