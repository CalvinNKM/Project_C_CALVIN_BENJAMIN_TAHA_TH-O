#include <stdio.h>
#include "utils.h"
#include "hasse.h"


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

    t_partition p = tarjan(g);

    for (int i=0; i<p.size; i++) {
        printf("\n%s: { ", p.lists[i].name);
        for (int j=0; j<p.lists[i].size; j++)
            printf("%d ", p.lists[i].list[j]->identifier+1);
        printf("}");
    }

    printf("\n\n Links betweens classes \n");

    t_link_array links = createLinkArray(p, g);

    exportHasse(p, links, "hasse_export.txt");

    printf("\n\n=== STEP 3 : Properties of the classes ===\n");
    computeClassProperties(p, links);
    free_adj_list(&g);

    return 0;

}
