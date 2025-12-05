#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h> // Graphics Library, will need to include

int main() {
    printf("Hello World!\n");

    SDL_Window *pwindow = SDL_CreateWindow("Image Viewer",
        SDL_WINDOWPOS_CENTERED, // x
        SDL_WINDOWPOS_CENTERED, // y
        900, // height
        600, // width
        0 // Flags
    );
    
    SDL_Delay(3000);
}