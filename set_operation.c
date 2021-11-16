#include <stdio.h>

int union_set(int A[], int B[], int C[], int a, int b);
int intersection_set(int A[], int B[], int C[], int a, int b);
int difference_set(int A[], int B[], int C[], int a, int b);
int symmetric_set(int A[], int B[], int C[], int a, int b);
int input_set(int A[], char name);
void output_set(int A[], int n);

int main()
{
    int A[100], B[100], C[200], a, b, c;
    int ch;

    printf("#Menu\n");
    printf("1. Union\n");
    printf("2. Intersection\n");
    printf("3. Difference\n");
    printf("4. Symmetric\n");
    printf("Enter the Choice: \n");
    scanf("%d", &ch);

    a = input_set(A, 'A');
    b = input_set(B, 'B');

    switch (ch)
    {
    case 1:
        c = union_set(A, B, C, a, b);
        output_set(C, c);
        break;

    case 2:
        c = intersection_set(A, B, C, a, b);
        output_set(C, c);
        break;
    case 3:
        c = difference_set(A, B, C, a, b);
        output_set(C, c);
        break;

    case 4:
        c = symmetric_set(A, B, C, a, b);
        output_set(C, c);
        break;

    default:
        printf("Wrong Input!");
        break;
    }
    return 0;
}

int union_set(int A[], int B[], int C[], int a, int b) {

    // all the elements of A which are not in B
    int c = difference_set(A, B, C, a, b);

    // insert the elements of B
    for (int j = 0; j < b; ++j)
    {
        C[c++] = B[j];
    }

    return c;
}

int intersection_set(int A[], int B[], int C[], int a, int b) {
    int AmB[100];

    int amb = difference_set(A, B, AmB, a, b);
    int c = difference_set(A, AmB, C, a, amb);

    return c;
}

int difference_set(int A[], int B[], int C[], int a, int b) {
    int c = 0;
    for (int i = 0; i < a; ++i)
    {
        int insert = 1;
        for (int j = 0; j < b; ++j)
        {
            if (A[i] == B[j])
            {
                insert = 0;
                break;
            }
        }

        if (insert)
        {
            C[c++] = A[i];
        }
        
    }
    return c;
}

int symmetric_set(int A[], int B[], int C[], int a, int b) {

    int AuB[20], aub;
    aub = union_set(A, B, AuB, a, b);

    int AnB[10], anb;
    anb = intersection_set(A, B, AnB, a, b);

    int c = difference_set(AuB, AnB, C, aub, anb);

    return c;
}

int input_set(int A[], char name) {
    int a;
    printf("Enter no. of elements in Set %c: ", name);
    scanf("%d", &a);

    printf("Enter the elements of Set %c: ", name);
    for (int i = 0; i < a; i++)
    {
        scanf("%d", &A[i]);
    }
    
    return a;
}

void output_set(int A[], int n) {

    printf("Result: { ");

    for (int i = 0; i < n-1; i++)
    {
        printf("%d, ", A[i]);
    }

    if (n > 0)
    {
        printf("%d }", A[n-1]);
    }
}