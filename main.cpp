#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <tuple>
#include <array>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <cmath>
//#include "next_generation.h"

int WIDTH = 1000, HEIGHT = 1000;
int FPS = 20;

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

    float zoom = 1.0;

    int loopCount = 0;
    int loopMax = 20;

    bool leftDrag = false;
    bool rightDrag = false;

    int fudge_X = 0;
    int fudge_Y = 0;

    int prevMouseX;
    int prevMouseY;
    if ( NULL == window ){
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

                    // scrolling screen
                    if (windowEvent.key.keysym.sym == SDLK_UP){
                        shift_y = std::floor((shift_y + std::floor(20 / zoom)));
                    }
                    if (windowEvent.key.keysym.sym == SDLK_DOWN){
                        shift_y = std::floor((shift_y - std::floor(20 / zoom)));
                    }
                    if (windowEvent.key.keysym.sym == SDLK_LEFT){
                        shift_x = std::floor((shift_x + std::floor(20 / zoom)));
                    }
                    if (windowEvent.key.keysym.sym == SDLK_RIGHT){
                        shift_x = std::floor((shift_x - std::floor(20 / zoom)));
                    }

                    // Change speed of computation
                    if (windowEvent.key.keysym.sym == SDLK_EQUALS){
                        if (FPS < 100) {
                            FPS += 10;
                        }
                    }
                    if (windowEvent.key.keysym.sym == SDLK_MINUS){
                        if (FPS > 10) {
                            FPS -= 10;
                        }
                    }
                    // Fudge Factors
                    if (windowEvent.key.keysym.sym == SDLK_e){
                        fudge_X += 1;
                        std::cout << "Fudge_X: " << fudge_X << "\n";
                    }
                    if (windowEvent.key.keysym.sym == SDLK_r){
                        fudge_X += 1;
                        std::cout << "Fudge_X: " << fudge_X << "\n";
                    }
                    if (windowEvent.key.keysym.sym == SDLK_d){
                        fudge_Y += 1;
                        std::cout << "Fudge_Y: " << fudge_X << "\n";
                    }
                    if (windowEvent.key.keysym.sym == SDLK_f){
                        fudge_Y -= 1;
                        std::cout << "Fudge_Y: " << fudge_X << "\n";
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

                    // Quit
                    if (windowEvent.key.keysym.sym == SDLK_ESCAPE){
                        quit = true;
                    }

                    // Zoom In/Out
                    if (windowEvent.key.keysym.sym == SDLK_m){
                        if (zoom > 0.2){
                            zoom -= 0.1;
                            std::cout << "Current Zoom: " << zoom << " \n";
                        }
                    }
                    if (windowEvent.key.keysym.sym == SDLK_n){
                        if (zoom < 2){
                            zoom += 0.1;
                            std::cout << "Current Zoom: " << zoom << " \n";
                        }
                    }
                }
                else if (windowEvent.type == SDL_MOUSEBUTTONDOWN){
                    if (windowEvent.button.button == SDL_BUTTON_LEFT){
                        leftDrag = true;
                        int mouseX = windowEvent.button.x;
                        int mouseY = windowEvent.button.y;

                        int correctX = std::floor(mouseX - (mouseX - shift_x) % 20 / zoom - shift_x);
                        int correctY = std::floor(mouseY - (mouseY - shift_y) % 20 / zoom - shift_y);

                        std::tuple<int, int> new_life = std::make_tuple(correctX, correctY);

                        temp_list.push_back(new_life);
                        
                        //std::cout << "correctX: " << correctX << ", correctY: " << correctY << "\n";
                        //SDL_Rect newLifeRect = {mouseX, mouseY, 20, 20};
                        //SDL_RenderFillRect(renderer, &newLifeRect);
                    }
                    else if (windowEvent.button.button == SDL_BUTTON_RIGHT){
                        rightDrag = true;
                    }
                }
                else if (windowEvent.type == SDL_MOUSEMOTION){
                    if (leftDrag){
                        int mouseX = windowEvent.button.x;
                        int mouseY = windowEvent.button.y;

                        int correctX = mouseX - std::floor((mouseX - shift_x) % 20 / zoom) - shift_x;
                        int correctY = mouseY - std::floor((mouseY - shift_y) % 20 / zoom) - shift_y;

                        std::tuple<int, int> new_life = std::make_tuple(correctX, correctY);

                        temp_list.push_back(new_life);
                    }
                    if (rightDrag){
                        int mouseX = windowEvent.button.x;
                        int mouseY = windowEvent.button.y;
                        if (prevMouseX && prevMouseY){
                            int delta_x = mouseX - prevMouseX;
                            int delta_y = mouseY - prevMouseY;

                            if(delta_x > 0){
                                shift_x = shift_x + std::floor(20 / zoom);
                            }
                            else if (delta_x < 0){
                                shift_x = shift_x - std::floor(20 / zoom);
                            }
                            else{
                                ;
                            }

                            if (delta_y > 0){
                                shift_y = shift_y + std::floor(20 / zoom);
                            }
                            else if (delta_y < 0){
                                shift_y = shift_y - std::floor(20 / zoom);
                            }
                            else{
                                ;
                            }
                        }
                        prevMouseX = mouseX;
                        prevMouseY = mouseY;
                    }
                }
                else if (windowEvent.type == SDL_MOUSEBUTTONUP){
                    leftDrag = false;
                    rightDrag = false;
                }
        }

        SDL_GetWindowSize(window, &WIDTH, &HEIGHT);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //Set render draw color to white
        
        int scaled_gridSize = std::floor(gridSize / zoom);
        // int start_x = shift_x % scaled_gridSize;
        // int start_y = shift_y % scaled_gridSize;

        // Have to put the mouse click into a temp_list then render it here, can't render it by the mouse click, will need to think about that
        for (const auto& tuple : temp_list){
            int x_pos = std::get<0>(tuple);
            int y_pos = std::get<1>(tuple);
            SDL_Rect newLife = {x_pos + shift_x, y_pos + shift_y, scaled_gridSize, scaled_gridSize};
            SDL_RenderFillRect(renderer, &newLife);
        }
        if (loopCount >= loopMax){

            int scaled_gridSize = std::floor(gridSize / zoom);
            
            // Vertical Lines
            for (int x = 0; x <= WIDTH; x += scaled_gridSize){
                SDL_RenderDrawLine(renderer, x, 0, x, HEIGHT);
            }
            
            // Horizontal Lines
            for (int y = 0; y <= HEIGHT; y += scaled_gridSize){
                SDL_RenderDrawLine(renderer, 0, y, WIDTH, y);
            }
            
            life_list = next_generation(life_list);
            life_list = life_fence(life_list);

            // Renders all the tuple coordinates in the array tracking live cell locations
            for (const auto& tuple : life_list){
                int x_pos = std::get<0>(tuple);
                int y_pos = std::get<1>(tuple);

                int x_pos_corrected = std::floor((x_pos + shift_x) / zoom);
                int y_pos_corrected = std::floor((y_pos + shift_y) / zoom);

                SDL_Rect newLife = {x_pos_corrected , y_pos_corrected, scaled_gridSize, scaled_gridSize};
                SDL_RenderFillRect(renderer, &newLife);
            }
            
        }
        loopCount += 1;
        SDL_RenderPresent(renderer);

        frameTime =  SDL_GetTicks() - frameStart;

        if (frameTime < 1000 / FPS) {
            SDL_Delay((1000 / FPS) - frameTime);
        }

        //Merge temp_list into life_list
        life_list.insert(life_list.end(), temp_list.begin(), temp_list.end());

    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
