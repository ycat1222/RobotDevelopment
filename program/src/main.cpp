#include "BeagleBone_Black.hpp"
#include <iostream>
#include <exception>
#include <chrono>

namespace BBB{
	void run(void);
	void msecWait(const unsigned int &time);
};

void BBB::run(void)
{
	msecWait(30000);//setting time

	auto motor1 = BBB::Motor(14, 61, 60);
	auto motor2 = BBB::Motor(22, 65, 46);

	motor1.setDutyRate(0.5);
	motor2.setDutyRate(0.5);

	motor1.runNormal();
	motor2.runNormal();

	msecWait(5000);

	motor1.runReverse();
	motor2.runReverse();

	msecWait(5000);

	motor2.stop();
	motor1.stop();
}

void BBB::msecWait(const unsigned int &time)
{
	auto start = std::chrono::system_clock::now();
	while (true)
	{
		auto nowTime = std::chrono::system_clock::now();
		auto dTime = nowTime - start;
		auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(dTime).count();
		if (msec > time) return;
	}
}

int main(void)
{
    try {
		BBB::run();
	}
	catch(BBB::ErrorBBB& e){
		std::cout << e.what() << std::endl;
	}
	catch(...){ }

    return 0;
}