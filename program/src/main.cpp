#include "BeagleBone_Black.hpp"
#include <iostream>
#include <exception>
#include <chrono>

namespace BBB{
	void run(void);
};


void BBB::run(void)
{
	auto pwm1 = BBB::PWM(14, 15);
	auto in1 = BBB::GPIO(61), in2 = BBB::GPIO(60);

	in1.setDirection(false);
	in2.setDirection(false);

	in1.setValue(true);
	in2.setValue(false);

	pwm1.setPeriod(10000000);
	pwm1.setDuty(pwm1.getDuty() * 0.5);

	pwm1.run();

	const int RUNTIME = 10000;

	auto start = std::chrono::system_clock::now();
	while(true)
	{
		auto nowTime =  std::chrono::system_clock::now();
		auto dTime = nowTime - start;
		auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(dTime).count();
		if(msec > RUNTIME) break;
	}

	pwm1.stop();
}


int main(void)
{
    try {
		BBB::run();
	}
	catch(std::exception& e){
		std::cout << e.what() << std::endl;
	}
	catch(...){ }

    return 0;
}