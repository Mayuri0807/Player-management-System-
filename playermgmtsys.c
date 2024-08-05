#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct PlayerInfo {
    int jerseyNo;
    char playerName[20];
    int runs;
    int wickets;
    int matchesPlayed;   
} Player;

void storeData(Player* arr);
Player* increaseMemory(Player* arr);
void display(Player* arr);
int searchByJerseyNo(Player* arr, int jn);
int searchByPlayerName(Player* arr, char* name);
void display1(Player p);
void updateInfo(Player* arr, int index);
void hardcodeValues(Player* arr);
int deletePlayer(Player* arr, int index);
void sortByRuns(Player* arr);
void sortByWickets(Player* arr);

int ctr = 0, size = 5;

int main() {
    int choice;
    Player* arr = (Player*)malloc(size * sizeof(Player));
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    hardcodeValues(arr);
    do {
        printf("\n\nEnter your choice:\n1. Add Player info\n2. Display Player info\n3. Search Player info\n4. Update Player info\n5. Delete Player info\n6. Sort Player info\n0. Exit\n");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                if (ctr == size) {
                    printf("\nInsufficient Memory! Would you like to increase the memory (y/n)? ");
                    char ch;
                    while(getchar() != '\n'); // Clear input buffer
                    scanf("%c", &ch);
                    if (ch == 'y' || ch == 'Y') {
                        arr = increaseMemory(arr);
                    } else {
                        printf("Memory not increased!\n");
                        continue;
                    }
                }
                storeData(arr);
                break;
            case 2: 
                display(arr);
                break;
            case 3: 
                if (ctr == 0) {
                    printf("\nNo player present\n");
                } else {
                    int ch;
                    printf("\n1. Search by jerseyNo\n2. Search by player name\nEnter choice: ");
                    scanf("%d", &ch);
                    if (ch == 1) {
                        int jn;
                        printf("Enter the jersey No of player you want to search: ");
                        scanf("%d", &jn);
                        int index = searchByJerseyNo(arr, jn);
                        if (index == -1) {
                            printf("Player not found!\n");
                        } else {
                            display1(arr[index]);
                        }
                    } else if (ch == 2) {
                        char name[20];
                        printf("Enter the name of player you want to search: ");
                        scanf("%s", name);  
                        int index = searchByPlayerName(arr, name);
                        if (index == -1) {
                            printf("Player not found!\n");
                        } else {
                            display1(arr[index]);
                        }
                    } else {
                        printf("Invalid choice for searching!\n");   
                    }
                }
                break;
            case 4: 
                if (ctr > 0) {
                    int jn;
                    printf("Enter the jersey no of player you want to update information: ");
                    scanf("%d", &jn);
                    int index = searchByJerseyNo(arr, jn);
                    if (index == -1) {
                        printf("Player not found!\n");
                    } else {
                        updateInfo(arr, index);
                        printf("\nPlayer information updated successfully!!!\n");              
                    }
                } else {
                    printf("\nNo player data available to update.\n");
                }
                break;
            case 5:
                if (ctr > 0) {
                    int jn;
                    printf("\nEnter the jersey of player that you want to delete:");
                    scanf("%d", &jn);
                    int index = searchByJerseyNo(arr, jn);
                    if (index == -1) {
                        printf("Player not found!\n");
                    } else {
                        deletePlayer(arr, index);
                        printf("\nPlayer information deleted successfully!!\n");
                    }
                } else {
                    printf("\nNo player data available to delete.\n");
                }
                break;
            case 6:
                if (ctr > 0) {
                    int ch;
                    printf("\n1. Sort by Runs\n2. Sort by wickets\nEnter choice: ");
                    scanf("%d", &ch);
                    if (ch == 1) {
                        sortByRuns(arr);
                    } else if (ch == 2) {
                        sortByWickets(arr);
                    } else {
                        printf("\nInvalid choice for sorting.\n");
                    }
                } else {
                    printf("\nNo player data available to sort.\n");
                }
                break;
            case 0:
                printf("Thank You!\n");
                free(arr);
                return 0;
            default:
                printf("Invalid Input!\n");
        }
    } while(choice != 0);

    free(arr); // In case user never chooses 0 for exit.
    return 0;
}

void storeData(Player* arr) {
    Player p;
    printf("Enter the jersey number: ");
    scanf("%d", &p.jerseyNo);
    for (int i = 0; i < ctr; i++) {
        if (arr[i].jerseyNo == p.jerseyNo) {
            printf("Player already exists with the same jersey no!\n");
            return;
        }
    }
    printf("Enter player name: ");
    while (getchar() != '\n'); // Clear input buffer
    fgets(p.playerName, 20, stdin);
    p.playerName[strcspn(p.playerName, "\n")] = 0; // Remove newline character if any
    printf("Enter runs: ");
    scanf("%d", &p.runs);
    printf("Enter wickets: ");
    scanf("%d", &p.wickets);
    printf("Enter number of matches played: ");
    scanf("%d", &p.matchesPlayed);
    arr[ctr++] = p;
}

void hardcodeValues(Player* arr) {
    Player p[] = {
        {10, "Sachin", 95, 1, 40},
        {7, "M.S.Dhoni", 70, 2, 25},
        {18, "Virat", 85, 3, 14}
    };
    for (int i = 0; i < sizeof(p)/sizeof(p[0]); i++) {
        arr[ctr++] = p[i];
    }
}

Player* increaseMemory(Player* arr) {
    size += 5; // Increment by fixed quantity
    Player* temp = realloc(arr, size * sizeof(Player));
    if (!temp) {
        printf("Failed to allocate memory.\n");
        return arr; // Return the original array if realloc fails
    }
    return temp;
}

void display(Player* arr) {
    printf("\n-------------------------------------------------------------------------------------------------------------------\n");
    printf("Jersey No        |       Name            |            Runs        |      Wickets       |       Matches Played         \n");
    printf("----------------------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < ctr; i++) {
        printf("%14d    |     %20s    |     %14d     |    %14d     |    %20d\n", arr[i].jerseyNo, arr[i].playerName, arr[i].runs, arr[i].wickets, arr[i].matchesPlayed);
    }
    printf("-------------------------------------------------------------------------------------------------------------------\n");
}

int searchByJerseyNo(Player* arr, int jn) {
    for (int i = 0; i < ctr; i++) {
        if (arr[i].jerseyNo == jn) {
            return i;
        }
    }
    return -1;  
}

int searchByPlayerName(Player* arr, char* name) {
    for (int i = 0; i < ctr; i++) {
        if (strcasecmp(arr[i].playerName, name) == 0) {
            return i;
        }
    }
    return -1;
}

void updateInfo(Player* arr, int index) {
    printf("\nEnter your choice:\n1. Update Runs\n2. Update Wickets\n3. Update Matches Played\n");
    int ch, value;
    scanf("%d", &ch);
    switch (ch) {
        case 1:
            printf("Enter additional Runs: ");
            scanf("%d", &value);
            arr[index].runs += value;
            break;
        case 2:
            printf("Enter additional Wickets: ");
            scanf("%d", &value);
            arr[index].wickets += value;
            break;
        case 3:
            printf("Enter additional Matches Played: ");
            scanf("%d", &value);
            arr[index].matchesPlayed += value;
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }
}

int deletePlayer(Player* arr, int index) {
    for (int i = index; i < ctr - 1; i++) {
        arr[i] = arr[i + 1];
    }
    ctr--;
}

void display1(Player p) {
    printf("\nJersey No: %d\nName: %s\nRuns: %d\nWickets: %d\nMatches Played: %d\n", p.jerseyNo, p.playerName, p.runs, p.wickets, p.matchesPlayed);
}

void sortByRuns(Player* arr) {
    for (int i = 0; i < ctr - 1; i++) {
        for (int j = i + 1; j < ctr; j++) {
            if (arr[i].runs < arr[j].runs) {
                Player temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    display(arr);
}

void sortByWickets(Player* arr) {
    for (int i = 0; i < ctr - 1; i++) {
        for (int j = i + 1; j < ctr; j++) {
            if (arr[i].wickets < arr[j].wickets) {
                Player temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    display(arr);
}
