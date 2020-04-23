#ifndef INPUTSTATE_H
#define INPUTSTATE_H

#include <string>
#include <map>
#include <SDL.h>

class InputState {
public:
    enum class Axis {
        HORIZONTAL,
        VERTICAL
    };

    SDL_KeyCode upKeyCode;
    SDL_KeyCode downKeyCode;
    SDL_KeyCode rightKeyCode;
    SDL_KeyCode leftKeyCode;
    SDL_KeyCode fireKeyCode;

    InputState();
    void UpdateInput();
    bool IsPressed(std::string inputId) const;
    float GetAxis(Axis axis) const;

private:
    float horizontalAxis;
    float verticalAxis;
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
