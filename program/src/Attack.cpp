#include "Attack.hpp"

void BBB::attack()
{
	using namespace std;

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
	array<int, 4> numUnPassedCell = { 0,0,0,0 };

	auto startTime = chrono::high_resolution_clock::now();

	// 180秒たったら終了
	while (true) {

		const unsigned int x = robot.x() / Map::CELL_SIZE;
		const unsigned int y = robot.y() / Map::CELL_SIZE;

		numBlankCell.fill(0);
		bounusDirection.fill(false);
		entityDirection.fill(false);
		numUnPassedCell.fill(0);

		cout << x << ", " << y << endl;

		passedMap[x][y] = true;

		//それぞれの方向の壁がないマスの数を取得
		for (int xi = x; xi < Map::MAP_SIZE; xi++) {
			if (!map[xi][y].east) numBlankCell[east]++;
			else break;
		}

		for (int xi = x; xi > 0; xi--) {
			if (!map[xi][y].west) numBlankCell[west]++;
			else break;
		}

		for (int yi = y; yi < Map::MAP_SIZE; yi++){
			if (!map[x][yi].north) numBlankCell[north]++;
			else break;
		}

		for (int yi = y; yi > 0; yi--){
			if (!map[x][yi].south) numBlankCell[south]++;
			else break;
		}

		//壁がない=まっすぐ進めるマスが一番多い方向を取得
		auto maxBlankDirection = distance( numBlankCell.begin(),
			max_element(numBlankCell.begin(), numBlankCell.end()) );

		//for (auto d : numBlankCell)
		//	cout << d << ", ";
		//cout << "maxBlank : " << maxBlankDirection;
		//cout << endl;


		//壁に阻まれず、かつ、まだ通過していなく、かつ、ボーナスマスでの方向を取得
		if (!map[x][y].east && !passedMap[x + 1][y] && map[x + 1][y].isBonus)
			bounusDirection[east] = true;

		if (!map[x][y].west && !passedMap[x - 1][y] && map[x - 1][y].isBonus)
			bounusDirection[west] = true;

		if (!map[x][y].north && !passedMap[x][y + 1] && map[x][y + 1].isBonus)
			bounusDirection[north] = true;

		if (!map[x][y].south && !passedMap[x][y - 1] && map[x][y - 1].isBonus)
			bounusDirection[south] = true;


		// 敵がいる方向の判定 (その方向に壁がないのに、明らかに距離が近い場合)
		if		(map[x][y].east == false && robot.distanceEast() < Map::CELL_SIZE)
			entityDirection[east] = true;

		else if (map[x][y].west == false && robot.distanceWest() < Map::CELL_SIZE)
			entityDirection[west] = true;

		else if (map[x][y].north == false && robot.distanceNorth() < Map::CELL_SIZE)
			entityDirection[north] = true;

		else if (map[x][y].south == false && robot.distanceSouth() < Map::CELL_SIZE)
			entityDirection[south] = true;


		//それぞれの方向の、壁までのまだ得点していないマスの数を取得
		for (int xi = x; xi < Map::MAP_SIZE - 1; xi++) {
			if (!map[xi][y].east){
				if (!passedMap[xi + 1][y]) numUnPassedCell[east]++;
			}
			else break;
		}

		for (int xi = x; xi > 0; xi--) {
			if (!map[xi][y].west) {
				if (!passedMap[xi - 1][y]) numUnPassedCell[west]++;
			}
			else break;
		}

		for (int yi = y; yi < Map::MAP_SIZE - 1; yi++) {
			if (!map[x][yi].north) {
				if (!passedMap[x][yi + 1]) numUnPassedCell[north]++;
			}
			else break;
		}

		for (int yi = y; yi > 0; yi--) {
			if (!map[x][yi].south) {
				if (!passedMap[x][yi - 1]) numUnPassedCell[south]++;
			}
			else break;
		}

		//for (auto d : numUnPassedCell)
		//	cout << d << ", ";
		//cout << endl;

		// すでに通ったマスが一番少ない(得点を取れる)方向 を取得
		auto maxUnPassedDirection = distance( numUnPassedCell.begin(), 
			max_element(numUnPassedCell.begin(), numUnPassedCell.end()) );

		bool existMaxUnPassedCell = true;
	
		if (numUnPassedCell[east] == 0 && numUnPassedCell[west] == 0 &&
			numUnPassedCell[south] == 0 && numUnPassedCell[north] == 0) 
				existMaxUnPassedCell = false;



		/*方向の優先順位について

			基本方針 : 敵から逃げつつ、できるだけ多くのマスを通過する

			0. 敵のいる方向には行かない
			1. まだ通っていないボーナスがあるマスへ行く
			2. まだ通っていないマスへ行く
			3. まっすぐ(一番壁までの距離が長い方向へ)進む
		*/

		for (auto d = 0; d < 4; d++) {
			//敵がいない方向で
			if (!entityDirection[d]) {
				//ボーナスがあるなら、その方向へ
				if (bounusDirection[d]) {
					if (d == east) {
						robot.moveEast(Map::CELL_SIZE + 15.0);
						robot.correctX(-15);
					}
					if (d == west){
						robot.moveWest(Map::CELL_SIZE + 15.0);
						robot.correctX(+15);
					}
					if (d == north) {
						robot.moveNorth(Map::CELL_SIZE + 15.0);
						robot.correctY(-15);
					}
					if (d == south) {
						robot.moveSouth(Map::CELL_SIZE + 15.0);
						robot.correctY(+15);
					}

					passedMap[x][y] = true;
					

					break;

				} else {
					//その方向が壁ではなく、かつ、ボーナスがないなら、まだ通ってないマスが多い方向へ
					if (existMaxUnPassedCell) {
						if (numBlankCell[east] > 0 && maxUnPassedDirection == east) robot.moveEast(Map::CELL_SIZE);
						else if (numBlankCell[west] > 0 && maxUnPassedDirection == west) robot.moveWest(Map::CELL_SIZE);
						else if (numBlankCell[north] > 0 && maxUnPassedDirection == north) robot.moveNorth(Map::CELL_SIZE);
						else if (numBlankCell[south] > 0 && maxUnPassedDirection == south) robot.moveSouth(Map::CELL_SIZE);
					}
					//まだ通っていないマスがなければ、一番 壁までが長い方向へ
					else if (maxBlankDirection == east) robot.moveEast(Map::CELL_SIZE);
					else if (maxBlankDirection == west) robot.moveWest(Map::CELL_SIZE);
					else if (maxBlankDirection == north) robot.moveNorth(Map::CELL_SIZE);
					else if (maxBlankDirection == south) robot.moveSouth(Map::CELL_SIZE);

					passedMap[x][y] = true;
					break;
				}

			}
			else {  // 敵がいたら
				if (d == east && !map[x][y].west) robot.moveWest(Map::CELL_SIZE);
				if (d == west && !map[x][y].east) robot.moveEast(Map::CELL_SIZE );
				if (d == north && !map[x][y].south) robot.moveSouth(Map::CELL_SIZE);
				if (d == south && !map[x][y].north) robot.moveNorth(Map::CELL_SIZE);
			}
		}

		if(chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now() - startTime).count() > 180)
			break;

	} //while終わり
	
	// 180秒後、停止
	robot.setDutyRate(0.0);
}