#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h> // Graphics Library, will need to include

int main(){

    // Initializing video subsystem cause some OSs require it
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        fprintf(stderr, "SDL_Init Failed: %s\n", SDL_GetError());
        return 1;
    }

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

    if(width <= 0 || height <= 0){
        fprintf(stderr, "Invalid Image Dimensions: %dx%d\n", width, height);
        free(pdimensions);
        SDL_Quit();
        return 1;
    }
    //printf("width=%d\n, height=%d\n", width, height);
    free(pdimensions);


    SDL_Window *pwindow = SDL_CreateWindow("Image Viewer",
        SDL_WINDOWPOS_CENTERED, // x
        SDL_WINDOWPOS_CENTERED, // y
        width, 
        height, 
        0 // Flags
    );
    if(pwindow  == NULL){
        fprintf(stderr, "SDL_CreateWindow Failed: %s\n", SDL_GetError());
        free(pdimensions);
        SDL_Quit();
        return 1;
    }
    
    SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);
    if(psurface == NULL){
        fprintf(stderr, "SDL_GetWindowSurface Failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(pwindow);
        free(pdimensions);
        SDL_Quit();
        return 1;
    }
    
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
    SDL_DestroyWindow(pwindow);
    SDL_Quit();
    return 0;
}