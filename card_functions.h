#ifndef CARD_FUNCTIONS_H
#define CARD_FUNCTIONS_H

#include "definations.h"

/* function to check all main list */
void card_category_sum(category_head *chd, l_head *hd);

/* function: category list init */
category *card_category_init_list(category_head *chd, l_elem *elem);

/* function: creates new or rewrite existing category */
category *card_category_add(category_head *chd, l_elem *elem);

/* function: report printing */
void card_category_report(category_head *chd);

#endif // CARD_FUNCTIONS_H
