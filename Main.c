#include <stdio.h>
// #include "TicTacToe-LuXeVi1/TicTacTor-3.h"
// #include "GuessingNumbers-LuXeVi1/GuessingNumbers-1.h"

int main() {
    srand(time(NULL));
    printf("Welcome to Tic Tac Toe!\n");
    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. XO game\n");
        printf("2. Guessing Number\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                // playGameTicTacTor();
                system("C:/Users/akani/OneDrive/Documents/VSC/InfinityArcadeByTACTYCAM/TicTacToe-LuXeVi1/TicTacTor-3.exe");
                break;
            // case 2:
            //     playGuessNumber();
            //     break;
            // case 3:
            //     viewGameResults();
            //     break;
            // case 4:
            //     saveGameHistoryToCSV();
            //     break;
            // case 5:
            //     readGameHistoryFromCSV();
            //     break;
            case 6:
                printf("End of program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}