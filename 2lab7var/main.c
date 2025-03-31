#include <stdio.h>
#include "fn_set.h"

int main() {
    int n;
    printf("Enter the size of the chessboard (N x N): ");
    scanf("%d", &n);

    solve_n_bishops(n);

    return 0;
}