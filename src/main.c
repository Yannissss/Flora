#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "l_system.h"
#include "window.h"
#include "utils.h"

/* Default config constants */
config_t default_config = {
    800,          // Window width
    600,          // Window height
    60,           // Window framerate cap
    2,            // Default view distance
    150,          // Travel speed in pixel/second
    95*PI/180,    // Angular speed in rad/second
    1.75,         // Scale sensitivity
};

/* Implement main routine */
int main(int argc, const char *argv[])
{
    /* Testing L-System constants */
    l_system_t testing_s = {
        "FF", 2,
        "F+{[[X]-X]}-F{[-FX]}{+X}", 24,
        {-5.0, -5.0, PI*65.0/180},
        1, 25.0
    };
    /* L-System test */
    char *str = NULL;
    size_t len = farm(&testing_s, "X", 1, &str);
    printf("%s \n", str);
    free(str);
    char testing[32] = "fd{kkk{kk}-kk{kk{kk}k}}f";
    printf("%s, %d \n", testing, strlen(testing));
    size_t branch_number = count_branches(testing, 32);
    branch_str_t arr[branch_number];
    branch_parse(testing, arr);
    for (int i = 0;i < branch_number; ++i)
        printf("%d, %s \n", arr[i].len, arr[i].str);
    free_branch(arr, branch_number);

    ///* Create window & displays it */
    //window_t *window_obj = init_window(&default_config);
    //if ( !window_obj )
    //{
        //printf(ERR "Qutting due to error...");
        //return EXIT_FAILURE;
    //}
    //printf(INFO "Successfully created SDL window at: " HEX "\n", 
		//window_obj->window); 
	//printf(INFO "Successfully created OpenGL context at: " HEX " \n", 
		//window_obj->context);
	//printf(INFO "Starting window's routine \n");
    ///* Start window loop */
    //start_window(window_obj);
    ///* Free window mem */
    //destroy_window(window_obj);
	//printf(INFO "Successfully destroyed SDL & OpenGL objects \n");

    return EXIT_SUCCESS;
}
