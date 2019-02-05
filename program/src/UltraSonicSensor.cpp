#include "UltraSonicSensor.hpp"
using namespace BBB;


BBB::UltraSonicSensor::UltraSonicSensor(int gpioNum_) : BBB::GPIO(gpioNum_)
{
	this->setDirection(IN);
	this->setEdge(true);
}

//距離[mm]を返す
double BBB::UltraSonicSensor::distance()
{
	using namespace std;

	if (!isGPIOSetted) throw BBB::ErrorBBB("GPIO num has NOT been setted.");

	stringstream path;
	path << "/sys/class/gpio/gpio" << gpioNum << "/value";
	ifstream valueFile(path.str());

	char c;

	//たち下がるまで待つ
	valueFile >> c;
	while (c == '1') { 
		//ファイルの先頭に戻る
		valueFile.seekg(0);
		valueFile >> c;
	};

	//立ち上がり(whileを抜ける瞬間、c == 1)を待つ
	valueFile.seekg(0);
	valueFile >> c;
	while (c == '0') { 
		valueFile.seekg(0);
		valueFile >> c;
	};
	auto edgeUpTime = chrono::high_resolution_clock::now();

	//立ち下がり(whileを抜ける瞬間、c == 0)を待つ
	valueFile.seekg(0);
	valueFile >> c;
	while (c == '1') {
		valueFile.seekg(0);
		valueFile >> c;
	}

	//立ち下がり - 立ち上がり の時間計算
	auto dtime = chrono::high_resolution_clock::now() - edgeUpTime;
	// 2*距離d÷時間t = 音速V → d[cm] = 0.5*V*t = 0.01718[cm/μs]*t[μs]
	return 0.01717975*chrono::duration_cast<chrono::microseconds>(dtime).count();
}
