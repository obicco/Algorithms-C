//
//  main.c
//  Lab09es2
//
//  Created by Oskar Bich on 21/12/20.
//

#include <stdio.h>
#include <stdlib.h>
#define T_FN "tiles.txt"
#define B_FN "board.txt"

typedef struct {
    char c1, c2;
    int v1, v2;
    int rot;
    int us;
} tiles_t;

typedef struct {
    tiles_t ***t;
    char *r_row;
    char *r_col;
    int r, c;
} board_t;

tiles_t *readTiles(char *fname, int *T);
board_t *readBoard(char *fname, tiles_t *tiles);
void printTile(tiles_t *t);
void printBoard(board_t *board);
void populate(board_t *board, tiles_t *tiles, int T);
void tileR (tiles_t *tiles, tiles_t **best_tile, char r_col, char c_col, int T, int pos);

int main(int argc, const char * argv[]) {
    int T;
    tiles_t *tiles = readTiles(T_FN, &T);
    board_t *board = readBoard(B_FN, tiles);
    
    printf("\t\t- INITIAL STATE -\n");
    printBoard(board);
    printf("\nTILES LIST:\n");
    for (int i = 0; i < T; i++) {
        printf("%d - ", i);
        printTile(&tiles[i]);
        printf("\n");
    }
    
    populate(board, tiles, T);
    printf("\n\n\t\t- END STATE -\n");
    printBoard(board);
    printf("\nTILES LIST:\n");
    for (int i = 0; i < T; i++) {
        printf("%d - ", i);
        printTile(&tiles[i]);
        printf("\n");
    }
    return 0;
}

void populate(board_t *board, tiles_t *tiles, int T) {
    for (int i = 0; i < board->r; i++) {
        for (int j = 0; j < board->c; j++) {
            if (board->t[i][j] == NULL)
                tileR(tiles, &board->t[i][j], board->r_row[i], board->r_col[j], T, 0);
            if (i == 2 && j == 1)
                continue;
        }
    }
}

// To-Do: Optimization for best same color value - missunderstood statement
//  (Currently best overall value)
void tileR (tiles_t *tiles, tiles_t **best_tile, char r_col, char c_col, int T, int pos) {
    if (pos > T)
        return;
    if (tiles[pos].us != 1 && (tiles[pos].c1 == r_col || tiles[pos].c2 == c_col)) {
        if (*best_tile == NULL) {
            *best_tile = &tiles[pos];
            tiles[pos].us = 1;
        } else
            if (tiles[pos].v1 > (*best_tile)->v1) {
                (*best_tile)->us = 0;
                *best_tile = &tiles[pos];
                tiles[pos].us = 1;
            }
    }
    if (tiles[pos].us != 1 && (tiles[pos].c1 == c_col || tiles[pos].c2 == r_col)) {
        if (*best_tile == NULL) {
            *best_tile = &tiles[pos];
            tiles[pos].us = 1;
            tiles[pos].rot = 1;
        } else
            if (tiles[pos].v1 > (*best_tile)->v1) {
                (*best_tile)->us = 0;
                *best_tile = &tiles[pos];
                tiles[pos].us = 1;
                tiles[pos].rot = 1;
            }
    }
    tileR(tiles, best_tile, r_col, c_col, T, pos+1);
}

void printBoard(board_t *board) {
    for (int i = 0; i < board->r; i++) {
        for (int j = 0; j < board->c; j++) {
            if (board->t[i][j] == NULL) {
                printf("- 0 - 0 0 0\t");
            } else printTile(board->t[i][j]);
            printf("\t");
        }
        printf("Row colour %c", board->r_row[i]);
        printf("\n");
    }
    for (int i = 0; i < board->c; i++) {
        printf("Column %c\t\t", board->r_col[i]);
    }
}

tiles_t *readTiles(char *fname, int *T) {
    FILE *fp = fopen(fname, "r");
    if (fp == NULL)
        exit(-1);
    fscanf(fp, "%d", T);
    tiles_t *t = calloc(*T, sizeof(tiles_t));
    for (int i = 0; i < *T; i++) {
        fscanf(fp, "%s%d%s%d", &t[i].c1, &t[i].v1, &t[i].c2, &t[i].v2);
    }
    return t;
}

board_t *readBoard(char *fname, tiles_t *tiles) {
    board_t *board = calloc(1, sizeof(board_t));
    int index, rot;
    FILE *fp = fopen(fname, "r");
    if (fp == NULL)
        exit(-1);
    fscanf(fp, "%d%d", &board->r, &board->c);
    board->t = calloc(board->r, sizeof(tiles_t**));
    board->r_row = calloc(board->r, sizeof(char));
    board->r_col = calloc(board->c, sizeof(char));
    for (int i = 0; i < board->r; i++) {
        board->t[i] = calloc(board->c, sizeof(tiles_t*));
        for (int j = 0; j < board->c; j++) {
            fscanf(fp, "%d/%d", &index, &rot);
            if (index != -1 && rot != -1) {
                board->t[i][j] = &tiles[index];
                tiles[index].rot = rot;
                tiles[index].us = 1;
                if (board->r_row[i] == '\0') {
                    if (rot == 0)
                        board->r_row[i] = board->t[i][j]->c1;
                    else board->r_row[i] = board->t[i][j]->c2;
                }
                if (board->r_col[j] == '\0') {
                    if (rot == 0)
                        board->r_col[j] = board->t[i][j]->c2;
                    else board->r_col[j] = board->t[i][j]->c1;
                }
            }
        }
    }
    return board;
}

void printTile(tiles_t *tile) {
    fprintf(stdout, "%c %d %c %d %d %d ", tile->c1, tile->v1, tile->c2, tile->v2, tile->us, tile->rot);
}
