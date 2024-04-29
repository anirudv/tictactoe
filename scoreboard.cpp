// scoreboard.cpp

#include "scoreboard.h"
#include <iostream>
#include <string>

using namespace std;

const int SCORE_WINDOW_WIDTH = 200;
const int SCORE_WINDOW_HEIGHT = 100;

SDL_Window* scoreWindow = nullptr;
SDL_Renderer* scoreRenderer = nullptr;
TTF_Font* scoreFont = nullptr;

void initializeScoreboardWindow(SDL_Renderer* renderer, int windowWidth, int scoreboardHeight) {
    // Initialize SDL for the scoreboard window
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    // Create the scoreboard window and renderer
    scoreWindow = SDL_CreateWindow("Scoreboard", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCORE_WINDOW_WIDTH, SCORE_WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    scoreRenderer = SDL_CreateRenderer(scoreWindow, -1, SDL_RENDERER_ACCELERATED);

    // Load font for score display
    scoreFont = TTF_OpenFont("arial.ttf", 18);
    if (!scoreFont) {
        cerr << "Failed to load font: " << TTF_GetError() << endl;
    }
}

void closeScoreboardWindow() {
    // Destroy the renderer and window for the scoreboard
    SDL_DestroyRenderer(scoreRenderer);
    SDL_DestroyWindow(scoreWindow);

    // Quit SDL subsystems
    TTF_Quit();
    SDL_Quit();
}

void renderScoreboardWindow(SDL_Renderer* renderer, int scoreX, int scoreO) {
    // Clear the renderer
    SDL_SetRenderDrawColor(scoreRenderer, 255, 255, 255, 255);
    SDL_RenderClear(scoreRenderer);

    // Render the score text
    string scoreText = "Score\nX: " + to_string(scoreX) + "\nO: " + to_string(scoreO);
    SDL_Color textColor = {0, 0, 0, 255}; // Black color for the text

    SDL_Surface* scoreSurface = TTF_RenderText_Solid(scoreFont, scoreText.c_str(), textColor);
    if (!scoreSurface) {
        cerr << "Failed to create text surface: " << TTF_GetError() << endl;
        return;
    }

    SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(scoreRenderer, scoreSurface);
    if (!scoreTexture) {
        cerr << "Failed to create texture from surface: " << SDL_GetError() << endl;
        SDL_FreeSurface(scoreSurface);
        return;
    }

    int scoreWidth, scoreHeight;
    SDL_QueryTexture(scoreTexture, NULL, NULL, &scoreWidth, &scoreHeight);

    SDL_Rect scoreRect = {10, 10, scoreWidth, scoreHeight}; // Adjust position as needed

    SDL_RenderCopy(scoreRenderer, scoreTexture, NULL, &scoreRect);

    SDL_FreeSurface(scoreSurface);
    SDL_DestroyTexture(scoreTexture);

    // Present the renderer
    SDL_RenderPresent(scoreRenderer);
}
