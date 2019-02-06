#include "Defence.hpp"

void BBB::defence()
{
    using namespace std;

    auto startTime = chrono::high_resolution_clock::now();
    std::random_device rnd;

	RobotController robot;
	robot.initPosition(15, 15);
	robot.initMotorGPIO(60, 61, 65, 46);
	robot.initMotorPWM(14, 22);
	robot.initSensorGPIO(27, 47, 115, 45);
	robot.setDutyRate(0.55);
    Map map("field.txt");
	enum Direction
	{
		east = 0,
		west = 1,
		south = 2,
		north = 3,
	};

    array<bool, 4> entityDirection = { false, false, false, false };

	auto x=5;
	auto y=5;
	for(auto j = 0; j < 4; j++){
		robot.moveWest(Map::CELL_SIZE);
		x--;
	}

   while (chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now() - startTime).count() > 180) {

        auto flag = rand() % 4;

		entityDirection = { false, false, false, false };

		cout << x << ", " << y << endl;

		if (map[x][y].east == false && robot.distanceEast() < Map::CELL_SIZE)
			entityDirection[east] = true;

		else if (map[x][y].west == false && robot.distanceWest() < Map::CELL_SIZE)
			entityDirection[west] = true;

		else if (map[x][y].north == false && robot.distanceNorth() < Map::CELL_SIZE)
			entityDirection[north] = true;

		else if (map[x][y].south == false && robot.distanceSouth() < Map::CELL_SIZE)
			entityDirection[south] = true;


        for (auto i = 0; i < 4; i++){
            if (entityDirection[i] == true){
                if (i == east){
					robot.moveEast(Map::CELL_SIZE);
					x++;
				}
				if (i == west){ 
					robot.moveWest(Map::CELL_SIZE);
					x--;
				}
				if (i == north){ 
					robot.moveNorth(Map::CELL_SIZE);
					y++;
				}
				if (i == south){
					robot.moveSouth(Map::CELL_SIZE);
					y--;
				}
            }
            else if (i == flag){
                if (i == east){
					robot.moveEast(Map::CELL_SIZE);
					x++;
				}
				if (i == west){ 
					robot.moveWest(Map::CELL_SIZE);
					x--;
				}
				if (i == north){ 
					robot.moveNorth(Map::CELL_SIZE);
					y++;
				}
				if (i == south){
					robot.moveSouth(Map::CELL_SIZE);
					y--;
				}
            }
        }
	}
	robot.setDutyRate(0.0);
}