#include "list_functions.h"

/* function: list initialization
give back: pointer to created elem;
*/
l_elem *list_init(l_head *hd, transaction *trans)
{
    // first elem init
    l_elem *lst = NULL;
    lst = (l_elem*) malloc(sizeof(l_elem)); // memory allocation: new elem
    lst->data = trans; // data save
    lst->next = NULL;
    // head start data init
    hd->count = 1;
    lst->index = 1;
    hd->first = lst;
    hd->last = lst;
    return lst;
}

/* function: new element add to list
give back: pointer to created elem;
*/
l_elem *list_add(l_head *hd, l_elem *c_lst, transaction *trans)
{
    l_elem *n_lst = NULL; // new elem init
    n_lst = (l_elem*) malloc(sizeof(l_elem)); // new elem memory allocation
    n_lst->data = trans; // data save for new elem
    n_lst->next = NULL; // because new elem == last
    c_lst->next = n_lst; // new elem is next for current
    hd->last = n_lst; // head "last" pointer to new elem
    hd->count++; // because +1 elem
    n_lst->index = hd->count;
    return n_lst;
}

/* function: list printing */
void list_print(l_head *hd)
{
    l_elem *tmp = NULL; // temp pointer
    tmp = hd->first; // ptr set to first elem
    do // cycle
    {
        printf("|%6d", tmp->index);
        struct_print(tmp->data); // data printing
        tmp = tmp->next; // ptr set to next elem
    }while(tmp != NULL); // cycle end if elem doesn't exist
}

/* function: swap list elements */
void list_swap(l_elem *n1, l_elem *n2)
{
    transaction *tmp; // tmp pointer for swap
    tmp = n1->data; // n1 remembered
    n1->data = n2->data; // n2 writed to n1
    n2->data = tmp; // n1 writed to n2
}

/* function: card searching by number
give back: pointer to element*/
l_elem *list_num_search(l_head *head, int i)
{
    int flag;
    flag = 0;
    l_elem *t = NULL;
    t = head->first;
    do
    {
        if(t->index == i)
        {
            flag = 1;
            break;
        }
        else t = t->next;
    }while(t != NULL);
    if(flag == 0)
    {
        t = NULL;
        printf("There is no element with this number\n");
    }
    return t;
}

/* function: element deleting by number */
void list_element_delete(l_head *head, l_elem *dlt)
{
    l_elem *tmp = NULL;
    tmp = head->first;
    if(dlt->index == 1) // deleting from start
    {
        tmp = dlt->next;
        free(dlt->data);
        dlt->next = NULL;
        free(dlt);
        head->first = tmp;
        tmp->index--;
        do
        {
            tmp = tmp->next;
            tmp->index--;
        }while(tmp->next != NULL);
    }
    else if(dlt->index == head->last->index) // deleting from end
    {
        do
        {
            tmp = tmp->next;
        }while(tmp->next != dlt); // set pointer to previous element
        head->last = tmp;
        tmp->next = NULL;
        free(dlt->data);
        free(dlt);
    }
    else
    {
        do
        {
            tmp = tmp->next;
        }while(tmp->next != dlt); // set pointer to previous element
        tmp->next = dlt->next;
        free(dlt->data);
        dlt->next = NULL;
        free(dlt);
        do
        {
            tmp = tmp->next;
            tmp->index--;
        }while(tmp->next != NULL);
    }
}

/* function: elements searching by date */
void list_search_date(l_head *head)
{
    date *tmp_date_min = NULL;
    date *tmp_date_max = NULL;
    char tmp_str[128];
    char** tmp_str_array = NULL;
    tmp_date_min = (date*) malloc(sizeof(date));
    tmp_date_max = (date*) malloc(sizeof(date));
    printf("This is searching between two dates, format: dd.mm.yyyy\n");
    printf("Print min (older) date: ");
    while (getchar() != '\n'); // stdin clear
    fgets(tmp_str, 128, stdin);
    tmp_str_array = split(tmp_str, 10, '.');
    tmp_date_min->day = atoi(tmp_str_array[0]);
    tmp_date_min->month = atoi(tmp_str_array[1]);
    tmp_date_min->year = atoi(tmp_str_array[2]);
    printf("Print max (newest) date: ");
    fgets(tmp_str, 128, stdin);
    tmp_str_array = split(tmp_str, 10, '.');
    tmp_date_max->day = atoi(tmp_str_array[0]);
    tmp_date_max->month = atoi(tmp_str_array[1]);
    tmp_date_max->year = atoi(tmp_str_array[2]);

    l_elem *p = NULL;
    p = head->first;
    do
    {
        if(p->data->date->year >= tmp_date_min->year && p->data->date->year <= tmp_date_max->year)
            if(p->data->date->month >= tmp_date_min->month && p->data->date->month <= tmp_date_max->month)
                if(p->data->date->day >= tmp_date_min->day && p->data->date->day <= tmp_date_max->day)
                {
                    printf("|%6d", p->index);
                    struct_print(p->data);
                }
        p = p->next;
    }while(p != NULL); // cycle end if elem doesn't exist

    // memory free
    free(tmp_date_min);
    free(tmp_date_max);
    tmp_date_min = NULL;
    tmp_date_max = NULL;
}

/* function: list sorting by a date*/
void list_sort_date(l_head *hd)
{
    // bubble sort
    int flag; // flag of swap
    int i, j;
    l_elem *p = NULL; // ptr for list se
    for(i = 0; i < hd->count-1; i++)
    {
        p = hd->first; // from start
        flag = 0;
        for(j = 0; j < hd->count-1-i; j++)
            if((p->data->date->year >= p->next->data->date->year) && (p->data->date->month >= p->next->data->date->month) && (p->data->date->day >= p->next->data->date->day))
            {
                list_swap(p, p->next);
                p = p->next; // move right
                flag = 1;
            }
            else
                p = p->next; // move right
        if(flag == 0) break; // stop if already sorted
    }
}

/* function: list sorting by a sum*/
void list_sort_sum(l_head *hd)
{
    // bubble sort
    int flag; // flag of swap
    int i, j;
    l_elem *p = NULL; // ptr for list see
    for(i = 0; i < hd->count-1; i++)
    {
        p = hd->first; // from start
        flag = 0;
        for(j = 0; j < hd->count-1-i; j++)
            // because all floats are positive
            if(p->data->sum - p->next->data->sum < -0.01)
            {
                list_swap(p, p->next);
                p = p->next; // move right
                flag = 1;
            }
            else
                p = p->next; // move right
        if(flag == 0) break; // stop if already sorted
    }
}
