#include <stdio.h>
#include <stdlib.h>
#include "window.h"
#include "utils.h"

/* Default config constants */
config_t default_config = {
    800,          // Window width
    600,          // Window height
    60,           // Window framerate cap
    2,          // Default view distance
    150,          // Travel speed in pixel/second
    95*PI/180,    // Angular speed in rad/second
    1.75,         // Scale sensitivity
};

/* Implement main routine */
int main(int argc, const char *argv[])
{
    /* Create window & displays it */
    window_t *window_obj = init_window(&default_config);
    if ( !window_obj )
    {
        printf(ERR "Qutting due to error...");
        return EXIT_FAILURE;
    }
    printf(INFO "Successfully created SDL window at: " HEX "\n", 
		window_obj->window); 
	printf(INFO "Successfully created OpenGL context at: " HEX " \n", 
		window_obj->context);
	printf(INFO "Starting window's routine \n");
    /* Start window loop */
    start_window(window_obj);
    /* Free window mem */
    destroy_window(window_obj);
	printf(INFO "Successfully destroyed SDL & OpenGL objects \n");

    return EXIT_SUCCESS;
}
