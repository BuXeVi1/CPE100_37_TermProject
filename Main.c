#include <stdio.h>
// #include "TicTacToe-LuXeVi1/TicTacTor-3.h"
// #include "GuessingNumbers-LuXeVi1/GuessingNumbers-1.h"

int main() {
    srand(time(NULL));
    int choice;
    do {
        printf("Welcome to InfinityArcade!\n");
        printf("This arcade create and develop by TACTYCAM Team\n");
        printf("\nMenu:\n");
        printf("1. Tic Tac Toe\n"); //this game done + comment
        printf("2. Guessing Number\n"); //this game done + comment
        printf("3. Rock Paper Sissor\n"); //this game done + comment
        printf("4. Pong\n"); //this game done+comment
        printf("5. Snake\n"); //this game done+comment
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
            case 4:
                system("C:/Users/akani/OneDrive/Documents/VSC/InfinityArcadeByTACTYCAM/Pong-pptCheer/pong-LuXeVi1-3.exe");
                break;
            case 5:
                system("C:/Users/akani/OneDrive/Documents/VSC/InfinityArcadeByTACTYCAM/Snake-Kanyaphat10/Snake-5.c");
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