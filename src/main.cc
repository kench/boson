#include <iostream>
#include <nlohmann/json.hpp>
#define SDL_MAIN_HANDLED
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "main-sdl.h"

using json = nlohmann::json;

int main(int argc, char* argv[], char* envp[]) {
    SDL_Log("Hello, world!");
    return SDL_RunApp(argc, argv, app_callback, NULL);
}
