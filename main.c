#include <stdio.h>
#include "utils.h"


#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int main(void)
{

    const char *inputFile = "../data/exemple_valid_step3.txt";


    adj_list g = readGraph(inputFile);
    if (g.lists == NULL || g.size == 0) {
        printf("Error on reading the graph\n");
        return 1;
    }

    printf("--- Adjacence Lists ---\n");
    print_adj_list(&g);
    isaMarkovGraph(&g);

    printf("\n--- Generation of the file Mermaid ---\n");
    exportMermaid(&g, "mermaid_output.txt");


    free_adj_list(&g);

    return 0;
}
