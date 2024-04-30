#pragma once
#include <iostream>
#include <SDL.h>
#include <vector>
#include "Player.h"

class Pillar {
private:
    SDL_Rect rectangle;

public:
    SDL_Rect* GetRectangle();
};


class Map
{
    private:
        SDL_Renderer* renderer;
        SDL_Texture * texturePillar = nullptr;
        std::vector<Pillar> pillars;
        int speed = 2;
        int width = 200;
        bool PointPossiblity = true;

    public:
        Map(SDL_Renderer* renderer);

        SDL_Texture *GetTexture();

        void SetTexture(SDL_Texture* temptex);

        SDL_Rect* GetRectangle();

        void SetSpeed(int temp);

        int GetSpeed();

        void SetWidth(int temp);

        int GetWidth();

        void Render();

        void MoveMap();

        void CreateMap();

        bool Collision(Player* player);

        void Reset();

        bool CheckPoints(Player* player);

        ~Map();
};
