#include <iostream>
#include "./Constants.h"
#include "./Game.h"
#include "./Map.h"
#include "../lib/glm/glm.hpp"
#include "Utils.h"

#include "./Components/Transform.h"
#include "./Components/Sprite.h"
#include "./Components/PlayerController.h";
#include "./Components/Avatar.h"
#include "./Components/TileCollider.h"

EntityManager entityManager;
AssetManager* Game::assetManager = new AssetManager(&entityManager);
InputState* Game::inputState = new InputState();
SDL_Renderer* Game::renderer;
SDL_Joystick* Game::joystick;
SDL_Event Game::event;
SDL_Rect Game::camera = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
Map* Game::map;

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

    joystick = SDL_JoystickOpen(0);

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

    for (auto entity : entityManager.GetEntities()) {
        entity->Initialize();
    }

    isRunning = true;
    return;
}

void Game::LoadLevel(int levelNumber) {
    // Start including new assets to the AssetManager list
    assetManager->AddTexture("player-sheet", std::string("./assets/images/player.png").c_str());
    assetManager->AddTexture("tank-image", std::string("./assets/images/tank-big-right.png").c_str());
    assetManager->AddTexture("snow-tilemap", std::string("./assets/tilemaps/snow.png").c_str());
    assetManager->AddTexture("water-tilemap", std::string("./assets/tilemaps/water.png").c_str());
    
    map = new Map("water-tilemap", "snow-tilemap", 1, 256, 128);
    map->LoadMap(50, 50);
    
    // Start including entities
    playerEntity.AddComponent<Transform>(240, 160, 128, 128, 1);
    playerEntity.AddComponent<Sprite>("player-sheet", true, false);
    playerEntity.AddComponent<Avatar>();
    playerEntity.AddComponent<PlayerController>();
    playerEntity.AddComponent<TileCollider>();
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
    inputState->UpdateInput();

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
    glm::vec2 isometricCoord = utils::CartesianToIsometric(playerTransform->GetPosition());

    camera.x = isometricCoord.x - (camera.w / 2.5);
    camera.y = isometricCoord.y - (camera.h / 2.5);
}

void Game::Destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
