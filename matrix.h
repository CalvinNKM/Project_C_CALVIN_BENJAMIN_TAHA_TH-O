//
// Created by theok on 20/11/2025.
//

#ifndef INC_2526_TI301_PJT_MATRIX_H
#define INC_2526_TI301_PJT_MATRIX_H
#include "hasse.h"
#include <math.h>

/* STEP 1 */
// Initialize a matrix with all 0's, allocating memory for it
float ** initialize_matrix(int size);
// Create a matrix with probabilities from the adjacency list
float ** create_matrix(adj_list l);
// Display the matrix
void print_matrix(float ** m, int size);
// Free the memory associated to the matrix
void free_matrix(float ** matrix, int size);
// Copy the matrix into a second matrix (to have 2 times the same matrix)
float ** copy_matrix(float ** matrix, int size);
// Multiply matrix1 with matrix2
float ** multiply_matrix(float ** matrix1, float ** matrix2, int size);
// Find out the general difference between two matrices by comparing them term by term
float difference_matrix(float ** matrix1, float ** matrix2, int size);

/* STEP 2 */
// Calculate the matrix linked to a class in a partition
float ** subMatrix(float ** matrix, t_partition part, int compo_index);

/* STEP 3 */
// Compute gcd of an array of integers
int gcd(int *vals, int nbvals);
// Compute the period of a class from its submatrix
int getPeriod(float **sub_matrix, int n);

#endif //INC_2526_TI301_PJT_MATRIX_H