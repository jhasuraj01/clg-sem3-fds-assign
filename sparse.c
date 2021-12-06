#include <stdio.h>

int main() {
    int arr[50][50];
    int R, C;

    printf("Enter number of rows and columns: ");
    scanf("%d %d", &R, &C);

    printf("Enter Matrix:\n");

    for(int i =0; i < R; ++i) {
        for (int j = 0; j < C; ++j)
        {
            scanf("%d", &arr[i][j]);
        }
    }

    int k = 0;
    for(int i =0; i < R; ++i) {
        for (int j = 0; j < C; ++j)
        {
            if(arr[i][j] != 0) ++k;
        }
    }

    int S[3][2500], index = 0;

    for(int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c)
        {
            if(arr[r][c] != 0) {
                S[0][index] = r;
                S[1][index] = c;
                S[2][index] = arr[r][c];

                index += 1;
            }
        }
    }

    printf("\nSparse Matrix: \n");
    for(int r = 0; r < 3; ++r) {
        for (int c = 0; c < index; ++c)
        {
            printf("%d ", S[r][c]);
        }
        printf("\n");
    }

    return 0;
}