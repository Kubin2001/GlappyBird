#pragma once
#include <SDL.h>
#include "Player.h"
#include "Map.h"
#include "Font.h"
#include "SDL_mixer.h"


class Game {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* background;
    Player* player;
    Font* font;
    Map* map;
    SDL_Rect backgroundRectangle{ 0, 0, 1280, 720 };
    int points = 0;
    int previousPoints = 0;
    Mix_Chunk* soundFling = nullptr;
    Mix_Chunk* soundPoint = nullptr;
    Mix_Chunk* soundLose = nullptr;



public:
    Game();

    void initialize();

    void update();

    void events();

    void render();

    SDL_Texture* load(const char *file, SDL_Renderer* ren);

    ~Game();
};

