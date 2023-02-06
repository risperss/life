#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

const int WIDTH = 204;
const int HEIGHT = 63;

int* create_array() {
    int* arr = calloc(WIDTH * HEIGHT, sizeof(int));

    return arr;
}

void destroy_array(int* arr) { free(arr); }

/*
1 2 3
4 i 6
7 8 9

1: i - WIDTH - 1
2: i - WIDTH
3: i - WIDTH + 1
4: i - 1
6: i + 1
7: i + WIDTH - 1
8: i + WIDTH
9: i + WIDTH + 1
*/

int num_neighbours(int* board, int idx) {
    const int coords[] = {-WIDTH - 1, -WIDTH,    -WIDTH + 1, -1,
                          +1,         WIDTH - 1, WIDTH,      WIDTH + 1};
    int n = 0;

    for (int i = 0; i < 8; i++) {
        int n_index = idx + coords[i];

        if (n_index >= 0 && n_index < WIDTH * HEIGHT) {
            if (board[n_index]) {
                n++;
            }
        }
    }

    return n;
}

int should_live(int* board, int idx) {
    int n = num_neighbours(board, idx);

    if (board[idx] && (n == 2 || n == 3)) {
        return 1;
    }
    if (!board[idx] && n == 3) {
        return 1;
    }

    return 0;
}

int* apply_generation(int* board) {
    int* new_board = create_array();

    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        if (should_live(board, i)) {
            new_board[i] = 1;
        }
    }

    destroy_array(board);

    return new_board;
}

void print_board(int* board) {
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        if (board[i]) {
            printf("%d", board[i]);
        } else {
            printf(" ");
        }

        if (i % WIDTH == WIDTH - 1) {
            printf("\n");
        }
    }
}

void seed(int* board) {
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        board[i] = rand() % 2;
    }
}

int main(void) {
    time_t t;
    int n;
    int* board;

    srand((unsigned)time(&t));

    board = create_array();
    seed(board);
    board = apply_generation(board);

    for (int g = 0; g < 100; g++) {
        board = apply_generation(board);
        print_board(board);

        sleep(1);
        system("clear");
    }

    destroy_array(board);

    return 0;
}