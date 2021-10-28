#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char string[10000], N;

    printf("Input String: ");
    gets(string);

    for (int i = 0; string[i] != '\0'; i++)
    {
        char c = string[i];
        if (64 < c && c < 91)
        {
            c += 32;
        }
        else if (96 < c && c < 123)
        {
            c -= 32;
        }
        string[i] = c;
    }

    printf("\nOutput String: ");
    puts(string);

    return 0;
}