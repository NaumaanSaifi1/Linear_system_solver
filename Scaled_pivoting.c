#include <stdio.h>
#include <math.h>
#define MAX 10

void swapRows(double A[MAX][MAX+1], int row1, int row2, int n) {
    for (int i = 0; i <= n; i++) {
        double temp = A[row1][i];
        A[row1][i] = A[row2][i];
        A[row2][i] = temp;
    }
}

int selectPivotRow(double A[MAX][MAX+1], double scale[MAX], int k, int n) {
    int maxrow = k;
    double maxratio = 0.0;
    for (int i = k; i < n; i++) {
        double ratio = fabs(A[i][k]) / scale[i];
        if (ratio > maxratio) {
            maxratio = ratio;
            maxrow = i;
        }
    }
    return maxrow;
}

void gaussElimination(int n, double A[MAX][MAX+1]) {
    double x[MAX];
    double scale[MAX];

    // Compute scale factors
    for (int i = 0; i < n; i++) {
        scale[i] = fabs(A[i][0]);
        for (int j = 1; j < n; j++) {
            if (fabs(A[i][j]) > scale[i]) {
                scale[i] = fabs(A[i][j]);
            }
        }
    }

    // Forward Elimination with scaled partial pivoting
    for (int k = 0; k < n - 1; k++) {
        int pivotRow = selectPivotRow(A, scale, k, n);
        if (pivotRow != k) {
            swapRows(A, k, pivotRow, n);
            double temp = scale[k];
            scale[k] = scale[pivotRow];
            scale[pivotRow] = temp;
        }

        for (int i = k + 1; i < n; i++) {
            if (A[k][k] == 0.0) {
                printf("Division by zero error.\n");
                return;
            }
            float ratio = A[i][k] / A[k][k];
            for (int j = k; j <= n; j++) {
                A[i][j] -= ratio * A[k][j];
            }
        }
    }

    // Back Substitution
    x[n - 1] = A[n - 1][n] / A[n - 1][n - 1];
    for (int i = n - 2; i >= 0; i--) {
        x[i] = A[i][n];
        for (int j = i + 1; j < n; j++) {
            x[i] -= A[i][j] * x[j];
        }
        x[i] /= A[i][i];
    }

    // Print solution
    printf("Solution Vector:\n");
    for (int i = 0; i < n; i++) {
        printf("x%d = %lf\n", i + 1, x[i]);
    }
    printf("\n");
}

int main() {
    int n;
    double A[MAX][MAX+1];

    printf("Enter the number of variables: ");
    scanf("%d", &n);

    printf("Enter the augmented matrix (coefficients and constants):\n");
    for (int i = 0; i < n; i++) {
        printf("Row %d: ", i + 1);
        for (int j = 0; j <= n; j++) {
            scanf("%lf", &A[i][j]);
        }
    }

    gaussElimination(n, A);

    return 0;
}
