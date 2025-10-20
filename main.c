#include <stdio.h>
#include "utils.h"


int main() {
    adj_list myAdjList = readGraph("../data/exemple1.txt");
    print_adj_list(&myAdjList);
    isaMarkovGraph(&myAdjList);

    adj_list myAdjList2 = readGraph("../data/exemple1_false.txt");
    print_adj_list(&myAdjList2);
    isaMarkovGraph(&myAdjList2);
    return 0;
}
