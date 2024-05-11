//
//  ballcode.cpp
//  scenefile
//
//  Created by Nneoma Osuji on 11/05/2024.
//

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <iostream>
#include <vector>
#include <cstdlib> // for rand() and srand()

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int BALL_RADIUS = 72;
const int GRAVITY = 1;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

struct Ball {
    int x, y;
    int dx, dy;
};

Ball ball;

bool initSDL()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create window
    gWindow = SDL_CreateWindow("2D Rendering", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create renderer
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (gRenderer == NULL) {
        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Set renderer color
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    // Allows for (Initializes) Image Loading abilities using SDL_image library
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }

    return true;
}

void closeSDL()
{
    // Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

void updateBall() {
    ball.x += ball.dx;
    ball.y += ball.dy;

    // Check collision with window edges
    if (ball.x < 0 || ball.x + BALL_RADIUS > SCREEN_WIDTH) {
        ball.x = (ball.x < 0)? 0 : SCREEN_WIDTH - BALL_RADIUS;
        ball.dx = -ball.dx; // Change horizontal direction
    }
    if (ball.y < 0 || ball.y + BALL_RADIUS > SCREEN_HEIGHT) {
        ball.y = (ball.y < 0)? 0 : SCREEN_HEIGHT - BALL_RADIUS;
        ball.dy = -ball.dy; // Change vertical direction
    }
}

int main(int argc, char* argv[]) {
    if (!initSDL()) {
        std::cout << "Failed to initialize SDL!" << std::endl;
        return -1;
    }

    SDL_Texture* ballText = IMG_LoadTexture(gRenderer, "/Users/nneomaosuji/Library/CloudStorage/OneDrive-Personal/Documents/YEAR 2 SEMESTER 2/COMPUTER GRAPHICS/scenefile copy/Assets/ball.png");
    if (ballText == NULL) {
        std::cout << "Failed to load ball texture! SDL_Error: " << SDL_GetError() << std::endl;
        closeSDL();
        return -1;
    }

    ball.x = SCREEN_WIDTH / 2;
    ball.y = SCREEN_HEIGHT / 2;
    ball.dx = rand() % 10 + 1; // Random value between 1 and 10
    ball.dy = rand() % 10 + 1; // Random value between 1 and 10

    // Main loop flag
    bool quit = false;

    // Event handler
    SDL_Event e;

    while (!quit) {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            // User requests quit
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Clear screen
        SDL_RenderClear(gRenderer);

        updateBall();

        SDL_Rect ballRect = { ball.x, ball.y, BALL_RADIUS, BALL_RADIUS };
        SDL_RenderCopy(gRenderer, ballText, NULL, &ballRect);

        // Update screen
        SDL_RenderPresent(gRenderer);
        SDL_Delay(10);
    }

    // Destroy textures
    SDL_DestroyTexture(ballText);

    // Close SDL
    closeSDL();

    return 0;
}
