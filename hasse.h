#ifndef __HASSE_H__
#define __HASSE_H__
#include "utils.h"
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
    char* name;
    t_tarjan_cell list;
} t_class;

typedef struct {
    int size;
    t_class *lists;
}t_partition;

void removeTransitiveLinks(t_link_array *p_link_array);

typedef struct {
    int *data;
    int size;
    int capacity;
} t_stack;

t_tarjan_vertex *create_tarjan(int identifier, int prob);
t_tarjan_vertex* createArrayTarjan(adj_list g);

t_stack create_stack(void);


/**
 * @brief Creates a link array from the given partition and graph.
 *
 * @param part The partition of the graph.
 * @param graph The adjacency list representation of the graph.
 * @return The created link array.
 */


#endif