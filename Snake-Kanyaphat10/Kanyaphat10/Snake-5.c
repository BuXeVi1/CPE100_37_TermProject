#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>

#define MAX_USERS 100
#define COLS 20
#define ROWS 10

struct User{
    char name[100];
    int score;
};

int speed;
int option;
int quit;
int heartsEaten = 0;
int fileCheck = 0;

void Run();
void delay(int mode);
void runSnakeGame();
void insertionSort(struct User user[], int count);
int fileSet();

//speed of snake
void delay(int mode){
    if(mode == 1){
        speed = (10 * 1000000 / 60);
    }else if(mode == 2){
        speed = (8 * 1000000 / 60);
    }else if(mode == 3){
        speed = (5 * 1000000 / 60);
    }else if(mode == 4){
        speed = (3 * 1000000 / 60);
    }
}

void runSnakeGame(){
    //Hide cursor
    printf("\e[?25l");

    // Switch to canonical mode, disable echo
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    int x[1000], y[1000];
    quit = 0;
    while(!quit){
        //Render table
        printf("┌");
        for(int i = 0; i <COLS; i++){
            printf("─");
        }
        printf("┐\n");
        for(int j = 0; j < ROWS; j++){
            printf("│");
            for(int i = 0; i < COLS; i++){
                printf("·");
            }
            printf("│\n");
        }
        printf("└");
        for(int i =0; i < COLS; i++){
            printf("─");
        }
        printf("┘\n");

        // Move cursor back to row+2
        printf("\e[%iA", ROWS+2);
        
        int head = 0, tail = 0;
        x[head] = COLS / 2;
        y[head] = ROWS / 2;
        int gameover = 0;
        int xdir = 1, ydir = 0;
        int heartx = -1, hearty;

        while(!quit && !gameover){
            if(heartx < 0){
                // Create new apple
                heartx = rand() % COLS;
                hearty = rand() % ROWS;

                for(int i = tail; i != head; i = (i + 1) % 1000){
                    if(x[i] == heartx && y[i] == hearty){
                        heartx = -1;
                    }
                }

                if(heartx >= 0){
                    // Draw apple
                    printf("\e[%iB\e[%iC❤", hearty + 1, heartx + 1);
                    printf("\e[%iF", hearty + 1);
                }
            }

            // Clear snake tail
            printf("\e[%iB\e[%iC·", y[tail] + 1, x[tail] + 1);
            printf("\e[%iF", y[tail] + 1);

            if(x[head] == heartx && y[head] == hearty){
                heartx = -1;
                heartsEaten++;// Increase the number of apples eaten by one.
            }else{
                tail = (tail + 1) % 1000;
            }

            int newhead = (head + 1) % 1000;
            x[newhead] = (x[head] + xdir + COLS) % COLS;
            y[newhead] = (y[head] + ydir + ROWS) % ROWS;
            head = newhead;

            for(int i = tail; i != head; i = (i + 1) % 1000){
                if(x[i] == x[head] && y[i] == y[head]){
                    gameover = 1;
                }
            }

            //Draw head
            printf("\e[%iB\e[%iC▓", y[head] + 1, x[head] + 1);
            printf("\e[%iF", y[head] + 1);
            fflush(stdout);

            usleep(speed);

            //Read keyboard
            struct timeval tv;
            fd_set fds;
            tv.tv_sec = 0;
            tv.tv_usec = 0;

            FD_ZERO(&fds);
            FD_SET(STDIN_FILENO, &fds);
            select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
            if(FD_ISSET(STDIN_FILENO, &fds)){
                int ch = getchar();
                if(ch == 'a' && xdir != 1){
                    xdir = -1;
                    ydir = 0;
                }else if(ch == 'd' && xdir != -1) {
                    xdir = 1;
                    ydir = 0;
                }else if(ch == 's' && ydir != -1){
                    xdir = 0;
                    ydir = 1;
                }else if(ch == 'w' && ydir != 1){
                    xdir = 0;
                    ydir = -1;
                }
            }
        }

        if(!quit){
            //Show game over
            printf("\e[%iB\e[%iC Game Over! ", ROWS / 2, COLS / 2 - 5);
            printf("\n\n\n\n\n\n\nHearts Eaten: %d\n", heartsEaten);
            printf("\e[%iF", ROWS / 5);
            //Show cursor
            printf("\e[?25h"); 
            fflush(stdout);
        }

        printf("\n\nDo you want to continue(y/n)? ");
        char wr;
        do{
            scanf(" %c", &wr);
            printf("%c", wr);
            switch(wr){
                case 'y':
                    quit = 1;
                    break;
                case 'n':
                    quit = 1;
                    fileCheck = option;
                    option = 5;
                    printf("\nThank you for your attention.\n");
                    break;
                default:
                    printf("\nPlease enter a valid option (y/n)? ");
            }
        }while(wr != 'y' && wr != 'n');
    }
    // Reset terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

void Run(){
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
        switch(option){
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
    }while(option != 5);
}

void insertionSort(struct User users[], int count){
    int i, j;
    struct User key;
    for(i = 1; i < count; i++){
        key = users[i];
        j = i-1;
        while(j >= 0 && users[j].score < key.score){
            users[j+1] = users[j];
            j = j - 1;
        }
        users[j+1] = key;
    }
}

void writeToFile(struct User users[], int count, const char *fileName){
    FILE *file = fopen(fileName, "w");
    if(file == NULL){
        printf("Error: Cannot open file %s\n", fileName);
        exit(1);
    }

    for(int i = 0; i < count; i++){
        fprintf(file, "%s %d\n", users[i].name, users[i].score);
    }

    fclose(file);
}

int fileSet(){
    char fileName[100];
    int check = 1;
    char outputFileName[100];
    if(fileCheck == 1){
        snprintf(outputFileName, sizeof(outputFileName), "easy.csv");
    }else if(fileCheck == 2){
        snprintf(outputFileName, sizeof(outputFileName), "normal.csv");
    }else if(fileCheck == 3){
        snprintf(outputFileName, sizeof(outputFileName), "hard.csv");
    }else if(fileCheck == 4){
        snprintf(outputFileName, sizeof(outputFileName), "god.csv");
    }

    FILE *file = fopen(outputFileName, "r");
    if(file == NULL){
        file = fopen(outputFileName, "w");
        if(file != NULL){
            printf("The file is created.\n");
        }else{
            printf("The file was not created.\n");
        }
    }

    struct User users[MAX_USERS];
    int num = 0;
    while(fscanf(file, "%s %d", users[num].name, &users[num].score) != EOF){
        printf("Student %d: %s, Score = %d\n", num + 1, users[num].name, users[num].score);
        num++;
    }

    if(num == 0){
        printf("No user scores found in the file.\n");
    }

    fclose(file);

    char newUsersname[100];
    do{
        printf("Enter name : ");
        scanf("%s", newUsersname);
        if(num < MAX_USERS){
            stpcpy(users[num].name, newUsersname);
            num++;
            users[num-1].score = heartsEaten;
        }else{
            printf("Maximum number of users reached.\n");
        }
    }while(check == 0);
    insertionSort(users, num);
    printf("---------------Sort users by scores---------------\n");
    printf("---------------------- Rank ----------------------\n");
    for(int i = 0; i < num; i++){
        printf("Rank %d: %s, Score = %d\n", i+1, users[i].name, users[i].score);
    }
    writeToFile(users, num, outputFileName);
    printf("End of program. Goodbye.\n");
    return 0;
}

int main(){
    Run();
    fileSet();
    return 0;
}