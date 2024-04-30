#include <iostream>
#include <SDL.h>
#include <ctime>
#include "Map.h"
#include "Colision.h"
#include "Player.h"

Map::Map(SDL_Renderer * renderer) {
    this->renderer = renderer;
}

SDL_Texture* Map::GetTexture() {
    return texturePillar;
}

void Map::SetTexture(SDL_Texture * temptex) {
    texturePillar = temptex;
}

void Map::SetSpeed(int temp) {
    speed = temp;
}

int Map::GetSpeed() {
    return speed;
}

void Map::SetWidth(int temp) {
    width = temp;
}

int Map::GetWidth() {
    return width;
}

void Map::Render() {
    for (int i = 0; i < pillars.size(); i++)
    {
        SDL_RenderCopy(renderer, texturePillar, NULL, pillars[i].GetRectangle());
    }
}

void Map::MoveMap() {
    for (int i = 0; i < pillars.size(); i++)
    {
        pillars[i].GetRectangle()->x-= speed;
    }
    if (pillars[0].GetRectangle()->x < -100) {
        PointPossiblity = true;
        int random = rand() % 11 +4;
        random *= 50;
        for (int i = 0; i < pillars.size(); i++)
        {
            pillars[i].GetRectangle()->x = 1400;
            if (i == 0) {
                pillars[i].GetRectangle()->h = random;
            }
            else
            {
                pillars[i].GetRectangle()->y = pillars[0].GetRectangle()->y + pillars[0].GetRectangle()->h + width;
            }
        }
    }

}

bool Map::CheckPoints(Player * player) {
    if (PointPossiblity) {
        if (player->GetRectangle()->x > pillars[0].GetRectangle()->x) {
            PointPossiblity = false;
            return 1;
        }
    }
    return 0;
}

void Map::CreateMap() {
    Pillar pillar;
    pillars.push_back(pillar);
    pillars[0].GetRectangle()->x = 1000;
    pillars[0].GetRectangle()->y = -100;
    pillars[0].GetRectangle()->w = 100;
    pillars[0].GetRectangle()->h = 400;
    pillars.push_back(pillar);
    pillars[1].GetRectangle()->x = 1000;
    pillars[1].GetRectangle()->y = pillars[0].GetRectangle()->y + pillars[0].GetRectangle()->h + 200;
    pillars[1].GetRectangle()->w = 100;
    pillars[1].GetRectangle()->h = 1000;
    
}

bool Map::Collision(Player* player) {
    for (int i = 0; i < pillars.size(); i++)
    {
        if (SimpleCollision(*player->GetRectangle(), *pillars[i].GetRectangle())){
            return 1;
        }
    }
    if (player->GetRectangle()->y < -50 || player->GetRectangle()->y > 800) {
        return 1;
    }
    return 0;

}

void Map::Reset() {
    pillars.clear();
    speed = 2;
    width = 200;
    PointPossiblity = true;
    CreateMap();
}

Map::~Map() {
    SDL_DestroyTexture(texturePillar);
}

SDL_Rect* Pillar::GetRectangle() {
    return &rectangle;
}

