//
//  PyramidRenderer.mm
//  Pyramid
//
//  Created by Nneoma Osuji on 31/03/2024.
//

#include "PyramidRenderer.h"

PyramidRenderer::PyramidRenderer() {
   
    SDL_Init(SDL_INIT_VIDEO);

    // Create a window
    window = SDL_CreateWindow("Pyramid", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);

    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Define vertices of the pyramid
    vertices = {
        {400, 100, 0},  // Top vertex
        {300, 500, 0},  // Bottom left vertex
        {500, 500, 0},  // Bottom right vertex
        {100, 300, 0},  // Bottom back-left vertex
        {700, 300, 0}   // Bottom back-right vertex
    };

    // Define edges of the pyramid
    edges = {
        {0, 1},  // Top to bottom left
        {0, 2},  // Top to bottom right
        {0, 3},  // Top to bottom back-left
        {0, 4},  // Top to bottom back-right
        {1, 2},  // Bottom left to bottom right
        {1, 3},  // Bottom left to bottom back-left
        {2, 4},  // Bottom right to bottom back-right
        {3, 4}   // Bottom back-left to bottom back-right
    };
}

void PyramidRenderer::renderPyramid() {
    // Set draw color (white)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Render the pyramid
    for (const Edge& edge : edges) {
        SDL_RenderDrawLine(renderer, vertices[edge.v1].x, vertices[edge.v1].y, vertices[edge.v2].x, vertices[edge.v2].y);
    }

   
    SDL_RenderPresent(renderer);

    
    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
        if (event.type == SDL_QUIT) {
            break;
        }
    }

   
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
