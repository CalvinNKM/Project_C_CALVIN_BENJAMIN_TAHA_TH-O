#ifndef __UTILS_H__
#define __UTILS_H__

// Represents an edge (a link) between to vertices
typedef struct cell {
    int to;
    float prob;
    struct cell *next;
} cell;

// List of all outgoing edges)
typedef struct {
    cell *head;
} list;

// Adjacency list
typedef struct {
    int size;
    list *lists;
} adj_list;

// Add a new edge
cell *create_cell(int to, float prob);
// Create a new empty adjacency list
adj_list create_adj_list(int n);

// Add a cell (edge) to a list of a vertex
void addCellToList(list *L, int dest, float prob);
// Create an empty List
list createList(void);

// Print list (all outgoing edges for one node)
void print_list(list l);
// Print adjacency list (repeats previous function for all nodes
void print_adj_list(const adj_list *al);

// From a graph file, read its values into the adjacency_list structure
adj_list readGraph(const char *filename);
// Checks if the adjacency list corresponds to a Markov graph
int isaMarkovGraph(adj_list *g);

// From the adjacency list, create a Mermaid representation of the graph
void exportMermaid(const adj_list *g, const char *filename);
// Free the space used by the adjacency_list
void free_adj_list(adj_list *g);

#endif
