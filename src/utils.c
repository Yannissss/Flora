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
