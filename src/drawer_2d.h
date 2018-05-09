#ifndef DRAWER_2D_H
#define DRAWER_2D_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

/* Data structures */
typedef struct {
    pos2f_t center;
    config_t *config;
    float view_distance;
    float x_scaling,y_scaling;
} drawer_2d_t;
typedef enum {
    NORTH = 0,
    EAST,
    SOUTH,
    WEST
} direction_t;

/* Drawers functions */
void init_drawer(drawer_2d_t *drawer);
void translate(drawer_2d_t *drawer, float x, float y);
void move(drawer_2d_t *drawer, double distance, direction_t direction);
void rotate(drawer_2d_t *drawer, double angle);
void update_view_distance(drawer_2d_t *drawer, float view_distance);
void zoom_in(drawer_2d_t *drawer);
void zoom_out(drawer_2d_t *drawer);
float pixel_proportion(drawer_2d_t *drawer);
void transform(drawer_2d_t *drawer, point2f_t *point, point2f_t *pc_point);
int draw_points(drawer_2d_t *drawer, point2f_t *point_arr, size_t points_number);

#endif 
