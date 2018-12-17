#include<Motor.hpp>
using namespace BBB;

// PWM固有の値(静的変数)の初期化
int BBB::Motor::pwmUniqueNum = 15;


BBB::Motor::Motor(int pwmPinNum, int gpioNumIN1, int gpioNumIN2)
{
	pwm = PWM(pwmPinNum, pwmUniqueNum);
	IN1 = GPIO(gpioNumIN1);
	IN1.activate();
	IN2 = GPIO(gpioNumIN2);
	IN2.activate();

	IN1.setDirection(false);
	IN2.setDirection(false);

	//たぶん有効化するごとに、1ずつ増えてく?
	pwmUniqueNum++;
}

void Motor::setPWM(int pwmPinNum)
{
	pwm = PWM(pwmPinNum, pwmUniqueNum);
}

void Motor::setGPIO(int gpioNumIN1, int gpioNumIN2)
{
	IN1 = GPIO(gpioNumIN1);
	IN2 = GPIO(gpioNumIN2);

	IN1.setDirection(false);
	IN2.setDirection(false);
}

void BBB::Motor::setDutyRate(double rate)
{
	pwm.setDutyRate(rate);
}

double BBB::Motor::dutyRate()
{
	return pwm.dutyRate();
}

int BBB::Motor::duty()
{
	return pwm.duty();
}

void BBB::Motor::runNormal()
{
	pwm.stop();
	IN1.setValue(true);
	IN2.setValue(false);
	pwm.run();
}

void BBB::Motor::runReverse()
{
	pwm.stop();
	IN1.setValue(false);
	IN2.setValue(true);
	pwm.run();
}

void BBB::Motor::brake()
{
	IN1.setValue(true);
	IN2.setValue(true);
}

void BBB::Motor::stop()
{
	IN1.setValue(false);
	IN2.setValue(false);

	pwm.stop();
}

BBB::Motor::~Motor()
{
	IN1.disActivate();
	IN2.disActivate();
}
