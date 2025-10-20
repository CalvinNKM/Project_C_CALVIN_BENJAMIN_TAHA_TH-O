#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

static char *getID(int i)
{
    // translate from 1,2,3, .. ,500+ to A,B,C,..,Z,AA,AB,...
    static char buffer[10];
    char temp[10];
    int index = 0;

    i--; // Adjust to 0-based index
    while (i >= 0)
    {
        temp[index++] = 'A' + (i % 26);
        i = (i / 26) - 1;
    }

    // Reverse the string to get the correct order
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

list createList(void) {
    list L;
    L.head = NULL;
    return L;
}

void addCellToList(list *L, int dest, float prob) {
    cell *newCell = create_cell(dest, prob);
    newCell->next = L->head;
    L->head = newCell;
}

adj_list create_adj_list(int n) {
    adj_list my_adj_list;// = (adj_list*) malloc(sizeof(adj_list));
    my_adj_list.size = n;
    my_adj_list.lists = (list*) malloc(n*sizeof(list));
    for (int i = 0; i < n; i++) {
        my_adj_list.lists[i] = createList();
    }
    return my_adj_list;
}

void print_adj_list(const adj_list *al) {
    for (int i=0; i<al->size; i++) {
        printf("List for vertex %d:", i);
        print_list(&al->lists[i]);
        printf("\n");
    }
}