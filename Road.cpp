#include "Road.h"

Road::Road(){
    light = 'R';
    for (int i = 0; i < MAX_CARS; i++)
        cars[0][i] = cars[1][i] = -1;
    numCars = 0;
    carsInRightLane = 0;
    carsInCenterLane = 0;
    carsInLeftLane = 0;
}

void Road::GenerateCars(int cols) {
    int spawnRow = (rand() % 3) +1;
    int spawnCol = cols-1;
    /*
        There are three conditions under which a car will not be spawned:
        1. The maximum number of cars is already on the road.
        2. The randomly selected lane is full.
        3. The random condition (rand_number < 3) is not met.
    */
    if ((!(numCars < MAX_CARS)) || !IsLaneOpen(spawnRow) || ((rand() % 10) > 3))
        return;

    /*
        The car will be spawned in the first free entry on the list. If there
        is a free spot on the road, there should never be a case where this
        index is not valid, so it shouldn't need to be checked.
    */
    int spawnIdx = -1;
    for (int i = 0; i < MAX_CARS; i++)
        if (cars[0][i] == -1 && cars[1][i] == -1) {
            spawnIdx = i;
            break;
        }

    // Check whether a car already exists at the spawn location.
    for (int i = 0; i < MAX_CARS; i++)
        if (cars[0][i] == spawnRow && cars[1][i] == spawnCol)
            return;

    // It should be safe to spawn the car at the chosen location.
    cars[0][spawnIdx] = spawnCol;
    cars[1][spawnIdx] = spawnRow;
    AddOrRemoveCarsFromRoad(spawnRow, 1);
}

void Road::MoveCars(int lightLocation) {
    for (int i = 0; i < MAX_CARS; i++) {
        /*
            There are three conditions where the horizontal position
            of any given piece should not be decremented:
            1. The car is not on the road.
            2. There is a car on the left (in front) of the current car.
            3. The car should be stopped at the light.
        */
        if ((!IsCarOnRoad(i)) || (IsCarOnLeft(i)) || (IsCarStoppedAtLight(i, lightLocation)))
            continue;

        // If we got here, all conditions under which the car should move have been met.
        cars[0][i]--;

        // If moving resulted in the car leaving the road, it should be removed.
        if (!IsCarOnRoad(i)) {
            AddOrRemoveCarsFromRoad(cars[1][i], -1);
            cars[0][i] = cars[1][i] = -1;
        }
    }
}

bool Road::IsCarOnRoad(int i) {
    // Car is considered to be on the road if the x coordinate is greater than or equal to zero.
    return cars[0][i] >= 0;
}

bool Road::IsCarOnLeft(int carIndex) {
    // Rows and columns were reversed.
    int c = cars[0][carIndex];
    int r = cars[1][carIndex];
    for (int i = 0; i < MAX_CARS; i++) {
        // Rows and columns were reversed.
        if ((cars[0][i]+1 == c && cars[1][i] == r) && (i != carIndex))
            return true;
    }
    return false;
}

bool Road::IsCarStoppedAtLight(int i, int lightLocation) {
    return ((light == 'R') && (GetCarX(i) == lightLocation + 1));
}

bool Road::IsLaneOpen(int lane) {
    switch (lane) {
        case 1:
            return carsInRightLane < maxCarsInRightLane;
        case 2:
            return carsInCenterLane < maxCarsInCenterLane;
        case 3:
            return carsInLeftLane < maxCarsInLeftLane;
        default:
            return false;
    }
}

void Road::AddOrRemoveCarsFromRoad(int lane, int addOrRemove) {

    switch (lane) {
        case 1:
            carsInRightLane += addOrRemove;
            break;
        case 2:
            carsInCenterLane += addOrRemove;
            break;
        case 3:
            carsInLeftLane += addOrRemove;
            break;
        default:
            return;
    }
    numCars += addOrRemove;
}

void Road::AdjustLight(int index) {
    if ((index % SWITCH_AFTER_N_TURNS) == 0)
        light == 'R' ? light = 'G' : light = 'R';
}

char Road::GetLight() {
   return light;
}

int Road::GetCarX(int i) {
    return cars[0][i];
}

int Road::GetCarY(int i) {
    return cars[1][i];
}