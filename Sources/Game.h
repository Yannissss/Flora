#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Drawer.h"
#include "LSystem.h"
#include "Utils.h"

#define VERSION "0.1"

using namespace std;

class Game
{
    public:

    Game(Config _config);
    ~Game();
    bool init();
    void handleEvents(Drawer *drawer);
    void loop();
    
    private:

    float framerate;
    bool running;
    Config config;
    SDL_Window* window;
    SDL_GLContext context;
    SDL_Event e;
};

#endif
