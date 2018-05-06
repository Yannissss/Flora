#include "Game.h"

Game::Game(Config _config) : window(0), context(0), 
    framerate(0), running(true), config(_config) {}

Game::~Game()
{
    // Cleaning up SDL & OpenGL
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Game::init()
{
    // Setting OpenGl version to 3.1
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    // Double Buffer
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // Initialazing SDL_VIDEO
    if ( SDL_Init(SDL_INIT_VIDEO) < 0 )
    {
        cout << ERR "Couldn't initialize SDL Video :" << SDL_GetError() << endl;
        return false;
    }

    // Create window
    window = SDL_CreateWindow("Flora - v" VERSION, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, config.width,
        config.height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if (window == 0)
    {
        cout << ERR "Couldn't create SDL window :" << SDL_GetError() << endl;
        SDL_Quit();
        return false;
    }
    cout << INFO "Successfully created SDL window at : " << window << endl;

    // Create OpenGL context
    context = SDL_GL_CreateContext(window);
    if (context == 0)
    {
        cout << ERR "Couldn't create OpenGL context :" << SDL_GetError() << endl;
        SDL_Quit();
        return false;
    }
    cout << INFO "Successfully created OpenGL context at : " << context << endl;

    // Successfully initialised game instance
    return true;
}

void Game::handleEvents(Drawer *drawer)
{
    while(SDL_PollEvent(&e))
    {
        switch(e.type)
        {
            case SDL_KEYDOWN:
            switch (e.key.keysym.scancode)
            {
                case SDL_SCANCODE_LEFT:
                if (e.key.keysym.mod == 4160)
                {
                    // Rotation of drawer
                    drawer->rotate(config.rotSpeed/framerate);
                } else {
                    // Translation of center point
                    drawer->moveLeft(
                        drawer->pixelView()*config.travelSpeed
                    );
                }
                break;
                case SDL_SCANCODE_RIGHT:
                if (e.key.keysym.mod == 4160)
                {
                    // Rotation of drawer
                    drawer->rotate(-config.rotSpeed/framerate);
                } else {
                    // Translation of center point
                    drawer->moveRight(
                        drawer->pixelView()*config.travelSpeed
                    );
                }
                break;
                case SDL_SCANCODE_DOWN:
                if (e.key.keysym.mod == 4160)
                {
                    // Decrease drawer's viewDistance
                    drawer->zoomOut();
                } else {
                    // Translation of center point
                    drawer->moveDown(
                        drawer->pixelView()*config.travelSpeed
                    );
                }
                break;
                case SDL_SCANCODE_UP:
                if (e.key.keysym.mod == 4160)
                {
                    // Rotation of drawer
                    drawer->zoomIn();
                } else {
                    // Translation of center point
                    drawer->moveUp(
                        drawer->pixelView()*config.travelSpeed
                    );
                }
                break;
            }
            break;
            case SDL_WINDOWEVENT:
                if(e.window.event == SDL_WINDOWEVENT_CLOSE)
                    running = false;
            break;
            default:
            break;
        }
    }
}

void Game::loop()
{
    // Drawer setup
    Drawer drawer(Position {0,0,0}, config);
//    LSystem forest(
//        "FF",                 
 //       "F[+FX[+FX]][FFX][--FX[+FX][-FX]]",
  //      Position {0,0,PI/2},
   //     5, 15
    //);
    // LSystem factory(
    //     "FF", // Les F deviennent ...
    //     "F+[[X]-X]-F[-FX]+X", // Les X deviennent ...
    //     Position {0,0,0}, // Position initial (x,y,angle)
    //     3 // Distance parcourue en un F
    // );
    LSystem forest(
         "FF", 
         "{F[--FX]+FX}",
         Position {0,0,PI/2}, 
         15, 27.5
    );
    PointSet points = forest.grow("X", 2);
   
    // Main loop
    int deltaTime((int) 1000/config.maxFramerate);
    while (running)
    {
        // Start timer
        int t1 = SDL_GetTicks();

        // Listening quit events
        handleEvents(&drawer);

        glClear(GL_COLOR_BUFFER_BIT);
        glPointSize(5);

        drawer.drawPoints(points);
        // Print debug info
        // TODO
        glFlush();

        SDL_GL_SwapWindow(window);

        // End timer
        int dt = SDL_GetTicks()-t1;
        if (dt < deltaTime)
        {
            framerate = config.maxFramerate;
            SDL_Delay(deltaTime-dt);
        } else {
            framerate = 1000/dt;
        }
    }
}
