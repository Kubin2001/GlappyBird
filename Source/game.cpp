#include <iostream>
#include <SDL.h>
#include <ctime>
#include <string>
#include "SDL_image.h"
#include "game.h"
#include "Font.h"
#include "SDL_mixer.h"

extern bool status;

Game::Game() {
    window = nullptr;
    renderer = nullptr;
    player = nullptr;
    map = nullptr;
    font = nullptr;
}

void Game::initialize() {


    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    player = new Player(renderer);
    map = new Map(renderer);
    font = new Font();

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);


    soundFling = Mix_LoadWAV("Sounds/fling.wav");
    soundPoint = Mix_LoadWAV("Sounds/point.wav");
    soundLose = Mix_LoadWAV("Sounds/lose.wav");

    font->SetTexture(load("Textures/font.png", renderer));

    font->LoadText(40, 29, 29);

    background = (load("Textures/background.png", renderer));

    player->SetTexture(load("Textures/player.png", renderer));

    map->SetTexture(load("Textures/column.png", renderer));

    map->CreateMap();

}

void Game::update() {
    map->MoveMap();
}

void Game::events() {
    SDL_PumpEvents();
    const Uint8* state = SDL_GetKeyboardState(NULL);
    player->Movement(state,soundFling);
    if (map->CheckPoints(player)) {
        points++;
        Mix_PlayChannel(-1, soundPoint, 0);
        previousPoints = points;
    }

    if (map->GetSpeed() < 30) {
        if (points % 3 == 0 && points > 0 && points == previousPoints) {
            int value = map->GetSpeed();
            value++;
            map->SetSpeed(value);
            previousPoints--;
        }
    }

    if (map->GetWidth() > 80) {
        if (points % 7 == 0 && points > 0 && points == previousPoints) {
            int value = map->GetWidth();
            value--;
            map->SetWidth(value);
            previousPoints--;
        }
    }

    if (map->Collision(player)) {
        Mix_PlayChannel(-1, soundLose, 0);
        SDL_Delay(2000);
        map->Reset();
        player->Reset();
        points = 0;
        previousPoints = 0;
    }

    if (state[SDL_SCANCODE_ESCAPE]) { status = false; }
}

void Game::render() {

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, NULL, &backgroundRectangle);
    player->Render();
    map->Render();
    font->RenderText(renderer, "SCORE:" +std::to_string(points), 50, 50, 29, 29, 30);
    SDL_RenderPresent(renderer);
}

SDL_Texture* Game::load(const char* file, SDL_Renderer* ren) {
    SDL_Surface* tmpSurface = IMG_Load(file);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tmpSurface);
    SDL_FreeSurface(tmpSurface);
    return tex;
}


Game::~Game() {
    delete player;
    delete map;
}