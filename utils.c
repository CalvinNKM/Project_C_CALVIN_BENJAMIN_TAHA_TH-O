#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include <errno.h>

#include "utils.h"
static char *getID(int i)
{
    static char buffer[10];
    char temp[10];
    int index = 0;

    i--;
    while (i >= 0)
    {
        temp[index++] = 'A' + (i % 26);
        i = (i / 26) - 1;
    }
    for (int j = 0; j < index; j++)
    {
        buffer[j] = temp[index - j - 1];
    }
    buffer[index] = '\0';

    return buffer;
}

cell *create_cell(int to, float prob)
{
    cell *c = (cell*)malloc(sizeof(cell));
    if (!c) {
        return NULL;
    }
    c->to = to;
    c->prob = prob;
    c->next = NULL;
    return c;
}


void print_list(const list *l)
{
    printf("[head @]");
    const cell *cur = l->head;
    while (cur) {
        printf(" -> (%d, %.2f)", cur->to, cur->prob);
        cur = cur->next;
    }
    printf("\n");
}
