#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>

typedef struct cell {
    int to;
    float prob;
    struct cell *next;
} cell;

typedef struct {
    cell *head;
} list;

typedef struct {
    int size;
    list *lists;
} adj_list;

cell *create_cell(int to, float prob);
adj_list create_adj_list(int n);

void addCellToList(list *L, int dest, float prob);
list createList(void);

void print_list(list l);
void print_adj_list(const adj_list *al);

adj_list readGraph(const char *filename);
int isaMarkovGraph(adj_list *g);

void exportMermaid(const adj_list *g, const char *filename);
void free_adj_list(adj_list *g);

#endif
