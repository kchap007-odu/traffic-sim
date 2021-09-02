#ifndef ROAD_H
#define ROAD_H
#include "macros.h"
#include <iostream>

using namespace std;
/*
    Global identifiers are allowed as long as they are constants,
    see https://www.blackboard.odu.edu/webapps/discussionboard/do/message?action=list_messages&course_id=_358374_1&nav=discussion_board_entry&conf_id=_400767_1&forum_id=_376375_1&message_id=_8971005_1
*/
// Both of the constants below can be changed to test the program logic.
const int MAX_CARS = 10;
const int SWITCH_AFTER_N_TURNS = 50;

struct Road{
    //public:
        Road();

        void AdjustLight(int);
        void AddOrRemoveCarsFromRoad(int, int);
        void GenerateCars(int);
        void MoveCars(int);

        bool IsCarOnRoad(int);
        bool IsCarOnLeft(int);
        bool IsCarStoppedAtLight(int, int);
        bool IsLaneOpen(int);

        int GetCarX(int);
        int GetCarY(int);
        char GetLight(void);

        char light;
        int cars[2][MAX_CARS];
        int numCars;

        // To keep track of number of cars in each lane.
        int carsInRightLane;
        int carsInCenterLane;
        int carsInLeftLane;

        /*
            From assignment description:
            In the solution, 4 cars are always assigned to row 1, three cars
            to row 2, and three cars to row 3.
        */
        // I am doing this as a percentage of the maximum to allow it to scale.
        const int maxCarsInRightLane = MAX_CARS * 0.4;
        const int maxCarsInCenterLane = MAX_CARS * 0.3;
        const int maxCarsInLeftLane = MAX_CARS * 0.3;
};

#endif // ROAD_H