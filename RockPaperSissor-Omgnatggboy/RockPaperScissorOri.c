//still broken xD
//play in .exe file
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void printTitle(char a[]);
void stringToCaps(char a[]);
void addGameToHistory(const char playerName[], int win, int loss, int draw);
void searchGameHistory(const char playerName[]);
void Endscreen();
void playGame();

typedef struct {
        char playerName[50];
        int win;
        int loss;
        int draw;
    } GameRecord;

GameRecord gameHistory[100];
int gameCount = 0;

int main(){
    int choice;
    char keepPlaying = 'N';
    char playerName[50];
    while(keepPlaying == 'n' || keepPlaying == 'N'){
    printf("Welcome!\n");
    printf("Choose an option:\n");
    printf("1. Play a game\n");
    printf("2. Search game history\n");
    printf("3. Exit game\n");

    printf("Enter your choice (1/2/3): ");
    scanf("%d", &choice);

    switch(choice) {
        case 1:
            playGame();
            break;
        case 2:
            
            break;
        case 3:
            Endscreen();
        default:
            printf("Invalid choice. Please enter 1 or 2.\n");
            break;
    }
    }
    

}

void printTitle(char a[]){
    int j = 0;
    printf("%c%c",176,177);
    for(int i = 0; i <= strlen(a)+7; i++)
        printf("%c",178);
    printf("%c%c\n",177,176);
    printf("%c%c%c%c%c ",176,177,178,177,176);
    while(a[j]!='\0'){
        printf("%c",a[j]);
        j++;
    }
    printf(" %c%c%c%c%c\n",176,177,178,177,176);
    printf("%c%c",176,177);
    for(int i = 0; i <= strlen(a)+7; i++)
        printf("%c",178);
    printf("%c%c\n",177,176);

}

void stringToCaps(char a[]){
    for(int i = 0; i < strlen(a); i++)
        if(a[i] > 96 && a[i] < 123)
            a[i] -= 32;
}

void addGameToHistory(const char playerName[], int win, int loss, int draw) {
    if (gameCount < 100) {
        strcpy(gameHistory[gameCount].playerName, playerName);
        gameHistory[gameCount].win = win;
        gameHistory[gameCount].loss = loss;
        gameHistory[gameCount].draw = draw;
        gameCount++;
    }
}

void searchGameHistory(const char playerName[]) {
    printf("Game History for Player: %s\n", playerName);
    printf("===================================\n");
    printf("Name\twin\tloss\tdraw\n"); // \tResult\n");
    for (int i = 0; i < gameCount; i++) {
        if (strcmp(playerName, gameHistory[i].playerName) == 0) {
            printf("%s\t%d\t\t%d\t\tdraw\n", gameHistory[i].playerName, gameHistory[i].win, gameHistory[i].loss, gameHistory[i].draw);
        }
    }

}

void playGame(){
    int userHand, computerHand;
    char userHandString[10], computerHandString[10];
    int result;
    int keepAsking;
    char keepPlaying = 'Y';
    char playerName[50];
    

    /*Start randomizer*/
    srand(time(NULL));

    while(keepPlaying == 'y' || keepPlaying == 'Y'){
        /*Generate computer's hand*/
        computerHand = rand() % 3;

        switch(computerHand){
            case 0:
                strcpy(computerHandString, "ROCK");
                break;
            case 1:
                strcpy(computerHandString, "PAPER");
                break;
            case 2:
                strcpy(computerHandString, "SCISSORS");
                break;
            default:
                break;
        }

        /*Game*/
        printTitle("ROCK, PAPER, SCISSORS BY OMGNAT");      

        do{
            char playerName[50];
            printf("Enter Your Name: ");
            scanf("%s", playerName);
            printf("\nRock, paper or scissors?: ");

            scanf("%s", userHandString);
            stringToCaps(userHandString);

            keepAsking = 0;

            if(strcmp(userHandString, "ROCK") == 0)
                userHand = 0;
            else if(strcmp(userHandString, "PAPER") == 0)
                userHand = 1;
            else if(strcmp(userHandString, "SCISSORS") == 0)
                userHand = 2;
            else
                keepAsking = 1;
        }while(keepAsking == 1);

        printf("\n\nYour hand: %s", userHandString);
        printf("\nComputer's hand: %s\n\n", computerHandString);

        int win=0;
        int draw=0;
        int loss=0;
        result = userHand - computerHand;
        if(result < 0)
            result += 3;

        switch(result){
            case 0:
                printf("It's a draw, gg\n\n");
                draw+=1;
                
                break;
            case 1:
                printf("YOU WON YAY!\n\n");
                win+=1;
                
                break;
            case 2:
                printf("Oh, you lost. GG EZ NOOB\n\n");
                loss+=1;
                break;
            default:
                break;
        }
        addGameToHistory(playerName, win, loss, draw);
               
        do{
            printf("Do you want to Keep playing? [Y/N]: ");
            fflush(stdin);
            scanf("%c",&keepPlaying);
        }while(keepPlaying != 'y' && keepPlaying != 'Y'&& keepPlaying != 'n' && keepPlaying != 'N');
        system("@cls||clear");
    }
}

void Endscreen(){
    printf("Thank you for playing!\n");
    clock_t start_time = clock(); 
    while (clock() < start_time + 1600);
}
