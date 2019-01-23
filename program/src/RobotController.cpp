#include "RobotController.hpp"


void RobotController::setMotorPWM(int motor1_PWM, int motor2_PWM)
{
	motor1.setPWM(motor1_PWM);
	motor2.setPWM(motor2_PWM);
	isSetMotorPWM = true;
}

void RobotController::setMotorGPIO(int motor1_IN1, int motor1_IN2, int motor2_IN1, int motor2_IN2)
{
	motor1.setGPIO(motor1_IN1, motor1_IN2);
	motor2.setGPIO(motor2_IN1, motor2_IN2);
	isSetMotorGPIO = true;
}

void RobotController::setSensorGPIO(int east, int west, int south, int north)
{
	sensorEast.setGPIO(east);
	sensorWest.setGPIO(west);
	sensotSouth.setGPIO(south);
	sensorNorth.setGPIO(north);
	isSetSensorGPIO = true;
}

void RobotController::mSecWait(const size_t time)
{
	auto start = std::chrono::high_resolution_clock::now();
	while (true)
	{
		auto nowTime = std::chrono::high_resolution_clock::now();
		auto dTime = nowTime - start;
		auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(dTime).count();
		if (msec > time) return;
	}
}

bool RobotController::checkRobotProperties()
{
	if (isSetMotorGPIO && isSetMotorPWM && isSetSensorGPIO)
		return true;
	else
		return false;
}

void RobotController::moveEast(const size_t mSec)
{
	if (!checkRobotProperties())
		BBB::ErrorBBB("Properties is not set.");

	motor1.runReverse();
	motor2.runNormal();

	mSecWait(mSec);

	motor1.stop();
	motor2.stop();
}

void RobotController::moveWest(const size_t mSec)
{
	if (!checkRobotProperties())
		BBB::ErrorBBB("Properties is not set.");

	motor1.runNormal();
	motor2.runReverse();

	mSecWait(mSec);

	motor1.stop();
	motor2.stop();
}

void RobotController::moveSouth(const size_t mSec)
{
	if (!checkRobotProperties())
		BBB::ErrorBBB("Properties is not set.");

	motor1.runReverse();
	motor2.runReverse();

	mSecWait(mSec);

	motor1.stop();
	motor2.stop();
}

void RobotController::moveNorth(const size_t mSec)
{
	if (!checkRobotProperties())
		BBB::ErrorBBB("Properties is not set.");

	motor1.runNormal();
	motor2.runNormal();

	mSecWait(mSec);

	motor1.stop();
	motor2.stop();
}

void RobotController::setDutyRate(double bothMotorRate)
{
	if (!checkRobotProperties())
		BBB::ErrorBBB("Properties is not set.");

	motor1.setDutyRate(bothMotorRate);
	motor2.setDutyRate(bothMotorRate);
}

void RobotController::setDutyRate(double motor1Rate, double motor2Rate)
{
	if (!checkRobotProperties())
		BBB::ErrorBBB("Properties is not set.");

	motor1.setDutyRate(motor1Rate);
	motor2.setDutyRate(motor2Rate);
}

