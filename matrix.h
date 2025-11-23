//
// Created by theok on 20/11/2025.
//

#ifndef INC_2526_TI301_PJT_MATRIX_H
#define INC_2526_TI301_PJT_MATRIX_H
#include "hasse.h"
#include <math.h>

float ** initialize_matrix(int size);
float ** create_matrix(adj_list l);
void print_matrix(float ** m, int size);
void free_matrix(float ** matrix, int size);
float ** copy_matrix(float ** matrix, int size);
float ** multiply_matrix(float ** matrix1, float ** matrix2, int size);
float difference_matrix(float ** matrix1, float ** matrix2, int size);

float ** subMatrix(float ** matrix, t_partition part, int compo_index);

int gcd(int *vals, int nbvals);
void copy_square_matrix(float **dest, float **src, int n);
void multiply_square_matrix(float **A, float **B, float **result, int n);
int getPeriod(float **sub_matrix, int n);
int gcd(int *vals, int nbvals);
int getPeriod(float **sub_matrix, int n);

#endif //INC_2526_TI301_PJT_MATRIX_H