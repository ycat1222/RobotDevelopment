#pragma once
#include <chrono>
#include <iostream>
#include "BeagleBone_Black.hpp"

using namespace BBB;

class RobotController{
public:
	RobotController() {};
	void setMotorPWM(int motor1_PWM, int motor2_PWM);
	void setMotorGPIO(int motor1_IN1, int motor1_IN2, int motor2_IN1, int motor2_IN2);
	void setSensorGPIO(int east, int west, int south, int north);
	void initializePosition(size_t __x, size_t __y);

	void mSecWait(const size_t mSec);

	bool checkRobotProperties();
	void moveEast(const size_t mSec);
	void moveWest(const size_t mSec);
	void moveSouth(const size_t mSec);
	void moveNorth(const size_t mSec);

	void setDutyRate(double bothMotorRate);
	void setDutyRate(double motor1Rate, double motor2Rate);

	//座標系の単位は[cm]
	size_t x();
	size_t y();

private:
	Motor motor1, motor2;
	GPIO sensorEast, sensorWest, sensotSouth, sensorNorth;

	bool isSetMotorPWM = false,
		isSetMotorGPIO = false,
		isSetSensorGPIO = false,
		isInitializePosition = false;

	double dutyRate_Motor1ToMotor2 = 1.0;

	size_t eastTime = 0, westTime = 0, southTime = 0, northTime = 0;
	size_t _x, _y;
};