//
//  scenecode.cpp
//  scenefile
//
//  Created by Nneoma Osuji on 03/05/2024.
//

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <iostream>
#include <string>
#include <vector>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int IMAGE_WIDTH = SCREEN_WIDTH + 300;

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
float speed = 0.1f;
int CameraX = 0;
int textureWidthDiff = IMAGE_WIDTH - SCREEN_WIDTH;

SDL_Texture* loadTexture(const std::string& path) {
    SDL_Texture* newTexture = nullptr;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        std::cerr << "Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << std::endl;
    } else {
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == nullptr) {
            std::cerr << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << std::endl;
        }
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

bool initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    gWindow = SDL_CreateWindow("2D Rendering", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (gRenderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    } // Add this closing brace

    return true; // Don't forget to return true if everything is successful
}


void closeSDL() {
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;
    gRenderer = nullptr;
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    if (!initSDL()) {
        std::cerr << "Failed to initialize SDL!" << std::endl;
        return -1;
    }

    std::vector<SDL_Texture*> backgroundTextures;
    backgroundTextures.push_back(loadTexture("/Users/nneomaosuji/Library/CloudStorage/OneDrive-Personal/Documents/YEAR 2 SEMESTER 2/COMPUTER GRAPHICS/scenefile/oak_woods_v1.0/background/background_layer_1.png"));
    backgroundTextures.push_back(loadTexture("/Users/nneomaosuji/Library/CloudStorage/OneDrive-Personal/Documents/YEAR 2 SEMESTER 2/COMPUTER GRAPHICS/scenefile/oak_woods_v1.0/background/background_layer_2.png"));
    backgroundTextures.push_back(loadTexture("/Users/nneomaosuji/Library/CloudStorage/OneDrive-Personal/Documents/YEAR 2 SEMESTER 2/COMPUTER GRAPHICS/scenefile/oak_woods_v1.0/background/background_layer_3.png"));

    SDL_Texture* backgroundFloor = loadTexture("/Users/nneomaosuji/Library/CloudStorage/OneDrive-Personal/Documents/YEAR 2 SEMESTER 2/COMPUTER GRAPHICS/scenefile/oak_woods_v1.0/decorations/grass_1.png");
    SDL_Texture* backgroundSky = loadTexture("/Users/nneomaosuji/Library/CloudStorage/OneDrive-Personal/Documents/YEAR 2 SEMESTER 2/COMPUTER GRAPHICS/scenefile/oak_woods_v1.0/decorations/grass_2.png");

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        SDL_RenderClear(gRenderer);

        for (SDL_Texture* texture : backgroundTextures) {
            SDL_Rect textureDest = { 0, 0, IMAGE_WIDTH, SCREEN_HEIGHT };
            SDL_RenderCopy(gRenderer, texture, NULL, &textureDest);
        }

        SDL_RenderPresent(gRenderer);
    }

    SDL_DestroyTexture(backgroundFloor);
    SDL_DestroyTexture(backgroundSky);

    for (SDL_Texture* texture : backgroundTextures) {
        SDL_DestroyTexture(texture);
    }

    closeSDL();

    return 0;
}
