#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <tuple>
#include <array>
#include <unordered_map>
#include <set>
#include <algorithm>
//#include "next_generation.h"

int WIDTH = 1000, HEIGHT = 1000;
const int FPS = 10;

namespace std {
    template <>
    struct hash<std::tuple<int,int>> {
        size_t operator()(const std::tuple<int,int>& t) const {
            return std::hash<int>()(std::get<0>(t)) ^ std::hash<int>()(std::get<1>(t));
        }
    };
}

std::vector<std::tuple<int,int>> next_generation(const std::vector<std::tuple<int,int>> &old_Life){


    std::unordered_map<std::tuple<int, int>, int> new_life_map;
    std::vector<std::tuple<int,int>> new_life;

    for (const auto& tuple : old_Life){
        int x_pos = std::get<0>(tuple);
        int y_pos = std::get<1>(tuple);
    
        // top left
        std::tuple<int, int> new_tuple = std::make_tuple(x_pos - 20, y_pos + 20);
        // std::tuple<int, int> new_tuple(x_pos, y_pos);  Could also do it this way
        int current_value = new_life_map[new_tuple];
        if (current_value != 0){
            new_life_map[new_tuple]++;
        }
        else {
            new_life_map[new_tuple] = 1;
        }

        // top
        std::get<0>(new_tuple) = x_pos;
        std::get<1>(new_tuple) = y_pos + 20;
        current_value = new_life_map[new_tuple];
        if (current_value != 0){
            new_life_map[new_tuple]++;
        }
        else {
            new_life_map[new_tuple] = 1;
        }

        // top right
        std::get<0>(new_tuple) = x_pos + 20;
        std::get<1>(new_tuple) = y_pos + 20;
        current_value = new_life_map[new_tuple];
        if (current_value != 0){
            new_life_map[new_tuple]++;
        }
        else {
            new_life_map[new_tuple] = 1;
        }

        // left
        std::get<0>(new_tuple) = x_pos - 20;
        std::get<1>(new_tuple) = y_pos;
        current_value = new_life_map[new_tuple];
        if (current_value != 0){
            new_life_map[new_tuple]++;
        }
        else {
            new_life_map[new_tuple] = 1;
        }

        // right
        std::get<0>(new_tuple) = x_pos + 20;
        std::get<1>(new_tuple) = y_pos;
        current_value = new_life_map[new_tuple];
        if (current_value != 0){
            new_life_map[new_tuple]++;
        }
        else {
            new_life_map[new_tuple] = 1;
        }

        // bot left
        std::get<0>(new_tuple) = x_pos - 20;
        std::get<1>(new_tuple) = y_pos - 20;
        current_value = new_life_map[new_tuple];
        if (current_value != 0){
            new_life_map[new_tuple]++;
        }
        else {
            new_life_map[new_tuple] = 1;
        }

        // bot
        std::get<0>(new_tuple) = x_pos;
        std::get<1>(new_tuple) = y_pos - 20;
        current_value = new_life_map[new_tuple];
        if (current_value != 0){
            new_life_map[new_tuple]++;
        }
        else {
            new_life_map[new_tuple] = 1;
        }

        // bot right
        std::get<0>(new_tuple) = x_pos + 20;
        std::get<1>(new_tuple) = y_pos - 20;
        current_value = new_life_map[new_tuple];
        if (current_value != 0){
            new_life_map[new_tuple]++;
        }
        else {
            new_life_map[new_tuple] = 1;
        }
    }
    // Iterate through all the keys looking for values that are equal to 3, indicating a new live square
    for (const auto& pair : new_life_map) {
        const std::tuple<int, int>& key = pair.first;
        const int val = pair.second;
        if (val == 3){
            new_life.push_back(pair.first);
        }
    }
    // check neighbors of living cells
    for (const auto& cell : old_Life){
        int nCount = 0;
        int x_cell = std::get<0>(cell);
        int y_cell = std::get<1>(cell);
        for(const auto& sub_cell : old_Life){
            if (cell != sub_cell){
                // top left
                if (x_cell - 20 == std::get<0>(sub_cell) && y_cell + 20 == std::get<1>(sub_cell)){
                    nCount++;
                }
                // top
                if (x_cell == std::get<0>(sub_cell) && y_cell + 20 == std::get<1>(sub_cell)){
                    nCount++;
                }
                // top right
                if (x_cell + 20 == std::get<0>(sub_cell) && y_cell + 20 == std::get<1>(sub_cell)){
                    nCount++;
                }
                // left
                if (x_cell - 20 == std::get<0>(sub_cell) && y_cell == std::get<1>(sub_cell)){
                    nCount++;
                }
                // right
                if (x_cell + 20 == std::get<0>(sub_cell) && y_cell == std::get<1>(sub_cell)){
                    nCount++;
                }
                // bot left
                if (x_cell - 20 == std::get<0>(sub_cell) && y_cell - 20 == std::get<1>(sub_cell)){
                    nCount++;
                }
                // bot
                if (x_cell == std::get<0>(sub_cell) && y_cell - 20 == std::get<1>(sub_cell)){
                    nCount++;
                }
                // bot right
                if (x_cell + 20 == std::get<0>(sub_cell) && y_cell - 20 == std::get<1>(sub_cell)){
                    nCount++;
                }
            }
        }
        //std::cout << "nCount for (" << x_cell << ", " << y_cell << ") is " << nCount << std::endl;
        if (nCount == 2 || nCount == 3){
            new_life.push_back(cell);
        }
    }
    // Remove duplicates
    std::set<std::tuple<int,int>> no_duplicates;
    for (std::tuple<int, int>& element : new_life) {
        no_duplicates.insert(element);
    }
    new_life.clear();
    for (const std::tuple<int, int>& unique_element : no_duplicates){
        new_life.push_back(unique_element);
    }

    return new_life;
}

// the initial life state
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

std::vector<std::tuple<int,int>> life_fence(const std::vector<std::tuple<int,int>> my_life_list){
    std::vector<std::tuple<int, int>> filteredList = my_life_list;

    auto isOutOfRange = [](const std::tuple<int, int>& t) {
        int x = std::get<0>(t);
        int y = std::get<1>(t);
        return (x < -2000 || x > 2000 || y < -2000 || y > 2000);
    };
    auto newEnd = std::remove_if(filteredList.begin(), filteredList.end(), isOutOfRange);

    filteredList.erase(newEnd, filteredList.end());

    return filteredList;
}

int main(int argc, char* argv[])
{
    // Graphic stuff
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow( "Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // (R, G, B, Alpha) background color
    
    //SDL_GetWindowSize(window, WIDTH, HEIGHT);

    int squareSize = 20;
    int squareX = 500;
    int squareY = 500;

    int gridSize = 20;
    Uint32 frameStart;
    int frameTime;

    int shift_x = 0;
    int shift_y = 0;

    if ( NULL == window )
    {
        std::cout << "Could not create window: " << SDL_GetError( ) << std::endl;
        return 1;
    }

    SDL_Event windowEvent;

    std::vector<std::tuple<int,int>> life_list = gosper_gun_builder();
    bool quit = false;
    while (!quit)
    {
        frameStart = SDL_GetTicks();

        std::vector<std::tuple<int,int>> temp_list;
        
        while ( SDL_PollEvent( &windowEvent ) ){
                if ( SDL_QUIT == windowEvent.type ) {
                    quit = true;
                }
                else if (windowEvent.type == SDL_KEYDOWN){
                    if (windowEvent.key.keysym.sym == SDLK_UP){
                        shift_y = shift_y + 20;
                    }
                    if (windowEvent.key.keysym.sym == SDLK_DOWN){
                        shift_y = shift_y - 20;
                    }
                    if (windowEvent.key.keysym.sym == SDLK_LEFT){
                        shift_x = shift_x + 20;
                    }
                    if (windowEvent.key.keysym.sym == SDLK_RIGHT){
                        shift_x = shift_x - 20;
                    }
                    // This wasn't working right, back to bunch of if conditions
                    //switch (windowEvent.key.keysym.sym){
                    //     case SDLK_UP:
                    //         shift_y = shift_y + 20;
                    //     case SDLK_DOWN:
                    //         shift_y = shift_y - 20;
                    //     case SDLK_LEFT:
                    //         shift_x = shift_x - 20;
                    //     case SDLK_RIGHT:
                    //         shift_x = shift_x + 20;
                    // }
                    if (windowEvent.key.keysym.sym == SDLK_ESCAPE){
                        quit = true;
                    }
                }
                else if (windowEvent.type == SDL_MOUSEBUTTONDOWN){
                        if (windowEvent.button.button == SDL_BUTTON_LEFT){
                            int mouseX = windowEvent.button.x;
                            int mouseY = windowEvent.button.y;

                            int correctX = mouseX - mouseX % 20;
                            int correctY = mouseY - mouseY % 20;

                            std::tuple<int, int> new_life = std::make_tuple(correctX, correctY);

                            temp_list.push_back(new_life);
                            
                            std::cout << "correctX: " << correctX << ", correctY: " << correctY << "\n";
                            //SDL_Rect newLifeRect = {mouseX, mouseY, 20, 20};
                            //SDL_RenderFillRect(renderer, &newLifeRect);
                        }
                }
        }

        SDL_GetWindowSize(window, &WIDTH, &HEIGHT);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //Set render draw color to white

        int start_x = shift_x % gridSize;
        int start_y = shift_y % gridSize;

        // Vertical Lines
        for (int x = start_x - shift_x; x <= WIDTH - shift_x; x += gridSize){
            SDL_RenderDrawLine(renderer, x + shift_x, 0, x +shift_x, HEIGHT);
        }

        // Horizontal Lines
        for (int y = start_y - shift_y; y <= HEIGHT - shift_y; y += gridSize){
            SDL_RenderDrawLine(renderer, 0, y + shift_y, WIDTH, y + shift_y);
        }
        
        life_list = next_generation(life_list);
        life_list = life_fence(life_list);

        // Have to put the mouse click into a temp_list then render it here, can't render it by the mouse click, will need to think about that
        for (const auto& tuple : temp_list){
            int x_pos = std::get<0>(tuple);
            int y_pos = std::get<1>(tuple);
            SDL_Rect newLife = {x_pos + shift_x, y_pos + shift_y, 20, 20};
            SDL_RenderFillRect(renderer, &newLife);
        }

        // Renders all the tuple coordinates in the array tracking live cell locations
        for (const auto& tuple : life_list){
            int x_pos = std::get<0>(tuple);
            int y_pos = std::get<1>(tuple);
            SDL_Rect newLife = {x_pos + shift_x, y_pos + shift_y, 20, 20};
            SDL_RenderFillRect(renderer, &newLife);
        }

        SDL_RenderPresent(renderer);

        frameTime =  SDL_GetTicks() - frameStart;

        if (frameTime < 1000 / FPS) {
            SDL_Delay((1000 / FPS) - frameTime);
        }

        // Merge temp_list into life_list
        life_list.insert(life_list.end(), temp_list.begin(), temp_list.end());

    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
