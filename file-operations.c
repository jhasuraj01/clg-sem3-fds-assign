#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StudentNode {
    struct StudentNode* next;
    char name[20];
    int roll;
    char div[10];
    char address[20];
};

struct Student {
    char name[20];
    int roll;
    char div[10];
    char address[20];
};

struct StudentNode* new_student(struct Student student) {
    struct StudentNode* student_node = (struct StudentNode*)malloc(sizeof(struct StudentNode));
    student_node->roll = student.roll;
    strcpy(student_node->name, student.name);
    strcpy(student_node->div, student.div);
    strcpy(student_node->address, student.address);
    student_node->next = NULL;
    return student_node;
}

struct List {
    struct StudentNode* head;
    struct StudentNode* tail;
    int size;
};

void append(struct Student student, struct List* list) {
    struct StudentNode* student_node = new_student(student);

    if(list->tail == NULL) {
        list->head = student_node;
        list->tail = student_node;
    }
    else {
        list->tail->next = student_node;
        list->tail = student_node;
    }
    list->size++;
}

int delete(char name[], struct List* list) {
    struct StudentNode* node = list->head;

    // head
    if(node && strcmp(node->name, name) == 0) {
        list->head = node->next;
        if(list->head == NULL) {
            list->tail = NULL;
        }
        free(node);
        return 1;
    }

    while(node && node->next) {
        if(strcmp(node->next->name, name) == 0) {
            node->next = node->next->next;
            free(node->next);
            list->size--;
            return 1;
        }
        node = node->next;
    }

    return 0;
}

void write(struct List* list, char filename[]) {
    FILE *file;
    file = fopen(filename, "w");
    struct StudentNode* student = list->head;

    while(student) {
        fprintf(file, "%s %d %s %s\n", student->name, student->roll, student->div, student->address);
        student = student->next;
    }

    fclose(file);
}

void read(struct List* list, char filename[]) {
    FILE *file;
    file = fopen(filename, "r");

    while(1) {
        struct Student student;
        int count = fscanf(file, "%s %d %s %s", student.name, &student.roll, student.div, student.address);

        printf("Count: %d\n", count);

        if(count > 0) {
            append(student, list);
        }
        else break;
    }

    fclose(file);
}

void print(struct List* list) {
    struct StudentNode* head = list->head;
    int counter = 1;
    while(head != NULL){
        printf("%d.\t%s\n", counter++, head->name);
        head = head->next;
    }
}

int main() {
    int print_menu();
    struct List* list = (struct List*)malloc(sizeof(struct List));

    // initialize a club;
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    char filename[] = "file.txt";
    read(list, filename);

    char name[20];
    int exit = 0;

    do
    {
        
        struct Student student;
        int option = print_menu();
        switch (option)
        {
        case 1: // add member
            
            printf("\n\nEnter Student Name: ");
            scanf("%s", student.name);
            printf("Enter Roll No: ");
            scanf("%d", &student.roll);
            printf("Enter Address: ");
            scanf("%s", student.address);
            printf("Enter Div: ");
            scanf("%s", student.div);

            append(student, list);
            write(list, filename);

            break;

        case 2: // delete Member
            printf("\n\nEnter the Name: ");
            scanf("%s", name);
            int isDeleted = delete(name, list);
            if(isDeleted) {
                printf("\n%s Deleted Sucessfully!\n", name);
                write(list, filename);
            }
            else {
                printf("\nCan't Delete: %s\n", name);
            }
            break;

        case 3: // Print Members
            printf("\nStudents: \n");
            print(list);
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
    printf("1. Add Student\n");
    printf("2. Delete Student\n");
    printf("3. Display Students\n");
    printf("4. Exit\n");
    printf("\nSelect an Option: ");

    int option;
    scanf("%d", &option);

    return option;
}