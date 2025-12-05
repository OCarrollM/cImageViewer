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
    
    SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);

    Uint8 r,g,b;
    r = 0xFF;
    g = b = 0x00;
    Uint32 color = SDL_MapRGB(psurface->format,r,g,b);

    int x = 50;
    int y = 50;
    const SDL_Rect pixel = (SDL_Rect){x,y,1,1};
    SDL_FillRect(psurface, &pixel, color);
    
    SDL_UpdateWindowSurface(pwindow);
    SDL_Delay(3000);
}