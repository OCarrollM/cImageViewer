#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h> // Graphics Library, will need to include

int main(){
    FILE *pin = stdin;
    char *pthrowaway = calloc(1000, sizeof(char));
    // R first line
    fgets(pthrowaway, 1000, pin);
    // R second line and so on....
    fgets(pthrowaway, 1000, pin);
    char *pdimensions = calloc(1000, sizeof(char));
    fgets(pdimensions, 1000, pin);
    fgets(pthrowaway, 1000, pin);
    
    free(pthrowaway);

    int width = -1;
    int height = -1;
    sscanf(pdimensions, "%d %d\n", &width, &height);
    printf("width=%d\n, height=%d\n", width, height);


    SDL_Window *pwindow = SDL_CreateWindow("Image Viewer",
        SDL_WINDOWPOS_CENTERED, // x
        SDL_WINDOWPOS_CENTERED, // y
        width, 
        height, 
        0 // Flags
    );
    
    SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);
    
    SDL_Rect pixel = (SDL_Rect){0,0,1,1};
    Uint32 color = 0;
    for(int y=0; y<height; y++){
        for(int x=0; x<width; x++){
            Uint8 r,g,b;
            r = (char) getchar();
            g = (char) getchar();
            b = (char) getchar();
            color = SDL_MapRGB(psurface->format,r,g,b);
            pixel.x=x;
            pixel.y=y;
            SDL_FillRect(psurface, &pixel, color);
        }
    }
    
    SDL_UpdateWindowSurface(pwindow);
    
    int app_running = 1;
    while(app_running){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                app_running = 0;
            }
        }
        SDL_Delay(100);
    }
}