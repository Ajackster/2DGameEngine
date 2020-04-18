#include <iostream>
#include "./Constants.h"
#include "./Game.h"
#include "./AssetManager.h"
#include "./Map.h"
#include "../lib/glm/glm.hpp"

#include "./Components/Transform.h"
#include "./Components/Sprite.h"
#include "./Components/KeyboardControl.h";

EntityManager entityManager;
AssetManager* Game::assetManager = new AssetManager(&entityManager);
SDL_Renderer* Game::renderer;
SDL_Event Game::event;
SDL_Rect Game::camera = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
Map* map;

Entity& playerEntity(entityManager.AddEntity("chopper", LayerType::PLAYER_LAYER));

Game::Game() {
    this->isRunning = false;
}

Game::~Game() {
}

bool Game::IsRunning() const {
    return this->isRunning;
}

void Game::Initialize(int width, int height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error initializing SDL." << std::endl;
        return;
    }

    window = SDL_CreateWindow(
            NULL,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width,
            height,
            SDL_WINDOW_BORDERLESS
            );

    if (!window) {
        std::cerr << "Error creating SDL window." << std::endl;
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        std::cerr << "Error creating SDL renderer." << std::endl;
        return;
    }

    LoadLevel(0);

    isRunning = true;
    return;
}

void Game::LoadLevel(int levelNumber) {
    // Start including new assets to the AssetManager list
    assetManager->AddTexture("chopper-image", std::string("./assets/images/chopper-spritesheet.png").c_str());
    assetManager->AddTexture("tank-image", std::string("./assets/images/tank-big-right.png").c_str());
    assetManager->AddTexture("jungle-tiletexture", std::string("./assets/tilemaps/jungle.png").c_str());
    
    map = new Map("jungle-tiletexture", 2, 32, 32);
    map->LoadMap("./assets/tilemaps/jungle.map", 25, 20);
    
    // Start including entities
    playerEntity.AddComponent<Transform>(240, 160, 0, 0, 32, 32, 1);
    playerEntity.AddComponent<Sprite>("chopper-image", 2, 90, true, false);
    playerEntity.AddComponent<KeyboardControl>("up", "right", "down", "left", "space");

    Entity& tankEntity(entityManager.AddEntity("tank", LayerType::ENEMY_LAYER));
    tankEntity.AddComponent<Transform>(0, 0, 20, 20, 32, 32, 1);
    tankEntity.AddComponent<Sprite>("tank-image");
}

void Game::ProcessInput() {
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
        {
            isRunning = false;
            break;
        }
        case SDL_KEYDOWN:
        {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                isRunning = false;
            }
            break;
        }

        default:
        {
            break;
        }
    }
}

void Game::Update() {
    // Wait until target frame miliseconds has elapsed since the last frame.
    int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - ticksLastFrame);

    // Delay update if we are too fast for the target time.
    if (timeToWait > 0 && timeToWait < FRAME_TARGET_TIME) {
        SDL_Delay(timeToWait);
    }

    // Delta time is the difference in ticks from last frame converted to miliseconds
    float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;
    ticksLastFrame = SDL_GetTicks();

    // Clamp delta time so we never use a super high value
    deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

    entityManager.Update(deltaTime);

    HandleCameraMovement();
}

void Game::Render() {
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    // TODO: Here we call the manager.render to render all entities
    if (entityManager.HasNoEntities()) {
        return;
    }

    entityManager.Render();

    SDL_RenderPresent(renderer);
}

void Game::HandleCameraMovement() {
    Transform* playerTransform = playerEntity.GetComponent<Transform>();

    camera.x = playerTransform->position.x - (camera.w / 2);
    camera.y = playerTransform->position.y - (camera.h / 2);
}

void Game::Destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}