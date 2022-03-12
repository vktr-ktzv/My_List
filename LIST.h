#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


const int INIT_SIZE = 2;
const int MULTIPLIER = 2;
const int TRASHHH = -999;
const int OUT_OF_MEMORY = 9999;

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
    int len  = 0;

    ListElem *elem;
} List;

int ListCtor(List* lst);
int ListDump (List* lst);
int ListInsert (List* lst, int pos, int newdata);
int ListDelete (List* lst, int delpos);
int ListDeleteFirst(List* lst);
int ListFilling (List* lst);
int liner (List* lst);
int Graphviz_Dump (FILE* log, List* lst);
int resize_list (List* lst);
