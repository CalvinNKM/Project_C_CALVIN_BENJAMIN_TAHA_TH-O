#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>

typedef struct cell {
    int to;
    float prob;
    struct cell *next;
} Cell;

typedef struct {
    Cell *head;
} List;

typedef struct {
    int size;
    List *lists;
} AdjList;

Cell *create_cell(int to, float prob);
void  free_list(List *l);
List  create_list(void);

AdjList create_adjlist(int n);
void    free_adjlist(AdjList *g);


void add_edge(AdjList *g, int from, int to, float prob);

void print_list(FILE *out, const List *l);
void print_adjlist(FILE *out, const AdjList *g);

AdjList readGraph(const char *filename);


int check_markov(const AdjList *g, FILE *out);

int export_mermaid(const AdjList *g, const char *filename);
#endif
