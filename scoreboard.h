#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void initializeScoreboardWindow(SDL_Renderer* renderer, int windowWidth, int scoreboardHeight);
void renderScoreboardWindow(SDL_Renderer* renderer, int scoreX, int scoreO);
void closeScoreboardWindow();


