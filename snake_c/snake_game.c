/**
 * This is a Snake Game written in C.
 * It uses a row, col system to represent a board environment for the snake to move around in.
 * This implementation utilizes the curses library which allows user input to be read immediately
 * and the game to be printed in a nice format.
 *
 * Author: Minji Kang
 */

// for usleep
#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <malloc.h>
#include <stdbool.h>
#include <curses.h>
#include <time.h>

// Size of the game board
#define SIZE 20
// Constants to keep track of the snake direction
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

// 2d array to represent game board
char **board;

// keeping track of game score
int score;

// keeping track of snake's direction
int direction;

// keeping track of game status
bool game;

// Using a struct to keep track of "coordinates" or locations of the board
typedef struct coordinates
{
    int row;
    int col;
} coords;

/**
 * Function that prints out the board. Gets called every second to update the screen.
 */
void printGame()
{
    // Clearing the screen
    erase();
    // Checking that the game is not over
    if (game)
    {
        // Printing the top row of *
        for (int i = 0; i < SIZE + 2; i++)
        {
            printw("%s", "* ");
        }
        printw("%c", '\n');
        // Printing the current state of the game board
        for (int i = 0; i < SIZE; i++)
        {
            printw("%s", "* ");
            for (int j = 0; j < SIZE; j++)
            {
                // Checking for snake parts and printing as appropriate
                if (!board[i][j] || board[i][j] == 0)
                {
                    printw("%s", "  ");
                }
                else
                {
                    printw("%c ", board[i][j]);
                }
            }
            printw("%s", "*\n");
        }
        // Printing bottom row of *
        for (int i = 0; i < SIZE + 2; i++)
        {
            printw("%s", "* ");
        }
        printw("%c", '\n');
        // Refreshing window to reveal the current board to user
        refresh();
    }
    else
    {
        // Game is over, closing window and printing score
        endwin();
        clear();
        printf("%s%d%s", "GAME OVER\nScore: ", score, "\n");
    }
}

/**
 * Since the board was malloc'ed, it needs to be freed
 */
void freeBoard()
{
    for (int i = 0; i < SIZE; i++)
    {
        free(board[i]);
    }
    free(board);
}

/**
 * Main function that deals with the bulk of the game
 */
int main()
{
    // Getting memory for the board
    board = malloc(sizeof(char *) * SIZE);
    for (int i = 0; i < SIZE; i++)
    {
        board[i] = calloc(SIZE, sizeof(char));
    }
    // Initializing variables needed to start
    score = 0;
    direction = RIGHT;
    coords head = {9, 9};
    board[head.row][head.col] = 'O';
    int command = -1;
    game = true;
    bool appleReached = true;
    int appleRow;
    int appleCol;
    // Initializing the stdscr which allows for a cleaner user experience
    initscr();
    // Does not need to echo user input
    noecho();
    // Read in user input right away
    nodelay(stdscr, true);
    // Allows arrow keys to be processed
    keypad(stdscr, true);
    // setting random seed
    srand(time(0));
    while (game)
    {
        // sleeping for half a second
        usleep(500000);
        // seeing if new apple needs to be generated
        if (appleReached)
        {
            appleRow = rand() % SIZE;
            appleCol = rand() % SIZE;
            while (board[appleRow][appleCol] != 0)
            {
                appleRow = rand() % SIZE;
                appleCol = rand() % SIZE;
            }
            board[appleRow][appleCol] = '@';
            appleReached = false;
        }
        // Getting user command
        if ((command = wgetch(stdscr)) != -1)
        {
            if (command == 'q')
            {
                game = false;
                endwin();
                clear();
                break;
            }
            else if (command == KEY_UP)
            {
                direction = UP;
            }
            else if (command == KEY_DOWN)
            {
                direction = DOWN;
            }
            else if (command == KEY_LEFT)
            {
                direction = LEFT;
            }
            else if (command == KEY_RIGHT)
            {
                direction = RIGHT;
            }
        }
        // Seeing if the snake is within bounds
        if (head.row > SIZE - 1 || head.col > SIZE - 1 || head.row < 1 || head.col < 1)
        {
            game = false;
        }
        else if (direction == UP)
        {
            if (board[head.row - 1][head.col] == '@')
            {
                score++;
                appleReached = true;
            }
            else if (board[head.row - 1][head.col] == 'O')
            {
                game = false;
            }
            board[head.row][head.col] = 0;
            head.row--;
            board[head.row][head.col] = 'O';
        }
        else if (direction == DOWN)
        {
            if (board[head.row + 1][head.col] == '@')
            {
                score++;
                appleReached = true;
            }
            else if (board[head.row + 1][head.col] == 'O')
            {
                game = false;
            }
            board[head.row][head.col] = 0;
            head.row++;
            board[head.row][head.col] = 'O';
        }
        else if (direction == LEFT)
        {
            if (board[head.row][head.col - 1] == '@')
            {
                score++;
                appleReached = true;
            }
            else if (board[head.row][head.col - 1] == 'O')
            {
                game = false;
            }
            board[head.row][head.col] = 0;
            head.col--;
            board[head.row][head.col] = 'O';
        }
        else if (direction == RIGHT)
        {
            if (board[head.row][head.col + 1] == '@')
            {
                score++;
                appleReached = true;
            }
            else if (board[head.row][head.col + 1] == 'O')
            {
                game = false;
            }
            board[head.row][head.col] = 0;
            head.col++;
            board[head.row][head.col] = 'O';
        }
        printGame();
    }
    freeBoard();
    return 0;
}
