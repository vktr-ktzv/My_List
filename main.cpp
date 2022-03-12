#include "LIST.h"


int main()
{
    List lst = {};

    ListCtor(&lst);

    /*lst.elem[1].data = 10;
    lst.elem[1].next = 2;

    lst.elem[2].data = 20;
    lst.elem[2].next = 3;

    lst.elem[3].data = 30;
    lst.elem[3].next = 0;

    lst.free = 4;
    lst.head = 1;
    lst.tail = 3;*/

    ListFilling(&lst);

    ListDump (&lst);

    ListInsert (&lst, 2, 99);

   // ListDelete (&lst, 5);

    //ListInsert (&lst, 7, 88);

   // ListInsert (&lst, 8, 77);

   // ListDelete (&lst, 9);

    //ListDelete (&lst, 1);

    ListDump (&lst);

    //liner (&lst);

    ListDump (&lst);

    FILE* log = fopen ("example2.dot", "w+");

    Graphviz_Dump (log, &lst);

    fclose(log);

    return 0;
}
