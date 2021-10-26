#include <stdio.h>

int main() {
    int a, b, N[100000] = {0};
    printf("Input 2 Numbers: ");
    scanf("%d %d", &a, &b);

    N[0] = 1;
    N[1] = 1;

    for (int n = 2; n <= b; n++)
    {
        for (int j = n*2; j <= b; j += n)
        {
            N[j] = 1;
        }
    }

    for (int n = a; n <= b; n++)
    {
        if (N[n] == 0)
        {
            printf("%d ", n);
        }
    }
    return 0;
}