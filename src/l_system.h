#ifndef L_SYSTEM_H
#define L_SYSTEM_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

/* Data Structures */
typedef struct {
    const char *f_rule;
    size_t f_len;
    const char *x_rule;
    size_t x_len;
    pos2f_t start_pos;
    float depth, angle; // Rotation angle in degrees
} l_system_t;
typedef struct {
    point2f_t *point_arr;
    size_t size;
} branch2f_t;

/* L-System manipulation functions */
size_t farm(l_system_t *l_system, char *axiom, 
            int generations, char **str_location);
size_t std_compile2f(l_system_t *l_system, char *sequence, 
            size_t len, point2f_t **point_arr);

#endif
