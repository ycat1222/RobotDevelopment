#pragma once
#include<BBB_gpio.hpp>
#include<BBB_pwm.hpp>
#include<new>

namespace BBB{
class Motor{
public:
	explicit Motor() {};
	explicit Motor(int pwmPinNum, int gpioNumIN1, int gpioNumIN2);

    void setPWM(int pwmPinNum);
    void setGPIO(int gpioNumIN1, int gpioNumIN2);

	void setDutyRate(double rate);
	double dutyRate();
	int duty();

	// IN1 = 1, IN2 = 0 に設定
    void runNormal();
	// IN1 = 0, IN2 = 1 に設定
    void runReverse();
	// IN1 = IN2 = 1 に設定
	void brake();
	// IN1 = IN2 = 0 に設定
	void stop();

	~Motor();
    
private:
    PWM pwm;
    GPIO IN1, IN2;

	static int pwmUniqueNum;
};
};