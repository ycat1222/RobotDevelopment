#include "Attack.hpp"

void BBB::attack()
{
	using namespace std;

	auto startTime = chrono::high_resolution_clock::now();

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

	//通過済みのマスの情報が入った配列(初期ではfalse)
	vector<vector<bool>> passedMap(Map::MAP_SIZE, vector<bool>(Map::MAP_SIZE, false));

	//それぞれの方向の壁がないマスの数
	array<unsigned int, 4> numBlankCell = { 0,0,0,0 };

	//壁に阻まれず、かつ、ボーナスマスがあるときの方向
	array<bool, 4> bounusDirection = { false, false, false, false };

	// 敵がいる方向
	array<bool, 4> entityDirection = { false, false, false, false };

	//それぞれの方向の得点した壁までのマスの数
	array<int, 4> numPassedCell = { 0,0,0,0 };

	// 180秒たったら終了
	while (chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now() - startTime).count() > 180) {

		unsigned int x = robot.x() / Map::CELL_SIZE;
		unsigned int y = robot.y() / Map::CELL_SIZE;

		numBlankCell = { 0,0,0,0 };
		bounusDirection = { false, false, false, false };
		entityDirection = { false, false, false, false };
		numPassedCell = { 0,0,0,0 };

		cout << robot.x() << ", " << robot.y() << endl;

		passedMap[x][y] = true;

		//それぞれの方向の壁がないマスの数を取得
		for (int xi = x + 1; xi < Map::MAP_SIZE; xi++)
			if (map[xi][y].east == 0) numBlankCell[east]++;

		for (int xi = x - 1; xi > 0; xi--)
			if (map[xi][y].west == 0) numBlankCell[west]++;

		for (int yi = y + 1; yi < Map::MAP_SIZE; yi++)
			if (map[x][yi].north == 0) numBlankCell[north]++;

		for (int yi = y - 1; yi > 0; yi--)
			if (map[x][yi].south == 0) numBlankCell[south]++;

		//壁がない=まっすぐ進めるマスが一番多い方向を取得
		auto maxItr = max_element(numBlankCell.begin(), numBlankCell.end());
		auto maxBlankDirection = distance(numBlankCell.begin(), maxItr);


		//壁に阻まれず、かつ、ボーナスマスがあるときの方向を取得
		if (map[x][y].east == false && map[x + 1][y].isBonus)
			bounusDirection[east] = true;

		if (map[x][y].west == false && map[x - 1][y].isBonus)
			bounusDirection[west] = true;

		if (map[x][y].north == false && map[x][y + 1].isBonus)
			bounusDirection[north] = true;

		if (map[x][y].south == false && map[x][y - 1].isBonus)
			bounusDirection[south] = true;


		// 敵がいる方向の判定 (その方向に壁がないのに、明らかに距離が近い場合)
		if (map[x][y].east == false && robot.distanceEast() < Map::CELL_SIZE)
			entityDirection[east] = true;

		else if (map[x][y].west == false && robot.distanceWest() < Map::CELL_SIZE)
			entityDirection[west] = true;

		else if (map[x][y].north == false && robot.distanceNorth() < Map::CELL_SIZE)
			entityDirection[north] = true;

		else if (map[x][y].south == false && robot.distanceSouth() < Map::CELL_SIZE)
			entityDirection[south] = true;


		//それぞれの方向の得点した壁までのマスの数を取得
		for (int xi = x + 1; xi < x + numBlankCell[east]; xi++)
			if (passedMap[xi][y]) numPassedCell[east]++;

		for (int xi = x - 1; xi > x - numBlankCell[west]; xi--)
			if (passedMap[xi][y]) numPassedCell[west]++;

		for (int yi = y + 1; yi < y + numBlankCell[north]; yi++)
			if (passedMap[x][yi]) numPassedCell[north]++;

		for (int yi = y - 1; yi > y - numBlankCell[south]; yi--)
			if (passedMap[x][yi]) numPassedCell[south]++;

		// すでに通ったマスが一番少ない(得点を取れる)方向 を取得
		auto minItr = min_element(numPassedCell.begin(), numPassedCell.end());
		auto minPassedDirection = distance(numPassedCell.begin(), minItr);


		/*方向の優先順位について

			基本方針 : 敵から逃げつつ、できるだけ多くのマスを通過する

			0. 敵のいる方向には行かない
			1. まだ通っていないボーナスがあるマスへ行く
			2. まだ通っていないマスへ行く
			3. まっすぐ(一番壁までの距離が長い方向へ)進む
		*/

		for (auto d = 0; d < 4; d++) {
			//敵がいない方向で
			if (entityDirection[d] == false) {
				//ボーナスがあるなら、その方向へ
				if (bounusDirection[d]) {
					if (d == east) robot.moveEast(Map::CELL_SIZE);
					if (d == west) robot.moveWest(Map::CELL_SIZE);
					if (d == north) robot.moveNorth(Map::CELL_SIZE);
					if (d == south) robot.moveSouth(Map::CELL_SIZE);
					passedMap[x][y] = true;
					continue;
				}

				//その方向が壁ではなく、かつ、ボーナスがないなら、まだ通ってないマスへ
				if (numBlankCell[east] > 0 && minPassedDirection == east) robot.moveEast(Map::CELL_SIZE);
				else if (numBlankCell[west] > 0 && minPassedDirection == west) robot.moveWest(Map::CELL_SIZE);
				else if (numBlankCell[north] > 0 && minPassedDirection == north) robot.moveNorth(Map::CELL_SIZE);
				else if (numBlankCell[south] > 0 && minPassedDirection == south) robot.moveSouth(Map::CELL_SIZE);
				else {
					//まだ通っていないマスがなければ、一番 壁までが長いとこへすすむ
					if (maxBlankDirection == east) robot.moveEast(Map::CELL_SIZE);
					else if (maxBlankDirection == west) robot.moveWest(Map::CELL_SIZE);
					else if (maxBlankDirection == north) robot.moveNorth(Map::CELL_SIZE);
					else if (maxBlankDirection == south) robot.moveSouth(Map::CELL_SIZE);
				}
				passedMap[x][y] = true;
			}
		}

	} //while終わり
	
	// 180秒後、停止
	robot.setDutyRate(0.0);
}
