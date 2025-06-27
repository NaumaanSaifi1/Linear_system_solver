#include <stdio.h>
#define MAX 10

void gaussjordan(int n, double A[MAX][MAX + 1]) {
    for (int i = 0; i < n; i++) {
        if (A[i][i] == 0.0) {
            printf("Division by zero\n");
            return;
        }

        double pivot = A[i][i];
        for (int j = 0; j <= n; j++) {
            A[i][j] /= pivot;
        }

        for (int k = 0; k < n; k++) {
            if (k != i) {
                double factor = A[k][i];
                for (int j = 0; j <= n; j++) {
                    A[k][j] -= factor * A[i][j];
                }
            }
        }
    }

    // Print solution
    printf("Solution Vector:\n");
    for (int i = 0; i < n; i++) {
        printf("x%d = %lf\n", i + 1, A[i][n]);
    }
}

int main() {
    int n;
    double A[MAX][MAX + 1];

    printf("Enter the number of variables: ");
    scanf("%d", &n);

    printf("Enter the augmented matrix (coefficients and constants):\n");
    for (int i = 0; i < n; i++) {
        printf("Row %d: ", i + 1);
        for (int j = 0; j <= n; j++) {
            scanf("%lf", &A[i][j]);
        }
    }

    gaussjordan(n, A);

    return 0;
}
