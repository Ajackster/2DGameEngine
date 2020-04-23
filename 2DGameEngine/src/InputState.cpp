#include <iostream>
#include "InputState.h"
#include "Game.h"
#include "Constants.h"

InputState::InputState() {
    this->upKeyCode = GetSDLKeyCodeForInputId("Up");
    this->rightKeyCode = GetSDLKeyCodeForInputId("Right");
    this->downKeyCode = GetSDLKeyCodeForInputId("Down");
    this->leftKeyCode = GetSDLKeyCodeForInputId("Left");
    this->fireKeyCode = GetSDLKeyCodeForInputId("Fire");
}

void InputState::UpdateInput() {
    // Handle joystick controls
    if (Game::event.type == SDL_JOYAXISMOTION) {
        // Ensure the event is coming from one joystick
        int sdlHorizontalAxis = SDL_JoystickGetAxis(Game::joystick, 0);
        int sdlVerticalAxis = SDL_JoystickGetAxis(Game::joystick, 1);
        
        if (sdlHorizontalAxis < JOYSTICK_DEADZONE * -1) {
            this->horizontalAxis = sdlHorizontalAxis / 32768.0f;
        }
        else if (sdlHorizontalAxis > JOYSTICK_DEADZONE) {
            this->horizontalAxis = sdlHorizontalAxis / 32767.0f;
        }
        else {
            this->horizontalAxis = 0;
        }

        if (sdlVerticalAxis < JOYSTICK_DEADZONE * -1) {
            this->verticalAxis = sdlVerticalAxis / 32768.0f;
        }
        else if (sdlVerticalAxis > JOYSTICK_DEADZONE) {
            this->verticalAxis = sdlVerticalAxis / 32767.0f;
        }
        else {
            this->verticalAxis = 0;
        }
    }

    if (Game::event.type == SDL_KEYDOWN) {
        int keyCode = Game::event.key.keysym.sym;

        if (keyCode == upKeyCode) {
            inputIdToIsPressed["Up"] = true;
            this->verticalAxis = -1;
        }

        if (keyCode == rightKeyCode) {
            inputIdToIsPressed["Right"] = true;
            this->horizontalAxis = 1;
        }

        if (keyCode == downKeyCode) {
            inputIdToIsPressed["Down"] = true;
            this->verticalAxis = 1;
        }

        if (keyCode == leftKeyCode) {
            inputIdToIsPressed["Left"] = true;
            this->horizontalAxis = -1;
        }

        if (keyCode == fireKeyCode) {
            inputIdToIsPressed["Fire"] = true;
        }
    }

    if (Game::event.type == SDL_KEYUP) {
        SDL_Keycode keyCode = Game::event.key.keysym.sym;
        if (keyCode == upKeyCode) {
            inputIdToIsPressed["Up"] = false;
            this->verticalAxis = 0;
        }

        if (keyCode == rightKeyCode) {
            inputIdToIsPressed["Right"] = false;
            this->horizontalAxis = 0;
        }

        if (keyCode == downKeyCode) {
            inputIdToIsPressed["Down"] = false;
            this->verticalAxis = 0;
        }

        if (keyCode == leftKeyCode) {
            inputIdToIsPressed["Left"] = false;
            this->horizontalAxis = 0;
        }

        if (keyCode == fireKeyCode) {
            inputIdToIsPressed["Fire"] = false;
        }
    }
}

float InputState::GetAxis(Axis axis) const {
    switch (axis) {
        case Axis::HORIZONTAL: {
            return this->horizontalAxis;
        }
        case Axis::VERTICAL: {
            return this->verticalAxis;
        }
        default: {
            return 0.0f;
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
