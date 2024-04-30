#include <iostream>
#include <SDL.h>
#include "Player.h"

Player::Player(SDL_Renderer * renderer) {
    this->renderer = renderer;
}

SDL_Texture* Player::GetTexture() {
    return texture;
}

void Player::SetTexture(SDL_Texture * temptex) {
    texture = temptex;
}

SDL_Rect* Player::GetRectangle() {
    return &rectangle;
}

void Player::Render() {
    if (buffer == 0) {
        SDL_RenderCopy(renderer, texture, NULL, &rectangle);
    }
    else
    {
        SDL_RenderCopyEx(renderer, texture, NULL, &rectangle, -35.0, NULL, SDL_FLIP_NONE);
    }

}

void Player::Movement(const Uint8* state) {
    if (state[SDL_SCANCODE_UP]) {
        if (buffer == 0) {
            buffer = 10;
        }
    }
    if (buffer > 0) {
        GetRectangle()->y-=6;
        buffer--;
    }
    else
    {
        GetRectangle()->y+=4;
    }

}

Player::~Player() {
    SDL_DestroyTexture(texture);
}

void Player::Reset() {
    rectangle.x = 640;
    rectangle.y = 360;
    rectangle.w = 62;
    rectangle.h = 40;
}

