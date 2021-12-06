#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Player {
    char name[20];
    int Age;
    char Country[15];
    char Category[20];
    int AverageScore;
    int WicketCount;
    int ODI;
    int T20;
} players [100];

int main() {
    int input_players();
    int print_menu();
    void output_players(struct Player*, int, int);
    int compare_with_average_score(struct Player, struct Player);
    int compare_with_wicket_count(struct Player, struct Player);
    int count_players(struct Player[], int, char[], char[]);
    void sort(struct Player[], int, int (*)(struct Player, struct Player));

    int size = input_players();
    
    char country[15];

    int exit = 0;
    do
    {
        int option = print_menu();
        switch (option)
        {
        case 1:
            printf("Enter Country Name: ");
            scanf("%s", country);

            int batsman_count = count_players(players, size, country, "Batsman");
            printf("\nThere are %d Batsman in %s\n", batsman_count, country);
            break;

        case 2:
            sort(players, size, compare_with_average_score);
            output_players(players, size, 0);
            break;

        case 3:
            sort(players, size, compare_with_average_score);
            output_players(players, 1, 0);
            break;

        case 4:
            printf("Enter Country Name: ");
            scanf("%s", country);

            int bowlers_count = count_players(players, size, country, "Bowler");
            printf("\nThere are %d Bowlers in %s\n", bowlers_count, country);
            break;

        case 5:
            sort(players, size, compare_with_wicket_count);
            output_players(players, 1, 0);
            break;

        case 6:
            output_players(players, size, 0);
            break;

        default:
            exit = 1;
            break;
        }
    } while (exit == 0);

    printf("\nThank You!");
    return 0;
}

int count_players(struct Player players[], int size, char country[], char category[]) {
    int count = 0;
    for (int i = 0; i < size; ++i)
    {
        if (strcmp(players[i].Country, country) == 0 && strcmp(players[i].Category, category) == 0)
        {
            ++count;
        }
    }
    return count;
}

void sort(struct Player players[], int size, int (*compare)(struct Player, struct Player)) {
    void swap_players(struct Player*, struct Player*);

    for (int i = 0; i < size; ++i)
    {
        for (int j = i+1; j < size; ++j)
        {
            if (compare(players[i], players[j]))
            {
                swap_players(&players[i], &players[j]);
            }
        }
    }
}

int compare_with_average_score(struct Player a, struct Player b) {
    return b.AverageScore > a.AverageScore;
}

int compare_with_wicket_count(struct Player a, struct Player b) {
    return b.WicketCount > a.WicketCount;
}

void swap_players (struct Player* p1, struct Player* p2) {
    struct Player p = *p1;
    *p1 = *p2;
    *p2 = p;
}

int print_menu() {
    printf("\n**Menu**\n");
    printf("1. Number of batsman of a particular country\n");
    printf("2. Sort the Batsman as per the average batting score\n");
    printf("3. Batsman with highest average score\n");
    printf("4. Number of bowlers of a particular country \n");
    printf("5. The bowler that has taken a maximum no of wickets\n");
    printf("6. Show All\n");
    printf("7. Exit\n");
    printf("\n\nSelect an Option: ");

    int option;
    scanf("%d", &option);

    return option;
}

void output_player(int srno, struct Player* p, int display_full) {
    printf("%-7d | %-10s | %-10s | %-15s | %-10d | %-10d | %-10d | %-10d\n", srno, (*p).name, (*p).Country, (*p).Category, (*p).AverageScore, (*p).WicketCount, (*p).ODI, (*p).T20);
}

void output_players(struct Player* player, int count, int display_full) {

    void output_player(int, struct Player*, int);

    printf("\n\n");
    printf("%-7s | %-10s | %-10s | %-15s | %-10s | %-10s | %-10s | %-10s\n", "Sr no.", "Name", "Country", "Category", "Avg Score", "Wickets", "ODI", "T20");

    for (int i = 0; i < count; ++i)
    {
        output_player(i+1, player + i, display_full);
    }
}

struct Player input_player() {
    struct Player p;

    printf("Enter Player's Name: ");
    scanf("%s", p.name);

    printf("Enter Player's Age: ");
    scanf("%d", &p.Age);

    printf("Enter Player's Country: ");
    scanf("%s", p.Country);

    printf("What is Player's Category?\n");
    printf("\t1. Batsman\n");
    printf("\t2. Bowler\n");
    printf("\t3. Wicket keeper\n");
    printf("\t4. All-rounder\n");
    printf("Enter: ");
    scanf("%s", p.Category);

    printf("Enter Player's Average Bating Score: ");
    scanf("%d", &p.AverageScore);

    printf("Enter Player's Wicket Count: ");
    scanf("%d", &p.WicketCount);

    printf("Enter Player's ODI: ");
    scanf("%d", &p.ODI);

    printf("Enter Player's T20: ");
    scanf("%d", &p.T20);

    return p;
}

int input_players() {

    struct Player input_player();

    int count;
    printf("Enter no. of players to Enter: ");
    scanf("%d", &count);

    for (int i = 0; i < count; ++i)
    {
        printf("\nPlayer no. %d\n", i + 1);
        players[i] = input_player();
    }

    printf("\n\n**All the players data is saved successfully**\n\n");

    return count;
}