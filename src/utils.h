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
struct std_stack {
    int top;
    struct std_stack *pile;
};
typedef struct std_stack std_stack_t;
typedef struct {
    char *str;
    size_t len;
} branch_str_t;

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
void linear_interpolation2f(point2f_t *a, point2f_t *b, 
        float paramter, point2f_t *res);
void bezier_point2f(point2f_t *control_polygon, size_t polygon_points, 
        float parameter, point2f_t *res);
void bezier_curve2f(point2f_t *control_polygon, size_t polygon_points, 
        point2f_t *curve, unsigned int point_number);

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
size_t run_length(char *str, size_t len);
size_t count_branches(char *str, size_t len);
void branch_parse(char *str, branch_str_t *branch_arr);
void free_branch(branch_str_t *arr, size_t size);

/* Stack helpers */

/* Standard stack helpers */
void pop(std_stack_t **stack);
void push(int new_top, std_stack_t **stack);
void free_stack(std_stack_t *stack);

/* 2-D stack helpers */
void update2f_top(float x, float y, float angle,
                pos2f_stack_t *root);
void pop2f(pos2f_stack_t **root);
void push2f(pos2f_t new_top, pos2f_stack_t **root);
void free2f_stack(pos2f_stack_t *root);

/* 3-D stack helper */
// TODO

#endif
