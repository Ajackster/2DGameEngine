#ifndef KEYBOARDCONTROL_H
#define KEYBOARDCONTROL_H

#include "../Game.h"
#include "../EntityManager.h"
#include "./Transform.h"
#include "./Sprite.h"

class KeyboardControl: public Component {
    public:
        SDL_KeyCode upKey;
        SDL_KeyCode downKey;
        SDL_KeyCode rightKey;
        SDL_KeyCode leftKey;
        SDL_KeyCode shootKey;
        Transform* transform;
        Sprite* sprite;
        
        KeyboardControl() {
            
        }
        
        KeyboardControl(std::string upKey, std::string rightKey, std::string downKey, std::string leftKey, std::string shootKey) {
            this->upKey = GetSDLKeyStringCode(upKey);
            this->rightKey = GetSDLKeyStringCode(rightKey);
            this->downKey = GetSDLKeyStringCode(downKey);
            this->leftKey = GetSDLKeyStringCode(leftKey);
            this->shootKey = GetSDLKeyStringCode(shootKey);
        }
        
        SDL_KeyCode GetSDLKeyStringCode(std::string key) {
            if (key.compare("up") == 0) return SDLK_w;
            if (key.compare("right") == 0) return SDLK_d;
            if (key.compare("down") == 0) return SDLK_s;
            if (key.compare("left") == 0) return SDLK_a;
            if (key.compare("shoot") == 0) return SDLK_SPACE;

            // who tf has an f24 key.
            return SDLK_F24;
        }
        
        void Initialize() override {
            transform = entity->GetComponent<Transform>();
            sprite = entity->GetComponent<Sprite>();
        }
        
        void Update(float deltaTime) override {
            if (Game::event.type == SDL_KEYDOWN) {
                int keyCode = Game::event.key.keysym.sym;

                if (keyCode == upKey) {
                    sprite->Play("UpAnimation");
                    transform->velocity.y = -200;
                }
                
                if (keyCode == rightKey) {
                    sprite->Play("RightAnimation");
                    transform->velocity.x = 200;
                }
                
                if (keyCode == downKey) {
                    sprite->Play("DownAnimation");
                    transform->velocity.y = 200;
                }
                
                if (keyCode == leftKey) {
                    sprite->Play("LeftAnimation");
                    transform->velocity.x = -200;
                }
                
                if (keyCode == shootKey) {
                    
                }
            }
            
            if (Game::event.type == SDL_KEYUP) {
                SDL_Keycode keyCode = Game::event.key.keysym.sym;
                if (keyCode == upKey) {
                    transform->velocity.y = 0;
                }
                
                if (keyCode == rightKey) {
                    transform->velocity.x = 0;
                }
                
                if (keyCode == downKey) {
                    transform->velocity.y = 0;
                }
                
                if (keyCode == leftKey) {
                    transform->velocity.x = 0;
                }
                
                if (keyCode == shootKey) {
                    
                }
            }
        }
};

#endif /* KEYBOARDCONTROL_H */

