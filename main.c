#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "definations.h"
#include "card_functions.h"
#include "list_functions.h"
#include "struct_functions.h"

int main()
{
    enum {SEP = ',', maxlen = 128};
    l_elem *p_elem = NULL; // ptr for list node
    l_head *p_head = NULL; // ptr for list ptr
    //category_head *cat_h = NULL;
    transaction *tmp_struct = NULL; // ptr for tmp struct
    if((p_head = (l_head*) malloc(sizeof(l_head))) == NULL)
    {
        printf("Error at memory allocation at main (p_head)\n");
        return 0;
    } // if mem. alloc. err

    // ->->->- ->->->-  reading from file   ->->->- ->->->-

    FILE *df;
    if((df = fopen("data.csv", "r")) == NULL) // file open
    {
        printf("Error at file opening at main (file.csv)\n");
        return 0;
    } // if file open err
    char tmp_str[maxlen]; // temp string for read
    char** tmp_str_array = NULL; // temp string array for struct create
    transaction *tmp_t = NULL; // temp ptr to struct
    int first_str;
    first_str = 1; // flag for init
    while((fgets(tmp_str, maxlen, df))!=NULL) // while not EOF
    {
        tmp_str_array = split(tmp_str, maxlen, SEP); // array from split
        tmp_t = struct_create(tmp_str_array); // struct from array
        if(first_str == 1)
        {
            p_elem = list_init(p_head, tmp_t); // list initialization, first elem add
            first_str = 0; // already initialized
        } // if list didn't initialized
        else
        {
            p_elem = list_add(p_head, p_elem, tmp_t); // element add
        } // if list was initialized
    }
    fclose(df); // file close

    // -<-<-<- -<-<-<-  reading from file   -<-<-<- -<-<-<-

    // ->->->- ->->->-  menu                ->->->- ->->->-
    int menu;
    menu = -1;
    while(menu != 7)
    {
        printf("MENU:\n0 -- info\n1 -- add a card\n2 -- redact a card\n3 -- delete a card\n4 -- print table\n");
        printf("5 -- search a card\n6 -- sort by param\n7 -- exit\nYour num: ");
        scanf("%d", &menu);
        switch(menu)
        {
        case 0: // info
            printf("This program is usable for budget calculations.\n");
            printf("About work: programming course work of second semester\nAbout author: Arkhipov Nikita, group 9305");
            menu = -1; // for next work;
            break;
        case 1: // add a card from keyboard
            while (getchar() != '\n'); // stdin clear
            printf("Format: day.month.year,sum,type,card name,category\n");
            printf("Write string by format: ");
            fgets(tmp_str, maxlen, stdin); // user string reading
            tmp_str_array = split(tmp_str, maxlen, SEP); // user string to string array
            tmp_struct = struct_create(tmp_str_array); // string array to struct
            p_elem = list_add(p_head, p_elem, tmp_struct); // element add
            menu = -1; // for next work;
            break;
        case 2: // redact a card
            printf("Write a number of card to redact: ");
            scanf("%d", &menu);
            p_elem = list_num_search(p_head, menu);
            if(p_elem != NULL)
            {
                while (getchar() != '\n'); // stdin clear
                printf("Format: day.month.year,sum,type,card name,category\n");
                printf("Write string by format: ");
                fgets(tmp_str, maxlen, stdin); // user string reading
                tmp_str_array = split(tmp_str, maxlen, SEP); // user string to string array
                tmp_struct = struct_create(tmp_str_array); // string array to struct
                free(p_elem->data); // memory clearing of old data
                p_elem->data = tmp_struct; // new data save
            }
            p_elem = p_head->last; // back to last element
            menu = -1; // for next work;
            break;
        case 3: // delete a card
            printf("Write a number of transaction to delete: ");
            scanf("%d", &menu);
            p_elem = list_num_search(p_head, menu);
            if(p_elem != NULL)
            {
                list_element_delete(p_head, p_elem);
            }
            p_elem = p_head->last; // back to last element
            menu = -1; // for next work;
            break;
        case 4: // print cards list
            print_header();
            list_print(p_head);
            print_line();
            menu = -1; // for next work;
            break;
        case 5: // search a card
            list_search_date(p_head);
            menu = -1;
            break;
        case 6: // sort by param
            printf("0 -- sort by date\n1 -- sort by price\nYour num: ");
            scanf("%d", &menu);
            if(menu == 0) list_sort_date(p_head);
            else if(menu == 1) list_sort_sum(p_head);
            else printf("Wrong num\n");
            menu = -1; // for next work;
            break;
            /* case 7
            cat_h = (category_head*) malloc(sizeof(category_head));
            card_category_sum(cat_h, p_head);
            card_category_report(cat_h);
            menu = -1;
            break;
            */
        case 7: // exit
            printf("Data saving...");
            if((df = fopen("data.csv", "w")) == NULL) // file open with rewrite
            {
                printf("Error at file opening, shutting down...\n");
                return 0;
            } // if file open error
            p_elem = p_head->first;
            do
            {
                struct_fprint(p_elem->data, df);
                if(p_elem->next != NULL) fprintf(df, "\n");
                p_elem = p_elem->next;
            }while(p_elem != NULL);
            fprintf(df, "\n");
            break;
        default:
            printf("Wrong num\n");
            break;
        }
    }
    // -<-<-<- -<-<-<-  menu                -<-<-<- -<-<-<-

    return 0;
}
