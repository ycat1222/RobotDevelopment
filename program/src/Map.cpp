#include "Map.hpp"

using namespace std;

//ファイルからマップを読み込む
BBB::Map::Map(std::string mapFilePath)
{
	ifstream mapFile(mapFilePath);

	if (!mapFile) throw BBB::ErrorBBB("Cannot open map file.");

	map = vector<vector<Cell>>(MAP_SIZE, vector<Cell>(MAP_SIZE));
	
	for (size_t i = 0; i < MAP_SIZE; i++) 
	{
		for(size_t j = 0; j < MAP_SIZE; j++)
		{
			unsigned int x, y;
			mapFile >> x >> y;

			if (x < MAP_SIZE && y < MAP_SIZE)
			{
				Cell& cell = map[x][y];

				int east, west, south, north;
				mapFile >> east >> west >> south >> north;

				cell.east = east;
				cell.west = west;
				cell.south = south;
				cell.north = north;

				std::string isBonus;
				mapFile >> isBonus;

				if (isBonus == "bonus") map[x][y].isBonus = true;
				else cell.isBonus = false;
			}
			else throw BBB::ErrorBBB("Map size is too large.");
		}
		
		
	}
}
