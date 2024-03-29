//
//  PyramidRenderer.m
//  Pyramid
//
//  Created by Nneoma Osuji on 29/03/2024.
//

// PyramidRenderer.m
#import "PyramidRenderer.h"
#include <SDL2/SDL.h>

@implementation PyramidRenderer

- (void)renderPyramidWithRows:(int)rows {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        NSLog(@"SDL_Init failed: %s", SDL_GetError());
        return;
    }

    // Create a window
    SDL_Window *window = SDL_CreateWindow("Pyramid", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        NSLog(@"Failed to create window: %s", SDL_GetError());
        SDL_Quit();
        return;
    }

    // Create a renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        NSLog(@"Failed to create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window); // Cleanup window
        SDL_Quit();
        return;
    }

    // Set draw color (white)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Draw the pyramid
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j <= i; ++j) {
            SDL_Rect rect = { j * 20, i * 20, 20, 20 };
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    // Present the renderer
    SDL_RenderPresent(renderer);

    // Handle events
    SDL_Event event;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

@end
