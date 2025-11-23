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
    free_adj_list(&g);


    printf("\n=== PART 3 ===\n");
    const char *inputFile2 = "../data/exemple_meteo.txt";
    adj_list g2 = readGraph(inputFile2);

    printf("\nHere is the matrix M:\n");
    float ** matrix = create_matrix(g2);
    float ** matrix2 = copy_matrix(matrix, g2.size);
    print_matrix(matrix2, g2.size);

    for (int i=0; i<2; i++) {
        matrix2 = multiply_matrix(matrix2,matrix,g2.size);
    }
    printf("\nHere is the matrix M^3:\n");
    print_matrix(matrix2, g2.size);

    for (int i=0; i<4; i++) {
        matrix2 = multiply_matrix(matrix2,matrix,g2.size);
    }
    printf("\nHere is the matrix M^7:\n");
    print_matrix(matrix2, g2.size);

    matrix2 = copy_matrix(matrix, g2.size);
    float ** matrix_temp = initialize_matrix(g2.size);
    int number = 1;
    do {
        matrix_temp = matrix2;
        matrix2 = multiply_matrix(matrix2,matrix,g2.size);
        number++;
    } while (difference_matrix(matrix_temp, matrix2, g2.size) >= 0.01 && number < 100);
    if (number < 100) {
        printf("\nThis is the M^n where the difference between the precedent is smaller than 0.01: %d .\n"
               "The difference is of %f\n",number,difference_matrix(matrix_temp, matrix2, g2.size));
    }else printf("\nAfter 100 iterations, the difference is still not of 0.01 (difference of %f), so it will probably never be.\n",difference_matrix(matrix_temp, matrix2, g2.size));

    free_matrix(matrix,g2.size);
    free_matrix(matrix2,g2.size);
    free_adj_list(&g2);


    const char *inputFile3 = "../data/exemple_hasse1.txt";
    adj_list g3 = readGraph(inputFile3);

    t_partition p3 = tarjan(g3);
    printf("\nThe graph contains the following classes:");
    for (int i=0; i<p3.size; i++) {
        printf("\n%s: { ", p3.lists[i].name);
        for (int j=0; j<p3.lists[i].size; j++)
            printf("%d ", p3.lists[i].list[j]->identifier+1);
        printf("}");
    }

    printf("\n\nLet's concentrate on class C1:\n");
    float ** matrix3 = create_matrix(g3);
    float ** submatrix = subMatrix(matrix3, p3, 0);
    print_matrix(submatrix, p3.lists[0].size);

    free_matrix(matrix3,g3.size);
    free_matrix(submatrix,g2.size);
    free_adj_list(&g3);

    const char *inputFile4 = "../data/exemple_period.txt";
    adj_list g4 = readGraph(inputFile4);
    t_partition p4 = tarjan(g4);
    printf("\nThe graph contains the following classes:");
    for (int i=0; i<p4.size; i++) {
        printf("\n%s: { ", p4.lists[i].name);
        for (int j=0; j<p4.lists[i].size; j++)
            printf("%d ", p4.lists[i].list[j]->identifier+1);
        printf("}");
    }
    float ** matrix4 = create_matrix(g4);
    float ** submatrix2 = subMatrix(matrix4, p4, 0);
    printf("\nLet's calculate the period of class C1: %d\n",getPeriod(submatrix2,p4.lists[0].size));

    free_matrix(matrix4,g4.size);
    free_matrix(submatrix2,g4.size);
    free_adj_list(&g4);

    return 0;

}
