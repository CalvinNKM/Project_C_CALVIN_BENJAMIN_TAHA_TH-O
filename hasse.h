#ifndef __HASSE_H__
#define __HASSE_H__
#include "utils.h"

#define NBMAX 50

typedef struct {
    int identifier;
    int number;
    int access_number;
    int processing;
} t_tarjan_vertex;

typedef struct tarjan_cell {
    t_tarjan_vertex val;
    struct tarjan_cell* next;
}t_tarjan_cell;

typedef struct {
    int size;
    t_tarjan_cell* head;
} t_tarjan_list;

typedef struct {
    char name[3];
    int size;
    t_tarjan_vertex ** list;
} t_class;

typedef struct {
    int size;
    t_class * lists;
}t_partition;

//void removeTransitiveLinks(t_link_array *p_link_array);

typedef struct {
    t_tarjan_vertex * data[NBMAX];
    int size;
} t_stack;

t_tarjan_vertex create_tarjan(int identifier);
t_tarjan_vertex* createTarjanArray(adj_list g);


t_stack create_stack();
void push_stack(t_stack *s, t_tarjan_vertex * val);
t_tarjan_vertex * pop_stack(t_stack *s);

void parcours(t_tarjan_vertex* v, int * number, t_stack * s, adj_list g, t_tarjan_vertex * arr, t_partition * p);
t_partition tarjan(adj_list g);

/**
 * @brief Creates a link array from the given partition and graph.
 *
 * @param part The partition of the graph.
 * @param graph The adjacency list representation of the graph.
 * @return The created link array.
 */


#endif