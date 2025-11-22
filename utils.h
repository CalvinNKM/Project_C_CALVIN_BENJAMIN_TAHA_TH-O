#ifndef __UTILS_H__
#define __UTILS_H__

//represents an edge (a link) between to vertices
typedef struct cell {
    int to;
    float prob;
    struct cell *next;
} cell;

// list of all outgoing edges)
typedef struct {
    cell *head;
} list;

//adjacency list
typedef struct {
    int size;
    list *lists;
} adj_list;

//add a new edge
cell *create_cell(int to, float prob);
//create a new empty adjacency list
adj_list create_adj_list(int n);

//add a cell (edge) to a list of a vertex
void addCellToList(list *L, int dest, float prob);
//create an empty List
list createList(void);

//print list (all outgoing edges for one node)
void print_list(list l);
//print adjacency list (repeats previous function for all nodes
void print_adj_list(const adj_list *al);

//from a graph file, read its values into the adjacency_list structure
adj_list readGraph(const char *filename);
//checks if the adjacency list corresponds to a Markov graph
int isaMarkovGraph(adj_list *g);

//from the adjacency list, create a Mermaid representation of the graph
void exportMermaid(const adj_list *g, const char *filename);
// free the space used by the adjacency_list
void free_adj_list(adj_list *g);

#endif
