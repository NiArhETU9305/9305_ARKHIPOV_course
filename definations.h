#ifndef DEFINATIONS_H
#define DEFINATIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// data cards list
typedef struct list_element
{
    int index;
    struct transaction_card *data;
    struct list_element *next;
} l_elem;

typedef struct
{
    int count; // number of elements in list
    struct list_element *first;
    struct list_element *last;
} l_head;

// categories list
typedef struct
{
    struct _category *first;
} category_head;

typedef struct _category
{
    float sum;
    char* name;
    unsigned type;
    struct _category *next;
} category;

// transaction card
typedef struct transaction_card
{
    float sum;          // sum in rubles
    char* category;     // category of transaction
    char* card_name;    // name of payment card or bank
    unsigned type:1;    // 0 -- outcome; 1 -- income
    struct _date *date; // date of transaction
} transaction;

// struct for date
typedef struct _date
{
    unsigned year:12;   // 4095 is max
    unsigned month:4;   // 12 is max
    unsigned day:5;     // 31 is max
} date;

#endif // DEFINATIONS_H
