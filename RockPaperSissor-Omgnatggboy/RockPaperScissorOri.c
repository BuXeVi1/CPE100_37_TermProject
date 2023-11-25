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
void _Exit( int exit_argument );

/**
 * @struct GameRecord
 * @brief Represents a game record for a player.
 * 
 * This struct stores the player's name, as well as the number of wins, losses, and draws they have in a game.
 * It is used to keep track of the player's performance in a Rock-Paper-Scissors game.
 */
typedef struct {
    char playerName[50]; ///< The name of the player.
    int win; ///< The number of wins for the player.
    int loss; ///< The number of losses for the player.
    int draw; ///< The number of draws for the player.
} GameRecord;

GameRecord gameHistory[100];
int gameCount = 0;

/**
 * @brief Main function of the Rock Paper Scissor game.
 * 
 * This function displays a menu to the user and allows them to choose between playing a game, searching game history, or exiting the game.
 * It uses a while loop to keep the game running until the user chooses to exit.
 * The user's choice is taken as input using scanf and a switch statement is used to perform the corresponding action based on the choice.
 * The playGame() function is called when the user chooses to play a game.
 * The searchGameHistory() function is called when the user chooses to search game history.
 * The Endscreen() function is called when the user chooses to exit the game.
 * If the user enters an invalid choice, an error message is displayed.
 */
int main(){
    srand(time(NULL));
    printf("Welcome to Rock Paper Scissor!\n");
    printf("This arcade create and develop by TACTYCAM Team | Omgnatggboy\n");
    int choice;
    char keepPlaying = 'N';
    char playerName[50];
    while(keepPlaying == 'n' || keepPlaying == 'N'){
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
            {
                printf("Enter player name to search: ");
                scanf("%s", playerName);
                searchGameHistory(playerName);
            }
            break;
        case 3:
            Endscreen();
            break;
        default:
            printf("Invalid choice. Please enter 1 or 2. or 3.\n");
            break;
    }
    }
    
}

/**
 * Prints the title of the game.
 * 
 * @param a The title string to be printed.
 */
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

/**
 * Converts a string to uppercase by modifying the input string in-place.
 * 
 * @param a The string to be converted to uppercase.
 */
void stringToCaps(char a[]){
    for(int i = 0; i < strlen(a); i++)
        if(a[i] > 96 && a[i] < 123)
            a[i] -= 32;
}

/**
 * Adds a game to the history.
 * 
 * This function adds the details of a game (player name, win, loss, draw) to the game history.
 * The game history is stored in the gameHistory array.
 * 
 * @param playerName The name of the player.
 * @param win The number of wins in the game.
 * @param loss The number of losses in the game.
 * @param draw The number of draws in the game.
 */
void addGameToHistory(const char playerName[], int win, int loss, int draw) {
    if (gameCount < 100) {
        strcpy(gameHistory[gameCount].playerName, playerName);
        gameHistory[gameCount].win = win;
        gameHistory[gameCount].loss = loss;
        gameHistory[gameCount].draw = draw;
        gameCount++;
    }
}

/**
 * Searches the game history for a specific player and prints their game statistics.
 *
 * @param playerName The name of the player to search for.
 */
void searchGameHistory(const char playerName[]) {
    printf("Game History for Player: %s\n", playerName);
    printf("===================================\n");
    printf("Name\t\twin\t\tloss\t\tdraw\n"); // \tResult\n");
    for (int i = 0; i < gameCount; i++) {
        if (strcmp(playerName, gameHistory[i].playerName) == 0) {
            printf("%s\t\t%d\t\t%d\t\t%d\n", gameHistory[i].playerName, gameHistory[i].win, gameHistory[i].loss, gameHistory[i].draw);
        }
    }
}

/**
 * @brief Function to play the Rock, Paper, Scissors game.
 * 
 * This function allows the user to play the Rock, Paper, Scissors game against the computer.
 * It prompts the user to enter their name, and then starts the game loop.
 * In each iteration of the loop, it generates a random hand for the computer and prompts the user to enter their hand.
 * It compares the user's hand with the computer's hand and determines the winner.
 * The result of each game is recorded in the game history.
 * After each game, the user is asked if they want to keep playing.
 * The game continues until the user chooses to stop playing.
 */
void playGame(){
    int userHand, computerHand;
    char userHandString[10], computerHandString[10];
    int result;
    int keepAsking;
    char keepPlaying = 'Y';
    char playerName[50];
    

    /*Start randomizer*/
    srand(time(NULL));
    printf("Enter Your Name: ");
    scanf("%s", playerName);
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
            if(result==0){
                draw+=1;
                addGameToHistory(playerName, win, loss, draw);
            }
            else if(result==1){
                win+=1;
                addGameToHistory(playerName, win, loss, draw);
            }
            else{
                loss+=1;
                addGameToHistory(playerName, win, loss, draw);
            }
        switch(result){
            case 0:
                printf("It's a draw, gg\n\n");
                break;
            case 1:
                printf("YOU WON YAY!\n\n");
                break;
            case 2:
                printf("Oh, you lost. GG EZ NOOB\n\n");
                break;
            default:
                break;
        }      
        do{
            printf("Do you want to Keep playing? [Y/N]: ");
            fflush(stdin);
            scanf("%c",&keepPlaying);
        }while(keepPlaying != 'y' && keepPlaying != 'Y'&& keepPlaying != 'n' && keepPlaying != 'N');
        system("@cls||clear");
        
    }
}

/**
 * Function: Endscreen
 * --------------------
 * Displays a thank you message and exits the program after a short delay.
 * 
 * This function is called at the end of the game to display a thank you message
 * to the player and then exit the program. It uses the clock function to introduce
 * a short delay before exiting.
 */
void Endscreen(){
    printf("Thank you for playing! | Omgnatggboy\n");
    clock_t start_time = clock(); 
    while (clock() < start_time + 800);
    _Exit(0);
}
