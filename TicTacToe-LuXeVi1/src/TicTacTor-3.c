/**
 * @file TicTacTor-3.c
 * @brief A simple Tic Tac Toe game implementation in C.
 * 
 * This file contains the implementation of a Tic Tac Toe game in C.
 * The game allows two players to play against each other or against the computer.
 * It also includes features to view game results and save game history to a CSV file.
 * 
 * The game is played on a 3x3 grid, where players take turns marking positions on the board.
 * The first player to get three of their marks in a row (horizontally, vertically, or diagonally) wins the game.
 * If all positions on the board are filled and no player has won, the game ends in a draw.
 * 
 * The implementation uses functions to handle various aspects of the game, such as initializing the board,
 * making moves, checking for wins or draws, and updating the game history.
 * 
 * @note This implementation assumes that the input provided by the players is valid and within the specified range.
 *       It does not include error handling for invalid input.
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 3
#define MAX_NAME_LENGTH 50
#define MAX_HISTORY 100

/**
 * @brief Structure to store game history
 * 
 * This structure is used to store the game history, including the player name,
 * winner name, number of rounds played, and the date and time of the game.
 */
typedef struct {
    char playerName[MAX_NAME_LENGTH]; ///< The name of the player
    char winner[MAX_NAME_LENGTH]; ///< The name of the winner
    int roundsPlayed; ///< The number of rounds played
    char dateTime[20]; ///< The date and time of the game
} GameRecord;

/**
 * @file TicTacTor-3.c
 * @brief This file contains the declaration of variables used in the Tic Tac Toe game.
 * 
 * The variables include the game board, game history, game count, and player name.
 * The game board is a 2D array representing the Tic Tac Toe board.
 * The game history is an array of GameRecord structures to store the history of each game played.
 * The game count keeps track of the number of games played.
 * The player name is a character array to store the name of the player.
 */
char board[BOARD_SIZE][BOARD_SIZE];
GameRecord gameHistory[MAX_HISTORY];
int gameCount = 0;
char playerName[MAX_NAME_LENGTH];

// Function prototypes
void initializeBoard();
void printBoard();
bool makeMove(char player, int position);
bool checkWin(char player);
bool checkDraw();
void playGame();
void playAgainstComputer();
void addGameToHistory(const char playerName[], const char winner[], int roundsPlayed, const char dateTime[]);
void viewGameResults();
void saveGameHistoryToCSV();
void readGameHistoryFromCSV();
void computerMove(char player);
bool isValidMove(int position);
int getComputerMove(char player);
bool isBoardFull();
char* getCurrentDateTime();
void searchGameHistoryByPlayer(const char playerName[]);


/**
 * @brief Main function that serves as the entry point of the Tic Tac Toe game.
 * 
 * This function displays a menu to the user and allows them to choose various options:
 * 1. Play against a friend
 * 2. Play against the computer
 * 3. View game results
 * 4. Save game history to CSV
 * 5. View game results from CSV
 * 6. Exit
 * 
 * The function uses a do-while loop to repeatedly display the menu and execute the chosen option
 * until the user chooses to exit the program.
 * 
 * @return 0 indicating successful execution of the program.
 */

int main() {
    srand(time(NULL));
    printf("Welcome to Tic Tac Toe!\n");
    printf("This game create and develop by TACTYCAM Team | LuXeVi1\n");
    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Play against a friend\n");
        printf("2. Play against the computer\n");
        printf("3. View game results\n");
        printf("4. Save game history to CSV\n");
        printf("5. View game results from CSV\n");
        printf("6. Search game history by player name\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                playGame();
                break;
            case 2:
                playAgainstComputer();
                break;
            case 3:
                viewGameResults();
                break;
            case 4:
                saveGameHistoryToCSV();
                break;
            case 5:
                readGameHistoryFromCSV();
                break;
            case 6:
            {
                char playerName[MAX_NAME_LENGTH];
                printf("Enter player name to search: ");
                scanf("%s", playerName);
                searchGameHistoryByPlayer(playerName);
            }
                break;
            case 7:
                printf("End of program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);

    return 0;
}

/**
 * @brief Initializes the Tic Tac Toe board.
 * 
 * This function fills the Tic Tac Toe board with numbers 1 to 9, representing the positions on the board.
 * 
 * @param None
 * @return None
 */
void initializeBoard() {
    int position = 1;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = position + '0'; // Fill the board with numbers 1 to 9
            position++;
        }
    }
}

/**
 * Prints the Tic Tac Toe board with numbered positions.
 * The board is displayed using ASCII characters.
 * Each position on the board is represented by a character.
 * The board is a 3x3 grid.
 * The characters on the board can be 'X', 'O', or ' ' (empty).
 * The board is printed with numbered positions for reference.
 */
void printBoard() {
    printf("\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf(" %c ", board[i][j]);
            if (j < BOARD_SIZE - 1) {
                printf("|");
            }
        }
        printf("\n");
        if (i < BOARD_SIZE - 1) {
            printf("---|---|---\n");
        }
    }
    printf("\n");
}

/**
 * @brief Makes a move on the Tic Tac Toe board.
 * 
 * This function allows a player to make a move on the Tic Tac Toe board by specifying the player and the position.
 * The position is adjusted to the corresponding array index and checked for validity.
 * If the position is valid and the corresponding cell on the board is empty, the player's symbol is placed in that cell.
 * 
 * @param player The symbol representing the player making the move.
 * @param position The position on the board where the move is to be made (1 to 9).
 * @return true if the move is successfully made, false otherwise.
 */
bool makeMove(char player, int position) {
    int row, col;
    position--; // Adjust position to array index

    if (position < 0 || position >= BOARD_SIZE * BOARD_SIZE) {
        return false; // Invalid position
    }

    row = position / BOARD_SIZE;
    col = position % BOARD_SIZE;

    if (board[row][col] >= '1' && board[row][col] <= '9') {
        board[row][col] = player;
        return true;
    }
    return false;
}

/**
 * Check if a player has won the game.
 * 
 * @param player The player to check for a win (either 'X' or 'O').
 * @return true if the player has won, false otherwise.
 */
bool checkWin(char player) {
    // Check rows and columns
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
            return true; // Row win
        }
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) {
            return true; // Column win
        }
    }

    // Check diagonals
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
        return true; // Diagonal win (top-left to bottom-right)
    }
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) {
        return true; // Diagonal win (top-right to bottom-left)
    }

    return false;
}
/**
 * Checks if the game is a draw.
 * 
 * @return true if the game is a draw, false otherwise.
 */
bool checkDraw() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] >= '1' && board[i][j] <= '9') {
                return false; // There are still empty positions
            }
        }
    }
    return true;
}

/**
 * @brief Play a game of Tic Tac Toe against a friend.
 * 
 * This function allows two players to play a game of Tic Tac Toe.
 * It prompts the players to enter their names, initializes the game board,
 * and alternates between the players to make moves until a player wins or
 * the game ends in a draw. The function also updates the game history with
 * the results of each game played.
 */
void playGame() {
    char player1[MAX_NAME_LENGTH], player2[MAX_NAME_LENGTH];
    char currentPlayer = 'X';
    int position;
    int roundsPlayed = 0;

    printf("Enter the name of Player 1 (X): ");
    scanf("%s", player1);
    printf("Enter the name of Player 2 (O): ");
    scanf("%s", player2);

    initializeBoard();

    printf("Let's start the game!\n");

    while (true) {
        printBoard();
        printf("%s's turn (%c):\n", (currentPlayer == 'X') ? player1 : player2, currentPlayer);
        printf("Enter the position (1-9): ");
        scanf("%d", &position);

        if (makeMove(currentPlayer, position)) {
            if (checkWin(currentPlayer)) {
                printBoard();
                printf("%s wins!\n", (currentPlayer == 'X') ? player1 : player2);
                addGameToHistory((currentPlayer == 'X') ? player1 : player2, (currentPlayer == 'X') ? player1 : player2, roundsPlayed + 1, getCurrentDateTime());
                break;
            } else if (checkDraw()) {
                printBoard();
                printf("It's a draw!\n");
                addGameToHistory(player1, "Draw", roundsPlayed + 1, getCurrentDateTime());
                addGameToHistory(player2, "Draw", roundsPlayed + 1, getCurrentDateTime());
                break;
            } else {
                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
                roundsPlayed++;
            }
        } else {
            printf("Invalid move. Try again.\n");
        }
    }
}

/**
 * @brief Play a game of Tic Tac Toe against the computer.
 * 
 * This function allows the user to play a game of Tic Tac Toe against the computer.
 * The user enters their name as 'X' and takes turns making moves with the computer ('O').
 * The game continues until one player wins, it's a draw, or the user chooses to exit.
 * The function also keeps track of the game history and displays the winner or draw result.
 */
void playAgainstComputer() {
    char player1[MAX_NAME_LENGTH];
    char currentPlayer = 'X';
    int position;
    int roundsPlayed = 0;

    printf("Enter your name (X): ");
    scanf("%s", player1);

    initializeBoard();

    printf("Let's start the game against the computer!\n");

    while (true) {
        if (currentPlayer == 'X') {
            printBoard();
            printf("%s's turn (%c):\n", player1, currentPlayer);
            printf("Enter the position (1-9): ");
            scanf("%d", &position);

            if (makeMove(currentPlayer, position)) {
                if (checkWin(currentPlayer)) {
                    printBoard();
                    printf("%s wins!\n", player1);
                    addGameToHistory(player1, player1, roundsPlayed + 1, getCurrentDateTime());
                    break;
                } else if (checkDraw()) {
                    printBoard();
                    printf("It's a draw!\n");
                    addGameToHistory(player1, "Draw", roundsPlayed + 1, getCurrentDateTime());
                    break;
                } else {
                    currentPlayer = 'O';
                    roundsPlayed++;
                }
            } else {
                printf("Invalid move. Try again.\n");
            }
        } else {
            printf("Computer's turn (O):\n");
            computerMove('O'); // Computer (O) makes a move

            if (checkWin('O')) {
                printBoard();
                printf("Computer wins!\n");
                addGameToHistory("Computer", "Computer", roundsPlayed + 1, getCurrentDateTime());
                break;
            } else if (checkDraw()) {
                printBoard();
                printf("It's a draw!\n");
                addGameToHistory(player1, "Draw", roundsPlayed + 1, getCurrentDateTime());
                break;
            } else {
                currentPlayer = 'X';
                roundsPlayed++;
            }
        }
    }
}

/**
 * Function to make a move for the computer player in the Tic Tac Toe game.
 * 
 * @param player The character representing the computer player.
 */
void computerMove(char player) {
    int position = getComputerMove(player);
    makeMove(player, position);
}

/**
 * Checks if the Tic-Tac-Toe board is full.
 * 
 * @return true if the board is full, false otherwise.
 */
bool isBoardFull() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] >= '1' && board[i][j] <= '9') {
                return false; // There are still empty positions
            }
        }
    }
    return true;
}

/**
 * @brief Get the computer's move based on the current state of the board.
 * 
 * This function checks if the computer can win in the next move and returns the winning move if possible.
 * If the computer cannot win, it checks if the player can win in the next move and blocks them by returning a move that blocks the player's winning move.
 * If neither winning nor blocking moves are available, the function makes a strategic move based on the following priorities:
 * 1. Choose the center if available.
 * 2. Choose a corner if available.
 * 3. Choose an edge if no corner is available.
 * 
 * @param player The computer's player symbol ('X' or 'O').
 * @return The computer's move as a number between 1 and 9, or -1 if no available moves.
 */
// Get the computer's move
int getComputerMove(char player) {
    // Check if the computer can win in the next move
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] >= '1' && board[i][j] <= '9') {
                char originalValue = board[i][j];
                board[i][j] = player;
                if (checkWin(player)) {
                    board[i][j] = originalValue;
                    return (i * BOARD_SIZE + j + 1); // Winning move
                }
                board[i][j] = originalValue;
            }
        }
    }

    // Check if the player can win in the next move and block them
    char opponent = (player == 'X') ? 'O' : 'X';
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] >= '1' && board[i][j] <= '9') {
                char originalValue = board[i][j];
                board[i][j] = opponent;
                if (checkWin(opponent)) {
                    board[i][j] = player;
                    return (i * BOARD_SIZE + j + 1); // Blocking opponent's winning move
                }
                board[i][j] = originalValue;
            }
        }
    }

    // If no winning or blocking move, make a strategic move
    if (board[1][1] >= '1' && board[1][1] <= '9') {
        return 5; // Center is the best move
    }

    // Choose a corner if available
    if (board[0][0] >= '1' && board[0][0] <= '9') {
        return 1;
    }
    if (board[0][2] >= '1' && board[0][2] <= '9') {
        return 3;
    }
    if (board[2][0] >= '1' && board[2][0] <= '9') {
        return 7;
    }
    if (board[2][2] >= '1' && board[2][2] <= '9') {
        return 9;
    }

    // Choose an edge if no corner is available
    if (board[0][1] >= '1' && board[0][1] <= '9') {
        return 2;
    }
    if (board[1][0] >= '1' && board[1][0] <= '9') {
        return 4;
    }
    if (board[1][2] >= '1' && board[1][2] <= '9') {
        return 6;
    }
    if (board[2][1] >= '1' && board[2][1] <= '9') {
        return 8;
    }

    return -1; // No available moves
}
/**
 * Checks if a move is valid.
 *
 * This function checks if the given position is within the bounds of the game board
 * and if the corresponding cell is empty.
 *
 * @param position The position of the move to be checked.
 * @return True if the move is valid, false otherwise.
 */
bool isValidMove(int position) {
    position--; // Adjust position to array index
    int row = position / BOARD_SIZE;
    int col = position % BOARD_SIZE;

    return position >= 0 && position < BOARD_SIZE * BOARD_SIZE && board[row][col] >= '1' && board[row][col] <= '9';
}

/**
 * @brief Adds a game result to the history.
 * 
 * This function adds a game result to the game history array. It stores the player's name, the winner's name,
 * the number of rounds played, and the date and time of the game.
 * 
 * @param playerName The name of the player.
 * @param winner The name of the winner.
 * @param roundsPlayed The number of rounds played in the game.
 * @param dateTime The date and time of the game.
 */
void addGameToHistory(const char playerName[], const char winner[], int roundsPlayed, const char dateTime[]) {
    if (gameCount < MAX_HISTORY) {
        strcpy(gameHistory[gameCount].playerName, playerName);
        strcpy(gameHistory[gameCount].winner, winner);
        gameHistory[gameCount].roundsPlayed = roundsPlayed;
        strcpy(gameHistory[gameCount].dateTime, dateTime);
        gameCount++;
    }
}

/**
 * Function: viewGameResults
 * -------------------------
 * Displays the game results including player name, winner, rounds played, and date and time.
 * 
 * This function iterates through the game history array and prints the details of each game.
 * 
 * Parameters: None
 * 
 * Returns: None
 */
void viewGameResults() {
    printf("Game Results:\n");
    printf("PlayerName\tWinner\tRoundsPlayed\tDateTime\n");
    for (int i = 0; i < gameCount; i++) {
        printf("%s\t%s\t%d\t%s\n", gameHistory[i].playerName, gameHistory[i].winner, gameHistory[i].roundsPlayed, gameHistory[i].dateTime);
    }
}


/**
 * Saves the game history to a CSV file.
 * The function opens a CSV file named "game_history.csv" in write mode.
 * It then writes the game history data to the file in CSV format.
 * The game history includes player name, winner, rounds played, and date and time.
 * After writing the data, the file is closed.
 * If there is an error opening the file, an error message is printed.
 * Finally, a success message is printed indicating that the game history has been saved.
 */
void saveGameHistoryToCSV() {
    FILE *csvFile = fopen("game_history.csv", "w");
    if (csvFile == NULL) {
        printf("Error opening the CSV file for writing.\n");
        return;
    }

    fprintf(csvFile, "PlayerName,Winner,RoundsPlayed,DateTime\n");
    for (int i = 0; i < gameCount; i++) {
        fprintf(csvFile, "%s,%s,%d,%s\n", gameHistory[i].playerName, gameHistory[i].winner, gameHistory[i].roundsPlayed, gameHistory[i].dateTime);
    }

    fclose(csvFile);
    printf("Game history saved to game_history.csv\n");
}


/**
 * Returns the current date and time as a string in the format "YYYY-MM-DD HH:MM:SS".
 *
 * @return A pointer to a string containing the current date and time.
 */
char* getCurrentDateTime() {
    time_t rawtime;
    struct tm* timeinfo;
    static char dateTime[20];

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(dateTime, sizeof(dateTime), "%Y-%m-%d %H:%M:%S", timeinfo);

    return dateTime;
}

/**
 * Reads game history from a CSV file and prints the results.
 * The CSV file should have the following format:
 * Player Name, Winner, Rounds Played, Date/Time
 * 
 * If the CSV file is not found, it prints an error message.
 * If there is an error parsing a line in the CSV file, it prints an error message.
 */
void readGameHistoryFromCSV() {
    // Open the CSV file for reading
    FILE *csvFile = fopen("game_history.csv", "r");
    if (csvFile == NULL) {
        printf("Game history CSV file not found.\n");
        return;
    }

    char line[256];
    printf("Game Results from CSV File:\n");
    printf("PlayerName\tWinner\tRoundsPlayed\tDateTime\n");
    while (fgets(line, sizeof(line), csvFile)) {
        char playerName[MAX_NAME_LENGTH];
        char winner[MAX_NAME_LENGTH];
        int roundsPlayed;
        char dateTime[20];

        // Parse the line and print the game results
        if (sscanf(line, "%[^,],%[^,],%d,%19[^\n]", playerName, winner, &roundsPlayed, dateTime) == 4) {
            printf("%s\t%s\t%d\t%s\n", playerName, winner, roundsPlayed, dateTime);
        } else {
            printf("Error parsing line: %s", line);
        }
    }
    fclose(csvFile);
}

/**
 * Searches the game history by player name and prints the details of the games played by the player.
 *
 * @param playerName The name of the player to search for in the game history.
 */
void searchGameHistoryByPlayer(const char playerName[]) {
    printf("Game History for Player: %s\n", playerName);
    printf("Opponent\tWinner\tRoundsPlayed\tDateTime\n");

    for (int i = 0; i < gameCount; i++) {
        if (strcmp(playerName, gameHistory[i].playerName) == 0) {
            const char* opponent = (strcmp(gameHistory[i].playerName, playerName) == 0) ? gameHistory[i].winner : gameHistory[i].playerName;
            printf("%s\t%s\t%d\t%s\n", opponent, gameHistory[i].winner, gameHistory[i].roundsPlayed, gameHistory[i].dateTime);
        }
    }
}