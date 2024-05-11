#pragma once
#include <iostream>
#include <SDL.h>
#include "SDL_mixer.h"


class Player
{
    private:
        SDL_Renderer* renderer;
        SDL_Texture * texture = nullptr;
        SDL_Rect rectangle{640, 360, 62, 40};
        int buffer = 0;

    public:
        Player(SDL_Renderer* renderer);

        SDL_Texture *GetTexture();

        void SetTexture(SDL_Texture* temptex);

        SDL_Rect* GetRectangle();

        void Render();

        void Reset();

        void Movement(const Uint8* state, Mix_Chunk* sound);

        ~Player();
};
