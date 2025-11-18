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
        printf("\n%s:", p.lists[i].name);
        for (int j=0; j<p.lists[i].size; j++)
            printf("%d-:", p.lists[i].list[j]->identifier+1);
    }

    printf("\n\n Links betweens classes \n");

    t_link_array links = createLinkArray(p, g);

    for (int i = 0; i < links.log_size; i++) {
        int from = links.links[i].from;
        int to   = links.links[i].to;

        printf("%s -> %s\n", p.lists[from].name, p.lists[to].name);
    }

    computeClassProperties(p, links);
    free_adj_list(&g);

    return 0;

}
