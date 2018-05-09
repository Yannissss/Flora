#ifndef UTILS_H
#define UTILS_H

/* Macros utils */
#define SQUARE(a) a*a

/* Data structures */
typedef struct {
    int width,height;
    int max_framerate;
    float view_distance;
    float travel_speed, rot_speed, scale_sens;
} config_t;

/* Geometric utils */

/* 2-D stuctures */
typedef struct {
    float x,y,angle;
} pos2f_t;
struct pos2f_stack {
    pos2f_t top;
    struct pos2f_stack *stack;
};
typedef struct pos2f_stack pos2f_stack_t;

typedef struct {
    float x,y;
} point2f_t;

/* 3-D structures */
// TODO

/* Geometry algorithms */
void linear_interpolation(point2f_t *a, point2f_t *b, 
                         float paramter, point2f_t *res);
void bezier_point(point2f_t *control_polygon, size_t polygon_points, 
                 float parameter, point2f_t *res);

/* Constants */

/* Log format */
#define INFO "\033[32m::\033[37m "
#define ERR  "\033[31m::\033[37m "
#define WARN "\033[33m::\033[37m "
#define HEX  "0x%08x"

/* Maths constants */
#define PI  3.14159265358979323846

/* Helpers */
int occurences(char *str, size_t len, int character);
void string_insert(const char *source, size_t source_len, 
                   char *dest);

/* Stack helpers */
/* 2-D stack helpers */
void update2f_top(float x, float y, float angle,
                pos2f_stack_t *root);
void pop2f(pos2f_stack_t **root);
void push2f(pos2f_t new_top, pos2f_stack_t **root);
void free2f_stack(pos2f_stack_t *root);
/* 3-D stack helper */
// TODO

#endif
