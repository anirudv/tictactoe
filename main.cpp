#include <SDL2/SDL.h>
#include <iostream>

const int WINDOW_WIDTH = 300;
const int WINDOW_HEIGHT = 300;
const int BOARD_SIZE = 3;
const int CELL_SIZE = WINDOW_WIDTH/BOARD_SIZE;

char board[BOARD_SIZE][BOARD_SIZE] = {{'-','-','-'},
                                    {'-','-','-'},
                                    {'-','-','-'}};

char current_player = 'X';
bool game_over = false;

void init() {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Tic Tac Toe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

}

void close() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void draw_board() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            SDL_Rect cell_rect = {j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE};
            SDL_RenderDrawRect(renderer, &cell_rect);

            if (board[i][j] == 'X') {
                SDL_RenderDrawLine(renderer, j * CELL_SIZE + 10, i * CELL_SIZE + 10, (j+1) * CELL_SIZE - 10, (i+1) * CELL_SIZE - 10);
                SDL_RenderDrawLine(renderer, (j+1) * CELL_SIZE - 10, i * CELL_SIZE + 10, j * CELL_SIZE + 10, (i+1) * CELL_SIZE - 10);

            }

            else if (board[i][j] == 'O') {
                int radius = CELL_SIZE / 3;
                int center_x = j * CELL_SIZE + CELL_SIZE / 2
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

    SDL_RenderPresent(renderer);

}

void handle_click(SDL_Event& event) {
    int x, y;
    SDL_GetMouseState(&x, &y);

    int row = y / CELL_SIZE;
    int col = x / CELL_SIZE;

    if (row >= 0 && row < BOARD_SIZE &&)
}
