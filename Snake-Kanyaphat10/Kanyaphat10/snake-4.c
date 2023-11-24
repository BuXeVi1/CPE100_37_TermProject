#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>

#define MAX_STUDENTS 100
#define COLS 20
#define ROWS 10

struct Student {
    char name[100];
    int score;
};

int speed;
int option;
int quit;
int heartsEaten = 0;
int fileCheck=0;


void Run();
void delay(int mode);
void runSnakeGame();
void insertionSort(struct Student students[], int count);
int play();

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
    // oldt = old terminal newt = new terminal
    // Switch to canonical mode, disable echo
    /*The termios functions describe a general terminal interface that
       is provided to control asynchronous communications ports.*/

    //  struct termios -> c_lflag -> ICANON, ECHO

    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt); //STDIN_FILENO value is 0. 
    //tcgetattr() get the parameters associated with the terminal มาใส่ไว้ &oldt (struct terminal)
    newt = oldt;// copy oldt to newt
    newt.c_lflag &= ~(ICANON | ECHO);//close ICANON This allows user input to be sent immediately to the program without waiting for the Enter key to be pressed.
    //close ECHO ทำให้ข้อมูลที่ผู้ใช้ป้อนไม่ถูกแสดงผลที่หน้าจอ
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);// tcsetattr To customize the behavior of the terminal
    //TCSANOW The change should take place immediately. ทำการตั้งค่าทันที.
    int x[1000], y[1000];
    quit = 0;
    while (!quit) { // quit = 1
    // Render table
    printf("┌");
    for (int i = 0; i < COLS; i++){
        printf("─");
    }
    printf("┐\n");

    for (int j = 0; j < ROWS; j++) {
      printf("│");
      for (int i = 0; i < COLS; i++){
        printf("·");
      }
      printf("│\n");
    }

    printf("└");
    for (int i = 0; i < COLS; i++){
        printf("─");
    }
    printf("┘\n");

    // Move cursor back to row+2
    printf("\e[%iA", ROWS+2);//Set the snake's travel so that the travel area is equal to the display grid.
    /*%i takes an integer value as an integer value with decimal, hexadecimal, or octal type.
    To enter a value in hexadecimal format, the value should be provided by preceding “0x” and to enter a value in value in octal format, the value should be provided by preceding “0”.*/

    int head = 0, tail = 0;
    x[head] = COLS / 2;
    y[head] = ROWS / 2;
    int gameover = 0;
    int xdir = 1, ydir = 0;
    int heartx = -1, hearty;
    

    while (!quit && !gameover) {
      if (heartx < 0) {
        // Create new apple
        heartx = rand() % COLS;
        hearty = rand() % ROWS;

        for (int i = tail; i != head; i = (i + 1) % 1000)//circular buffer = the head pointer is incremented and likewise, when the data is being removed (read) the tail pointer is incremented
          if (x[i] == heartx && y[i] == hearty)
            heartx = -1;

        if (heartx >= 0) {
          // Draw apple
          printf("\e[%iB\e[%iC❤", hearty + 1, heartx + 1);//\e[%iB\e[%iC is escape sequence =Move the cursor to the specified location.
          printf("\e[%iF", hearty + 1);
          //This is to check that a heart (❤) has not been eaten (or the heart position is not set to -1) before drawing an apple on the screen.
        }
      }

      // Clear snake tail  Type a dot to replace the moving tail.
      printf("\e[%iB\e[%iC·", y[tail] + 1, x[tail] + 1);
      printf("\e[%iF", y[tail] + 1);

      if (x[head] == heartx && y[head] == hearty) {
        heartx = -1;
        //heart ถูกกิน
        heartsEaten++;// Increase the number of apples eaten by one.
      } else{
        tail = (tail + 1) % 1000;
      }
        
        //The snake's head moves to the next position in the specified direction (xdir, ydir).
      int newhead = (head + 1) % 1000; // new head position calculate
      x[newhead] = (x[head] + xdir + COLS) % COLS;
      y[newhead] = (y[head] + ydir + ROWS) % ROWS;
      head = newhead;

      for (int i = tail; i != head; i = (i + 1) % 1000)
        if (x[i] == x[head] && y[i] == y[head])
          gameover = 1;
          //The head of the snake collides with the body, ending the game.

      // Draw head
      printf("\e[%iB\e[%iC▓", y[head] + 1, x[head] + 1);//ค่า head เปลี่ยนเรื่อยๆ ก็จะวาดหัวงูที่ตำแหน่งใหม่เรื่อยๆ
      printf("\e[%iF", y[head] + 1);//เลื่อน cursor
      fflush(stdout);//แสดงข้อมูลทันที

      usleep(speed);//ความเร็วของการเคลื่อนที่ของงูในเกม

      // Read keyboard
      struct timeval tv;
      fd_set fds;//fds Check the status of STDIN_FILENO fds = Disk file related to receiving data from the keyboard.
      //ช่วยให้โปรแกรมสามารถตรวจสอบว่ามีการกดปุ่มบนคีย์บอร์ดหรือไม่, โดยไม่ต้องรอเวลานานก่อนที่จะดำเนินการต่อ.
      tv.tv_sec = 0;// 0 = ไม่มีการรอ วินาที. ในการใช้ฟังก์ชัน select()
      tv.tv_usec = 0;// 0 = ไม่มีการรอ ไมครอนด์วินาที. ในการใช้ฟังก์ชัน select()

      FD_ZERO(&fds);//ไม่มีไฟล์ดิสก์ที่ถูกตรวจสอบสถานะอยู่. ZERO
      FD_SET(STDIN_FILENO, &fds); //เพิ่ม STDIN_FILENO = 0
      select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);// +1 เพื่อให้ select ทำงานถูกต้อง เพื่อเป็นค่าสูงสุด อ่านไฟล์ดิสก์ fds กำหนดเวลา timeout &tv
      if (FD_ISSET(STDIN_FILENO, &fds)) {//ตรวจสอบได้ว่ามีข้อมูล (input) ที่พร้อมให้อ่านจากคีย์บอร์ด
        int ch = getchar();
        if (ch == 27 ) {//escape
          quit = 1;//End of program
        } else if (ch == 'a' && xdir != 1) {//can't move back to right
          xdir = -1;//press a move left
          ydir = 0;//does not move on the y axis
        } else if (ch == 'd' && xdir != -1) {//can't move back to left
          xdir = 1;//press d move right
          ydir = 0;//does not move on the y axis
        } else if (ch == 's' && ydir != -1) {//can't move back to down
          xdir = 0;//does not move on the x axis
          ydir = 1;//press s move down
        } else if (ch == 'w' && ydir != 1) {//can't move back to up
          xdir = 0;//does not move on the x axis
          ydir = -1;//press w move up
        }
      }
    }

        if (!quit) {
            // Show game over
            printf("\e[%iB\e[%iC Game Over! ", ROWS / 2, COLS / 2 - 5);
            printf("\n\n\n\n\n\n\nHearts Eaten: %d\n", heartsEaten);//show heart that snake eaten
            printf("\e[%iF", ROWS / 5);//เลื่อนตำแหน่งของ cursor ไปที่บรรทัดที่กำหนดโดยค่า 
            printf("\n");
            // Show cursor
            printf("\e[?25h"); 
            fflush(stdout);//แสดงผลทันที
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
                    fileCheck = option;
                    option = 5;
                    printf("\nThank you for your attention.\n");
                    break;
                default:
                    printf("\nPlease enter a valid option (y/n)? ");
            }
        } while (ch != 'y' && ch != 'n');
    }
    // Reset terminal settings  กลับไปการตั้งค่าเริ่มต้น
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    
}

void Run() {
    option = 0;
    quit = 0;
    do {
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
    } while (option != 5);
}

void insertionSort(struct Student students[], int count) {
    int i, j;
    struct Student key;
    for (i = 1; i < count; i++) {
        key = students[i];
        j = i - 1;
        while (j >= 0 && students[j].score < key.score) {
            students[j + 1] = students[j];
            j = j - 1;
        }
        students[j + 1] = key;
    }
}

void writeToFile(struct Student students[], int count, const char *fileName) {//ไม่อนุญาตให้ฟังก์ชันนี้เปลี่ยนแปลงชื่อไฟล์ที่ถูกส่งเข้ามา
    FILE *file = fopen(fileName, "w");
    if (file == NULL) {
        printf("Error: Cannot open file %s\n", fileName);
        exit(1);
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %d\n", students[i].name, students[i].score);
    }

    fclose(file);
}

int play() {
    char fileName[100];
    int check=1;
    char outputFileName[100];
    if (fileCheck==1)
    {
        snprintf(outputFileName, sizeof(outputFileName), "easy.csv");
    }
    else if (fileCheck==2)
    {
        snprintf(outputFileName, sizeof(outputFileName), "normal.csv");
    }
    else if (fileCheck==3)
    {
        snprintf(outputFileName, sizeof(outputFileName), "hard.csv");
    }
    else if (fileCheck) 
    {
        snprintf(outputFileName, sizeof(outputFileName), "god.csv");//ป้องกัน buffer overflow 
    }
    

    FILE *file = fopen(outputFileName, "r"), *file2 = fopen(outputFileName, "a+");
    if (file == NULL) {
        file = fopen(outputFileName, "w");
        if (file != NULL) {
            printf("The file is created.\n");
        } else {
            printf("The file was not created.\n");
        }
    } 

    if (file2 == NULL) {
        printf("Error: Cannot open file ");
        return 1;
    }

    struct Student students[MAX_STUDENTS];
    int numStudents = 0;
    while (fscanf(file, "%s %d", students[numStudents].name, &students[numStudents].score) != EOF) {
        printf("Student %d: %s, Score = %d\n", numStudents + 1, students[numStudents].name, students[numStudents].score);
        numStudents++;
    }


    fprintf(file2, "%s %d", students[numStudents].name, students[numStudents].score);
    
    if (numStudents == 0) {
        printf("No student scores found in the file.\n");
        }

    fclose(file);
    fclose(file2);

    
    char newStudentsname[100];
    do{
        printf("Enter new student name (type “END” to sort student score and end the program):");
        scanf("%s", newStudentsname);
        if(strcmp(newStudentsname, "END") == 0){
            break;
        } 
          if(numStudents < MAX_STUDENTS){
            stpcpy(students[numStudents].name, newStudentsname);
            numStudents++;
            students[numStudents-1].score = heartsEaten;
        }
        
        else{
            printf("Maximum number of students reached.\n");
        }
    }while (check == 0);
    insertionSort(students, numStudents);
    printf("---------------Sort students by scores---------------\n");
    for(int i = 0; i < numStudents; i++){
        printf("Student %d: %s, Score = %d\n", i+1, students[i].name, students[i].score);
    }
    

    writeToFile(students, numStudents, outputFileName);
    printf("End of program. Goodbye.\n");
    return 0;
}

int main() {
    option = 0;
    Run();
    play();
    return 0;
}