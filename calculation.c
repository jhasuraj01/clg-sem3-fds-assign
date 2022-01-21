#include<stdio.h>
#include<stdlib.h>

// Stack
struct Node {
    int data;
    struct Node* next;
};
struct Stack {
    struct Node* top;
    int size;
};
struct Node* CreateNode(int);
struct Stack* CreateStack();
void push(int, struct Stack*);
int pop(struct Stack*);
int empty(struct Stack*);
int top(struct Stack*);

// Calculator
int precedence(char);
void infixToPreFix(char [], char [], int);
void infixToPostFix(char [], char [], int);
int evalPostFix(char []);
int evalPreFix(char []);

// utils
void reverse(char [], int);
int length(char []);

int main() {
    char expression[100];
    int exit = 0;

    while (1)
    {
        printf("\n\nEnter Expression: ");
        scanf("%s", expression);
        int len = length(expression);

        char* prefix = (char*)calloc(sizeof(char), len + 1);
        char* postfix = (char*)calloc(sizeof(char), len + 1);
        
        infixToPreFix(expression, prefix, len);
        infixToPostFix(expression, postfix, len);

        printf("\nResults:");
        printf("\nPreFix:  %s = %d", prefix, evalPreFix(prefix));
        printf("\nPostFix: %s = %d", postfix, evalPostFix(postfix));

    }

    return 0;
}

struct Node* CreateNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->next = NULL;
    return node;
}

struct Stack* CreateStack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->size = 0;
    stack->top = NULL;
    return stack;
}

void push(int data, struct Stack* stack) {
    struct Node* node = CreateNode(data);
    node->next = stack->top;
    stack->top = node;
    stack->size++;
}

int pop(struct Stack* stack) {
    if(stack->size > 0) {
        int data = stack->top->data;
        stack->top = stack->top->next;
        stack->size--;
        return data;
    }
    printf("\n\n!!!ERROR: ");
    printf("No Elements to pop from stack!!!\n\n");

    return 0;
}

int empty(struct Stack* stack) {
    return (stack->size == 0);
}

int top(struct Stack* stack) {
    return stack->top->data;
}

int precedence(char symbol) {
    switch (symbol)
    {
    case '^':
        return 3;
    case '/':
    case '*':
        return 2;
    case '-':
    case '+':
        return 1;
    default:
        return 0;
    }
}

void infixToPostFix(char infix[], char postfix[], int length) {

    struct Stack* stack = CreateStack();
    int p = 0;

    for (int i = 0; i < length; ++i)
    {
        char c = infix[i];

        if(c >= '0' && c <= '9') {
            postfix[p++] = c;
        }
        else if(c == '(') {
            push('(', stack);
        }
        else if(c == ')') {
            while(!empty(stack) && top(stack) != '(')
            {
                postfix[p++] = pop(stack);
            }
            pop(stack);
        }
        else {
            while(!empty(stack) && precedence(c) <= precedence(top(stack))) {
                postfix[p++] = pop(stack);
            }
            push(c, stack);
        }
    }

    while(!empty(stack)) {
        postfix[p++] = pop(stack);
    }

}

void infixToPreFix(char infix[], char postfix[], int length) {

    struct Stack* stack = CreateStack();
    int p = 0;

    for (int i = length - 1; i >= 0; --i)
    {
        char c = infix[i];

        if(c >= '0' && c <= '9') {
            postfix[p++] = c;
        }
        else if(c == ')') {
            push(')', stack);
        }
        else if(c == '(') {
            while(!empty(stack) && top(stack) != ')')
            {
                postfix[p++] = pop(stack);
            }
            pop(stack);
        }
        else {
            while(!empty(stack) && precedence(c) <= precedence(top(stack))) {
                postfix[p++] = pop(stack);
            }
            push(c, stack);
        }
    }

    while(!empty(stack)) {
        postfix[p++] = pop(stack);
    }

    reverse(postfix, p);

}

int evalPostFix(char postfix[]) {

    struct Stack* stack = CreateStack();

    for (int i = 0; postfix[i] != '\0'; ++i) {
        char c = postfix[i];

        if(c >= '0' && c <= '9') {
            push(c - '0', stack);
        }
        else {
            int num1 = pop(stack);
            int num2 = pop(stack);

            if(c == '-') push(num2 - num1, stack);
            else if(c == '*') push(num2 * num1, stack);
            else if(c == '/') push(num2 / num1, stack);
            else if(c == '+') push(num2 + num1, stack);
        }
    }

    return pop(stack);
}

int evalPreFix(char prefix[]) {
    int len = length(prefix);
    struct Stack* stack = CreateStack();
    
    for (int i = len - 1; i >= 0; --i) {
        char c = prefix[i];

        if(c >= '0' && c <= '9') {
            push(c - '0', stack);
        }
        else {
            int num2 = pop(stack);
            int num1 = pop(stack);

            if(c == '-') push(num2 - num1, stack);
            else if(c == '*') push(num2 * num1, stack);
            else if(c == '/') push(num2 / num1, stack);
            else if(c == '+') push(num2 + num1, stack);
        }
    }

    return pop(stack);
}

void reverse(char array[], int length) {
    for(int i = 0; i < length/2; ++i) {
        char temp = array[length - i - 1];
        array[length - i - 1] = array[i];
        array[i] = temp;
    }
}

int length(char array[]) {
    int len = 0;
    while (array[len] != '\0') len++;
    return len;
}