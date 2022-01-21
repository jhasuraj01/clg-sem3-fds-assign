#include <stdio.h>
#include <stdlib.h>

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

void input_matrix(int R, int C, int arr[][C])
{
    for(int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c)
        {
            scanf("%d", &arr[r][c]);
        }
    }
}

int sparse(int R, int C, int A[][C], int S[][3])
{
    int index = 0;
    for(int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c)
        {
            if(A[r][c] != 0) {
                S[index][0] = r;
                S[index][1] = c;
                S[index][2] = A[r][c];
                index += 1;
            }
        }
    }

    return index;
}

void fast_transpose(int length, int C, int S[][3], int R[][3]) {

    int* NonZeroCols = (int*)calloc(C, sizeof(int));
    int* startIndex = (int*)calloc(C, sizeof(int));

    for (int i = 0; i < length; ++i)
    {
        ++NonZeroCols[S[i][1]];
    }

    for (int c = 1; c < C; ++c)
    {
        startIndex[c] = startIndex[c - 1] + NonZeroCols[c - 1];
    }

    for (int i = 0; i < length; ++i)
    {
        int position = startIndex[S[i][1]];
        R[position][0] = S[i][1];
        R[position][1] = S[i][0];
        R[position][2] = S[i][2];
        startIndex[S[i][1]]++;
    }
}

void simple_transpose(int length, int C, int S[][3], int R[][3]) {

    int index = 0;
    for (int c = 0; c < C; ++c)
    {
        for (int r = 0; r < length; ++r)
        {
            if (S[r][1] == c)
            {
                R[index][0] = S[r][1];
                R[index][1] = S[r][0];
                R[index][2] = S[r][2];
                ++index;
            }
        }
    }
}

int sparse_sum(int A[][3], int B[][3], int R[][3], int la, int lb) {
    int a = 0, b = 0, r = 0;

    while(a < la && b < lb) {
        if(A[a][0] == B[b][0] && A[a][1] == B[b][1]) {
            R[r][0] = A[a][0];
            R[r][1] = A[a][1];
            R[r][2] = A[a][2] + B[b][2];
            ++r;
            ++a;
            ++b;
        }
        else if(A[a][0] == B[b][0]) {
            if(A[a][1] < B[b][1]) {
                R[r][0] = A[a][0];
                R[r][1] = A[a][1];
                R[r][2] = A[a][2];
                ++r;
                ++a;
            }
            else {
                R[r][0] = B[b][0];
                R[r][1] = B[b][1];
                R[r][2] = B[b][2];
                ++r;
                ++b;
            }
        }
        else {
            if(A[a][0] < B[b][0]) {
                R[r][0] = A[a][0];
                R[r][1] = A[a][1];
                R[r][2] = A[a][2];
                ++r;
                ++a;
            }
            else {
                R[r][0] = B[b][0];
                R[r][1] = B[b][1];
                R[r][2] = B[b][2];
                ++r;
                ++b;
            }
        }
    }

    while(a < la) {
        R[r][0] = A[a][0];
        R[r][1] = A[a][1];
        R[r][2] = A[a][2];
        ++r;
        ++a;
    }

    while(b < lb) {
        R[r][0] = B[b][0];
        R[r][1] = B[b][1];
        R[r][2] = B[b][2];
        ++r;
        ++b;
    }

    return r;
}

int main() {
    int r, c;

    printf("Enter no of Rows and Cols respectively: ");
    scanf("%d %d", &r, &c);

    int max_sparse_row = r*c;

    int mat1[r][c], mat2[r][c], sparse1[max_sparse_row][3], sparse2[max_sparse_row][3];

    printf("Enter First Matrix: \n");
    input_matrix(r, c, mat1);

    printf("Enter Second Matrix: \n");
    input_matrix(r, c, mat2);

    int sparse_length_1 = sparse(r, c, mat1, sparse1);
    int sparse_length_2 = sparse(r, c, mat2, sparse2);


    // Calculate Results
    int transpose1[max_sparse_row][3], transpose2[max_sparse_row][3], sum[max_sparse_row][3];

    simple_transpose(sparse_length_1, c, sparse1, transpose1);
    fast_transpose(sparse_length_2, c, sparse2, transpose2);
    int sum_length = sparse_sum(sparse1, sparse2, sum, sparse_length_1, sparse_length_2);


    // Print Sparse of a Matrix
    printf("\n\nSparse of First Matrix:\n");
    print_matrix(sparse_length_1, 3, sparse1);

    printf("\n\nSparse of Second Matrix:\n");
    print_matrix(sparse_length_2, 3, sparse2);


    // Print Transpose
    printf("\n\nSimple Transpose of First Matrix:\n");
    print_matrix(sparse_length_1, 3, transpose1);

    printf("\n\nFast Transpose of Second Matrix:\n");
    print_matrix(sparse_length_2, 3, transpose2);


    // Print Sum
    printf("\n\nSum of Sparse Matrix:\n");
    print_matrix(sum_length, 3, sum);
    
    return 0;
}