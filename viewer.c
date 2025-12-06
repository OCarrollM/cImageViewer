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

    char *pline = calloc(1000, sizeof(char));
    fgets(pline, 1000, pin);
    if(pline[0] != 'P' || pline[1] != '6'){
        fprintf(stderr, "Not A Valid PPM File\n");
        free(pline);
        SDL_Quit();
        return 1;
    }

    do{
        fgets(pline, 1000, pin);
    } while(pline[0] == '#');

    int width = -1;
    int height = -1;
    sscanf(pline, "%d %d", &width, &height);

    do{
        fgets(pline, 1000, pin);
    } while(pline[0] == '#');


    if(width <= 0 || height <= 0){
        fprintf(stderr, "Invalid Image Dimensions: %dx%d\n", width, height);
        SDL_Quit();
        return 1;
    }
    free(pline);


    SDL_Window *pwindow = SDL_CreateWindow("Image Viewer",
        SDL_WINDOWPOS_CENTERED, // x
        SDL_WINDOWPOS_CENTERED, // y
        width, 
        height, 
        0 // Flags
    );
    if(pwindow  == NULL){
        fprintf(stderr, "SDL_CreateWindow Failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    
    SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);
    if(psurface == NULL){
        fprintf(stderr, "SDL_GetWindowSurface Failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(pwindow);
        free(pline);
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