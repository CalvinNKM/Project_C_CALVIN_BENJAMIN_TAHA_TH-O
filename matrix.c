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
    for (int i = 0; i < size; i++) {
        printf("|"); // Start row indicator
        for (int j = 0; j < size; j++) {
            printf(" %.2f ", m[i][j]);
        }
        printf("|\n"); // End row indicator and new line
    }
    for (int i = 0; i < size; i++) {
        printf("-------");
    }printf("\n");
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

float ** subMatrix(float ** matrix, t_partition part, int compo_index) {
    float ** submatrix = initialize_matrix(part.lists[compo_index].size);
    for (int i=0; i<part.lists[compo_index].size; i++) {
        for (int j=0; j<part.lists[compo_index].size; j++) {
            submatrix[i][j] = matrix[part.lists[compo_index].list[i]->identifier][part.lists[compo_index].list[j]->identifier];
        }
    }return submatrix;
}


int gcd(int *vals, int nbvals) {
    // If there are no values, return 0
    if (nbvals == 0) return 0;

    int result = vals[0];
    int i;

    // Euclid algorithm on all values
    for (i = 1; i < nbvals; i++) {
        int a = result;
        int b = vals[i];

        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }

        result = a;
    }

    return result;
}

int getPeriod(float **sub_matrix, int n) {
    // periods[] stores all c values where the diagonal is > 0
    int *periods = (int *)malloc(n * sizeof(int));
    int period_count = 0;

    // power_matrix will store M^c, starting from M^1 = sub_matrix
    float **power_matrix = copy_matrix(sub_matrix, n);

    int cpt, i;

    // Compute M^1, M^2, ..., M^n
    for (cpt = 1; cpt <= n; cpt++) {
        int diag_nonzero = 0;

        // Check if some diagonal entry of M^cpt is > 0
        for (i = 0; i < n; i++) {
            if (power_matrix[i][i] > 0.0f) {
                diag_nonzero = 1;
            }
        }

        // If diagonal has a positive value, store the current power cpt
        if (diag_nonzero) {
            periods[period_count] = cpt;
            period_count++;
        }

        // No need to compute the next power after the last iteration
        if (cpt < n) {
            // Compute next power: M^(cpt+1) = M^cpt * M
            float **next_power = multiply_matrix(power_matrix, sub_matrix, n);

            // Free the old power matrix and replace it
            free_matrix(power_matrix, n);
            power_matrix = next_power;
        }
    }

    // Compute gcd of all recorded periods
    int period = gcd(periods, period_count);

    // Free allocated memory
    free(periods);
    free_matrix(power_matrix, n);

    return period;
}
