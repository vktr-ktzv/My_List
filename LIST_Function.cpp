int ListInsert (List* lst, int pos, int newdata)
{
    int tmp = abs(lst->elem[lst->free].next);
    /*0*/ lst->elem[lst->free].data  = newdata;
    /*1*/ lst->elem[lst->elem[pos].next].prev = lst->free;
    /*2*/ lst->elem[lst->free].next  = lst->elem[pos].next;
    /*3*/ lst->elem[pos].next = lst->free;

    lst->elem[lst->free].prev = pos;

    lst->free = tmp;
     printf(">>>>>>>> NEW FREE -- %d <<<<", lst->free);
    lst->tail++;

     printf (">>> ListInsert worked:\n");
               printf ("               data[%d] = %d <<<\n", lst->free-1, lst->elem[lst->free-1].data); 
    return 0;
}

int ListCtor(List* lst)
{
    for (int i = 1; i < NUMOFDATA; i++)
    {
        lst->elem[i].data = 0;
        lst->elem[i].next = -(i +1);
        lst->elem[i].prev = i - 1;
    }

    return 0;
}

int ListDump (List* lst)
{
    for (int i = 1; i < NUMOFDATA; i++)
    {
         printf (">>> Elem[%d] = %d, NEXT = %d, PrevPos = %d <<<\n", i, lst->elem[i].data, lst->elem[i].next, lst->elem[i].prev);
    }

    printf (">>> FREE = %d, HEAD = %d, TAIL = %d <<<\n\n", lst->free, lst->head, lst->tail);

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
    //lst->elem[lst->elem[delpos - 1].next].
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

        if (scanf("%d", &lst->elem[i].data) == 0)
        {
            lst->elem[i-1].next = 0;
            break;
        }

        lst->elem[i].next = i + 1;
        lst->elem[i].prev = lst->elem[i - 1].next - 1;

        lst->free ++;
        lst->tail++;

        i++;
    }

    lst->free++;

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

        if(i >= NUMOFDATA - 1)
        {
            fprintf (log, "%d[label = \"{%d}|{Data = %d| Next = %d| Prev = %d}\"];\n", i, i, lst->elem[i].data, lst->elem[i].next, lst->elem[i].prev);
            break;
        }

        fprintf (log, "%d[label = \"{%d}|{Data = %d| Next = %d| Prev = %d}\"];\n", i, i, lst->elem[i].data, lst->elem[i].next, lst->elem[i].prev);

        i++;
    }

    i = 1;
    fprintf (log, "edge [color=\"white\"]\n");

    while(i < NUMOFDATA - 1)
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



        /*

        fprintf (log, "\"data: %d - %d\" -> \"data: %d - %d\";\n  ", i, lst->elem[i].data, lst->elem[i].next, lst->elem[lst->elem[i].next].data );


        if (lst->elem[lst->elem[i].next].next <= 0)
        {
            fprintf (log, "\"data: %d - %d\" -> \"data: %d - %d\" ", i, lst->elem[i].data, lst->elem[i].next, lst->elem[lst->elem[i].next].data);
            break;
        }

        i = lst->elem[i].next;

    }*/
   // fprintf (log, "[style =



    fprintf (log, "\n}");


    return 0;
}

int liner (List* lst)
{
    int tmp_arr[NUMOFDATA] = {};

    lst->elem[lst->head].data = tmp_arr[1];

    int nxt = lst->elem[lst->head].next;

    for (int i = 2; i < NUMOFDATA - lst->head; i++)
    {
        tmp_arr[i] = lst->elem[nxt].data;

        nxt = lst->elem[nxt].next;
    }

    for (int i = 1; i < NUMOFDATA; i++)
    {
        lst->elem[i].data = tmp_arr[i];
    }

    return 0;
}
