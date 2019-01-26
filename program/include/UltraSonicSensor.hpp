#pragma once
#include "BBB_gpio.hpp"
#include <chrono>
#include <fstream>
//#include <fcntl.h>
//#include <unistd.h>
//#include <poll.h>

namespace BBB{

class UltraSonicSensor : public BBB::GPIO {
public:

	UltraSonicSensor() {}
	UltraSonicSensor(int gpioNum_);

	//距離[mm]を返す
	double distance();
};

};