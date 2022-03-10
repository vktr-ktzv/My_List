#include <TXLib.h>


const int NUMOFDATA = 15;
const int TRASHHH = -999;

typedef struct
{
    int data;
    int next;
    int prev;
} ListElem;

typedef struct
{
    int free = 0;
    int head = 0;
    int tail = 0;

    ListElem elem[NUMOFDATA] = {};
} List;

int ListCtor(List* lst);
int ListDump (List* lst);
int ListInsert (List* lst, int pos, int newdata);
int ListDelete (List* lst, int delpos);
int ListDeleteFirst(List* lst);
int ListFilling (List* lst);
int liner (List* lst);
int Graphviz_Dump (FILE* log, List* lst);

#include "LIST_Function.cpp"
