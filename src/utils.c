#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

/* Counting characters function */
int occurences(char *str, size_t len, int character)
{
    char *ptr = NULL;
    int char_number = 0;
    for ( ptr = str; ptr < str+len; ++ptr)
        if (*ptr == character)
            ++char_number;
    return char_number;
}

/* Insert source string into dest string */
void string_insert(const char *source, size_t source_len, 
                   char *dest)
{
    for (int i = 0; i < source_len; ++i)
        dest[i] = source[i];
    return;
}

/*
 * Change to top pos2fition to new_pos2f
 */
void update2f_top(float x, float y, float angle,
                pos2f_stack_t *root)
{
    pos2f_t new_top = {x, y, angle};
    root->top = new_top;
}

/* Free top stack memory and link to
 * new top
 */
void pop2f(pos2f_stack_t **root)
{
    pos2f_stack_t *new_root = (*root)->stack;
    free(*root);
    *root = new_root;
    return;
}

/*
 * Add new pos2fition on top of
 * a stack
 */
void push2f(pos2f_t pos2f, pos2f_stack_t **root)
{
    pos2f_stack_t *new_root = malloc( sizeof(pos2f_stack_t) );
    new_root->top = pos2f;
    new_root->stack = *root;
    *root = new_root;
    return;
}

/*
 * Free all memory used by a stack
 */
void free2f_stack(pos2f_stack_t *root)
{
    pos2f_stack_t *ptr = root;
    while ( !ptr )
    {
        pos2f_stack_t *new_ptr = ptr->stack;
        free(ptr);
        ptr = new_ptr;
    }
    free(root);
    return;
}

/*
 * Calculate the linear interpolation between 
 * points a, b of a given paramter and store it into
 * res
 */
void liner_interpolation(point2f_t *a, point2f_t *b, 
                         float parameter, point2f_t *res)
{
    res->x = (1.0-parameter)*a->x
             + parameter*b->x;
    res->y = (1.0-parameter)*a->y
             + parameter*b->y;
}

/*
 * Using the Casteljau's algorithm to calculate the
 * coordinates of the point of a given paramter of
 * a Bézier curve given its control polygon and store
 * it into res
 */
void bezier_point(point2f_t *control_polygon, size_t polygon_points, 
                 float parameter, point2f_t *res)
{
    /* Copying control polygon into a buffer */
    point2f_t polygon_buffer[polygon_points];
    for (int i = 0;i < polygon_points; ++i)
        polygon_buffer[i] = control_polygon[i];
    /* Looping through the layers the compose the
     * triangular array of points
     */
    for (int i = 0;i < polygon_points; ++i)
    {
        /* Looping through the current layer 
         * of points 
         */
        for (int j = 0;j < (polygon_points-j); ++j)
        {
            point2f_t point_buffer;
            linear_interpolation(polygon_buffer+j, polygon_buffer+j+1,
                    parameter, &point_buffer);
            polygon_buffer[j] = point_buffer;
        }   
    }
    /* Storing the last calculated point in res */
    (*res) = polygon_buffer[0];
}
