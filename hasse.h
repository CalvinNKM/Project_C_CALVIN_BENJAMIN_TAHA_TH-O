#ifndef __HASSE_H__
#define __HASSE_H__
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

#define NBMAX 50

// Vertex structure for the tarjan algo
typedef struct {
    int identifier;
    int number;
    int access_number;
    int processing;
} t_tarjan_vertex;

// Class (name and a set of lists of tarjan vertices)
typedef struct {
    char name[3];
    int size;
    t_tarjan_vertex ** list;
} t_class;

// Partition (set of classes)
typedef struct {
    int size;
    t_class * lists;
} t_partition;

// Link from one class to another
typedef struct {
    int from;
    int to;
} t_link;

// Array containing all the links between all the classes
typedef struct {
    int log_size;
    t_link links[NBMAX];
} t_link_array;

// Stack used by the Tarjan algo
typedef struct {
    t_tarjan_vertex * data[NBMAX];
    int size;
} t_stack;

// Create an empty tarjan vertex
t_tarjan_vertex create_tarjan(int identifier);
// Convert all vertices from an adjacency list into tarjan vertices
t_tarjan_vertex* createTarjanArray(adj_list g);

// Create an empty stack
t_stack create_stack();
// Add a tarjan vertex on the top of the stack
void push_stack(t_stack *s, t_tarjan_vertex * val);
// Delete the tarjan vertex on the top of the stack and return its value (pointer)
t_tarjan_vertex * pop_stack(t_stack *s);

// Main function of the Tarjan algo (see Wikipedia)
void parcours(t_tarjan_vertex* v, int * number, t_stack * s, adj_list g, t_tarjan_vertex * arr, t_partition * p);
// Function executing the Tarjan algo
t_partition tarjan(adj_list g);

/**
 * @brief Creates a link array from the given partition and graph.
 *
 * @param part The partition of the graph.
 * @param graph The adjacency list representation of the graph.
 * @return The created link array.
 */
t_link_array createLinkArray(t_partition part, adj_list graph);
// Create a mermaid file representing the Hasse diagram (links between classes)
void exportHasse(t_partition p, t_link_array links, const char *filename);
// Find the class properties (transient, persistent, absorbing)
void computeClassProperties(t_partition part, t_link_array links);
#endif