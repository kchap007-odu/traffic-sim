#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()
#include <ostream>      // std::flush
#include <fstream>
#include "Road.h"
/*
    Global identifiers are allowed as long as they are constants,
    see https://www.blackboard.odu.edu/webapps/discussionboard/do/message?action=list_messages&course_id=_358374_1&nav=discussion_board_entry&conf_id=_400767_1&forum_id=_376375_1&message_id=_8971005_1
*/
const int SLEEP_DURATION_MS = 100;
// This should not be changed. There is only support for three lanes in the road structure.
const int ROWS = 5;
// Both of constants below can be changed to test the program logic.
const int COLS = 40;
const int LIGHT_LOCATION = 10;
// Change the appearance of characters if desired.
const char CAR_CHAR = 'O';
const char ROAD_CHAR = ' ';
const char LINE_CHAR = '-';

void Operate(char[][COLS], int, int);
void ResetGrid(char[][COLS], int, int);
void SetGrid(char[][COLS], int, int);
void PrintGrid(char[][COLS], char, int, int);
void InitializeGrid(char[][COLS], int, int);
void LoadCarsOnGrid(char[][COLS], Road*, int, int);
void InitializeCars(Road&);

int main() {
    char grid[ROWS][COLS];

    srand(time(NULL));
    Operate(grid, ROWS, COLS);

    return 0;
}

void ResetGrid(char grid[][COLS], int rows, int cols) {
    // Flattened nested for loop.
    for (int i = rows; i < (rows-1)*cols; i++)
        grid[(i % (rows - 2) + 1)][i%cols] = ROAD_CHAR;
}

void SetGrid(char grid[][COLS], int rows, int cols) {
    for (int i = 0; i < cols; i++)
        grid[0][i] = grid[4][i] = LINE_CHAR;
}

void PrintGrid(char grid[][COLS], char light, int rows, int cols) {
    grid[0][LIGHT_LOCATION] = grid[4][LIGHT_LOCATION] = light;

    CLEAR_WINDOW;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            cout << grid[i][j];
        cout << endl;
    }
}

void LoadCarsOnGrid(char grid[][COLS], Road *road, int rows, int cols) {
    int r, c;

    ResetGrid(grid, rows, cols);

    for (int i = 0; i < MAX_CARS; i++) {
        // Rows and columns were reversed.
        c = road->GetCarX(i);
        r = road->GetCarY(i);
        if (r != -1 && c != -1)
            grid[r][c] = CAR_CHAR;
    }
}

void Operate(char grid[][COLS], int rows, int cols) {
    Road road;
    int loopIndex = 0;

    SetGrid(grid, rows, cols);
    ResetGrid(grid, rows, cols);

    while (true) {
        road.GenerateCars(COLS);
        road.MoveCars(LIGHT_LOCATION);
        LoadCarsOnGrid(grid, &road, rows, cols);
        road.AdjustLight(loopIndex);
        PrintGrid(grid, road.GetLight(), rows, cols);
        loopIndex++;
        SLEEP(SLEEP_DURATION_MS);
    }
}