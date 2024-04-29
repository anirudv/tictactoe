#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Board.h"
#include "scoreboard.h"
#include <iostream>
#include <string>

using namespace std;

const int WINDOW_WIDTH = 400;
const int WINDOW_HEIGHT = 450;
const int BOARD_SIZE = 3;
const int CELL_SIZE = WINDOW_WIDTH/BOARD_SIZE;
const int SCORE_COUNT_HEIGHT = 50;
const int BUTTON_HEIGHT = 50;

Board board;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
TTF_Font* font = nullptr;


char current_player = 'X';
bool game_over = false;

int scoreX = 0;
int scoreO = 0;

int textX = 10; 
int textY = 10; 


void init() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    window = SDL_CreateWindow("Tic Tac Toe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    font = TTF_OpenFont("arial.ttf", 24);

}

void close() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
}

void render_text(const string& text, const SDL_Point& position) {
    SDL_Color textColor = {0, 0, 0, 255};
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    int width, height;
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);

    SDL_Rect dstRect = {position.x, position.y, width, height};
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

}


void draw_board() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    for (int i = 1; i < BOARD_SIZE; ++i) {
        int x = i * CELL_SIZE;
        SDL_RenderDrawLine(renderer, x, 0, x, WINDOW_HEIGHT - BUTTON_HEIGHT - SCORE_COUNT_HEIGHT);

        int y = i * CELL_SIZE;
        SDL_RenderDrawLine(renderer, 0, y, WINDOW_WIDTH, y);
    }

    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (!board.isCellEmpty(i, j)) {
                char mark = board.getMarkAt(i, j);
                if (mark == 'X') {
                    SDL_RenderDrawLine(renderer, j * CELL_SIZE + 10, i * CELL_SIZE + 10, (j+1) * CELL_SIZE - 10, (i+1) * CELL_SIZE - 10);
                    SDL_RenderDrawLine(renderer, (j+1) * CELL_SIZE - 10, i * CELL_SIZE + 10, j * CELL_SIZE + 10, (i+1) * CELL_SIZE - 10);
                } else if (mark == 'O') {
                    int radius = CELL_SIZE / 3;
                    int center_x = j * CELL_SIZE + CELL_SIZE / 2;
                    int center_y = i * CELL_SIZE + CELL_SIZE / 2;
                    for (int k = 0; k <= 360; k+=5) {
                        double rad = k * 3.14159 / 180;
                        int x = center_x + radius * cos(rad);
                        int y = center_y + radius * sin(rad);
                        SDL_RenderDrawPoint(renderer, x, y);
                    }
                }
            }
        }
    }

    SDL_RenderPresent(renderer);
}


void handle_click(SDL_Event& event) {
    int x, y;
    SDL_GetMouseState(&x, &y);

    int row = y / CELL_SIZE;
    int col = x / CELL_SIZE;

    if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE && board.isCellEmpty(row, col)) {
        board.placeMark(row, col, current_player); // Corrected the usage of placeMark here

        if (board.checkWin(current_player)) {
            if (current_player == 'X') {
                scoreX++;
                renderScoreboardWindow(renderer, scoreX, scoreO);
                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Game Over", "Player X wins!", NULL);
            } else {
                scoreO++;
                renderScoreboardWindow(renderer, scoreX, scoreO);
                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Game Over", "Player O wins!", NULL);
            }
            board.resetBoard();
        } else if (board.isBoardFull()) {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Game Over", "It's a draw!", NULL);
            board.resetBoard();
        } else {
            current_player = (current_player == 'X') ? 'O' : 'X';
        }
    }
}




void handle_restart_button(SDL_Event& event) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    if (y >= WINDOW_HEIGHT - 50 && y <= WINDOW_HEIGHT && event.type == SDL_MOUSEBUTTONDOWN) {
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                board.setMarkAt(i,j,'-');
            }
        }
        current_player = 'X';
    }
}

void render_loop() {
    while (!game_over) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                game_over = true;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                handle_click(event);
                handle_restart_button(event);
            }
        }
        draw_board();
    }
}

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cerr << "SDL initialization failed: " << SDL_GetError() << endl;
        return 1;
    }

    // Initialize TTF
    if (TTF_Init() < 0) {
        cerr << "TTF initialization failed: " << TTF_GetError() << endl;
        SDL_Quit();
        return 1;
    }

    // Create the main game window and renderer
    SDL_Window* window = SDL_CreateWindow("Tic Tac Toe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        cerr << "Window creation failed: " << SDL_GetError() << endl;
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        cerr << "Renderer creation failed: " << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Initialize the scoreboard window
    initializeScoreboardWindow(renderer, WINDOW_WIDTH, SCORE_COUNT_HEIGHT);

    // Example scores
    int scoreX = 5;
    int scoreO = 3;

    // Render the scoreboard window with the example scores
    renderScoreboardWindow(renderer, scoreX, scoreO);

    // Initialize the game
    init();

    // Run the game loop
    render_loop();

    // Close the game and quit SDL
    close();

    // Close the scoreboard window and quit SDL
    closeScoreboardWindow();

    // Clean up and quit SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}

