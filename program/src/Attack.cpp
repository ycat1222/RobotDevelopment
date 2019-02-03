#include "Attack.hpp"

void BBB::attack()
{
	RobotController robot;
	robot.initPosition(15, 15);
	robot.initMotorGPIO(61, 60, 65, 46);
	robot.initMotorPWM(14, 22);
	robot.initSensorGPIO(27, 47, 115, 45);

	Map map("field.txt");

	//通過済みのマスの情報が入った配列(初期ではfalse)
	std::vector<std::vector<bool>> passedMap(Map::MAP_SIZE, std::vector<bool>(Map::MAP_SIZE, false));

	passedMap[0][0] = true;

	enum Direction
	{
		east = 0,
		west = 1,
		south = 2,
		north = 3,
	};

	while (true) {

		unsigned int x = robot.x() / Map::CELL_SIZE;
		unsigned int y = robot.y() / Map::CELL_SIZE;

		//それぞれの方向の壁がないマスの数
		std::array<int, 4> numBlankCell;
		for (auto xi = x + 1; xi < Map::MAP_SIZE; xi++)
			if (map[xi][y].east == 0) numBlankCell[east]++;

		for (auto xi = x - 1; xi > 0; xi--)
			if (map[xi][y].east == 0) numBlankCell[west]++;

		for (auto yi = y + 1; yi < Map::MAP_SIZE; yi++)
			if (map[x][yi].north == 0) numBlankCell[north]++;

		for (auto yi = y - 1; yi > 0; yi--)
			if (map[x][yi].south == 0) numBlankCell[south]++;

		//壁がない=まっすぐ進めるマスが一番多い方向を取得
		auto maxItr = std::max_element(numBlankCell.begin(), numBlankCell.end());
		auto maxBlankDirection = std::distance(numBlankCell.begin(), maxItr);

		//壁に阻まれず、かつ、ボーナスマスがあるときの方向を取得
		std::array<bool, 4> bounusDirection = { false, false, false, false };

		if (map[x][y].east == false && map[x + 1][y].isBonus)
			bounusDirection[east] = true;

		if (map[x][y].west == false && map[x - 1][y].isBonus)
			bounusDirection[west] = true;

		if (map[x][y].north == false && map[x][y + 1].isBonus)
			bounusDirection[north] = true;

		if (map[x][y].south == false && map[x][y - 1].isBonus)
			bounusDirection[south] = true;

		// 敵がいる方向の判定
		std::array<bool, 4> entityDirection = { false, false, false, false };

		if (std::abs(numBlankCell[east] * Map::CELL_SIZE - robot.distanceEast()) > Map::CELL_SIZE + 10.0)
			entityDirection[east] = true;

		else if (std::abs(numBlankCell[west] * Map::CELL_SIZE - robot.distanceWest()) > Map::CELL_SIZE + 10.0)
			entityDirection[west] = true;

		else if (std::abs(numBlankCell[south] * Map::CELL_SIZE - robot.distanceSouth()) > Map::CELL_SIZE + 10.0)
			entityDirection[south] = true;

		else if (std::abs(numBlankCell[north] * Map::CELL_SIZE - robot.distanceNorth()) > Map::CELL_SIZE + 10.0)
			entityDirection[north] = true;


		//それぞれの方向の得点したマスの数(壁までの)
		std::array<int, 4> numPassedCell;
		for (auto xi = x + 1; xi < x + numBlankCell[east]; xi++)
			if (passedMap[xi][y]) numPassedCell[east]++;

		for (auto xi = x - 1; xi > 0; xi--)
			if (passedMap[xi][y]) numPassedCell[west]++;

		for (auto yi = y + 1; yi < y + numBlankCell[north]; yi++)
			if (passedMap[x][yi]) numPassedCell[north]++;

		for (auto yi = y - 1; yi > 0; yi--)
			if (passedMap[x][yi]) numPassedCell[south]++;

		// すでに通ったマスが一番少ない(得点を取れる)方向 を取得
		auto minItr = std::min_element(numPassedCell.begin(), numPassedCell.end());
		auto minPassedDirection = std::distance(numPassedCell.begin(), minItr);


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
					if (d == east) robot.moveEast(Map::CELL_SIZE);
					if (d == west) robot.moveWest(Map::CELL_SIZE);
					if (d == north) robot.moveNorth(Map::CELL_SIZE);
					if (d == south) robot.moveSouth(Map::CELL_SIZE);
					continue;
				}
				//ボーナスがないなら、まだ通ってないマスへ
				else {
					if		(minPassedDirection == east) robot.moveEast(Map::CELL_SIZE);
					else if (minPassedDirection == west) robot.moveWest(Map::CELL_SIZE);
					else if (minPassedDirection == north) robot.moveNorth(Map::CELL_SIZE);
					else if (minPassedDirection == south) robot.moveSouth(Map::CELL_SIZE);
					else {
						//まだ通っていないマスがなければ、一番 壁までが長いとこへすすむ
						if		(maxBlankDirection == east) robot.moveEast(Map::CELL_SIZE);
						else if (maxBlankDirection == west) robot.moveWest(Map::CELL_SIZE);
						else if (maxBlankDirection == north) robot.moveNorth(Map::CELL_SIZE);
						else if (maxBlankDirection == south) robot.moveSouth(Map::CELL_SIZE);
					}
					continue;
					
				}
			}
		}

	} //while終わり
	


	
}
