#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>

//a vertex
typedef struct cell {
    int to;
    float prob;
    struct cell *next;
} cell;

//all outgoing vertices of a node
typedef struct {
    cell *head;
} list;

//the adjacency list
typedef struct {
    int size;
    list *lists;
} adj_list;

//create a new cell (a vertex)
cell *create_cell(int to, float prob);
//create the adjacency list
adj_list create_adj_list(int n);

//add the vertex to the adjacency list
void addCellToList(list *L, int dest, float prob);
//create a list containing the outgoing vertices of one node
list createList(void);

//print the list of all outgoing vertices of one node
void print_list(const list *l);
//print the list of outgoing vertices for each node
void print_adj_list(const adj_list *al);

//read the data of the file into the variables
adj_list readGraph(const char *filename);
//checks if the graph is Markov (the sum of outgoing probabilities of each node is 1)
int isaMarkovGraph(adj_list *g);

//generate the file that can be read by Mermaid
void exportMermaid(const adj_list *g, const char *filename);
//free the space allocated
void free_adj_list(adj_list *g);

#endif
