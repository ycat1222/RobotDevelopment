#include<Motor.hpp>
using namespace BBB;

// PWM固有の値(静的変数)の初期化
int BBB::Motor::pwmUniqueNum = 15;


BBB::Motor::Motor(int pwmPinNum, int gpioNumIN1, int gpioNumIN2)
{
	pwm = PWM(pwmPinNum, pwmUniqueNum);
	IN1 = GPIO(gpioNumIN1);
	IN2 = GPIO(gpioNumIN2);

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
	IN1.setValue(1);
	IN2.setValue(0);
}

void BBB::Motor::runReverse()
{
	IN1.setValue(0);
	IN2.setValue(1);
}

void BBB::Motor::brake()
{
	IN1.setValue(1);
	IN2.setValue(1);
}

void BBB::Motor::stop()
{
	IN1.setValue(0);
	IN2.setValue(0);
}
