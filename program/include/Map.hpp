#pragma once
#include "BBB_error.hpp"
#include <vector>
#include <fstream>
#include <string>

//一つ一つのマスとマップについてのクラス
namespace BBB
{

//マップのそれぞれのマスのクラス
class Cell
{
  public:
	bool east, west, south, north;
	bool isBonus;
};

class Map
{
  public:
	Map(std::string path);

	std::vector<Cell> operator[](const size_t _x) 
	{ 
		if(_x < MAP_SIZE) return map[_x];
		else throw BBB::ErrorBBB("Map's index is to large.");
	}

  protected:
	std::vector<std::vector<Cell>> map;
	const unsigned int MAP_SIZE = 6;
};

}; // namespace BBB
