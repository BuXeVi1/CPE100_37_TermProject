#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

#define TRUE 1
#define FALSE 0

// common constants for each key in the conio.h
#define UP_KEY 72
#define DOWN_KEY 80
#define ESCAPE_KEY 27
#define PAUSE_KEY 'p'


// player struct definition
typedef struct {
	unsigned short x, y, score;			// x and y coordinates of the paddle and player score
} Player;

// ball struct definition
typedef struct {
	unsigned short x, y, direction;		// x and y coordinates of the ball's location and the direction where it is headed
} Ball;

typedef enum {
	RIGHT_UP, LEFT_UP, RIGHT_DOWN, LEFT_DOWN   // Declare to use in ball.direction
} BallDirection;

void MoveCursorToXY(unsigned short x, unsigned short y) {          // moves the cursor to a different (x, y) location on the terminal
	COORD coord = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

#define BOARD_WIDTH 60
#define BOARD_HEIGHT 20
#define PADDLE_1_LENGTH 5
#define PADDLE_2_LENGTH 5
#define END_SCORE 10


// Initialize positions of paddles and ball on the screen
Player player1 = {9 + 2, (BOARD_HEIGHT-PADDLE_1_LENGTH)/2 + 6, 0};
Player player2 = {BOARD_WIDTH + 9, (BOARD_HEIGHT - PADDLE_2_LENGTH)/2 + 6, 0};
Ball ball = {9 + BOARD_WIDTH/2 + 1, BOARD_HEIGHT/2 + 5, RIGHT_DOWN};

unsigned short game_on_flag_1 = TRUE;


// All functions used
void instructionScreen();
void LoadingScreen();
void UpdateFrame1();
void PrintBoard();
void MoveBall();
void ChangeBallDirection();
unsigned short RecordScore();
void PlayPong();


// after user chose to play pong, instruction about the game shows up
void instructionScreen(){
    system("cls");      // system clear screen
    printf("Welcome to the Pong game!!!\n\n"
            "\t\tGame Instruction\n\n"
            "Player 1's keys                   Player 2's keys\n"
            "    w : move up                       up arrow : move up\n"
            "    s : move down                   down arrow : move down\n"
            "\nMove the paddles to catch the ping pong ball.\n"
            "For each time your component fails to catch the ball, you get 1 point.\n"
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

// updates the frame of the Pong game
void UpdateFrame1() {
	unsigned short i;
	for(i=0;game_on_flag_1;i++) {
		Sleep(16);					// update every 16 milliseconds, this provides a frame rate of 1/0.016 = 62.5 FPS
		if(kbhit()) {				// kbhit() stands for "keyboard hit" : check if a key has been pressed, if so, return a value indicating that a key has been hit without waiting for the user to press Enter
			char key = getch();
			switch(key) {
				case 'w':			// if press 'w', Player1's paddle move upward by 1 unit
				case 'W':
					if(player1.y > 6) {  // if the paddle doesn't reach the top border of the board
						MoveCursorToXY(player1.x, player1.y + PADDLE_1_LENGTH - 1);		// delete 1 unit of '█' at the bottom of the paddle
						printf(" ");
						MoveCursorToXY(player1.x, --player1.y);							// add 1 unit of '█' at the top of the paddle
						printf("%c", 219);
					}
					break;
				case 's':			// if press 's', Player1's paddle move downward by 1 unit
				case 'S':
					if(player1.y + PADDLE_1_LENGTH < 5 + BOARD_HEIGHT) {   // if the paddle doesn't the bottom border of the board	 
						MoveCursorToXY(player1.x, player1.y);							 // add 1 unit of '█' at the bottom of the paddle
						printf(" ");
						MoveCursorToXY(player1.x, (++player1.y) + PADDLE_1_LENGTH - 1);  // delete 1 unit of '█' at the top of the paddle
						printf("%c", 219);
					}
					break;
				case UP_KEY:		// if press up arrow key, Player2's paddle move upward by 1 unit
					if(player2.y > 6) {
						MoveCursorToXY(player2.x, player2.y + PADDLE_2_LENGTH - 1);
						printf(" ");
						MoveCursorToXY(player2.x, --player2.y);
						printf("%c", 219);
					}
					break;
				case DOWN_KEY:		// if press down arrow key, Player2's paddle move downward by 1 unit
					if(player2.y + PADDLE_2_LENGTH < 5 + BOARD_HEIGHT) {
						MoveCursorToXY(player2.x, player2.y);
						printf(" ");
						MoveCursorToXY(player2.x, (++player2.y) + PADDLE_2_LENGTH - 1);
						printf("%c", 219);
					}
					break;
				case PAUSE_KEY:		// pause the game
					do {
						key = getch();
						if(key == ESCAPE_KEY) {
							MoveCursorToXY(0, 5 + BOARD_HEIGHT);
							exit(0);
						}
					} while(key != PAUSE_KEY);
					break;
				case ESCAPE_KEY:	// exit the game
					MoveCursorToXY(0, 5 + BOARD_HEIGHT);
					exit(0);
			}
		}
		if(!(i%3)) {				// the ball will move in every 3 frames (only when i mod 3 = 0, because (!(0)) = TRUE)
			MoveBall();
			ChangeBallDirection();
		}
	}
	system("cls");
	printf( "Game Over! "			// game over
			"\nBetter luck next time, Player %d."
			"\n(Press C to continue...)", (player1.score == END_SCORE) + 1);
	char key;
	do {
		key = getch();
		if(key == ESCAPE_KEY)
			exit(0);
	} while(key!='c' && key!='C');
	system("cls");
}

// prints the board of the Pong game, including player scores and paddles
void PrintBoard() {
	MoveCursorToXY(20, 4);
	printf("PLAYER 1: %hu", player1.score);
	MoveCursorToXY(50, 4);
	printf("PLAYER 2: %hu", player2.score);
	unsigned short i;
	for(i=10;i<11+BOARD_WIDTH;i++) {
		MoveCursorToXY(i, 5);
		printf("_");
		MoveCursorToXY(i, 5 + BOARD_HEIGHT);
		printf("_");
	}
	for(i=6;i<6+BOARD_HEIGHT;i++) {
		MoveCursorToXY(10, i);
		printf("|");
		MoveCursorToXY(10 + BOARD_WIDTH, i);
		printf("|");
	}
	for(i=0;i<PADDLE_1_LENGTH;i++) {
		MoveCursorToXY(player1.x, player1.y + i);
		printf("%c", 219);    // 219 = '█' , the paddle.
	}
	for(i=0;i<PADDLE_2_LENGTH;i++) {
		MoveCursorToXY(player2.x, player2.y + i);
		printf("%c", 219);
	}
}

// moves the ball by one unit in the direction ball is facing
void MoveBall() {
	MoveCursorToXY(ball.x, ball.y);
	printf(" ");
	switch(ball.direction) {
		case RIGHT_UP:
			ball.x++;
			ball.y--;
			break;
		case LEFT_UP:
			ball.x--;
			ball.y--;
			break;
		case RIGHT_DOWN:
			ball.x++;
			ball.y++;
			break;
		case LEFT_DOWN:
			ball.x--;
			ball.y++;
	}
	MoveCursorToXY(ball.x, ball.y);
	printf("O");
}

// changes the direction of the wall
void ChangeBallDirection() {
	if(ball.y < 7 || ball.y > 3 + BOARD_HEIGHT)			// if the ball hit the wall (the top and bottom of the board)
		ball.direction += ball.direction<2 ? 2 : -2;
	if(ball.x <= player1.x + 1) {								// if the ball hits player 1's paddle
		if(player1.y <= ball.y && ball.y < player1.y + PADDLE_1_LENGTH)
			ball.direction += ball.direction%2 ? -1 : 1;
		else {
			MoveCursorToXY(ball.x, ball.y);
			printf("X");
			Sleep(400);
			printf("\b ");
			ball.x = BOARD_WIDTH/2 + 10;
			ball.y = rand()%(BOARD_HEIGHT - 3) + 7;
			ball.direction = rand()%4;
			MoveCursorToXY(60, 4);
			printf("%hu", ++player2.score);		//update the score 
			if(player2.score == END_SCORE)
				game_on_flag_1 = FALSE;
		}
	}
	else if(ball.x >= player2.x - 1) {							// if the ball hits player 2's paddle
		if(player2.y <= ball.y && ball.y < player2.y + PADDLE_2_LENGTH)
			ball.direction += ball.direction%2 ? -1 : 1;
		else {
			MoveCursorToXY(ball.x, ball.y);
			printf("X");
			Sleep(400);
			printf("\b ");
			ball.x = BOARD_WIDTH/2 + 10;
			ball.y = rand()%(BOARD_HEIGHT - 3) + 7;
			ball.direction = rand()%4;
			MoveCursorToXY(30, 4);
			printf("%hu", ++player1.score);		//update the score 
			if(player1.score == END_SCORE)
				game_on_flag_1 = FALSE;
		}
	}
}

// records the scores of the Pong game in .txt file
unsigned short RecordScore() {
	time_t mytime = time(NULL);
	char player_name1[250], player_name2[250];
	printf("Player 1, enter your name:\n");
	gets(player_name1);
	printf("Player 2, enter your name:\n");
	gets(player_name2);
	FILE *info = fopen("pong_score_record.txt", "a+");
	fprintf(info, "Player Names: %s  -  %s\n", player_name1, player_name2);
	fprintf(info, "Scores: %hu  -  %hu\n", player1.score, player2.score);
	fprintf(info, "Played Date: %s", ctime(&mytime));
	fprintf(info, "__________________________________________________\n");
	fclose(info);
	system("cls");
	printf( "Press Y to see past records."
			"\nPress R to play again."
//			"\nPress M to return to the menu."
			"\nPress any other key to exit.");
	char key = getch();
	switch(key) {
		case 'Y':
		case 'y':
			system("cls");
			info = fopen("pong_score_record.txt", "r");
			char ch;
			while((ch = fgetc(info)) != EOF)
				printf("%c", ch);
			fclose(info);
			break;
		case 'R':
		case 'r':
			game_on_flag_1 = TRUE;
			Player player1 = {11, (BOARD_HEIGHT-PADDLE_1_LENGTH)/2 + 6, 0};
			Player player2 = {BOARD_WIDTH + 9, (BOARD_HEIGHT - PADDLE_2_LENGTH)/2 + 6, 0};
			ball = (Ball){BOARD_WIDTH/2 + 10, BOARD_HEIGHT/2 + 5, rand()%4};
			system("cls");
			return TRUE;
//		case 'M':
//		case 'm':
//			return FALSE;
	}
	exit(0);
}

// the main function to play Pong
void PlayPong() {
	unsigned short play_again_flag = FALSE;
	do {
		instructionScreen();
		LoadingScreen();
		PrintBoard();
		UpdateFrame1();
		play_again_flag = RecordScore();
	} while(play_again_flag);
}

int main(){
    PlayPong();
    return 0;
}