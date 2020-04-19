#ifndef INPUTSTATE_H
#define INPUTSTATE_H

#include <string>
#include <map>
#include <SDL.h>

class InputState {
public:
    SDL_KeyCode upKeyCode;
    SDL_KeyCode downKeyCode;
    SDL_KeyCode rightKeyCode;
    SDL_KeyCode leftKeyCode;
    SDL_KeyCode fireKeyCode;

    InputState();
    void UpdateInput();
    bool IsPressed(std::string inputId) const;

private:
    SDL_KeyCode GetSDLKeyCodeForInputId(std::string inputId) const;
    std::map<std::string, bool> inputIdToIsPressed = {
        { "Up", false },
        { "Right", false },
        { "Down", false },
        { "Left", false },
        { "Fire", false }
    };
};

#endif INPUTSTATE_H
