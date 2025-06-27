#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 10

void swapRows(double A[MAX][MAX + 1], int row1, int row2, int n) {
    for (int i = 0; i <= n; i++) {
        float temp = A[row1][i];
        A[row1][i] = A[row2][i];
        A[row2][i] = temp;
    }
}

void gaussElimination(int n, double A[MAX][MAX + 1]) {
    float x[MAX];
    int i, j, k, maxRow;
    float ratio, maxVal;
    // Forward Elimination with Partial Pivoting
    for (i = 0; i < n - 1; i++) {
        // Partial Pivoting
        maxRow = i;
        maxVal = fabs(A[i][i]);
        for (k = i + 1; k < n; k++) {
            if (fabs(A[k][i]) > maxVal) {
                maxVal = fabs(A[k][i]);
                maxRow = k;
            }
        }

        if (maxVal == 0.0) {
            printf("Mathematical Error: Zero column encountered\n");
            return;
        }

        // Swap the rows
        if (maxRow != i) {
            swapRows(A, i, maxRow, n);
        }

        // Elimination
        for (j = i + 1; j < n; j++) {
            ratio = A[j][i] / A[i][i];
            for (k = i; k <= n; k++) {
                A[j][k] -= ratio * A[i][k];
            }
        }
    }

    // Back Substitution
    x[n - 1] = A[n - 1][n] / A[n - 1][n - 1];
    for (i = n - 2; i >= 0; i--) {
        x[i] = A[i][n];
        for (j = i + 1; j < n; j++) {
            x[i] -= A[i][j] * x[j];
        }
        x[i] /= A[i][i];
    }

    // Output the solution
    printf("Solution Vector:\n");
    for (i = 0; i < n; i++) {
        printf("x%d = %.3f\n", i + 1, x[i]);
    }
    printf("\n");
}

int main() {
    int n, i, j;
    double A[MAX][MAX + 1];

    printf("Enter the number of variables: ", MAX);
    scanf("%d", &n);

    if (n < 1 || n > MAX) {
        printf("Invalid number of variables.\n");
        return 1;
    }

    printf("Enter the augmented matrix (each row of %d coefficients including RHS):\n", n + 1);
    for (i = 0; i < n; i++) {
        printf("Row %d: ", i + 1);
        for (j = 0; j <= n; j++) {
            scanf("%lf", &A[i][j]);
        }
    }

    printf("\nSolving the system using Gauss Elimination with Partial Pivoting:\n");
    gaussElimination(n, A);

    return 0;
}
