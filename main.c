#include <stdio.h>
#include "utils.h"


int main() {
    adj_list myAdjList = readGraph("../data/exemple1.txt");
    print_adj_list(&myAdjList);
    return 0;
}
