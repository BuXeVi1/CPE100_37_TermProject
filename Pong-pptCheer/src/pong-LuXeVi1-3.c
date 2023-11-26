#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

// Constants for boolean values
#define TRUE 1 /**< Represents the boolean value true */
#define FALSE 0 /**< Represents the boolean value false */

// Constants for keyboard keys
#define UP_KEY 72 /**< Represents the ASCII value of the up arrow key */
#define DOWN_KEY 80 /**< Represents the ASCII value of the down arrow key */
#define ESCAPE_KEY 27 /**< Represents the ASCII value of the escape key */
#define PAUSE_KEY 'p' /**< Represents the character value of the pause key */

// Constants for board and paddle dimensions
#define BOARD_WIDTH 60 /**< Represents the width of the game board */
#define BOARD_HEIGHT 20 /**< Represents the height of the game board */
#define PADDLE_1_LENGTH 5 /**< Represents the length of paddle 1 */
#define PADDLE_2_LENGTH 5 /**< Represents the length of paddle 2 */

/**
 * @struct Player
 * @brief Represents a player in the Pong game.
 * 
 * This struct stores the x and y coordinates of the paddle, as well as the player's score.
 */
typedef struct {
    unsigned short x, y, score;			// x and y coordinates of the paddle and player score
} Player;

/**
 * @struct Ball
 * @brief Represents a ball in the Pong game.
 * 
 * The Ball struct stores the x and y coordinates of the ball's location
 * and the direction where it is headed.
 */
typedef struct {
    unsigned short x, y, direction;		// x and y coordinates of the ball's location and the direction where it is headed
} Ball;

/**
 * @brief Enumeration representing the possible directions of the ball in the Pong game.
 *        The ball can move in four directions: RIGHT_UP, LEFT_UP, RIGHT_DOWN, LEFT_DOWN.
 */
typedef enum {
    RIGHT_UP, LEFT_UP, RIGHT_DOWN, LEFT_DOWN   // Declare to use in ball.direction
} BallDirection;



int EndScore = 0;                       // Variable to store the end score of the game
Player player1 = {11, (BOARD_HEIGHT - PADDLE_1_LENGTH) / 2 + 6, 0};                 // Structure representing player 1
Player player2 = {BOARD_WIDTH + 9, (BOARD_HEIGHT - PADDLE_2_LENGTH) / 2 + 6, 0};    // Structure representing player 2
Ball ball = {9 + BOARD_WIDTH/2 + 1, BOARD_HEIGHT/2 + 5, RIGHT_DOWN};                // Structure representing the ball
unsigned short game_on_flag_1 = TRUE;   // Flag indicating if the game is still ongoing

// Function declarations
void MoveCursorToXY(unsigned short x, unsigned short y);
void instructionScreen();
void LoadingScreen();
void UpdateFrame();
void PrintBoard();
void MoveBall();
void ChangeBallDirection();
unsigned short RecordScore();
void PlayPong();

/**
 * @brief The main function to play Pong.
 * 
 * This function executes the Pong game by performing the following steps:
 * 1. Displays the instruction screen.
 * 2. Shows the loading screen.
 * 3. Prints the game board.
 * 4. Updates the game frame.
 * 5. Records the player's score.
 * 6. Repeats the above steps if the player wants to play again.
 */
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

/**
 * @brief The main function of the program.
 * 
 * This function calls the PlayPong() function and returns 0.
 * 
 * @return int Returns 0 to indicate successful execution.
 */
int main(){
    PlayPong();
    return 0;
}

/**
 * Moves the cursor to a different (x, y) location on the terminal.
 *
 * @param x The x-coordinate of the new cursor position.
 * @param y The y-coordinate of the new cursor position.
 */
void MoveCursorToXY(unsigned short x, unsigned short y) {
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/**
 * @brief Displays the instruction screen for the Pong game.
 * 
 * This function clears the screen and displays the game instructions, including the controls for each player,
 * the objective of the game, and additional options like pausing and exiting the game.
 * 
 * @param None
 * @return None
 */
void instructionScreen(){
    system("cls");      // system clear screen
    printf("Welcome to the Pong game!\n");
    printf("This arcade create and develop by TACTYCAM Team | pptCheer\n\n"
            "\t\tGame Instruction\n\n"
            "Player 1's keys                   Player 2's keys\n"
            "    w : move up                       up arrow : move up\n"
            "    s : move down                   down arrow : move down\n"
            "\nMove the paddles to catch the ping pong ball.\n"
            "For each time your component fails to catch the ball, you get 1 point.\n"
            "The goal is to reach the end score. The first player to reach will be the winner."
            "\n\nYou can pause/contine in the middle of the game by pressing P\n"
            "You can exit the game by pressing ESC. (but there won't be a score record)\n"
            "\nSet your end score : ");
	scanf("%d", &EndScore);
	printf("\n\nPress any key to to continue to the game...");
	if (getch() == ESCAPE_KEY)
        exit(0);
    system("cls");
}


/**
 * @brief Prints a loading screen with a progress bar.
 * 
 * This function displays a loading screen with a progress bar. It first prints the text "Loading..."
 * at coordinates (36, 14) on the console screen. Then, it iterates from 1 to 20 and prints a vertical
 * bar character (ASCII code 178) to represent the progress. Each bar is printed with a delay of 100 milliseconds.
 * Finally, it clears the console screen using the "cls" command.
 */
void LoadingScreen() {
    MoveCursorToXY(36, 14);
    printf("Loading...");
    MoveCursorToXY(30, 15);
    unsigned short i;
    for(i = 1; i <= 20; i++) {
        Sleep(100);
        printf("%c", 178);  // 178 = '|'
    }
    system("cls");
}

/**
 * @brief Updates the frame of the Pong game.
 * 
 * This function updates the frame of the Pong game by handling player input, moving the paddles, and updating the ball's position.
 * It also checks for game over conditions and allows the player to continue or exit the game.
 * 
 * @note This function assumes the existence of the following variables: game_on_flag_1, player1, player2, PADDLE_1_LENGTH, PADDLE_2_LENGTH, BOARD_HEIGHT, UP_KEY, DOWN_KEY, PAUSE_KEY, ESCAPE_KEY, EndScore.
 * 
 * @note This function relies on the following functions: Sleep(), kbhit(), getch(), MoveCursorToXY(), printf(), MoveBall(), ChangeBallDirection(), system(), exit().
 */
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
				case PAUSE_KEY:		// pause or resume to the game
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
			"\n(Press C to continue...)", (player1.score == EndScore) + 1);
	char key;
	do {
		key = getch();
		if(key == ESCAPE_KEY)
			exit(0);
	} while(key!='c' && key!='C');
	system("cls");
}


/**
 * Function: PrintBoard
 * ---------------------
 * Prints the game board on the console screen.
 * The board includes the scores of player 1 and player 2,
 * the boundaries of the board, and the paddles of both players.
 */
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


/**
 * Moves the ball in the specified direction.
 * The ball's current position is updated based on its direction.
 * The previous position of the ball is cleared by printing a space character.
 * The new position of the ball is marked by printing the character 'O'.
 */
void MoveBall() {
    // Move the cursor to the previous position of the ball and clear it
    MoveCursorToXY(ball.x, ball.y);
    printf(" ");

    // Update the ball's position based on its direction
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

    // Move the cursor to the new position of the ball and mark it
    MoveCursorToXY(ball.x, ball.y);
    printf("O");
}


/**
 * @brief Changes the direction of the ball based on collision with walls or paddles.
 * 
 * This function checks if the ball hits the top or bottom wall of the board and changes its direction accordingly.
 * If the ball hits player 1's paddle, it checks if the ball's y-coordinate is within the paddle's range and changes its direction accordingly.
 * If the ball hits player 2's paddle, it checks if the ball's y-coordinate is within the paddle's range and changes its direction accordingly.
 * If the ball goes out of bounds, it updates the score and resets the ball's position and direction.
 * 
 * @param None
 * @return None
 */
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
			if(player2.score == EndScore)
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
			if(player1.score == EndScore)
				game_on_flag_1 = FALSE;
		}
	}
}

/**
 * Records the scores of the Pong game in a .txt file.
 * 
 * @return TRUE if the game should continue, FALSE otherwise.
 */
unsigned short RecordScore() {
    time_t mytime = time(NULL);
    char player_name1[250], player_name2[250];
    
    // Clear input buffer before reading player names
    fflush(stdin);

    printf("Player 1, enter your name:\n");
    fgets(player_name1, sizeof(player_name1), stdin);
    player_name1[strcspn(player_name1, "\n")] = '\0';  // Remove the newline character

    printf("Player 2, enter your name:\n");
    fgets(player_name2, sizeof(player_name2), stdin);
    player_name2[strcspn(player_name2, "\n")] = '\0';  // Remove the newline character

    FILE *info = fopen("pong_score_record.txt", "a+");
    if (info == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fprintf(info, "Player Names: %s  -  %s\n", player_name1, player_name2);
    fprintf(info, "Scores: %hu  -  %hu\n", player1.score, player2.score);
    fprintf(info, "Played Date: %s", ctime(&mytime));
    fprintf(info, "__________________________________________________\n");

    fclose(info);
    system("cls");

    printf("Press Y to see past records."
           "\nPress R to play again."
           "\nPress any other key to exit.");

    char key = getch();
    switch (key) {
        case 'Y':
        case 'y':
            system("cls");
            info = fopen("pong_score_record.txt", "r");
            if (info == NULL) {
                perror("Error opening file");
                exit(EXIT_FAILURE);
            }

            char ch;
            while ((ch = fgetc(info)) != EOF)
                printf("%c", ch);

            fclose(info);
            break;
        case 'R':
        case 'r':
            game_on_flag_1 = TRUE;
            player1 = (Player){11, (BOARD_HEIGHT - PADDLE_1_LENGTH) / 2 + 6, 0};
            player2 = (Player){BOARD_WIDTH + 9, (BOARD_HEIGHT - PADDLE_2_LENGTH) / 2 + 6, 0};
            ball = (Ball){BOARD_WIDTH / 2 + 10, BOARD_HEIGHT / 2 + 5, rand() % 4};
            system("cls");
            return TRUE;
    }

    exit(0);
}

