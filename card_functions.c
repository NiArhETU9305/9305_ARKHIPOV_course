#include "card_functions.h"

/* function to check all main list */
void card_category_sum(category_head *chd, l_head *hd)
{
    l_elem *tmp = NULL;
    category *cat = NULL;
    tmp = hd->first;
    if(chd->first == NULL)
    {
        cat = card_category_init_list(chd, tmp);
        printf("%f --", cat->sum);
    }
    do
    {
        cat = card_category_add(chd, tmp);
        printf("%f --", cat->sum);
        tmp = tmp->next;
    }while(tmp != NULL);
}

/* function: category list init */
category *card_category_init_list(category_head *chd, l_elem *elem)
{
    category *tmp = NULL;
    tmp = (category*) malloc(sizeof(category));
    tmp->sum = elem->data->sum;
    tmp->name = elem->data->category;
    tmp->type = elem->data->type;
    tmp->next = NULL;
    chd->first = tmp;
    return tmp;
}

/* function: creates new or rewrite existing category */
category *card_category_add(category_head *chd, l_elem *elem)
{
    category *c_cat = NULL;
    c_cat = chd->first;
    int flag;
    flag = 0;
    while(c_cat != NULL)
    {
        if(strcmp(c_cat->name, elem->data->category) == 0)
        {
            c_cat->sum += elem->data->sum;
            flag = 1;
            break;
        }
        c_cat = c_cat->next;
    }
    if(flag == 0)
    {
        category *crt = NULL;
        crt = (category*) malloc(sizeof(category));
        crt->sum = elem->data->sum;
        crt->name = elem->data->category;
        crt->type = elem->data->type;
        crt->next = NULL;
        c_cat->next = crt;
        c_cat = c_cat->next;
    }
    return c_cat;
}

void card_category_report(category_head *chd)
{
    category *c_cat = NULL;
    c_cat = chd->first;
    printf("INCOME\n");
    while(c_cat != NULL)
    {
        if(c_cat->type == 1) printf("%20s: %.2f\n", c_cat->name, c_cat->sum);
        c_cat = c_cat->next;
    }
    c_cat = chd->first;
    printf("OUTCOME\n");
    while(c_cat != NULL)
    {
        if(c_cat->type == 0) printf("%20s: %.2f\n", c_cat->name, c_cat->sum);
        c_cat = c_cat->next;
    }
}
