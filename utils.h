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
list  create_list(void);

adj_list create_adj_list(int n);
void    free_adj_list(adj_list *g);


void add_edge(adj_list *g, int from, int to, float prob);

void print_list(const list *l);
void print_adj_list(FILE *out, const adj_list *g);

adj_list readGraph(const char *filename);


int check_markov(const adj_list *g, FILE *out);

int export_mermaid(const adj_list *g, const char *filename);
#endif
