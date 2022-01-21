#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char name[20];
    struct Node* next;
};

struct Node* new_node(char name[]) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    strcpy(node->name, name);
    node->next = NULL;
    return node;
}

struct Club {
    struct Node* president;
    struct Node* secretary;
    int length;
};

void addMember(char name[], struct Club* club) {
    struct Node* member = new_node(name);
    member->next = club->president->next;
    club->president->next = member;
    club->length++;
}

int deleteMember(char name[], struct Club* club) {
    struct Node* node = club->president;

    while(node->next != club->secretary) {
        if(strcmp(node->next->name, name) == 0) {
            node->next = node->next->next;
            club->length--;
            return 1;
        }
        node = node->next;
    }

    return 0;
}

void printMembers(struct Club club) {
    struct Node* head = club.president;
    int counter = 1;
    while(head != NULL){
        printf("%d.\t%s\n", counter++, head->name);
        head = head->next;
    }
}

int main() {
    int print_menu();
    struct Club pinnacle_club;

    // initialize a club;
    pinnacle_club.president = new_node("President");
    pinnacle_club.secretary = new_node("Secretary");
    pinnacle_club.president->next = pinnacle_club.secretary;
    pinnacle_club.length = 2;

    char name[20];
    int exit = 0;

    do
    {
        int option = print_menu();
        switch (option)
        {
        case 1: // add member
            printf("\n\nEnter the Name: ");
            scanf("%s", name);
            addMember(name, &pinnacle_club);
            printf("\n%s Added Sucessfully!\n", name);
            break;

        case 2: // delete Member
            printf("\n\nEnter the Name: ");
            scanf("%s", name);
            int isDeleted = deleteMember(name, &pinnacle_club);
            if(isDeleted) {
                printf("\n%s Deleted Sucessfully!\n", name);
            }
            else {
                printf("\nCan't Delete: %s\n", name);
            }
            break;

        case 3: // Print Members
            printMembers(pinnacle_club);
            break;

        case 4: // Total
            printf("\n\nTotal Member: %d\n", pinnacle_club.length);
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
    printf("1. Add Member\n");
    printf("2. Delete Member\n");
    printf("3. Display Members\n");
    printf("4. Compute Total\n");
    printf("5. Exit\n");
    printf("\nSelect an Option: ");

    int option;
    scanf("%d", &option);

    return option;
}