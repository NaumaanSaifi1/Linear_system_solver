#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 10

// Swap two rows in the augmented matrix
void swapRows(double A[MAX][MAX + 1], int row1, int row2, int n) {
    for (int i = 0; i <= n; i++) {
        float temp = A[row1][i];
        A[row1][i] = A[row2][i];
        A[row2][i] = temp;
    }
}

// Swap two columns in the augmented matrix
void swapCols(double A[MAX][MAX + 1], int col1, int col2, int n) {
    for (int i = 0; i < n; i++) {
        float temp = A[i][col1];
        A[i][col1] = A[i][col2];
        A[i][col2] = temp;
    }
}

void gaussEliminationCompletePivoting(int n, double A[MAX][MAX + 1]) {
    float x[MAX];
    int varIndex[MAX];  // To store the original variable indices
    for (int i = 0; i < n; i++) varIndex[i] = i;

    // Forward Elimination with Complete Pivoting
    for (int i = 0; i < n - 1; i++) {  // we dont need last row element as pivot
        int maxRow = i, maxCol = i;
        float maxVal = fabs(A[i][i]);

        // Find the maximum element in the submatrix
        for (int r = i; r < n; r++) {
            for (int c = i; c < n; c++) {
                if (fabs(A[r][c]) > maxVal) {
                    maxVal = fabs(A[r][c]);
                    maxRow = r;
                    maxCol = c;
                }
            }
        }

        if (maxVal == 0.0) {
            printf("Mathematical Error: Singular matrix detected\n");
            return;
        }

        // Swap rows
        if (maxRow != i) swapRows(A, i, maxRow, n);

        // Swap columns and update variable index tracking
        if (maxCol != i) {
            swapCols(A, i, maxCol, n);
            int temp = varIndex[i];
            varIndex[i] = varIndex[maxCol];
            varIndex[maxCol] = temp;
        }

        // Elimination
        for (int j = i + 1; j < n; j++) {
            float ratio = A[j][i] / A[i][i];
            for (int k = i; k <= n; k++) {
                A[j][k] -= ratio * A[i][k];
            }
        }
    }

    // Back Substitution
    for (int i = n - 1; i >= 0; i--) {
        x[i] = A[i][n];
        for (int j = i + 1; j < n; j++) {
            x[i] -= A[i][j] * x[j];
        }
        x[i] /= A[i][i];
    }

    // Output the solution in original variable order
    float finalSol[MAX];
    for (int i = 0; i < n; i++) {
        finalSol[varIndex[i]] = x[i];
    }

    printf("Solution Vector (after Complete Pivoting):\n");
    for (int i = 0; i < n; i++) {
        printf("x%d = %lf\n", i + 1, finalSol[i]);
    }
    printf("\n");
}

int main() {
    int n;
    double A[MAX][MAX + 1];

    printf("Enter number of variables (max %d): ", MAX);
    scanf("%d", &n);
    if (n < 1) {
        printf("Invalid number of variables.\n");
        return 1;
    }

    printf("Enter the augmented matrix (%d rows with %d elements each):\n", n, n + 1);
    for (int i = 0; i < n; i++) {
        printf("Row %d: ", i + 1);
        for (int j = 0; j <= n; j++) {
            scanf("%lf", &A[i][j]);
        }
    }

    gaussEliminationCompletePivoting(n, A);

    return 0;
}
