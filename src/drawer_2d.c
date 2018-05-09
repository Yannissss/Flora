#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include "drawer_2d.h"
#include "utils.h"

/* Setup OpenGL for the drawer */
void init_drawer(drawer_2d_t *drawer)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1,1,-1,1,-1,1);
    update_view_distance(drawer, drawer->config->view_distance);
}

/* Translate drawer's center by vector (x,y) */
void translate(drawer_2d_t *drawer, float x, float y)
{
    pos2f_t new_center = {
        drawer->center.x + x,
        drawer->center.y + y,
        drawer->center.angle 
    };
    drawer->center = new_center;
}

/* Move drawer's center in a given cardinal direction */
void move(drawer_2d_t *drawer, double distance, direction_t direction)
{
    switch ( direction )
    {
        case NORTH:
            translate(drawer, +distance*sin(drawer->center.angle), 
                    +distance*cos(drawer->center.angle));
            break;
        case EAST:
            translate(drawer, +distance*cos(drawer->center.angle), 
                    -distance*sin(drawer->center.angle));
            break;
        case SOUTH:
            translate(drawer, -distance*sin(drawer->center.angle), 
                    -distance*cos(drawer->center.angle));
            break;
        case WEST:
            translate(drawer, -distance*cos(drawer->center.angle), 
                    +distance*sin(drawer->center.angle));
            break;
    }
}

/* Rotate drawer around z-axis */
void rotate(drawer_2d_t *drawer, double angle)
{
    pos2f_t new_center = {
        drawer->center.x,
        drawer->center.y,
        drawer->center.angle + angle
    };
    drawer->center = new_center;
}

/* Update the view distance according to window's dimensions */
void update_view_distance(drawer_2d_t *drawer, float view_distance)
{
    drawer->view_distance = view_distance;
    float parameter = atan((float)drawer->config->height/(float)drawer->config->width);
    drawer->x_scaling = view_distance*cos(parameter);
    drawer->y_scaling = view_distance*sin(parameter);
}

/* Zoom the drawer in */
void zoom_in(drawer_2d_t *drawer)
{
    update_view_distance(drawer, drawer->view_distance
            -drawer->config->scale_sens);
}

/* Zoom the drawer out */
void zoom_out(drawer_2d_t *drawer)
{
    update_view_distance(drawer, drawer->view_distance
            +drawer->config->scale_sens);
}

/* Given the proportionality coefficient between 
 * the view_distance and the pixels of the SDL display
 */
float pixel_proportion(drawer_2d_t *drawer)
{
    return SQUARE(drawer->view_distance)/
    (SQUARE((float)drawer->config->width)+SQUARE((float)drawer->config->height));
}

/* Transform a point in the 2-D model panel 
 * to the 2-D project plane of the drawer
 */
void transform(drawer_2d_t *drawer, point2f_t *point, 
        point2f_t *pc_point)
{
    float x = (point->x-drawer->center.x)*cos(drawer->center.angle)
             -(point->y-drawer->center.y)*sin(drawer->center.angle);
    float y = (point->x-drawer->center.x)*sin(drawer->center.angle)
             +(point->y-drawer->center.y)*cos(drawer->center.angle);
    x /= drawer->x_scaling;
    y /= drawer->y_scaling;
    pc_point->x = x;
    pc_point->y = y;
}
/* 
 * Draw the requested points on the window
 * appliying necessery transformations
 */
int draw_points(drawer_2d_t *drawer, point2f_t *point_arr, size_t points_number)
{
    int drawn_points = 0;
    point2f_t *ptr = NULL;
    glBegin(GL_POINTS);
    for (ptr = point_arr;ptr < point_arr+points_number; ++ptr)
    {
        point2f_t render_point;
        transform(drawer, ptr, &render_point);
        float x = render_point.x;
        float y = render_point.y;
        if (x <= 1 && x >= -1
         && y <= 1 && y >= -1)
        {
            glVertex2d(x,y);
            ++drawn_points;
        }
    }
    glEnd();
    return drawn_points;
}
