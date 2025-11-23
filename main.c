#include <stdio.h>
#include "utils.h"
#include "hasse.h"
#include "matrix.h"

int main(void)
{

    const char *inputFile = "../data/exemple_valid_step3.txt";

    printf("=== PART 1 ===\n");
    adj_list g = readGraph(inputFile);
    if (g.lists == NULL || g.size == 0) {
        printf("Error on reading the graph\n");
        return 1;
    }

    printf("--- Adjacency Lists ---\n");
    print_adj_list(&g);
    isaMarkovGraph(&g);

    printf("--- Generation of the file Mermaid ---\n");
    exportMermaid(&g, "mermaid_graph.txt");

    printf("\n=== PART 2 ===\n");

    t_partition p = tarjan(g);
    printf("The graph contains the following classes:\n");
    for (int i=0; i<p.size; i++) {
        printf("\n%s: { ", p.lists[i].name);
        for (int j=0; j<p.lists[i].size; j++)
            printf("%d ", p.lists[i].list[j]->identifier+1);
        printf("}");
    }

    printf("\n\n--- Links betweens classes ---\n");

    t_link_array links = createLinkArray(p, g);

    exportHasse(p, links, "mermaid_hasse.txt");

    printf("\n\n--- Properties of the classes ---\n");
    computeClassProperties(p, links);

    float ** matrix = create_matrix(g);
    print_matrix(matrix, g.size);
    free_matrix(matrix,g.size);

    free_adj_list(&g);
    return 0;

}
