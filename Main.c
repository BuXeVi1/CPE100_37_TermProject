#include <stdio.h>
// #include "TicTacToe-LuXeVi1/TicTacTor-3.h"
// #include "GuessingNumbers-LuXeVi1/GuessingNumbers-1.h"

int main() {
    srand(time(NULL));
    printf("Welcome to InfinityArcade!\n");
    printf("This arcade create and develop by TACTYCAM Team\n");

    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Tic Tac Toe game\n"); //this game done
        printf("2. Guessing Number\n"); //this game done
        printf("3. Rock Paper Sissor\n"); //ขาดเรื่องไฟล์
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                system("C:/Users/akani/OneDrive/Documents/VSC/InfinityArcadeByTACTYCAM/TicTacToe-LuXeVi1/TicTacTor-3.exe");
                break;
            case 2:
                system("C:/Users/akani/OneDrive/Documents/VSC/InfinityArcadeByTACTYCAM/GuessingNumbers-LuXeVi1/GuessingNumbers-1.exe");
                break;
            case 3:
                system("C:/Users/akani/OneDrive/Documents/VSC/InfinityArcadeByTACTYCAM/RockPaperSissor-Omgnatggboy/RockPaperScissorOri.exe");
                 break;
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