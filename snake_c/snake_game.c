#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <malloc.h>
#include <stdbool.h>
#include <curses.h>
// #include <conio.h>

#define SIZE 20
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

// 2d array to represent game board
char **board;

// keeping track of snake length
int length;

// keeping track of snake's direction
int direction;

// keeping track of game status
bool game;

// semaphore to control game board
sem_t sem;

// typedef struct coordinates {
//     int x;
//     int y;
//     bool head;
//     bool tail;
//     struct coordinates *next;
// } coords;

typedef struct coordinates {
    int row;
    int col;
} coords;

// // head of the snake 
// coords head;

// // tail of the snake
// coords tail;

// // keeping track of snake
// coords **snake;

void print() {
    system( "clear" );
    if ( game ) {
        for ( int i = 0; i < SIZE + 2; i++ ) {
            printf( "%s", "* " );
        }
        printf( "%c", '\n' );
        for ( int i = 0; i < SIZE; i++ ) {
            printf( "%s", "* " );
            for ( int j = 0; j < SIZE; j++ ) {
                if ( !board[ i ][ j ] || board[ i ][ j ] == 0 ) {
                    printf( "%s", "  " );
                } else {
                    printf( "%c ", board[ i ][ j ] );
                }
            }
            printf( "%s", "*\n" );
        }
        for ( int i = 0; i < SIZE + 2; i++ ) {
            printf( "%s", "* " );
        }
        printf( "%c", '\n' );
    } else {
        printf( "%s%d%s", "GAME OVER\nScore: ", length, "\n" );
    }
}

void freeBoard() {
    for ( int i = 0; i < SIZE; i++ ) {
        free( board [ i ] );
    }
    free( board ); 
    // free( snake );
}

// void moveSnake() {

// }

int main() {
    board = malloc( sizeof( char * ) * SIZE );
    for ( int i = 0; i < SIZE; i++ ) {
        board[ i ] = calloc( SIZE, sizeof( char ) );
    }
    // snake = malloc( sizeof( coords ) * SIZE * SIZE );
    length = 1;
    direction = RIGHT;
    // coords *head = {9, 9, true, true, NULL };
    // snake = head;
    coords head = { 9, 9 };
    coords tail = { 9, 9 };
    board[ head.row ][ head.col ] = 'O';
    char command;
    // WINDOW *scr = initscr();
    // cbreak();
    nodelay( stdscr, TRUE );
    game = true;
    while( game ) {
        sleep( 1 );
        if ( ( command = getch() ) != -1 ) {
            if ( command == 'q' ) {
                game = false;
                break;
            } else if ( command == KEY_UP ) {
                direction = UP;

            } else if ( command == KEY_DOWN ) {
                direction = DOWN;
                
            } else if ( command == KEY_LEFT ) {
                direction = LEFT;
                
            } else if ( command == KEY_RIGHT ) {
                direction = RIGHT;
            }
        }
        // int prev_row, prev_y;
        if ( head.row > SIZE - 2 || head.col > SIZE - 2 ) {
            game = false;
        } else if ( direction == UP ) {
            if ( board[ head.row - 1 ][ head.col ] == '@' ) {
                length++;
                board[ --head.row ][ head.col ] = 'O';
                continue;
            } else if ( board[ head.row - 1 ][ head.col ] == 'O' ) {
                sem_wait( &sem );
                game = false;
                sem_post( &sem );
            }
            // current = current->nerowt;
            // for ( int i = 0; current && i < length; i++ ) {
            //     board[ current.x ][ current.y ] = 
            // }
            board[ --head.row ][ head.col ] = 'O';
            board[ tail.row-- ][ tail.col ] = 0;
        } else if ( direction == DOWN ) {
            if ( board[ head.row + 1 ][ head.col ] == '@' ) {
                length++;
                board[ ++head.row ][ head.col ] = 'O';
                continue;
            } else if ( board[ head.row + 1 ][ head.col ] == 'O' ) {
                sem_wait( &sem );
                game = false;
                sem_post( &sem );
            }
            board[ ++head.row ][ head.col ] = 'O';
            board[ tail.row++ ][ tail.col ] = 0;
        } else if ( direction == LEFT ) {
            if ( board[ head.row ][ head.col - 1 ] == '@' ) {
                length++;
                board[ head.row ][ head.col-- ] = 'O';
                continue;
            } else if ( board[ head.row ][ head.col - 1 ] == 'O' ) {
                sem_wait( &sem );
                game = false;
                sem_post( &sem );
            }
            board[ head.row ][ --head.col ] = 'O';
            board[ tail.row ][ tail.col-- ] = 0;
        } else if ( direction == RIGHT ) {
            if ( board[ head.row ][ head.col + 1 ] == '@' ) {
                length++;
                board[ head.row ][ ++head.col ] = 'O';
                continue;
            } else if ( board[ head.row ][ head.col + 1 ] == 'O' ) {
                sem_wait( &sem );
                game = false;
                sem_post( &sem );
            }
            board[ head.row ][ ++head.col ] = 'O';
            board[ tail.row ][ tail.col++ ] = 0;
        }
        print();
        // sleep( 2 );
    }
    freeBoard();
}
