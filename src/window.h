#ifndef WINDOW_H 
#define WINDOW_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <GL/gl.h>
#include "utils.h"

/* Window data structures */
typedef struct {
    float framerate;
    int running;
    config_t *config;
    SDL_Window *window;
    SDL_GLContext context;
    SDL_Event e;
} window_t;

/* Window handling functions */
window_t *init_window(config_t *config);
void start_window(window_t *window_obj);
void destroy_window(window_t *window_obj);
void handle_events(window_t *window_obj, void *drawer, unsigned int used_dim);

#endif
