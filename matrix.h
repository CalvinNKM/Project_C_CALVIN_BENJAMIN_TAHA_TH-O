//
// Created by theok on 20/11/2025.
//

#ifndef INC_2526_TI301_PJT_MATRIX_H
#define INC_2526_TI301_PJT_MATRIX_H
#include "hasse.h"
#include <math.h>

/* STEP 1 */
float ** initialize_matrix(int size); // Initialize a matrix with all 0's, allocating memory for it
float ** create_matrix(adj_list l); // Create a matrix with probabilities from the adjacency list
void print_matrix(float ** m, int size); // Display the matrix
void free_matrix(float ** matrix, int size); // Free the memory associated to the matrix
float ** copy_matrix(float ** matrix, int size); // Copy the matrix into a second matrix (to have 2 times the same matrix)
float ** multiply_matrix(float ** matrix1, float ** matrix2, int size); // Multiply matrix1 with matrix2
float difference_matrix(float ** matrix1, float ** matrix2, int size); // Find out the general difference between two matrices by comparing them term by term

/* STEP 2 */
float ** subMatrix(float ** matrix, t_partition part, int compo_index); // Calculate the matrix linked to a class in a partition

/* STEP 3 */
int gcd(int *vals, int nbvals); // Compute gcd of an array of integers
int getPeriod(float **sub_matrix, int n); // Compute the period of a class from its submatrix

#endif //INC_2526_TI301_PJT_MATRIX_H