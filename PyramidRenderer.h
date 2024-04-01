//
//  PyramidRenderer.h
//  Pyramid
//
//  Created by Nneoma Osuji on 29/03/2024.
//

// PyramidRenderer.h

#ifndef PYRAMID_RENDERER_H
#define PYRAMID_RENDERER_H

#include <SDL2/SDL.h>
#include <vector>


struct Vertex {
    int x, y, z;
};


struct Edge {
    int v1, v2;
};

class PyramidRenderer {
public:
    PyramidRenderer();
    void renderPyramid();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::vector<Vertex> vertices;
    std::vector<Edge> edges;
};

#endif // PYRAMID_RENDERER_H
