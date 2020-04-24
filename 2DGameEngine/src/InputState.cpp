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
    float newHorizontalAxis = 0;
    float newVerticalAxis = 0;

    if (Game::event.type == SDL_JOYAXISMOTION) {
        // Ensure the event is coming from one joystick
        int sdlHorizontalAxis = SDL_JoystickGetAxis(Game::joystick, 0);
        int sdlVerticalAxis = SDL_JoystickGetAxis(Game::joystick, 1);

        if (sdlHorizontalAxis < JOYSTICK_DEADZONE * -1) {
            newHorizontalAxis = sdlHorizontalAxis / 32768.0f;
        }
        else if (sdlHorizontalAxis > JOYSTICK_DEADZONE) {
            newHorizontalAxis = sdlHorizontalAxis / 32767.0f;
        }
        else {
            newHorizontalAxis = 0;
        }

        if (sdlVerticalAxis < JOYSTICK_DEADZONE * -1) {
            newVerticalAxis = sdlVerticalAxis / 32768.0f;
        }
        else if (sdlVerticalAxis > JOYSTICK_DEADZONE) {
            newVerticalAxis = sdlVerticalAxis / 32767.0f;
        }
        else {
            newVerticalAxis = 0;
        }
    }

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

    // TODO: Make sure left->right overrides input like left<-right does. Same goes for up & down.
    if (IsPressed("Up")) {
        newVerticalAxis = -1;
    }

    if (IsPressed("Right")) {
        newHorizontalAxis = 1;
    }

    if (IsPressed("Down")) {
        newVerticalAxis = 1;
    }

    if (IsPressed("Left")) {
        newHorizontalAxis = -1;
    }

    this->horizontalAxis = newHorizontalAxis;
    this->verticalAxis = newVerticalAxis;
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
