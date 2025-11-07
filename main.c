#include <stdio.h>
#include "utils.h"


#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int main(void)
{

    const char *inputFile = "/Users/calvinnkm/Downloads/NewProject_C/data/exemple1.txt";


    adj_list g = readGraph(inputFile);
    if (g.lists == NULL || g.size == 0) {
        printf("Error on reading the graph\n");
        return 1;
    }

    printf("--- Adjacence Lists ---\n");
    print_adj_list(&g);
    printf("\n--- Verification of the graph---\n");
    if (isaMarkovGraph(&g))
        printf("The graph is a Markov graph.\n");
    else
        printf("The graph is not a Markov graph.\n");

    printf("\n--- Generation of the file Mermaid ---\n");
    exportMermaid(&g, "exemple3.txt");


    free_adj_list(&g);

    return 0;
}
