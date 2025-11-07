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
        printf("List for vertex %d:", i+1);
        print_list(&al->lists[i]);
    }
}

adj_list readGraph(const char *filename) {
    FILE *file = fopen(filename, "rt"); // read-only, text
    int nbvert, start, end;
    float proba;
    adj_list al;
    if (file == NULL)
    {
        perror("Could not open file for reading");
        exit(EXIT_FAILURE);
    }
    // first line contains number of vertices
    if (fscanf(file, "%d", &nbvert) != 1)
    {
        perror("Could not read number of vertices");
        exit(EXIT_FAILURE);
    }
    al = create_adj_list(nbvert);
    while (fscanf(file, "%d %d %f", &start, &end, &proba) == 3)
    {
        // we obtain, for each line of the file, the values
        // start, end and proba
        addCellToList(&al.lists[start - 1], end, proba);
    }
    fclose(file);
    return al;
}

int isaMarkovGraph(adj_list *g) {
    int isaMarkov = 1;
    for (int i = 0; i < g->size; i++) {
        float sum = 0;
        cell *cur = g->lists[i].head;  // ✅ correct index
        while (cur != NULL) {
            sum += cur->prob;
            cur = cur->next;
        }
        if (sum > 1.00 || sum < 0.99) {
            printf("The graph is not a Markov graph\n");
            printf("The sum of the probabilities of vertex %d is %f\n\n", i+1, sum);
            isaMarkov = 0;
        }
    }
    if (isaMarkov) {
        printf("The graph is a Markov graph\n\n");
        return 1;
    }
    return 0;
}

void free_adj_list(adj_list *g) {
    for (int i = 0; i < g->size; i++) {
        cell *cur = g->lists[i].head;
        while (cur) {
            cell *next = cur->next;
            free(cur);
            cur = next;
        }
    }
    free(g->lists);
    g->lists = NULL;
    g->size = 0;
}
void exportMermaid(const adj_list *g, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Could not open file for writing");
        return;
    }

    fprintf(file, "---\n");
    fprintf(file, "config:\n   layout: elk\n   theme: neo\n   look: neo\n---\n\n");
    fprintf(file, "flowchart LR\n");

    for (int i = 0; i < g->size; i++) {
        fprintf(file, "%s((%d))\n", getID(i + 1), i + 1);
    }
    fprintf(file, "\n");

    for (int i = 0; i < g->size; i++) {
        char fromID[10];
        strcpy(fromID, getID(i + 1));

        cell *cur = g->lists[i].head;
        while (cur) {
            char toID[10];
            strcpy(toID, getID(cur->to));

            fprintf(file, "%s -->|%.2f|%s\n", fromID, cur->prob, toID);
            cur = cur->next;
        }
    }

    fclose(file);
    printf("Mermaid file '%s' generated successfully.\n", filename);
}
