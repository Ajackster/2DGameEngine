#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include "./Entity.h"
#include "./Component.h"
#include "./EntityManager.h"
#include "./AssetManager.h"
#include "./InputManager.h"

class AssetManager;

class Game {
public:
    Game();
    ~Game();
    static SDL_Renderer* renderer;
    static AssetManager* assetManager;
    static InputManager* inputManager;
    static SDL_Event event;
    static SDL_Rect camera;

    int ticksLastFrame;
    bool IsRunning() const;
    void Initialize(int width, int height);
    void LoadLevel(int levelNumber);
    void ProcessInput();
    void Update();
    void Render();
    void Destroy();
    void HandleCameraMovement();
private:
    bool isRunning;
    SDL_Window *window;
};

#endif