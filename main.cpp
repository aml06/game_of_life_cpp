#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <tuple>
#include <array>

const int WIDTH = 1000, HEIGHT = 1000;

std::vector<std::tuple<int,int>> gosper_gun_builder() {
    
    std::vector<std::tuple<int, int>> figure_a = {{std::make_tuple(100, 500), std::make_tuple(120, 500), std::make_tuple(100, 520), std::make_tuple(120, 520)}};
    
    std::vector<std::tuple<int, int>> figure_b = {{std::make_tuple(780, 480), std::make_tuple(780, 460), std::make_tuple(800, 480), std::make_tuple(800, 460)}};

    std::vector<std::tuple<int, int>> figure_c ={{std::make_tuple(300, 500), std::make_tuple(300, 520), std::make_tuple(300, 540), std::make_tuple(320, 480), std::make_tuple(320, 560),
                std::make_tuple(340, 460), std::make_tuple(340, 580), std::make_tuple(360, 460), std::make_tuple(360, 580), std::make_tuple(380, 520),
                std::make_tuple(400, 480), std::make_tuple(400, 560), std::make_tuple(420, 500), std::make_tuple(420, 520), std::make_tuple(420, 540),
                std::make_tuple(440, 520)}};

    std::vector<std::tuple<int, int>> figure_d = {{std::make_tuple(500, 500), std::make_tuple(500, 480), std::make_tuple(500, 460), std::make_tuple(520, 500), std::make_tuple(520, 480), std::make_tuple(520, 460),
                std::make_tuple(540, 440), std::make_tuple(540, 520), std::make_tuple(580, 420), std::make_tuple(580, 440), std::make_tuple(580, 520), std::make_tuple(580, 540)}};

    std::vector<std::tuple<int, int>> joinedArray;

    for (const auto& tuple : figure_a) {
        joinedArray.push_back(tuple);
    }
    for (const auto& tuple : figure_b) {
        joinedArray.push_back(tuple);
    }
    for (const auto& tuple : figure_c) {
        joinedArray.push_back(tuple);
    }
    for (const auto& tuple : figure_d) {
        joinedArray.push_back(tuple);
    }
    return joinedArray;
}

int main(int argc, char* argv[])
{
    // Graphic stuff
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow( "Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // (R, G, B, Alpha) background color
    
    //SDL_GetWindowSize(window, WIDTH, HEIGHT);

    int squareSize = 20;
    int squareX = 500;
    int squareY = 500;

    int gridSize = 20;

    // Logic
    std::vector<int> positionArray;

    if ( NULL == window )
    {
        std::cout << "Could not create window: " << SDL_GetError( ) << std::endl;
        return 1;
    }

    SDL_Event windowEvent;

    std::vector<std::tuple<int,int>> life_list = gosper_gun_builder();

    while ( true )
    {
        if ( SDL_PollEvent( &windowEvent ) )
        {
            if ( SDL_QUIT == windowEvent.type )
            {break;}
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //Set render draw color to white
        // Vertical Lines
        for (int x = 0; x <= WIDTH; x += gridSize){
            SDL_RenderDrawLine(renderer, x, 0, x, HEIGHT);
        }

        // Horizontal Lines
        for (int y = 0; y <= HEIGHT; y += gridSize){
            SDL_RenderDrawLine(renderer, 0, y, WIDTH, y);
        }
        
        for (const auto& tuple : life_list){
            int x_pos = std::get<0>(tuple);
            int y_pos = std::get<1>(tuple);
            SDL_Rect newLife = {x_pos, y_pos, 20, 20};
            SDL_RenderFillRect(renderer, &newLife);
        }
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
