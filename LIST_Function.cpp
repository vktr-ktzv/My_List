#include <stdio.h>
#include "LIST.h"

int ListInsert (List* lst, int pos, int newdata)
{
   
    printf(">>> TAIL - %d;   FREE - %d <<< \n", lst->tail, lst->free);

    if (lst->tail + 2 >= lst->len)
    {
        resize_list(lst);
    }

    int tmp = abs(lst->elem[lst->free].next);
    /*0*/ lst->elem[lst->free].data = newdata;
    /*1*/ lst->elem[lst->elem[pos].next].prev = lst->free;
    printf(">>> FREE - %d, TMP - %d", lst->free, tmp);
    /*2*/ lst->elem[lst->free].next = lst->elem[pos].next;
    /*3*/ lst->elem[pos].next = lst->free;

    lst->elem[lst->free].prev = pos;

    lst->free = tmp;
    printf(">>>>>>>> NEW FREE -- %3d <<<<", lst->free);
    lst->tail++;

    printf (">>> ListInsert worked:\n");
    printf ("               data[%d] = %3d <<<\n", lst->free-1, lst->elem[lst->free-1].data); 
    return 0;
}

int ListCtor(List* lst)
{
    lst->free = 1;
    lst->elem = (ListElem*)calloc(INIT_SIZE, sizeof(List));
    if (lst->elem == NULL)
        exit (OUT_OF_MEMORY);

    lst->len = INIT_SIZE;

    lst->elem[0].next = 1;

    for (int i = 1; i < INIT_SIZE; i++)
    {
        lst->elem[i].data = 0;
        lst->elem[i].next = -(i + 1);
        lst->elem[i].prev = i - 1;
    }

    return 0;
}

int ListDctor (List* lst)
{
    for (int i = 1; i < lst->len; i++)
    {
        lst->elem[i].data = 0;
        lst->elem[i].next = 0;
        lst->elem[i].prev = 0;    
    } 

    free(lst->elem);

    return 0;
}

int ListDump (List* lst)
{
    for (int i = 1; i < lst->len; i++)
    {
         printf (">>> Elem[%3d] = %4d, NEXT = %4d, PrevPos = %3d <<<\n", i, lst->elem[i].data, lst->elem[i].next, lst->elem[i].prev);
    }

    printf (">>> FREE = %4d, HEAD = %4d, TAIL = %4d <<<\n\n", lst->free, lst->head, lst->tail);

    return 0;
}

int ListDeleteFirst(List* lst)
{
    lst->elem[1].data = TRASHHH;
    lst->elem[1].next = -(lst->free);
    lst->head = 2;
    lst->free = 1;

    return 0;
}

int ListDelete (List* lst, int delpos)
{
    ListDump(lst);

    /*0*/ lst->elem[lst->elem[delpos].next].prev = lst->elem[delpos].prev;
    /*1*/ lst->elem[lst->elem[delpos].prev].next = lst->elem[delpos].next;
    /*2*/ lst->elem[delpos].next = -(lst->free);
    /*3*/ lst->elem[delpos].data = TRASHHH;

    ListDump(lst);

    lst->free = delpos;

    return 0;
}

int ListFilling (List* lst)
{
     printf (">>> This is ListFilling. If you want to stop insert ^stop^ <<<\n");

    int i = 1;

    while (true)
    {
        printf(">>> Insert data <<<\n");

        if (i >= lst->len)
        {
            printf(">> WANT TO RESIZE <<< \n\n");
            resize_list (lst);
            printf(">>> Resize_List WORKED <<<\n");     
        }

        if (scanf("%d", &lst->elem[i].data) == 0)
        {    
            lst->elem[i - 1].next = 0; 
            break;
        }

        lst->elem[i].next = i + 1;
        lst->elem[i].prev = i - 1; //lst->elem[i - 1].next - 1;

        lst->free++;
        lst->tail++;

        i++;
    }

    //lst->free++;

     return 0;
}

int Graphviz_Dump (FILE* log, List* lst)
{
    fprintf (log, "digraph DUMP { \n ");

    fprintf (log, "node [shape=record, color = \"red\"]\n;");


    int i = 1;
    while(true)
    {
        //$r printf(">>>>>>>>>>>>>> GRAPHVIZ DUMP -> n == %d<<<<<<<<<<<<<<<<<<<<<<<\n", n);

        if(i >= lst->len - 1)
        {
            fprintf (log, "%d[label = \"{%d}|{Data = %d| Next = %d| Prev = %d}\"];\n", i, i, lst->elem[i].data, lst->elem[i].next, lst->elem[i].prev);
            break;
        }

        fprintf (log, "%d[label = \"{%d}|{Data = %d| Next = %d| Prev = %d}\"];\n", i, i, lst->elem[i].data, lst->elem[i].next, lst->elem[i].prev);

        i++;
    }

    i = 1;
    fprintf (log, "edge [color=\"white\"]\n");

    while(i < lst->len - 1)
    {
        fprintf(log, " %d->%d; \n", i, i + 1);
        i++;
    }

    fprintf(log," edge [color=\"black\"]\n");

    i = 1;
    while (true)
    {
        if (lst->elem[i].data == TRASHHH)
        {
            i++;
        }
        fprintf(log, "%d->%d;\n", i, lst->elem[i].next);



        if (lst->elem[abs(lst->elem[i].next)].next <= 0)
        {
            fprintf(log, "%d->%d;\n", i, lst->elem[i].next);
            break;
        }

        i = lst->elem[i].next;

    }

    fprintf (log, "\n}");


    return 0;
}

int liner (List* lst)
{
    int tmp = lst->len;

    int* tmp_arr;
    tmp_arr = (int*)calloc(lst->len, sizeof(int));

    int nxt = lst->elem[lst->head].next;

    for (int i = 1; (i < lst->len - lst->head) ; i++)
    {
        
        tmp_arr[i] = lst->elem[nxt].data;
        printf(">>>tmp_arr[%d] = %d\n", i, lst->elem[nxt].data);

        nxt = lst->elem[nxt].next;
        if (nxt == 0)
        {
            break;
        }
    }

    int list_counter = 1;
    for (int tmp_counter = 1; tmp_counter < lst->len; tmp_counter++)
    {
       if (lst->elem[tmp_counter].data != TRASHHH)
       {
           lst->elem[list_counter].data = tmp_arr[tmp_counter];
           lst->elem[list_counter].next = list_counter + 1;
           lst->elem[list_counter].prev = list_counter - 1;

           list_counter++;
       }
        
    }

    free (tmp_arr);

    return 0;
}

int resize_list (List* lst)
{
    int tmp = lst->len;

    lst->elem = (ListElem*)realloc(lst->elem, sizeof(ListElem)*MULTIPLIER*(lst->len));
    lst->len *= MULTIPLIER;

    for (int i = tmp; i < lst->len; i++)
    {
        lst->elem[i].data = 0;
        lst->elem[i].next = -(i + 1);
        lst->elem[i].prev = i - 1; 
    }
    
    if (lst->elem == NULL)
    {
        exit (OUT_OF_MEMORY);
    }

    printf(">>RESIZE IN<<<\n\n >>> NEW LEN  - %d <<<\n\n", lst->len);
    return 0;
}
