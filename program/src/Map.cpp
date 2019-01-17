#include "Map.hpp"

using namespace std;

//ファイルからマップを読み込む
BBB::Map::Map(std::string mapFilePath)
{
	ifstream mapFile(mapFilePath);

	if (!mapFile) throw BBB::ErrorBBB("Cannot open map file.");

	map = vector<vector<Cell>>(MAP_SIZE, vector<Cell>(MAP_SIZE));
	
	while (!mapFile.eof()) 
	{
		unsigned int x, y;
		mapFile >> x >> y;

		if(x < MAP_SIZE && y < MAP_SIZE)
		{
			int east, west, south, north;
			mapFile >> east >> west >> south >> north;

			map[x][y].east = east;
			map[x][y].west = west;
			map[x][y].south = south;
			map[x][y].north = north;

			int isBonus;
			mapFile >> isBonus;

			if (isBonus == true) map[x][y].isBonus = true;
			else map[x][y].isBonus = false;
		}
		else throw BBB::ErrorBBB("Map size is too large.");
		
	}
}
