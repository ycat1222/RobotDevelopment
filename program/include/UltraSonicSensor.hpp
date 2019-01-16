#pragma once
#include "BBB_gpio.hpp"
#include <chrono>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>
#include <poll.h>

class UltraSonicSensor : public BBB::GPIO {
public:

	UltraSonicSensor() {}
	UltraSonicSensor(int gpioNum_) : BBB::GPIO(gpioNum_)
	{
		this->setDirection(true);
		this->setEdge(true);
	}

	//距離[mm]を返す
	double distance()
	{
		if (!isGPIOSetted) throw BBB::ErrorBBB("GPIO num has NOT been set.");

		std::stringstream path;
		path << "/sys/class/gpio/gpio" << gpioNum << "/value";

		auto valueFd = open(path.str().c_str(), O_RDONLY);

		pollfd pfd;
		pfd.fd = valueFd;
		pfd.events = POLLPRI;

		auto edgeUpTime = std::chrono::high_resolution_clock::now();

		while (true)
		{
			char c;
			
			lseek(valueFd, 0, SEEK_SET);
			auto ret = poll(&pfd, 1, -1);
			read(valueFd, &c, 1);
			//パルスの立ち上がり時刻を取得
			if(c == '1') edgeUpTime = std::chrono::high_resolution_clock::now();
			else continue;

			lseek(valueFd, 0, SEEK_SET);
			ret = poll(&pfd, 1, -1);
			read(valueFd, &c, 1);
			//パルスの立ち下がり時刻を所得
			if(c == '0'){
				//立ち下がり - 立ち上がり の時間計算
				auto dtime = std::chrono::high_resolution_clock::now() - edgeUpTime;
				// 2*距離d÷時間t = 音速V → d = 0.5*V*t = 0.1718[mm/μs]*t[μs]
				return 0.1717975*std::chrono::duration_cast<std::chrono::microseconds>(dtime).count();
			}
			else continue;
		}
		

	}
};