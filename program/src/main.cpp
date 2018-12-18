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
	//auto pwm1 = BBB::PWM(22, 16);
	//auto in1 = BBB::GPIO(65), in2 = BBB::GPIO(46);

	//in1.setDirection(false);
	//in2.setDirection(false);

	//in1.setValue(true);
	//in2.setValue(false);

	////pwm1.setPeriod(10000000);
	//pwm1.setDutyRate(0.5);

	//pwm1.run();

	//const int RUNTIME = 5000;

	//msecWait(RUNTIME);

	//pwm1.stop();

	//auto pwm1 = BBB::PWM(14, 15);
	//auto in1 = BBB::GPIO(61), in2 = BBB::GPIO(60);

	//in1.setDirection(false);
	//in2.setDirection(false);

	//in1.setValue(true);
	//in2.setValue(false);

	////pwm1.setPeriod(10000000);
	//pwm1.setDutyRate(0.5);

	//pwm1.run();

	//const int RUNTIME = 5000;

	//msecWait(RUNTIME);

	//pwm1.stop();


	auto motor1 = BBB::Motor(14, 61, 60);
	auto motor2 = BBB::Motor(22, 65, 46);
	motor1.setDutyRate(0.5);
	motor1.runNormal();
	motor2.setDutyRate(0.5);
	motor2.runNormal();

	msecWait(5000);

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