#include <iostream>
#include <SDL2/SDL.h>

const int WIDTH = 1000, HEIGHT = 1000;

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow( "Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // (R, G, B, Alpha) background color
    
    //SDL_GetWindowSize(window, WIDTH, HEIGHT);

    int squareSize = 100;
    int squareX = (WIDTH - squareSize) / 2;
    int squareY = (HEIGHT - squareSize) / 2;

    int gridSize = 20;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Line Color

    SDL_Rect squareRect = { squareX, squareY, squareSize, squareSize };

    if ( NULL == window )
    {
        std::cout << "Could not create window: " << SDL_GetError( ) << std::endl;
        return 1;
    }

    SDL_Event windowEvent;

    while ( true )
    {
        if ( SDL_PollEvent( &windowEvent ) )
        {
            if ( SDL_QUIT == windowEvent.type )
            {break;}
        }
        // Vertical Lines
        for (int x = 0; x <= WIDTH; x += gridSize){
            SDL_RenderDrawLine(renderer, x, 0, x, HEIGHT);
        }

        // Horizontal Lines
        for (int y = 0; y <= HEIGHT; y += gridSize){
            SDL_RenderDrawLine(renderer, 0, y, WIDTH, y);
        }
        //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //Set render draw color to white

        //SDL_RenderFillRect(renderer, &squareRect); // render white square
        
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
