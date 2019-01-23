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

	void mSecWait(const size_t mSec);

	bool checkRobotProperties();
	void moveEast(const size_t mSec);
	void moveWest(const size_t mSec);
	void moveSouth(const size_t mSec);
	void moveNorth(const size_t mSec);

	void setDutyRate(double bothMotorRate);
	void setDutyRate(double motor1Rate, double motor2Rate);
	
private:
	Motor motor1, motor2;
	GPIO sensorEast, sensorWest, sensotSouth, sensorNorth;

	bool isSetMotorPWM = false, isSetMotorGPIO = false, isSetSensorGPIO = false;
	double dutyRate_Motor1ToMotor2 = 1.0;
};