#include <stdio.h>
#include <math.h>
#define MAX 100
void printMatrix(int n, double M[MAX][MAX], const char *name) {
    printf("%s Matrix:\n", name);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%8.3f ", M[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
void dolittle(double A[MAX][MAX], int n, double L[MAX][MAX], double U[MAX][MAX]){
    for (int i = 0; i < n; i++) {
        // Compute U
        for (int k = i; k < n; k++) {
            double sum = 0;
            for (int j = 0; j < i; j++)
                sum += L[i][j] * U[j][k];
            U[i][k] = A[i][k] - sum;
        }

        // Compute L
        for (int k = i; k < n; k++) {
            if (i == k)
                L[i][i] = 1;
            else {
                double sum = 0;
                for (int j = 0; j < i; j++)
                    sum += L[k][j] * U[j][i];
                L[k][i] = (A[k][i] - sum) / U[i][i];
            }
        }
    }
    printMatrix(n, L, "L");

    printMatrix(n, U, "U");
}

int crouts(double A[MAX][MAX], int n, double L[MAX][MAX], double U[MAX][MAX]){
      // Crout's algorithm
    for (int j = 0; j < n; j++) {
        U[j][j] = 1; // Unit diagonal for U

        for (int i = j; i < n; i++) {
            double sum = 0;
            for (int k = 0; k < j; k++)
                sum += L[i][k] * U[k][j];
            L[i][j] = A[i][j] - sum;
        }

        for (int i = j + 1; i < n; i++) {
            double sum = 0;
            for (int k = 0; k < j; k++)
                sum += L[j][k] * U[k][i];
            if (L[j][j] == 0) {
                printf("Zero pivot encountered. Decomposition not possible.\n");
                return 1;
            }
            U[j][i] = (A[j][i] - sum) / L[j][j];
        }
    }

    
    printMatrix(n, L, "L");

    
    printMatrix(n, U, "U");
    return 0;
}
 int cholesky(double A[MAX][MAX], int n, double L[MAX][MAX], double U[MAX][MAX]){
    // Cholesky Decomposition
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            double sum = 0;

            for (int k = 0; k < j; k++)
                sum += L[i][k] * L[j][k];

            if (i == j) {
                double val = A[i][i] - sum;
                if (val <= 0) {
                    printf("Matrix is not positive definite.\n");
                    return 1;
                }
                L[i][j] = sqrt(val);
            } else {
                L[i][j] = (A[i][j] - sum) / L[j][j];
            }
        }
    }

    printMatrix(n, L, "L");

    
    printf("\nTranspose of L:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%6.3f ", L[j][i]);
        printf("\n");
    }
    return 0;
 }
int main() {
    int n;
    double A[MAX][MAX],  L[MAX][MAX] = {0}, U[MAX][MAX] = {0};

    printf("Enter the size of the square matrix: ");
    scanf("%d", &n);

    if (n > MAX || n <= 0) {
        printf("Invalid size. Please enter a number between 1 and %d.\n", MAX);
        return 1;
    }

    printf("Enter the matrix row-wise:\n");
    for (int i = 0; i < n; i++) {
        printf("Row %d: ", i + 1);
        for (int j = 0; j < n; j++) {
            scanf("%lf", &A[i][j]);
        }
    }
    printf("Dolittle's Algrithm\n");
    dolittle(A, n, L, U);
    printf("Crout's Algrithm\n");
    crouts(A, n, L, U);
    printf("Cholesky's Algrithm\n");
    cholesky(A, n, L, U);

    return 0;
}
