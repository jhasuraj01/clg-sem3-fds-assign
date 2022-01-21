#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char data[20];
    struct Node* next;
    struct Node* previous;
};

struct Node* new_node(char data[]) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    strcpy(node->data, data);
    node->next = NULL;
    node->previous = NULL;
    return node;
}

struct Database {
    struct Node* head;
    struct Node* tail;
    int size;
};

void insert(char data[], struct Database* database) {
    struct Node* node = new_node(data);
    if(database->size == 0) {
        database->head = node;
        database->tail = node;
    }
    else {
        node->previous = database->tail;
        database->tail->next = node;
        database->tail = node;
    }
    database->size++;
}

int modify(int index, char data[], struct Database* database) {
    struct Node* node = database->head;

    while (--index > 0)
    {
        node = node->next;
    }

    if(node) {
        strcpy(node->data, data);
        return 1;
    }

    return 0;
}


int delete(char data[], struct Database* database) {
    struct Node* node = database->head;

    while(node) {
        if(strcmp(node->data, data) == 0) {
            if(node->previous) {
                node->previous->next = node->next;
                if(node->next) {
                    node->next->previous = node->previous;
                }
                else {
                    database->tail = node->previous;
                }
            }
            else {
                database->head = node->next;
                if(node->next) {
                    node->next->previous = NULL;
                }
                else {
                    database->tail = NULL;
                }
            }
            database->size--;
            return 1;
        }
        node = node->next;
    }

    return 0;
}

void printForward(struct Database* database) {
    struct Node* node = database->head;
    int counter = 1;
    while(node){
        printf("%d.\t%s\n", counter++, node->data);
        node = node->next;
    }
}

void printBackward(struct Database* database) {
    struct Node* node = database->tail;
    int counter = 1;
    while(node){
        printf("%d.\t%s\n", counter++, node->data);
        node = node->previous;
    }
}



int main() {
    int print_menu();
    struct Database database;

    // initialize a club;
    database.size = 0;
    database.head = NULL;
    database.tail = NULL;

    char data[20];
    int exit = 0, index, counter;

    do
    {
        int option = print_menu();
        switch (option)
        {
        case 1: // Insert
            printf("\n\nEnter no. of Records to Insert: ");
            scanf("%d", &counter);
            while(counter--) {
                printf("\nEnter Record to Insert: ");
                scanf("%s", data);
                insert(data, &database);
                printf("\n%s Added Sucessfully!\n", data);
            }
            break;

        case 2: // Delete
            printf("\n\nEnter no. of Records to Delete: ");
            scanf("%d", &counter);
            while (counter--)
            {
                printf("\nEnter Record to Delete: ");
                scanf("%s", data);

                if(delete(data, &database))
                    printf("\n%s Deleted Sucessfully!\n", data);
                else
                    printf("\nCan't Delete: %s\n", data);
            }
            break;

        case 3: // Modify
            printf("\n\nEnter Record Index: ");
            scanf("%d", &index);
            printf("\n\nEnter New Record: ");
            scanf("%s", data);
            
            if(modify(index, data, &database))
                printf("\n%s Modified Sucessfully!\n", data);
            else
                printf("\nCan't Modify: %s\n", data);

            break;

        case 4: // Print Forward
            printForward(&database);
            break;

        case 5: // Print Backward
            printBackward(&database);
            break;

        default:
            exit = 1;
            break;
        }
    } while (exit == 0);

    return 0;
}

int print_menu() {
    printf("\n**Menu**\n");
    printf("1. Insert\n");
    printf("2. Delete\n");
    printf("3. Modify\n");
    printf("4. Print Forward\n");
    printf("5. Print Backward\n");
    printf("6. Exit\n");
    printf("\nSelect an Option: ");

    int option;
    scanf("%d", &option);

    return option;
}