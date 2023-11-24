#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

#define TRUE 1
#define FALSE 0

// common constants for each key in the conio.h

#define LEFT_KEY 75		 
#define RIGHT_KEY 77
#define UP_KEY 72
#define DOWN_KEY 80
#define ESCAPE_KEY 27
#define PAUSE_KEY 'p'

#define END_SCORE 10


// after user chose to play pong

void instructionScreen(){
    system("cls");      // system clear screen
    printf("Welcome to the Pong game!!!\n\n"
            "\tGame Instruction\n"
            "Player 1's keys                   Player 2's keys\n"
            "    w : move up                       up arrow : move up\n"
            "    s : move down                   down arrow : move down\n"
            "\nMove the paddles to catch the ping pong ball\n"
            "For each time your component fails to catch the ball, you get 1 point\n"
            "The goal is to reach a score of %d. The first player to reach %d points wins."
            "\n\nYou can pause/contine in the middle of the game by pressing P\n"
            "You can exit the game by pressing ESC. (but there won't be a score record)\n"
            "\nPress any key to to continue to the game...", END_SCORE, END_SCORE
        );
        if (getch() == ESCAPE_KEY) 
            exit(0);
    system("cls");
}

// loading screen 

void MoveCursorToXY(unsigned short x, unsigned short y) {          // moves the cursor to a different (x, y) location on the terminal
	COORD coord = (COORD){x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void LoadingScreen() {       // prints a loading screen with a progress bar
	MoveCursorToXY(36, 14);
	printf("Loading...");
	MoveCursorToXY(30, 15);
	unsigned short i;
	for(i=1;i<=20;i++) {
		Sleep(100);
		printf("%c", 178);  // 178 = '|'
	}
	system("cls");
}