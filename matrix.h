//
// Created by theok on 20/11/2025.
//

#ifndef INC_2526_TI301_PJT_MATRIX_H
#define INC_2526_TI301_PJT_MATRIX_H
#include "hasse.h"
#include <stdio.h>


float ** initialize_matrix(int size);
float ** create_matrix(adj_list l);
void print_matrix(float ** m, int size);
void free_matrix(float ** matrix, int size);



#endif //INC_2526_TI301_PJT_MATRIX_H