// Simple Calculator
#include <stdio.h>

int main()
{
    float num1, num2;
    char sign;

    printf("Enter Expression: ");
    scanf("%f %c %f", &num1, &sign, &num2);

    switch (sign)
    {
    case '+':
        printf("Sum = %f", num1 + num2);
        break;
    case '-':
        printf("Difference = %f", num1 - num2);
        break;
    case '*':
        printf("Product = %f", num1 * num2);
        break;
    case '/':
        printf("Division = %f", num1 / num2);
        break;
    default:
        printf("Invalid Expression");
    }
    return 0;
}