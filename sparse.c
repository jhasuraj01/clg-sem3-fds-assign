#include <stdio.h>

void print_matrix(int R, int C, int arr[][C])
{
    for(int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c)
        {
            printf("%-3d ", arr[r][c]);
        }
        printf("\n");
    }
}

int main() {
    int A[50][50], B[50][50];
    int ra, ca, rb, cb;

    printf("Enter number of rows and columns of first matrix: ");
    scanf("%d %d", &ra, &ca);

    printf("Enter First Matrix:\n");

    for(int i =0; i < ra; ++i) {
        for (int j = 0; j < ca; ++j)
        {
            scanf("%d", &A[i][j]);
        }
    }

    printf("\nEnter number of rows and columns of second matrix: ");
    scanf("%d %d", &rb, &cb);

    printf("Enter Second Matrix:\n");

    for(int i =0; i < rb; ++i) {
        for (int j = 0; j < cb; ++j)
        {
            scanf("%d", &B[i][j]);
        }
    }


    int SA[3][2500], SB[3][2500], Ai = 0, Bi = 0;

    for(int r = 0; r < ra; ++r) {
        for (int c = 0; c < ca; ++c)
        {
            if(A[r][c] != 0) {
                SA[0][Ai] = r;
                SA[1][Ai] = c;
                SA[2][Ai] = A[r][c];

                Ai += 1;
            }
        }
    }

    for(int r = 0; r < rb; ++r) {
        for (int c = 0; c < cb; ++c)
        {
            if(B[r][c] != 0) {
                SB[0][Bi] = r;
                SB[1][Bi] = c;
                SB[2][Bi] = B[r][c];

                Bi += 1;
            }
        }
    }

    printf("\nFirst Sparse Matrix: \n");
    print_matrix(3, Ai, SA);

    printf("\nSecond Sparse Matrix: \n");
    print_matrix(3, Bi, SB);


    int a = 0, b = 0, sum_index = 0;
    int SSUM[3][2500];
    while (a < Ai || b < Bi)
    {
        if(SA[0][a] != SB[0][b]) {
            if(SA[0][a] < SB[0][b]) {
                SSUM[0][sum_index] = SA[0][a];
                SSUM[1][sum_index] = SA[1][a];
                SSUM[2][sum_index] = SA[2][a];
                ++a;
            }
            else {
                SSUM[0][sum_index] = SB[0][b];
                SSUM[1][sum_index] = SB[1][b];
                SSUM[2][sum_index] = SB[2][b];
                ++b;
            }
        }
        else if(SA[1][a] != SB[1][b]) {
            if(SA[1][a] < SB[1][b]) {
                SSUM[0][sum_index] = SA[0][a];
                SSUM[1][sum_index] = SA[1][a];
                SSUM[2][sum_index] = SA[2][a];
                ++a;
            }
            else {
                SSUM[0][sum_index] = SB[0][b];
                SSUM[1][sum_index] = SB[1][b];
                SSUM[2][sum_index] = SB[2][b];
                ++b;
            }
        }
        else {
            SSUM[0][sum_index] = SA[0][a];
            SSUM[1][sum_index] = SA[1][a];
            SSUM[2][sum_index] = SA[2][a] + SB[2][b];
            ++a;
            ++b;
        }
        ++sum_index;
    }
    
    
    printf("\nSUM: \n");
    for(int r = 0; r < 3; ++r) {
        for (int c = 0; c < sum_index; ++c)
        {
            printf("%-3d ", SSUM[r][c]);
        }
        printf("\n");
    }

    return 0;
}