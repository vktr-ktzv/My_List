#include "LIST.h"


int main()
{
    List lst = {};

    ListCtor(&lst);

    ListFilling(&lst);

    ListDump (&lst);

    ListInsert (&lst, 2, 99);

    ListDelete (&lst, 5);

    //ListInsert (&lst, 7, 88);

   // ListInsert (&lst, 8, 77);

   // ListDelete (&lst, 9);

    //ListDelete (&lst, 1);

    ListDump (&lst);

    liner (&lst);

    ListDump (&lst);

    FILE* log = fopen ("example2.dot", "w+");

    Graphviz_Dump (log, &lst);

    fclose(log);

    ListDctor(&lst);

    return 0;
}
