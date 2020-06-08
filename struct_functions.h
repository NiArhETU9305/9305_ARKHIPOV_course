#ifndef STRUCT_FUNCTIONS_H
#define STRUCT_FUNCTIONS_H

#include "definations.h"

/* function: splits string to array of strings by separator
give back: array of strings
*/
char **split(char *str, int length, char sep);

/* function: clears memory of string array */
void clear_str_array(char **str, int n);

/* function: creates structure from array of strings
give back: ptr to created struct */
transaction *struct_create(char **str);

/* function: struct memory free */
void struct_clear(transaction *t);

/* function: struct print */
void struct_print(transaction *t);

/* function: header printing */
void print_header();

/* function: line printing */
void print_line();

/* function: print structure to file */
void struct_fprint(transaction *t, FILE *df);

#endif // STRUCT_FUNCTIONS_H
