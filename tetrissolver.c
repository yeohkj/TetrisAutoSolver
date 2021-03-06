#include <stdio.h>
#include <stdint.h>
#include <string.h>


#define BOARD_HEIGHT 25
#define BOARD_WIDTH 6

// 0 = Hard, 1 = Easy
const int EASY = 1;

// 0 = No-rotation, 1 = rotation
const int ROTATION = 0;

uint8_t tetrominoes[7][4][4][4] = {
    { //I
        {
            {1, 1, 1, 1},
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        }, {
            {1, 0, 0, 0},
            {1, 0, 0, 0},
            {1, 0, 0, 0},
            {1, 0, 0, 0}
        }
    },
    { //O
        {
            {1, 1, 0, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        }
    },
    { //T
        {
            {1, 1, 1, 0},
            {0, 1, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        }, {
            {1, 0, 0, 0},
            {1, 1, 0, 0},
            {1, 0, 0, 0},
            {0, 0, 0, 0}
        }, {
            {0, 1, 0, 0},
            {1, 1, 1, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        }, {
            {0, 1, 0, 0},
            {1, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 0, 0}
        }
    },
    { //J
        {
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0}
        }, {
            {1, 0, 0, 0},
            {1, 1, 1, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        }, {
            {1, 1, 0, 0},
            {1, 0, 0, 0},
            {1, 0, 0, 0},
            {0, 0, 0, 0}
        }, {
            {1, 1, 1, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        }
    },
    { //L
        {
            {1, 0, 0, 0},
            {1, 0, 0, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0}
        }, {
            {1, 1, 1, 0},
            {1, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        }, {
            {1, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 0, 0}
        },  {
            {0, 0, 1, 0},
            {1, 1, 1, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        }
    },
    { //S
        {
            {0, 1, 1, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        }, {
            {1, 0, 0, 0},
            {1, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 0, 0}
        }
    },
    { //Z
        {
            {1, 1, 0, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        }, {
            {0, 1, 0, 0},
            {1, 1, 0, 0},
            {1, 0, 0, 0},
            {0, 0, 0, 0}
        }
    }
};


uint8_t board[BOARD_HEIGHT][BOARD_WIDTH];

uint8_t final_board[BOARD_HEIGHT][BOARD_WIDTH];

int min_height = BOARD_HEIGHT;

int piece_in_row(uint8_t board[BOARD_HEIGHT][BOARD_WIDTH], int y) {
    int total = 0;

    for (int i = 0; i < BOARD_WIDTH; i++) {
        total += board[y][i];
    }

    return total;
}

int tetris_height(uint8_t board[BOARD_HEIGHT][BOARD_WIDTH]) {
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        if (!piece_in_row(board, i)) return i;
    }

    return BOARD_HEIGHT;
}


void copy_board(uint8_t a[BOARD_HEIGHT][BOARD_WIDTH], uint8_t b[BOARD_HEIGHT][BOARD_WIDTH]) {

    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            b[i][j] = a[i][j];
        }
    }
}

int max_right_index(uint8_t tetromino[4][4]) {
    int max_right = 0;

    for (size_t i = 0; i < 4; i++)
    {   
        for (size_t j = 0; j < 4; j++)
        {
            if (tetromino[i][j] == 1 && j > max_right) max_right = j;
        }

    }

    return max_right;
}

int max_bottom_index(uint8_t tetromino[4][4]) {
    int max_bottom = 0;

    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            if (tetromino[i][j] == 1 && i > max_bottom) max_bottom = i;
        }
    }

    return max_bottom;
}

int block_height(uint8_t tetromino[4][4]) {
    return max_bottom_index(tetromino) + 1;
}

int block_width(uint8_t tetromino[4][4]) {
    return max_right_index(tetromino) + 1;
}

int tetromino_inside_board(uint8_t board[BOARD_HEIGHT][BOARD_WIDTH], uint8_t tetromino[4][4], int x) {
    int block_w = block_width(tetromino);
    if (x + block_w > 6 || x < 0) return 0;

    return 1;
}

int tetromino_collides(uint8_t board[BOARD_HEIGHT][BOARD_WIDTH], uint8_t tetromino[4][4], int x, int y) {
    int block_h = block_height(tetromino);
    int block_w = block_width(tetromino);


    for (int i = 0; i < block_h; i++) {
        for (int j = 0; j < block_w; j++) {
            if (board[i + y][j + x] != 0 && tetromino[i][j] != 0) return 1;
        }
    }

    return 0;
}


void place_on_board(uint8_t board[BOARD_HEIGHT][BOARD_WIDTH], uint8_t tetromino[4][4], int x, int y) {
    int block_h = block_height(tetromino);
    int block_w = block_width(tetromino);


    for (int i = 0; i < block_h; i++) {
        for (int j = 0; j < block_w; j++) {
            board[i + y][j + x] += tetromino[i][j];
        }
    }
}

void remove_from_board(uint8_t board[BOARD_HEIGHT][BOARD_WIDTH], uint8_t tetromino[4][4], int x, int y) {
    int block_h = block_height(tetromino);
    int block_w = block_width(tetromino);


    for (int i = 0; i < block_h; i++) {
        for (int j = 0; j < block_w; j++) {
            board[i + y][j + x] -= tetromino[i][j];
        }
    }
}

int fall_on_board(uint8_t board[BOARD_HEIGHT][BOARD_WIDTH], uint8_t tetromino[4][4], int x) {
    int y = 0;
    while (tetromino_collides(board, tetromino, x, y)) y++;

    place_on_board(board, tetromino, x, y);
    return y;
}

void print_board(uint8_t board[BOARD_HEIGHT][BOARD_WIDTH]) {

    int height = tetris_height(board) + 2;
    if (height > BOARD_HEIGHT) height = BOARD_HEIGHT;

    for (int i = height - 1; i >= 0; i--)
    {
        for (size_t j = 0; j < BOARD_WIDTH; j++)
        {
            if (board[i][j] == 0) {
                printf(".");
            }
            else {
                printf("#");
            }
            printf(" ");
        }
        printf("\n");
    }

}


int get_puzzle(uint32_t seed, char* buf, int buf_size) {
    const char pieces[] = "IOTJLSZ";
    srand(seed);

    int puzzlesize = seed % 2 ? 4 : 12;
    if (buf_size < puzzlesize) return 0;

    for (int i = 0; i < puzzlesize; i++) {
        buf[i] = pieces[rand() % 7];
    }

    buf[puzzlesize] = 0;

    return 1;
}

int get_tetromino_index(char piece) {
    switch (piece)
    {
    case 'I':
        return 0;

    case 'O':
        return 1;

    case 'T':
        return 2;

    case 'J':
        return 3;

    case 'L':
        return 4;

    case 'S':
        return 5;

    case 'Z':
        return 6;

    default:
        return 0;
    }
}

int get_tetromino_count(char piece) {
    switch (piece)
    {
    case 'I':
        return 2;

    case 'O':
        return 1;

    case 'T':
        return 4;

    case 'J':
        return 4;

    case 'L':
        return 4;

    case 'S':
        return 2;

    case 'Z':
        return 2;

    default:
        return 0;
    }
}



void dfs(uint8_t board[BOARD_HEIGHT][BOARD_WIDTH], char* pieces, int piece_index, int piece_length) {

    if (piece_index >= piece_length) {
        
        int height = tetris_height(board);
        if (height < min_height) {
            copy_board(board, final_board);
            min_height = height;

            /*print_board(board);
            printf("\n\n");*/
        }

        return;
    }

    int tetromino_index = get_tetromino_index(pieces[piece_index]);
    int tetromino_count = get_tetromino_count(pieces[piece_index]);

    if (!ROTATION) tetromino_count = 1;

    for (int rotation_index = 0; rotation_index < tetromino_count; rotation_index++) {
        uint8_t** tetromino = tetrominoes[tetromino_index][rotation_index];

        for (int i = 0; i < BOARD_WIDTH; i++) {
            int height = tetris_height(board);
            if (height > min_height) continue;

            if (tetromino_inside_board(board, tetromino, i)) {
                int y = fall_on_board(board, tetromino, i);

                dfs(board, pieces, piece_index + 1, piece_length);

                remove_from_board(board, tetromino, i, y);
            }
        }
    }

    
}

int main() {

    

    char pieces[20] = "\0";

    get_puzzle(EASY, pieces, 20);

    dfs(board, pieces, 0, strlen(pieces));



    print_board(final_board);


    return 0;
}
