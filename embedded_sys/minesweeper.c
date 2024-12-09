#include <stdio.h>
#include <string.h>

/*

*/
typedef enum {
    NOT_REVEALED = 0,
    REVEALED = 1,
    MINE = -1
} State;

typedef struct {
    State state;
    int nearestMines;
} Cell;

typedef struct {
    int x;
    int y;
} Coordinate;

#define ROWS 5
#define COLS 5

Cell game[ROWS][COLS];

void updateNearestMines(Coordinate mine){
    Coordinate neighbors[8] = {{0, 1}, {1, 0}, {1, 1}, {-1, -1}, {-1, 1}, {1, -1},{-1, 0}, {0, -1}};

    for(int i = 0; i < 8; i++){
        Coordinate dpos = neighbors[i];
        int nx = mine.x + dpos.x;
        int ny = mine.y + dpos.y;
        if((nx >= 0 && nx < ROWS) && (ny < COLS && ny >= 0)){
            game[nx][ny].nearestMines += 1;
        }
    }
}

void initGame(Coordinate* mines, int numMines){
    for(int row = 0; row < ROWS; row++){
        for(int col = 0; col < COLS; col++){
            game[row][col].state = NOT_REVEALED;
            game[row][col].nearestMines = 0;
        }
    }

    for(int i = 0; i < numMines; i++){
        game[mines[i].x][mines[i].y].state = MINE;
        updateNearestMines(mines[i]);
    }
}

void reveal(Coordinate pos){
    if(game[pos.x][pos.y].state == MINE ){
        return;
    }

    Coordinate neighbors[8] = {{0, 1}, {1, 0}, {1, 1}, {-1, -1}, {-1, 1}, {1, -1},{-1, 0}, {0, -1}};

    for(int i = 0; i < 8; i++){
        Coordinate dpos = neighbors[i];
        int nx = pos.x + dpos.x;
        int ny = pos.y + dpos.y;
        Coordinate nextCoord = {nx, ny};
        
        if((nx >= 0 && nx < ROWS) && (ny < COLS && ny >= 0)){
            game[pos.x][pos.y].state == REVEALED;
            if(game[nx][ny].nearestMines == 0){
                reveal(nextCoord);
            }
        }
    }
}

void userPress(Coordinate pos){
    if(game[pos.x][pos.y].state == MINE){
        print("Game over");
    }
    reveal(pos);
}

