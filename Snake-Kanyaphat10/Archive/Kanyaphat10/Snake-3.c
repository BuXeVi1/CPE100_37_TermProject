#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>

#define COLS 20
#define ROWS 10

int speed;
int option;
int quit;

void Run();

void delay(int mode) {
    if (mode == 1) {
        speed = (10 * 1000000 / 60);
    } else if (mode == 2) {
        speed = (8 * 1000000 / 60);
    } else if (mode == 3) {
        speed = (5 * 1000000 / 60);
    } else if (mode == 4) {
        speed = (3 * 1000000 / 60);
    }
}

void runSnakeGame() {
    // Hide cursor
    printf("\e[?25l");

    // Switch to canonical mode, disable echo
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    int x[1000], y[1000];
    quit = 0;
    while (!quit) {
        // ... (rest of the code remains the same)
        // Render table
    printf("┌");
    for (int i = 0; i < COLS; i++)
      printf("─");
    printf("┐\n");

    for (int j = 0; j < ROWS; j++) {
      printf("│");
      for (int i = 0; i < COLS; i++)
        printf("·");
      printf("│\n");
    }

    printf("└");
    for (int i = 0; i < COLS; i++)
      printf("─");
    printf("┘\n");

    // Move cursor back to top
    printf("\e[%iA", ROWS + 2);

    int head = 0, tail = 0;
    x[head] = COLS / 2;
    y[head] = ROWS / 2;
    int gameover = 0;
    int xdir = 1, ydir = 0;
    int applex = -1, appley;
    int heartsEaten=0;

    while (!quit && !gameover) {
      if (applex < 0) {
        // Create new apple
        applex = rand() % COLS;
        appley = rand() % ROWS;

        for (int i = tail; i != head; i = (i + 1) % 1000)
          if (x[i] == applex && y[i] == appley)
            applex = -1;

        if (applex >= 0) {
          // Draw apple
          printf("\e[%iB\e[%iC❤", appley + 1, applex + 1);
          printf("\e[%iF", appley + 1);
        }
      }

      // Clear snake tail
      printf("\e[%iB\e[%iC·", y[tail] + 1, x[tail] + 1);
      printf("\e[%iF", y[tail] + 1);

      if (x[head] == applex && y[head] == appley) {
        applex = -1;
        heartsEaten++;// Increase the number of apples eaten by one.
      } else
        tail = (tail + 1) % 1000;

      int newhead = (head + 1) % 1000;
      x[newhead] = (x[head] + xdir + COLS) % COLS;
      y[newhead] = (y[head] + ydir + ROWS) % ROWS;
      head = newhead;

      for (int i = tail; i != head; i = (i + 1) % 1000)
        if (x[i] == x[head] && y[i] == y[head])
          gameover = 1;

      // Draw head
      printf("\e[%iB\e[%iC▓", y[head] + 1, x[head] + 1);
      printf("\e[%iF", y[head] + 1);
      fflush(stdout);

      usleep(speed);

      // Read keyboard
      struct timeval tv;
      fd_set fds;
      tv.tv_sec = 0;
      tv.tv_usec = 0;

      FD_ZERO(&fds);
      FD_SET(STDIN_FILENO, &fds);
      select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
      if (FD_ISSET(STDIN_FILENO, &fds)) {
        int ch = getchar();
        if (ch == 27 || ch == 'q') {
          quit = 1;
        } else if (ch == 'a' && xdir != 1) {
          xdir = -1;
          ydir = 0;
        } else if (ch == 'd' && xdir != -1) {
          xdir = 1;
          ydir = 0;
        } else if (ch == 's' && ydir != -1) {
          xdir = 0;
          ydir = 1;
        } else if (ch == 'w' && ydir != 1) {
          xdir = 0;
          ydir = -1;
        }
      }
    }

        if (!quit) {
            // Show game over
            printf("\e[%iB\e[%iC Game Over! ", ROWS / 2, COLS / 2 - 5);
            printf("\n\n\n\n\n\n\nHearts Eaten: %d\n", heartsEaten);
            printf("\e[%iF", ROWS / 5);
            printf("\n");
            // Show cursor
            printf("\e[?25h"); 
            fflush(stdout);
        }
        printf("\n\nDo you want to continue(y/n)? ");
            char ch;
            do {
            scanf(" %c", &ch);
            printf("%c", ch);
            switch (ch) {
                case 'y':
                    // Code to restart the game goes here
                    quit = 1;
                    break;
                case 'n':
                    quit = 1;
                    option = 5;
                    printf("\nThank you for your attention.");
                    break;
                default:
                    printf("\nPlease enter a valid option (y/n)? ");
            }
        } while (ch != 'y' && ch != 'n');
    }
    // Reset terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

void Run() {
    option = 0;
    quit = 0;
    do{
        printf("\nSelect your difficulty from options below");
        printf("\n1. Easy");
        printf("\n2. Normal");
        printf("\n3. Hard");
        printf("\n4. God");
        printf("\n5. Exit game");
        printf("\nEnter option no. : ");

        scanf("%d", &option);

        delay(option);
        switch (option) {
            case 1:
            case 2:
            case 3:
            case 4:
                runSnakeGame();
                break;
            case 5:
                printf("Thank you for your attention.\n");
                break;
            default:
                printf("Please enter a valid option (1-5).\n");
        }
    } while (option!=5);
}

int main() {
    option=0;
    Run();
    return 0;
}
