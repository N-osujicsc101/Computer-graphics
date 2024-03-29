//
//  main.m
//  Pyramid
//
//  Created by Nneoma Osuji on 29/03/2024.
//

// main.m
#import <Foundation/Foundation.h>
#import "PyramidRenderer.h"
#include <SDL2/SDL.h>

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        // Initialize SDL
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            NSLog(@"SDL_Init failed: %s", SDL_GetError());
            return 1;
        }

        int rows;
        printf("Enter the number of rows for the pyramid: ");
        scanf("%d", &rows);

        PyramidRenderer *pyramidRenderer = [[PyramidRenderer alloc] init];
        [pyramidRenderer renderPyramidWithRows:rows];
    }
    return 0;
}
