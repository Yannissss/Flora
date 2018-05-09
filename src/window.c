#include <stdio.h>
#include <stdlib.h>
#include "drawer_2d.h"
#include "l_system.h"
#include "window.h"
#include "utils.h"

/* Init SDL & OpenGL & return a window object */
window_t *init_window (config_t *config)
{
    window_t *window_obj = malloc( sizeof(window_t) );
    // Setting OpenGl version to 3.1
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    // Double Buffer
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // Initialazing SDL_VIDEO
    if ( SDL_Init(SDL_INIT_VIDEO) < 0 )
    {
        free(window_obj);
        return NULL;
    }

    // Create window
    window_obj->window = SDL_CreateWindow("Vanille", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        config->width, config->height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if (window_obj->window == 0)
    {
        printf(ERR "Couldn't create SDL window : %d", SDL_GetError());
        SDL_Quit();
        free(window_obj);
        return NULL;
    }

    // Create OpenGL context
    window_obj->context = SDL_GL_CreateContext(window_obj->window);
    if (window_obj->context == 0)
    {
        printf(ERR "Couldn't create OpenGL context : %d", SDL_GetError());
        SDL_Quit();
        free(window_obj);
        return NULL;
    }

    window_obj->config = config;
    // Successfully initialised window instance
    return window_obj;
}

/* Destroy SDL & OpenGL objs and free memory */
void destroy_window(window_t *window_obj)
{
    // Cleaning up SDL & OpenGL
    SDL_GL_DeleteContext(window_obj->context);
    SDL_DestroyWindow(window_obj->window);
    SDL_Quit();
    free(window_obj);
    return;
}

/* Implementation of the runnning loop */
void start_window(window_t *window_obj)
{
    /* Window parametres decl. */
    int delta_time = 1000 / 
      window_obj->config->max_framerate;
    window_obj->running = 1;

    /* Init drawer */
    drawer_2d_t drawer = { {0,0,0}, window_obj->config };
    init_drawer(&drawer);

    /* Testing drawer */
    point2f_t polygon[5] = {
        {-0.25, 0.15}, 
        {0.1, -0.4},
        {0.75, 0.85},
        {1.2, -0.78},
        {2.5, -1.7}
    };
    unsigned int test_size = 850;
    point2f_t curve[test_size];
    bezier_curve2f(polygon, 5, curve, test_size);
    
    /* Window loop */
    while (window_obj->running)
    {
        // Start timer
        int t1 = SDL_GetTicks();

        /* Running routine */
        handle_events(window_obj, &drawer, 2);
        glClear(GL_COLOR_BUFFER_BIT);
        glPointSize(1.25);
        
        /* Implement rendering here */
        int drawn_points = draw_points(&drawer, curve, test_size);

        /* Render debug infos */
        // TODO

        glFlush();
        SDL_GL_SwapWindow(window_obj->window);

        // End timer
        int dt = SDL_GetTicks()-t1;
        if (dt < delta_time)
        {
            window_obj->framerate = window_obj->config->max_framerate;
            SDL_Delay(delta_time-dt);
        } else {
            window_obj->framerate = 1000/dt;
        }
    }
    /* Free testing mem. */
    free(point_arr);
    free(str);
    return;
}

/* Event handler implementation */
void handle_events(window_t *window_obj, void *drawer, unsigned int used_dim)
{
    /* Queuing events */
    while(SDL_PollEvent(&(window_obj->e)))
    {
        /* Handle events for the drawer */
        switch((window_obj->e).type)
        {
            case SDL_KEYDOWN:
            switch (window_obj->e.key.keysym.scancode)
            {
                case SDL_SCANCODE_A:
                    /* Quit window */
                    window_obj->running = 0;
                    break;
                case SDL_SCANCODE_LEFT:
                if (window_obj->e.key.keysym.mod == 4160)
                {
                    // Rotation of drawer
                    rotate(drawer, window_obj->config->rot_speed
                                  /window_obj->framerate);
                } else {
                    // Translation of center point
                    move(drawer, pixel_proportion(drawer) 
                                 *window_obj->config->travel_speed
                    , WEST);
                }
                break;
                case SDL_SCANCODE_RIGHT:
                if (window_obj->e.key.keysym.mod == 4160)
                {
                    // Rotation of drawer
                    rotate(drawer, -window_obj->config->rot_speed
                                  /window_obj->framerate);
                } else {
                    // Translation of center point
                    move(drawer, pixel_proportion(drawer) 
                                 *window_obj->config->travel_speed
                    , EAST);
                }
                break;
                case SDL_SCANCODE_DOWN:
                if (window_obj->e.key.keysym.mod == 4160)
                {
                    // Decrease drawer's viewDistance
                    zoom_out(drawer);
                } else {
                    // Translation of center point
                    move(drawer, pixel_proportion(drawer) 
                                 *window_obj->config->travel_speed
                    , SOUTH);
                }
                break;
                case SDL_SCANCODE_UP:
                if (window_obj->e.key.keysym.mod == 4160)
                {
                    // Decrease drawer's viewDistance
                    zoom_in(drawer);
                } else {
                    // Translation of center point
                    move(drawer, pixel_proportion(drawer) 
                                 *window_obj->config->travel_speed
                    , NORTH);
                }
                break;
            }
            break;
            case SDL_WINDOWEVENT:
                if((window_obj->e).window.event == SDL_WINDOWEVENT_CLOSE)
                    window_obj->running = 0;
                break;
        }
    }
    return;
}
