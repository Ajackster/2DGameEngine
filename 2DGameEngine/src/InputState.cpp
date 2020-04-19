#include "InputState.h"
#include "Game.h"

InputState::InputState() {
    this->upKeyCode = GetSDLKeyCodeForInputId("Up");
    this->rightKeyCode = GetSDLKeyCodeForInputId("Right");
    this->downKeyCode = GetSDLKeyCodeForInputId("Down");
    this->leftKeyCode = GetSDLKeyCodeForInputId("Left");
    this->fireKeyCode = GetSDLKeyCodeForInputId("Fire");
}

void InputState::UpdateInput() {
    if (Game::event.type == SDL_KEYDOWN) {
        int keyCode = Game::event.key.keysym.sym;

        if (keyCode == upKeyCode) {
            inputIdToIsPressed["Up"] = true;
        }

        if (keyCode == rightKeyCode) {
            inputIdToIsPressed["Right"] = true;
        }

        if (keyCode == downKeyCode) {
            inputIdToIsPressed["Down"] = true;
        }

        if (keyCode == leftKeyCode) {
            inputIdToIsPressed["Left"] = true;
        }

        if (keyCode == fireKeyCode) {
            inputIdToIsPressed["Fire"] = true;
        }
    }

    if (Game::event.type == SDL_KEYUP) {
        SDL_Keycode keyCode = Game::event.key.keysym.sym;
        if (keyCode == upKeyCode) {
            inputIdToIsPressed["Up"] = false;
        }

        if (keyCode == rightKeyCode) {
            inputIdToIsPressed["Right"] = false;
        }

        if (keyCode == downKeyCode) {
            inputIdToIsPressed["Down"] = false;
        }

        if (keyCode == leftKeyCode) {
            inputIdToIsPressed["Left"] = false;
        }

        if (keyCode == fireKeyCode) {
            inputIdToIsPressed["Fire"] = false;
        }
    }
}

bool InputState::IsPressed(std::string inputId) const {
    return inputIdToIsPressed.at(inputId);
}

SDL_KeyCode InputState::GetSDLKeyCodeForInputId(std::string inputId) const {
    if (inputId.compare("Up") == 0) return SDLK_w;
    if (inputId.compare("Right") == 0) return SDLK_d;
    if (inputId.compare("Down") == 0) return SDLK_s;
    if (inputId.compare("Left") == 0) return SDLK_a;
    if (inputId.compare("Shoot") == 0) return SDLK_SPACE;

    // who tf has an f24 key.
    return SDLK_F24;
}
