#pragma once
#include "BBB_gpio.hpp"

class UltraSonicSensor : public BBB::GPIO {
public:
	//距離[mm]を返す
	double distance()
	{
		// 2*距離d÷時間t = 音速V → d = 0.5*V*t = 0.6874[mm/μs]*t[μs]
		return this->value()*0.6874;
	}
};