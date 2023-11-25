#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/**
 * @file GuessingNumbers-1.c
 * @brief This file contains the definitions of the constants MAX_NAME_LENGTH and MAX_HISTORY.
 */

#define MAX_NAME_LENGTH 50 /**< The maximum length of a name. */
#define MAX_HISTORY 100    /**< The maximum number of history records. */

/**
 * @brief Structure to store game history.
 * 
 * This structure is used to store information about a game, including the player's name,
 * the target number, and the number of guesses made.
 */
typedef struct {
    char playerName[MAX_NAME_LENGTH]; /**< The name of the player. */
    int targetNumber; /**< The target number to be guessed. */
    int numGuesses; /**< The number of guesses made by the player. */
    /*char result[20];*/ /**< The result of the game. */
} GameRecord;

// Function
void playGame();
void addGameToHistory(const char playerName[], int targetNumber, int numGuesses/*, const char result[]*/);
void searchGameHistory(const char playerName[]);
void summarizeGameHistory();
void saveGameHistoryToCSV();
// void loadGameHistoryFromCSV();
void viewGameResultsFromCSV();

GameRecord gameHistory[MAX_HISTORY];
int gameCount = 0;

/**
 * @brief Main function that runs the Guessing Numbers game.
 * 
 * This function displays a menu to the user and allows them to choose various options:
 * 1. Play a game
 * 2. Search for game history by player name
 * 3. Summarize game history
 * 4. Save game history to CSV
 * 5. View game results from CSV
 * 6. Exit
 * 
 * The function uses a do-while loop to repeatedly display the menu and process the user's choice until they choose to exit.
 * 
 * @return 0 indicating successful execution of the program.
 */
int main() {
    srand(time(NULL));
    // loadGameHistoryFromCSV(); // Load game history from CSV file if available
    printf("Welcome to Guessing Numbers game!\n");
    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Play a game\n");
        printf("2. Search for game history by player name\n");
        printf("3. Summarize game history\n");
        printf("4. Save game history to CSV\n");
        printf("5. View game results from CSV\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                playGame();
                break;
            case 2:
                {
                    char playerName[MAX_NAME_LENGTH];
                    printf("Enter player name to search: ");
                    scanf("%s", playerName);
                    searchGameHistory(playerName);
                }
                break;
            case 3:
                summarizeGameHistory();
                break;
            case 4:
                saveGameHistoryToCSV();
                break;
            case 5:
                viewGameResultsFromCSV();
                break;
            case 6:
                printf("End of program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}

/**
 * Function to play a game.
 * 
 * This function allows the user to play a number guessing game.
 * It prompts the user to enter their name and then generates a random number between 1 and 100.
 * The user is then prompted to guess the number, and the function provides feedback on whether the guess is too high or too low.
 * The function continues to prompt the user for guesses until they guess the correct number.
 * Once the correct number is guessed, the function displays a congratulatory message along with the number of guesses made.
 * 
 * @param None
 * @return None
 */
void playGame() {
    char playerName[MAX_NAME_LENGTH];
    int number, guess, numGuesses = 0;
    int low = 1, high = 100;

    printf("Enter your name: ");
    scanf("%s", playerName);

    number = rand() % 100 + 1;

    printf("Welcome, %s! Guess the number between 1 and 100\n", playerName);

    do {
        printf("Enter your guess: ");
        scanf("%d", &guess);
        numGuesses++;

        if (guess > number) {
            printf("Too high\n");
            high = guess - 1;
        } else if (guess < number) {
            printf("Too low\n");
            low = guess + 1;
        } else {
            printf("Congratulations, %s! You guessed the number in %d guesses!\n", playerName, numGuesses);
            // addGameToHistory(playerName, number, numGuesses, "Win");
        }
    } while (guess != number);

    addGameToHistory(playerName, number, numGuesses);
}

/**
 * Adds a game to the history.
 *
 * @param playerName The name of the player.
 * @param targetNumber The target number of the game.
 * @param numGuesses The number of guesses made in the game.
 */
void addGameToHistory(const char playerName[], int targetNumber, int numGuesses/*, const char result[]*/) {
    if (gameCount < MAX_HISTORY) {
        strcpy(gameHistory[gameCount].playerName, playerName);
        gameHistory[gameCount].targetNumber = targetNumber;
        gameHistory[gameCount].numGuesses = numGuesses;
        // strcpy(gameHistory[gameCount].result, result);
        gameCount++;
    }
}

// Function to search for game history by player name
/**
 * Searches the game history for a specific player and prints their game records.
 * 
 * @param playerName The name of the player to search for.
 */
void searchGameHistory(const char playerName[]) {
    printf("Game History for Player: %s\n", playerName);
    printf("===================================\n");
    printf("Name\tTarget Number\tGuesses\n"); // \tResult\n");
    for (int i = 0; i < gameCount; i++) {
        if (strcmp(playerName, gameHistory[i].playerName) == 0) {
            printf("%s\t%d\t\t%d\n", gameHistory[i].playerName, gameHistory[i].targetNumber, gameHistory[i].numGuesses/*\t%s, gameHistory[i].result*/);
        }
    }
}

/**
 * Function to summarize the game history.
 * This function prints the summary of the game history, including the total number of games played.
 */
void summarizeGameHistory() {
    printf("Game History Summary\n");
    printf("====================\n");
    printf("Total Games Played: %d\n", gameCount);
}

/**
 * Function to save the game history to a CSV file.
 * The function opens a CSV file named "game_history.csv" in write mode.
 * It then writes the player name, target number, and number of guesses for each game in the game history array to the CSV file.
 * Finally, it closes the CSV file and prints a message indicating that the game history has been saved.
 */
void saveGameHistoryToCSV() {
    FILE *csvFile = fopen("game_history.csv", "w");
    if (csvFile == NULL) {
        printf("Error opening the CSV file for writing.\n");
        return;
    }

    fprintf(csvFile, "Player Name,Target Number,Guesses\n");
    for (int i = 0; i < gameCount; i++) {
        fprintf(csvFile, "%s,%d,%d\n", gameHistory[i].playerName, gameHistory[i].targetNumber, gameHistory[i].numGuesses /*,%s , gameHistory[i].result*/);
    }

    fclose(csvFile);
    printf("Game history saved to game_history.csv\n");
}

/**
 * Function to view game results from a CSV file.
 * The function reads the contents of a CSV file named "game_history.csv"
 * and prints the game results in a tabular format.
 * The format of each line in the CSV file should be:
 * Player Name, Target Number, Guesses
 * 
 * If the CSV file is not found, the function prints an error message.
 */
void viewGameResultsFromCSV() {
    // Open the CSV file for reading
    FILE *csvFile = fopen("game_history.csv", "r");
    if (csvFile == NULL) {
        printf("Game history CSV file not found.\n");
        return;
    }

    char line[256];
    printf("Game Results from CSV File:\n");
    printf("Player Name\tTarget Number\tGuesses\n"); /*\tResult*/

    // Read each line from the CSV file and print it
    while (fgets(line, sizeof(line), csvFile)) {
        printf("%s", line);
    }

    // Close the CSV file
    fclose(csvFile);
}
