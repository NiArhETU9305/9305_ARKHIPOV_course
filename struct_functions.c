#include "struct_functions.h"

/* function: splits string to array of strings by separator
give back: array of strings
*/
char **split(char *str, int length, char sep)
{
    char **sep_str=NULL;
    int i,j,k,m;
    int key,count;
    for(j=0,m=0;j<length;j++) if(str[j]==sep) m++; // sep in str count

    key=0;
    if((sep_str=(char**)malloc((m+1)*sizeof(char*)))!=NULL) // str array memory allocation
    {
        for(i=0,count=0;i<=m;i++,count++)
        {
            if((sep_str[i]=(char*)malloc(length*sizeof(char)))!=NULL) key=1; // str memory allocation
            else
            {
                // cycle stop because memory error
                key=0;
                i=m;
            }
        }
        if(key)
        {
            k=0;
            m=0;
            for(j=0;j<length;j++)
            {
                if(str[j]!=sep) sep_str[m][j-k]=str[j];
                else
                {
                    sep_str[m][j-k]='\0'; // str end
                    k=j+1;
                    m++;
                }
            }
        }
        else
        {
            //clear because memory error
            clear_str_array(sep_str,count);
        }
     }
     return sep_str;
}

/* function: clears memory of string array */
void clear_str_array(char **str, int n)
{
    int i;

    for(i=0;i<n;i++)
    {
        free(str[i]);
        str[i]=NULL;
    }
    free(str);
    str=NULL;
}

/* function: creates structure from array of strings
give back: ptr to created struct */
transaction *struct_create(char **str)
{
    transaction *t=NULL;
    date *d = NULL;
    d = (date*) malloc(sizeof(date));
    char** tmp_date = NULL; // temp array for date save

    if((t=(transaction*)malloc(sizeof(transaction)))!=NULL)
    {
        // date save
        tmp_date = split(str[0], 10, '.');
        d->day = atoi(tmp_date[0]);
        d->month = atoi(tmp_date[1]);
        d->year = atoi(tmp_date[2]);
        t->date = d;
        clear_str_array(tmp_date, 3);
        // type save
        if(strcmp("income", str[2]) == 0) t->type = 1;
        else t->type = 0;
        // other fields save
        t->sum = atof(str[1]);
        t->card_name = str[3];
        int len;
        len = strlen(str[4]);
        str[4][len-1] = '\0';
        t->category = str[4];
    }
    else printf("Error at struct creating\n");
    return t;
}

/* function: struct memory free */
void struct_clear(transaction *t)
{
    free(t);
    t=NULL;
}

/* function: struct print */
void struct_print(transaction *t)
{
    printf("|%2d.%2d.%4d|", t->date->day, t->date->month, t->date->year);
    printf("%10.2f R|", t->sum);
    if(t->type == 1) printf("  income|");
    else printf(" outcome|");
    printf("%10s|", t->card_name);
    printf("%18s|\n", t->category);
}

/* function: header printing */
void print_header()
{
    print_line();
    printf("|number|%10s|%12s|%8s|%10s|%18s|\n", "date", "sum", "type", "card name", "category");
    print_line();
}

/* function: line printing */
void print_line()
{
    int i;
    printf("+");
    for(i = 0; i < 69; i++) printf("-");
    printf("+\n");
}

/* function: print structure to file */
void struct_fprint(transaction *t, FILE *df)
{
    fprintf(df, "%d.%d.%d,", t->date->day, t->date->month, t->date->year);
    fprintf(df, "%.2f,", t->sum);
    if(t->type == 1) fprintf(df, "income,");
    else fprintf(df, "outcome,");
    fprintf(df, "%s,", t->card_name);
    fprintf(df, "%s", t->category);
}
