#ifndef LIST_FUNCTIONS_H
#define LIST_FUNCTIONS_H

#include "definations.h"
#include "struct_functions.h"

/* function: list initialization
give back: pointer to created elem;
*/
l_elem *list_init(l_head *hd, transaction *trans);

/* function: new element add to list
give back: pointer to created elem;
*/
l_elem *list_add(l_head *hd, l_elem *c_lst, transaction *trans);

/* function: list printing */
void list_print(l_head *hd);

/* function: swap list elements */
void list_swap(l_elem *n1, l_elem *n2);

/* function: card searching by number
give back: pointer to element*/
l_elem *list_num_search(l_head *head, int i);

/* function: element deleting by number */
void list_element_delete(l_head *head, l_elem *dlt);

/* function: elements searching by date */
void list_search_date(l_head *head);

/* function: list sorting by a date*/
void list_sort_date(l_head *hd);

/* function: list sorting by a sum*/
void list_sort_sum(l_head *hd);

#endif // LIST_FUNCTIONS_H
