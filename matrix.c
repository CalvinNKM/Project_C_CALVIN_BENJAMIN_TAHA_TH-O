//
// Created by theok on 20/11/2025.
//

#include "matrix.h"

float ** initialize_matrix(int size) {
    float ** matrix = (float **)malloc(size * sizeof(float *));
    for (int i=0; i<size; i++) {
        matrix[i] = (float *)malloc(size * sizeof(float));
        for (int j=0; j<size; j++) {
            matrix[i][j] = 0.0f;
        }
    } return matrix;
}

float ** create_matrix(adj_list l) {
    float ** matrix = initialize_matrix(l.size);
    for (int i=0; i<l.size; i++) {
        const cell *cur = l.lists[i].head;
        while (cur){
            matrix[i][cur->to-1] = cur->prob;
            cur = cur->next;
        }
    }return matrix;
}

void print_matrix(float ** m, int size) {
    printf("--- Matrix (%d x %d) ---\n", size, size); // Header for clarity
    for (int i = 0; i < size; i++) {
        printf("|"); // Start row indicator
        for (int j = 0; j < size; j++) {
            printf(" %.2f ", m[i][j]);
        }
        printf("|\n"); // End row indicator and new line
    }
    printf("------------------------\n");
}

void free_matrix(float ** matrix, int size) {
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

float ** copy_matrix(float ** matrix, int size) {
    float ** copy = (float **)malloc(size * sizeof(float *));
    for (int i=0; i<size; i++) {
        copy[i] = (float *)malloc(size * sizeof(float));
        for (int j=0; j<size; j++) {
            copy[i][j] = matrix[i][j];
        }
    }return copy;
}

float ** multiply_matrix(float ** matrix1, float ** matrix2, int size) {
    float ** result = initialize_matrix(size);
    for (int i=0; i<size; i++) {
        for (int j=0; j<size; j++) {
            for (int k=0; k<size; k++) {
                result[j][i] += matrix1[j][k] * matrix2[k][i];
            }
        }
    }return result;
}

float difference_matrix(float ** matrix1, float ** matrix2, int size) {
    float result = 0.0f;
    for (int i=0; i<size; i++) {
        for (int j=0; j<size; j++) {
            result += fabs(matrix1[i][j] - matrix2[i][j]);
        }
    } return result;
}