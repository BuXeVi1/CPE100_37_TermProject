#include <stdio.h>
#include "TicTacToe-LuXeVi1/TicTacTor-3.h"
#include "GuessingNumbers-LuXeVi1/GuessingNumbers-1.h"

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
                playGameTicTacTor();
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

// int playGameTicTacTor() {
//     srand(time(NULL));
//     printf("Welcome to Tic Tac Toe!\n");
//     int choice;
//     do {
//         printf("\nMenu:\n");
//         printf("1. Play against a friend\n");
//         printf("2. Play against the computer\n");
//         printf("3. View game results\n");
//         printf("4. Save game history to CSV\n");
//         printf("5. View game results from CSV\n");
//         printf("6. Exit\n");
//         printf("Enter your choice: ");
//         scanf("%d", &choice);
//         switch (choice) {
//             case 1:
//                 playGame();
//                 break;
//             case 2:
//                 playAgainstComputer();
//                 break;
//             case 3:
//                 viewGameResults();
//                 break;
//             case 4:
//                 saveGameHistoryToCSV();
//                 break;
//             case 5:
//                 readGameHistoryFromCSV();
//                 break;
//             case 6:
//                 printf("End of program. Goodbye!\n");
//                 break;
//             default:
//                 printf("Invalid choice. Please try again.\n");
//         }
//     } while (choice != 6);

//     return 0;
// }